/*
 * Copyright (C) 2002-2020  Auriga
 *
 * This file is part of Auriga.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#define _INT_PARTY_C_

#include <stdio.h>
#include <stdlib.h>

#include "mmo.h"
#include "socket.h"
#include "malloc.h"
#include "utils.h"

#include "char.h"
#include "int_party.h"

static int party_share_level = 10;

// EXP�������z�ł��邩�`�F�b�N
static int party_check_exp_share(struct party *p,int baby_id)
{
	int i;
	int maxlv=0, minlv=0x7fffffff;

	for(i=0; i<MAX_PARTY; i++) {
		int lv = p->member[i].lv;
		if( p->member[i].online ) {
			if( lv < minlv ) minlv = lv;
			if( maxlv < lv ) maxlv = lv;
		}
	}
	if(maxlv == 0 || maxlv - minlv <= party_share_level)
		return 1;

	if(baby_id > 0) {
		// �Ƒ������̉\��������̂Ń`�F�b�N����
		const struct mmo_chardata *b, *p1, *p2;

		if((b = chardb_load(baby_id)) == NULL)
			return 0;

		p1 = chardb_load(b->st.parent_id[0]);
		p2 = chardb_load(b->st.parent_id[1]);

		if(p1 && p2) {
			if( p1->st.party_id == b->st.party_id && p1->st.baby_id == baby_id && p1->st.base_level >= 70 &&
			    p2->st.party_id == b->st.party_id && p2->st.baby_id == baby_id && p2->st.base_level >= 70 &&
			    p1->st.partner_id == p2->st.char_id && p2->st.partner_id == p1->st.char_id ) {
				return 1;
			}
		}
	}
	return 0;
}

// �p�[�e�B���󂩂ǂ����`�F�b�N
int party_check_empty(const struct party *p)
{
	int i;

	for(i=0;i<MAX_PARTY;i++){
		if(p->member[i].account_id>0){
			return 0;
		}
	}
	return 1;
}

//-------------------------------------------------------------------
// map server�ւ̒ʐM

// �p�[�e�B�쐬��
int mapif_party_created(int fd,int account_id,struct party *p)
{
	WFIFOW(fd,0)=0x3820;
	WFIFOL(fd,2)=account_id;
	if(p!=NULL){
		WFIFOB(fd,6)=0;
		WFIFOL(fd,7)=p->party_id;
		memcpy(WFIFOP(fd,11),p->name,24);
		printf("int_party: created! %d %s\n",p->party_id,p->name);
	} else {
		WFIFOB(fd,6)=1;
		WFIFOL(fd,7)=0;
	}
	WFIFOSET(fd,35);
	return 0;
}

// �p�[�e�B��񌩂��炸
int mapif_party_noinfo(int fd,int party_id)
{
	WFIFOW(fd,0)=0x3821;
	WFIFOW(fd,2)=8;
	WFIFOL(fd,4)=party_id;
	WFIFOSET(fd,8);
	printf("int_party: info not found %d\n",party_id);
	return 0;
}

// �p�[�e�B���܂Ƃߑ���
int mapif_party_info(int fd,const struct party *p)
{
	size_t size = sizeof(struct party);
	unsigned char *buf = (unsigned char *)aMalloc(size+4);

	WBUFW(buf,0)=0x3821;
	WBUFW(buf,2)=(unsigned short)(size+4);
	memcpy(WBUFP(buf,4),p,size);
	if(fd<0)
		mapif_sendall(buf,WBUFW(buf,2));
	else
		mapif_send(fd,buf,WBUFW(buf,2));

	aFree(buf);
	return 0;
}

// �p�[�e�B�����o�ǉ���
void mapif_party_memberadded(int fd, int party_id, int account_id, int char_id, const char *name, unsigned char flag)
{
	WFIFOW(fd,0)=0x3822;
	WFIFOL(fd,2)=party_id;
	WFIFOL(fd,6)=account_id;
	WFIFOL(fd,10)=char_id;
	WFIFOB(fd,14)=flag;
	strncpy(WFIFOP(fd,15), name, 24);
	WFIFOSET(fd,39);

	return;
}

// �p�[�e�B�ݒ�ύX�ʒm
int mapif_party_optionchanged(int fd,struct party *p,int account_id,int flag)
{
	unsigned char buf[16];

	WBUFW(buf,0)=0x3823;
	WBUFL(buf,2)=p->party_id;
	WBUFL(buf,6)=account_id;
	WBUFB(buf,10)=p->exp;
	WBUFB(buf,11)=p->item;
	WBUFB(buf,12)=flag;
	if(flag==0)
		mapif_sendall(buf,13);
	else
		mapif_send(fd,buf,13);
	printf("int_party: option changed %d %d %d %d %d\n",p->party_id,account_id,p->exp,p->item,flag);
	return 0;
}

// �p�[�e�B�E�ޒʒm
int mapif_party_leaved(int party_id,int account_id,int char_id,const char *name)
{
	unsigned char buf[64];

	WBUFW(buf,0)=0x3824;
	WBUFL(buf,2)=party_id;
	WBUFL(buf,6)=account_id;
	WBUFL(buf,10)=char_id;
	strncpy(WBUFP(buf,14),name,24);
	mapif_sendall(buf,38);
	printf("int_party: party leaved %d %d %s\n",party_id,account_id,name);
	return 0;
}

// �p�[�e�B�}�b�v�X�V�ʒm
static void mapif_party_membermoved(int party_id, struct party_member *m)
{
	unsigned char buf[36];

	WBUFW(buf,0)=0x3825;
	WBUFL(buf,2)=party_id;
	WBUFL(buf,6)=m->account_id;
	WBUFL(buf,10)=m->char_id;
	memcpy(WBUFP(buf,14),m->map,16);
	WBUFB(buf,30)=m->online;
	WBUFW(buf,31)=m->lv;
	WBUFW(buf,33)=m->class_;
	mapif_sendall(buf,35);

	return;
}

// �p�[�e�B���U�ʒm
int mapif_party_broken(int party_id,int flag)
{
	unsigned char buf[16];

	WBUFW(buf,0)=0x3826;
	WBUFL(buf,2)=party_id;
	WBUFB(buf,6)=flag;
	mapif_sendall(buf,7);
	printf("int_party: broken %d\n",party_id);
	return 0;
}

// �p�[�e�B������
int mapif_party_message(int party_id,int account_id,const char *mes,size_t len)
{
	unsigned char buf[512];

	WBUFW(buf,0)=0x3827;
	WBUFW(buf,2)=(unsigned short)(len+12);
	WBUFL(buf,4)=party_id;
	WBUFL(buf,8)=account_id;
	memcpy(WBUFP(buf,12),mes,len);
	mapif_sendall(buf,len+12);
	return 0;
}

// ���[�_�[�ύX�ʒm
int mapif_party_leader_changed(int party_id,int old_account_id,int account_id)
{
	unsigned char buf[16];

	WBUFW(buf,0)=0x3828;
	WBUFL(buf,2)=party_id;
	WBUFL(buf,6)=old_account_id;
	WBUFL(buf,10)=account_id;
	mapif_sendall(buf,14);
	return 0;
}

//-------------------------------------------------------------------
// map server����̒ʐM


// �p�[�e�B
int mapif_parse_CreateParty(int fd, int account_id, int char_id, const char *name,
	unsigned char item, unsigned char item2, const char *nick, const char *map, unsigned short lv, unsigned short class_)
{
	struct party *p;
	int i;

	for(i=0; i<24 && name[i]; i++) {
		if(!(name[i]&0xe0) || name[i]==0x7f) {
			printf("int_party: illegal party name [%s]\n",name);
			mapif_party_created(fd,account_id,NULL);
			return 0;
		}
	}
	if(partydb_load_str(name) != NULL) {
		printf("int_party: same name party exists [%s]\n",name);
		mapif_party_created(fd,account_id,NULL);
		return 0;
	}

	p = (struct party *)aCalloc(1,sizeof(struct party));
	memcpy(p->name,name,24);
	p->exp  = 0;
	p->item = (item? 1: 0) | (item2? 2: 0);
	p->memorial_id = 0;
	p->member[0].account_id = account_id;
	p->member[0].char_id    = char_id;
	memcpy(p->member[0].name,nick,24);
	p->member[0].name[23] = '\0';	// force \0 terminal
	memcpy(p->member[0].map,map,16);
	p->member[0].map[15] = '\0';	// force \0 terminal
	p->member[0].leader = 1;
	p->member[0].online = 1;
	p->member[0].lv     = lv;
	p->member[0].class_ = class_;

	if(partydb_new(p) == true) {
		// ����
		mapif_party_created(fd,account_id,p);
		mapif_party_info(fd,p);
	} else {
		// ���s
		mapif_party_created(fd,account_id,NULL);
	}

	return 0;
}

// �p�[�e�B���v��
int mapif_parse_PartyInfo(int fd,int party_id)
{
	const struct party *p = partydb_load_num(party_id);

	if(p!=NULL)
		mapif_party_info(fd,p);
	else
		mapif_party_noinfo(fd,party_id);
	return 0;
}

// �p�[�e�B�ǉ��v��
int mapif_parse_PartyAddMember(int fd,int party_id,int account_id,int char_id,const char *nick,const char *map,int lv,int class_)
{
	const struct party *p1 = partydb_load_num(party_id);
	struct party p2;
	int i;

	if(p1 == NULL){
		mapif_party_memberadded(fd, party_id, account_id, char_id, nick, 1);
		return 0;
	}
	memcpy(&p2,p1,sizeof(struct party));

	for(i=0;i<MAX_PARTY;i++){
		if(p2.member[i].account_id == account_id && p2.member[i].char_id == char_id)
			break;
		if(p2.member[i].account_id == 0) {
			p2.member[i].account_id = account_id;
			p2.member[i].char_id    = char_id;
			memcpy(p2.member[i].name,nick,24);
			p2.member[i].name[23] = '\0';	// force \0 terminal
			memcpy(p2.member[i].map,map,16);
			p2.member[i].map[15] = '\0';	// force \0 terminal
			p2.member[i].leader  = 0;
			p2.member[i].online  = 1;
			p2.member[i].lv      = lv;
			p2.member[i].class_  = class_;
			mapif_party_memberadded(fd, party_id, account_id, char_id, nick, 0);
			mapif_party_info(-1,&p2);

			if( p2.exp>0 && !party_check_exp_share(&p2,0) ){
				p2.exp=0;
				mapif_party_optionchanged(fd,&p2,0,0);
			}
			partydb_save(&p2);
			return 0;
		}
	}
	mapif_party_memberadded(fd, party_id, account_id, char_id, nick, 1);
	partydb_save(&p2);
	return 0;
}

// �p�[�e�B�[�ݒ�ύX�v��
int mapif_parse_PartyChangeOption(int fd,int party_id,int account_id,int baby_id,unsigned char exp,unsigned char item)
{
	const struct party *p1 = partydb_load_num(party_id);
	struct party p2;
	int flag=0;

	if(p1 == NULL){
		return 0;
	}
	memcpy(&p2,p1,sizeof(struct party));

	p2.exp = exp;
	if( exp>0 && !party_check_exp_share(&p2,baby_id) ){
		flag|=0x01;
		p2.exp=0;
	}
	p2.item = item;

	mapif_party_optionchanged(fd,&p2,account_id,flag);
	partydb_save(&p2);
	return 0;
}

// �p�[�e�B�E�ޗv��
void mapif_parse_PartyLeave(int fd, int party_id, int account_id, int char_id)
{
	const struct party *p1 = partydb_load_num(party_id);
	struct party p2;
	int i;

	if(p1 == NULL)
		return;

	memcpy(&p2,p1,sizeof(struct party));
	for(i=0;i<MAX_PARTY;i++){
		if(p2.member[i].account_id == account_id && p2.member[i].char_id == char_id)
		{
			mapif_party_leaved(party_id,account_id,p2.member[i].char_id,p2.member[i].name);
			memset(&p2.member[i],0,sizeof(struct party_member));

			if(fd >= 0) {
				// �L�����폜�łȂ��ꍇ�̓p�[�e�BID��0�ɏ�����
				const struct mmo_chardata *cd = chardb_load(char_id);
				if(cd) {
					struct mmo_charstatus st;
					memcpy(&st, &cd->st, sizeof(st));
					st.party_id = 0;
					chardb_save(&st);
				}
			}

			if( party_check_empty(&p2) ) {
				// ��ɂȂ����̂ŉ��U
				mapif_party_broken(p2.party_id,0);
				partydb_delete(p2.party_id);
			} else {
				// �܂��l������̂Ńf�[�^���M
				mapif_party_info(-1,&p2);

				if( p2.exp>0 && !party_check_exp_share(&p2,0) ){
					p2.exp=0;
					mapif_party_optionchanged(fd,&p2,0,0);
				}
				partydb_save(&p2);
			}
			return;
		}
	}

	return;
}

// �p�[�e�B�}�b�v�X�V�v��
static void mapif_parse_PartyChangeMap(int fd, int party_id, int account_id, int char_id, const char *map, unsigned char online, unsigned short lv, unsigned short class_)
{
	const struct party *p1 = partydb_load_num(party_id);
	struct party p2;
	int i;

	if(p1 == NULL)
		return;

	memcpy(&p2,p1,sizeof(struct party));
	for(i=0;i<MAX_PARTY;i++){
		if(p2.member[i].account_id == account_id && p2.member[i].char_id == char_id) {
			memcpy(p2.member[i].map,map,16);
			p2.member[i].map[15] = '\0';	// force \0 terminal
			p2.member[i].online  = online;
			p2.member[i].lv      = lv;
			p2.member[i].class_  = class_;
			mapif_party_membermoved(party_id, &p2.member[i]);

			if( p2.exp>0 && !party_check_exp_share(&p2,0) ){
				p2.exp=0;
				mapif_party_optionchanged(fd,&p2,0,0);
			}
			break;
		}
	}
	partydb_save(&p2);

	return;
}

// �p�[�e�B���U�v��
int mapif_parse_BreakParty(int fd,int party_id)
{
	const struct party *p = partydb_load_num(party_id);

	if(p==NULL){
		return 0;
	}
	partydb_delete(party_id);
	mapif_party_broken(fd,party_id);
	return 0;
}

// �p�[�e�B���b�Z�[�W���M
int mapif_parse_PartyMessage(int fd,int party_id,int account_id,const char *mes,size_t len)
{
	return mapif_party_message(party_id,account_id,mes,len);
}

// �p�[�e�B�`�F�b�N�v��
int mapif_parse_PartyCheck(int fd,int party_id,int account_id,int char_id)
{
	// �Ƃ肠��������
	return 0;
}

// �p�[�e�B�[���[�_�[�ύX�v��
int mapif_parse_PartyLeaderChange(int fd,int party_id,int account_id,int char_id)
{
	const struct party *p1 = partydb_load_num(party_id);
	struct party p2;
	int i, old_account_id = 0;

	if(p1 == NULL)
		return 0;

	memcpy(&p2,p1,sizeof(struct party));

	for(i = 0; i < MAX_PARTY; i++) {
		if(p2.member[i].leader) {
			p2.member[i].leader = 0;
			old_account_id = p2.member[i].account_id;
		}
		if(p2.member[i].account_id == account_id && p2.member[i].char_id == char_id)
			p2.member[i].leader = 1;
	}

	mapif_party_leader_changed(party_id,old_account_id,account_id);
	partydb_save(&p2);

	return 0;
}

// map server ����̒ʐM
// �E�P�p�P�b�g�̂݉�͂��邱��
// �E�p�P�b�g���f�[�^��inter.c�ɃZ�b�g���Ă�������
// �E�p�P�b�g���`�F�b�N��ARFIFOSKIP�͌Ăяo�����ōs����̂ōs���Ă͂Ȃ�Ȃ�
// �E�G���[�Ȃ�0(false)�A�����łȂ��Ȃ�1(true)���������Ȃ���΂Ȃ�Ȃ�
int inter_party_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3020: mapif_parse_CreateParty(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOP(fd,10),RFIFOB(fd,34),RFIFOB(fd,35),RFIFOP(fd,36),RFIFOP(fd,60),RFIFOW(fd,76),RFIFOW(fd,78)); break;
	case 0x3021: mapif_parse_PartyInfo(fd,RFIFOL(fd,2)); break;
	case 0x3022: mapif_parse_PartyAddMember(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOP(fd,14),RFIFOP(fd,38),RFIFOW(fd,54),RFIFOW(fd,56)); break;
	case 0x3023: mapif_parse_PartyChangeOption(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14),RFIFOB(fd,15)); break;
	case 0x3024: mapif_parse_PartyLeave(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10)); break;
	case 0x3025: mapif_parse_PartyChangeMap(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOP(fd,14),RFIFOB(fd,30),RFIFOW(fd,31),RFIFOW(fd,33)); break;
	case 0x3026: mapif_parse_BreakParty(fd,RFIFOL(fd,2)); break;
	case 0x3027: mapif_parse_PartyMessage(fd,RFIFOL(fd,4),RFIFOL(fd,8),RFIFOP(fd,12),RFIFOW(fd,2)-12); break;
	case 0x3028: mapif_parse_PartyCheck(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10)); break;
	case 0x3029: mapif_parse_PartyLeaderChange(fd, RFIFOL(fd,2), RFIFOL(fd,6), RFIFOL(fd,10)); break;
	default:
		return 0;
	}
	return 1;
}

// �T�[�o�[����E�ޗv���i�L�����폜�p�j
void inter_party_leave(int party_id, int account_id, int char_id)
{
	mapif_parse_PartyLeave(-1, party_id, account_id, char_id);

	return;
}

// �p�[�e�B�[�ݒ�ǂݍ���
int party_config_read(const char *w1,const char* w2)
{
	if(strcasecmp(w1,"party_share_level")==0) {
		party_share_level = atoi(w2);
		if(party_share_level < 0) {
			party_share_level = 0;
		}
		return 1;
	}

	return partydb_config_read_sub(w1,w2);
}

