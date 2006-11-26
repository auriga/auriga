#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "party.h"
#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "pc.h"
#include "map.h"
#include "battle.h"
#include "intif.h"
#include "clif.h"
#include "status.h"
#include "skill.h"
#include "unit.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

#define PARTY_SEND_XYHP_INVERVAL	1000	// 座標やＨＰ送信の間隔

static struct dbt* party_db = NULL;

// 検索
struct party *party_search(int party_id)
{
	return numdb_search(party_db,party_id);
}

static int party_searchname_sub(void *key, void *data, va_list ap)
{
	struct party *p=(struct party *)data,**dst;
	char *str;

	str=va_arg(ap,char *);
	dst=va_arg(ap,struct party **);
	if(strcmpi(p->name,str)==0)
		*dst=p;

	return 0;
}

// パーティ名検索
struct party* party_searchname(char *str)
{
	struct party *p=NULL;

	numdb_foreach(party_db,party_searchname_sub,str,&p);

	return p;
}

// 作成要求
void party_create(struct map_session_data *sd, char *name)
{
	int i;
	char party_name[24]; // 23 + NULL

	nullpo_retv(sd);

	if (sd->status.party_id == 0) {
		strncpy(party_name, name, 23);
		// force '/0' at end (against hacker: normal player can not create a party with a name longer than 23 characters)
		party_name[23] = '\0';

		// if too short name (hacker)
		if (party_name[0] == '\0') {
			clif_party_created(sd, 1); // 0xfa <flag>.B: 0: Party has successfully been organized, 1: That Party Name already exists., 2: The Character is already in a party.
			return;
		}

		// check control chars and del (is checked in char-server, check before to send to char-server to avoid packet transmission)
		for(i = 0; party_name[i]; i++) {
			if (!(party_name[i] & 0xe0) || party_name[i] == 0x7f) {
				clif_party_created(sd, 1); // 0xfa <flag>.B: 0: Party has successfully been organized, 1: That Party Name already exists., 2: The Character is already in a party.
				return;
			}
		}

		// ask char-server for creation
		intif_create_party(sd, party_name);
	} else
		clif_party_created(sd,2); // 0xfa <flag>.B: 0: Party has successfully been organized, 1: That Party Name already exists., 2: The Character is already in a party.

	return;
}

// 作成可否
void party_created(int account_id, unsigned char fail, int party_id, char *name)
{
	struct map_session_data *sd;

	nullpo_retv(sd = map_id2sd(account_id));

	if(fail==0){
		struct party *p;
		if (numdb_search(party_db,party_id) != NULL) {
			printf("party: id already exists!\n");
			exit(1);
		}
		sd->status.party_id=party_id;
		p=(struct party *)aCalloc(1,sizeof(struct party));
		p->party_id=party_id;
		memcpy(p->name,name,24);
		numdb_insert(party_db,party_id,p);
		clif_party_created(sd,0);
	}else{
		clif_party_created(sd,1);
	}

	return;
}

// 情報要求
void party_request_info(int party_id)
{
	intif_request_partyinfo(party_id);

	return;
}

// 所属キャラの確認
static void party_check_member(struct party *p)
{
	int i;
	struct map_session_data *sd;

	nullpo_retv(p);

	for(i=0;i<fd_max;i++){
		if(session[i] && (sd=session[i]->session_data) && sd->state.auth){
			if(sd->status.party_id==p->party_id){
				int j,f=1;
				for(j=0;j<MAX_PARTY;j++){	// パーティにデータがあるか確認
					if(	p->member[j].account_id==sd->status.account_id){
						if(	strcmp(p->member[j].name,sd->status.name)==0 )
							f=0;	// データがある
						else
							p->member[j].sd=NULL;	// 同垢別キャラだった
					}
				}
				if(f){
					sd->status.party_id=0;
					if(battle_config.error_log)
						printf("party: check_member %d[%s] is not member\n",sd->status.account_id,sd->status.name);
				}
			}
		}
	}

	return;
}

// 情報所得失敗（そのIDのキャラを全部未所属にする）
void party_recv_noinfo(int party_id)
{
	int i;
	struct map_session_data *sd;

	for(i=0;i<fd_max;i++){
		if(session[i] && (sd=session[i]->session_data) && sd->state.auth){
			if(sd->status.party_id==party_id)
				sd->status.party_id=0;
		}
	}

	return;
}

// 情報所得
void party_recv_info(struct party *sp)
{
	struct map_session_data *sd;
	struct party *p;
	int i;

	nullpo_retv(sp);

	if((p=numdb_search(party_db,sp->party_id))==NULL){
		p=(struct party *)aCalloc(1,sizeof(struct party));
		numdb_insert(party_db,sp->party_id,p);

		// 最初のロードなのでユーザーのチェックを行う
		party_check_member(sp);
	}
	memcpy(p,sp,sizeof(struct party));

	for(i=0;i<MAX_PARTY;i++){	// sdの設定
		sd = map_id2sd(p->member[i].account_id);
		p->member[i].sd=(sd!=NULL && sd->status.party_id==p->party_id && !sd->state.waitingdisconnect)?sd:NULL;
	}

	clif_party_info(p,-1);

	for(i=0;i<MAX_PARTY;i++){	// 設定情報の送信
		sd = p->member[i].sd;
		if(sd!=NULL && sd->party_sended==0){
			clif_party_option(p,sd,0x100);
			sd->party_sended=1;
		}
	}

	return;
}

// パーティへの勧誘
void party_invite(struct map_session_data *sd, int account_id)
{
	struct map_session_data *tsd;
	struct party *p;
	int i;

	nullpo_retv(sd);

	p = party_search(sd->status.party_id);
	if (p == NULL)
		return;

	tsd = map_id2sd(account_id);
	if (tsd == NULL)
		return;

	if(!battle_config.invite_request_check) {
		if (tsd->guild_invite>0 || tsd->trade_partner || tsd->adopt_invite) {	// 相手が取引中かどうか
			clif_party_inviteack(sd,tsd->status.name,0);
			return;
		}
	}
	if( tsd->status.party_id>0 || tsd->party_invite>0 ){	// 相手の所属確認
		clif_party_inviteack(sd,tsd->status.name,0);
		return;
	}
	for(i=0;i<MAX_PARTY;i++){	// 同アカウント確認
		if (p->member[i].account_id == account_id) {
			if (battle_config.party_join_limit || strncmp(p->member[i].name, tsd->status.name, 24) == 0){
				clif_party_inviteack(sd,tsd->status.name,0);
				return;
			}
		}
	}

	tsd->party_invite=sd->status.party_id;
	tsd->party_invite_account=sd->status.account_id;

	clif_party_invite(sd,tsd);

	return;
}

// パーティ勧誘への返答
void party_reply_invite(struct map_session_data *sd, int account_id, int flag)
{
	struct map_session_data *tsd;

	nullpo_retv(sd);

	if(flag==1){	// 承諾
		//inter鯖へ追加要求
		intif_party_addmember(sd);
	}
	else {		// 拒否
		sd->party_invite=0;
		sd->party_invite_account=0;
		tsd = map_id2sd(account_id);
		if(tsd==NULL)
			return;
		clif_party_inviteack(tsd,sd->status.name,1);
	}

	return;
}

// パーティ競合確認
static void party_check_conflict(struct map_session_data *sd)
{
	nullpo_retv(sd);

	intif_party_checkconflict(sd->status.party_id,sd->status.account_id,sd->status.name);

	return;
}

// パーティが追加された
void party_member_added(int party_id, int account_id, unsigned char flag, const char* name)
{
	struct map_session_data *sd= map_id2sd(account_id),*sd2;

	if(sd==NULL && flag==0){
		if(battle_config.error_log)
			printf("party: member added error %d is not online\n",account_id);
		intif_party_leave(party_id, account_id, name); // キャラ側に登録できなかったため脱退要求を出す
		return;
	}
	sd2=map_id2sd(sd->party_invite_account);
	sd->party_invite=0;
	sd->party_invite_account=0;

	if(flag==1){	// 失敗
		if( sd2!=NULL )
			clif_party_inviteack(sd2,sd->status.name,0);
		return;
	}

		// 成功
	sd->party_sended=0;
	sd->status.party_id=party_id;

	if( sd2!=NULL)
		clif_party_inviteack(sd2,sd->status.name,2);

	// いちおう競合確認
	party_check_conflict(sd);

	return;
}

// パーティ除名要求
void party_removemember(struct map_session_data *sd, int account_id, char *name)
{
	struct party *p;
	int i;

	nullpo_retv(sd);

	if( (p = party_search(sd->status.party_id)) == NULL )
		return;

	for(i=0;i<MAX_PARTY;i++){	// リーダーかどうかチェック
		if (p->member[i].account_id == sd->status.account_id &&
		    strncmp(p->member[i].name, sd->status.name, 24) == 0)
			if(p->member[i].leader==0)
				return;
	}

	for(i=0;i<MAX_PARTY;i++){	// 所属しているか調べる
		if (p->member[i].account_id == account_id &&
		    strncmp(p->member[i].name, name, 24) == 0){
			intif_party_leave(p->party_id, account_id, p->member[i].name);
			return;
		}
	}

	return;
}

// パーティ脱退要求
void party_leave(struct map_session_data *sd)
{
	struct party *p;
	int i;

	nullpo_retv(sd);

	if( (p = party_search(sd->status.party_id)) == NULL )
		return;

	for(i=0;i<MAX_PARTY;i++){	// 所属しているか
		if (p->member[i].account_id == sd->status.account_id &&
		    strncmp(p->member[i].name, sd->status.name, 24) == 0) {
			intif_party_leave(p->party_id, sd->status.account_id, p->member[i].name);
			return;
		}
	}

	return;
}

// パーティメンバが脱退した
void party_member_leaved(int party_id, int account_id, char *name)
{
	struct map_session_data *sd=map_id2sd(account_id);
	struct party *p=party_search(party_id);

	if(p!=NULL){
		int i;
		for(i=0;i<MAX_PARTY;i++)
			if (p->member[i].account_id == account_id &&
			    strncmp(p->member[i].name, name, 24) == 0) {
				clif_party_leaved(p,sd,account_id,name,0x00);
				p->member[i].account_id=0;
				p->member[i].sd=NULL;
			}
	}
	if(sd!=NULL && sd->status.party_id==party_id && !strcmp(sd->status.name, name) ){
		sd->status.party_id=0;
		sd->party_sended=0;
	}

	return;
}

// パーティ解散通知
void party_broken(int party_id)
{
	struct party *p;
	int i;

	if( (p=party_search(party_id))==NULL )
		return;

	for(i=0;i<MAX_PARTY;i++){
		if(p->member[i].sd!=NULL){
			clif_party_leaved(p, p->member[i].sd, p->member[i].account_id, p->member[i].name, 0x10);
			p->member[i].sd->status.party_id=0;
			p->member[i].sd->party_sended=0;
		}
	}
	aFree(p);
	numdb_erase(party_db,party_id);

	return;
}

// パーティの設定変更要求
void party_changeoption(struct map_session_data *sd, unsigned short exp, unsigned short item)
{
	struct party *p;
	int i;

	nullpo_retv(sd);

	if ((p = party_search(sd->status.party_id)) == NULL)
		return;

	// ONLY the party leader can choose either 'Each Take' or 'Even Share' for experience points.
	for(i = 0; i < MAX_PARTY; i++) {
		if (p->member[i].account_id == sd->status.account_id &&
		    strncmp(p->member[i].name, sd->status.name, 24) == 0) {
			if (p->member[i].leader) {
				intif_party_changeoption(sd->status.party_id, sd->status.account_id, exp, item);
				return;
			}
		}
	}

	return;
}

// パーティの設定変更通知
void party_optionchanged(int party_id, int account_id, int exp, int item, int flag)
{
	struct party *p;
	struct map_session_data *sd=map_id2sd(account_id);

	if( (p=party_search(party_id))==NULL)
		return;

	if(!(flag&0x01)) p->exp=exp;
	if(!(flag&0x10)) p->item=item;
	clif_party_option(p,sd,flag);

	return;
}

// 位置通知クリア
static void party_send_xy_clear(struct party *p)
{
	int i;

	nullpo_retv(p);

	for(i=0;i<MAX_PARTY;i++){
		struct map_session_data *sd;
		if((sd=p->member[i].sd)!=NULL){
			sd->party_x=-1;
			sd->party_y=-1;
			sd->party_hp=-1;
		}
	}

	return;
}

// パーティメンバの移動通知
void party_recv_movemap(int party_id, int account_id, char *map, int online, int lv, const char* name)
{
	struct map_session_data *sd;
	struct party *p;
	int i;

	if( (p=party_search(party_id))==NULL)
		return;

	for(i=0;i<MAX_PARTY;i++){
		struct party_member *m=&p->member[i];
		if( m == NULL ){
			printf("party_recv_movemap nullpo?\n");
			return;
		}
		if (m->account_id == account_id && strncmp(m->name, name, 24) == 0){
			memcpy(m->map,map,16);
			m->online=online;
			m->lv=lv;
			break;
		}
	}
	if(i==MAX_PARTY){
		if(battle_config.error_log)
			printf("party: not found member %d on %d[%s]",account_id,party_id,p->name);
		return;
	}

	for(i=0;i<MAX_PARTY;i++){	// sd再設定
		sd= map_id2sd(p->member[i].account_id);
		p->member[i].sd=(sd!=NULL && sd->status.party_id==p->party_id && !sd->state.waitingdisconnect)?sd:NULL;
	}

	party_send_xy_clear(p);	// 座標再通知要請

	clif_party_info(p,-1);

	return;
}

// パーティメンバの移動
void party_send_movemap(struct map_session_data *sd)
{
	struct party *p;

	nullpo_retv(sd);

	if( sd->status.party_id==0 )
		return;

	intif_party_changemap(sd,1);

	if( sd->party_sended!=0 )	// もうパーティデータは送信済み
		return;

	// 競合確認
	party_check_conflict(sd);

	// あるならパーティ情報送信
	if( (p=party_search(sd->status.party_id))!=NULL ){
		party_check_member(p);	// 所属を確認する
		if(sd->status.party_id==p->party_id){
			clif_party_info(p,sd->fd);
			clif_party_option(p,sd,0x100);
			sd->party_sended=1;
		}
	}

	return;
}

// パーティメンバのログアウト
void party_send_logout(struct map_session_data *sd)
{
	struct party *p;

	nullpo_retv(sd);

	if( sd->status.party_id>0 )
		intif_party_changemap(sd,0);

	// sdが無効になるのでパーティ情報から削除
	if( (p=party_search(sd->status.party_id))!=NULL ){
		int i;
		for(i=0;i<MAX_PARTY;i++)
			if(p->member[i].sd==sd)
				p->member[i].sd=NULL;
	}

	return;
}

// パーティメッセージ送信
void party_send_message(struct map_session_data *sd, char *mes, int len)
{
	if(sd->status.party_id==0)
		return;

	intif_party_message(sd->status.party_id,sd->status.account_id,mes,len);

	return;
}

// パーティメッセージ受信
void party_recv_message(int party_id, int account_id, char *mes, int len)
{
	struct party *p;

	if( (p=party_search(party_id))==NULL)
		return;
	clif_party_message(p,account_id,mes,len);

	return;
}

// 位置やＨＰ通知用
static int party_send_xyhp_timer_sub(void *key, void *data, va_list ap)
{
	struct party *p=(struct party *)data;
	int i;

	nullpo_retr(0, p);

	for(i=0;i<MAX_PARTY;i++){
		struct map_session_data *sd;
		if((sd=p->member[i].sd)!=NULL){
			// 座標通知
			if(sd->party_x!=sd->bl.x || sd->party_y!=sd->bl.y){
				clif_party_xy(sd);
				sd->party_x=sd->bl.x;
				sd->party_y=sd->bl.y;
			}
			// ＨＰ通知
			if(sd->party_hp!=sd->status.hp){
				clif_party_hp(sd);
				sd->party_hp=sd->status.hp;
			}
		}
	}

	return 0;
}

// 位置やＨＰ通知
static int party_send_xyhp_timer(int tid, unsigned int tick, int id, int data)
{
	numdb_foreach(party_db,party_send_xyhp_timer_sub,tick);

	return 0;
}

// HP通知の必要性検査用（map_foreachinmoveareaから呼ばれる）
int party_send_hp_check(struct block_list *bl,va_list ap)
{
	int party_id;
	int *flag;
	struct map_session_data *sd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd=(struct map_session_data *)bl);

	party_id=va_arg(ap,int);
	flag=va_arg(ap,int *);

	if(sd->status.party_id==party_id){
		*flag=1;
		sd->party_hp=-1;
	}

	return 0;
}

// 経験値公平分配
void party_exp_share(struct party *p, struct mob_data *md, atn_bignumber base_exp, atn_bignumber job_exp)
{
	struct map_session_data *sd;
	int i,c;
	atn_bignumber base_bonus, job_bonus;
	struct map_session_data *sdlist[MAX_PARTY];

	nullpo_retv(p);
	nullpo_retv(md);

	for(i=c=0;i<MAX_PARTY;i++)
	{
		if((sd=p->member[i].sd)!=NULL && sd->bl.m==md->bl.m && !unit_isdead(&sd->bl) && sd->bl.prev != NULL &&
			(!sd->sc_data ||
				((sd->sc_data[SC_TRICKDEAD].timer == -1 || !battle_config.noexp_trickdead ) && 	// 死んだふり していない
				 (sd->sc_data[SC_HIDING].timer == -1	|| !battle_config.noexp_hiding    ) ))	// ハイド していない
			)
			sdlist[c++] = sd;
	}
	if(c==0)
		return;

	base_bonus = 100 + (battle_config.pt_bonus_b*(c-1));
	job_bonus  = 100 + (battle_config.pt_bonus_j*(c-1));
	for(i=0;i<c;i++)
	{
		atn_bignumber bexp = base_bonus * base_exp / 100 / c + 1;
		atn_bignumber jexp = job_bonus * job_exp / 100 / c + 1;

		pc_gainexp(sdlist[i],md,
			(bexp>0x7fffffff)? 0x7fffffff: (int)bexp ,
			(jexp>0x7fffffff)? 0x7fffffff: (int)jexp  );

//		pc_gainexp(sd,md,(base_exp/c)*(1+battle_config.pt_bonus_b*0.01*(c-1))+1,(job_exp/c)*(1+battle_config.pt_bonus_j*0.01*(c-1))+1);
//		pc_gainexp(sd,md,base_exp/c+1,job_exp/c+1);//
	}

	return;
}

// 同じマップのパーティメンバー全体に処理をかける
// type==0 同じマップ
//     !=0 画面内
void party_foreachsamemap(int (*func)(struct block_list*,va_list),
	struct map_session_data *sd,int type,...)
{
	struct party *p;
	va_list ap;
	int i;
	int x0,y0,x1,y1;
	struct block_list *list[MAX_PARTY];
	int blockcount=0;

	nullpo_retv(sd);

	if((p=party_search(sd->status.party_id))==NULL)
		return;

	x0=sd->bl.x-PT_AREA_SIZE;
	y0=sd->bl.y-PT_AREA_SIZE;
	x1=sd->bl.x+PT_AREA_SIZE;
	y1=sd->bl.y+PT_AREA_SIZE;

	va_start(ap,type);

	for(i=0;i<MAX_PARTY;i++){
		struct party_member *m=&p->member[i];
		if(m!=NULL && m->sd!=NULL){
			if(sd->bl.m!=m->sd->bl.m)
				continue;
			if(type!=0 &&
				(m->sd->bl.x<x0 || m->sd->bl.y<y0 ||
				 m->sd->bl.x>x1 || m->sd->bl.y>y1 ) )
				continue;
			list[blockcount++]=&m->sd->bl;
		}
	}

	map_freeblock_lock();	// メモリからの解放を禁止する

	for(i=0;i<blockcount;i++)
		if(list[i]->prev)	// 有効かどうかチェック
			func(list[i],ap);

	map_freeblock_unlock();	// 解放を許可する

	va_end(ap);

	return;
}

// 同じマップでオンライン中のパーティメンバーの数を返す
// 0:居ないか,PTがない
int party_check_same_map_member_count(struct map_session_data *sd)
{
	int count = 0;
	int i;
	struct party* pt = NULL;

	nullpo_retr(0,sd);

	pt = party_search(sd->status.party_id);

	if(pt == NULL)
		return 0;

	for(i=0;i<MAX_PARTY;i++)
	{
		if(pt->member[i].online && pt->member[i].sd!=NULL)
		{
			if((sd != pt->member[i].sd) && sd->bl.m == pt->member[i].sd->bl.m)
				count++;
		}
	}

	return count;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int party_db_final(void *key,void *data,va_list ap)
{
	free(data);

	return 0;
}

void do_final_party(void)
{
	if(party_db)
		numdb_final(party_db,party_db_final);

	return;
}

// 初期化
void do_init_party(void)
{
	party_db=numdb_init();
	add_timer_func_list(party_send_xyhp_timer,"party_send_xyhp_timer");
	add_timer_interval(gettick()+PARTY_SEND_XYHP_INVERVAL,party_send_xyhp_timer,0,0,PARTY_SEND_XYHP_INVERVAL);

	return;
}
