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

#include <stdio.h>

#include "nullpo.h"

#include "clif.h"
#include "map.h"
#include "pc.h"

/*==========================================
 * 預け入れ
 *------------------------------------------
 */
void bank_deposit(struct map_session_data *sd, int target_id, int zeny)
{
	struct map_session_data *tmpsd = map_id2sd(target_id);

	nullpo_retv(sd);

	// anti hacker
	if(!tmpsd || sd != tmpsd)
		return;

	// 取引不可チェック
	if( sd->npc_id != 0 || sd->state.storage_flag || sd->state.store || sd->state.deal_mode != 0 ||
	    sd->state.mail_appending || sd->chatID != 0 )
		return;

	// Zenyチェック
	if(zeny <= 0) {
		clif_bank_deposit(sd, 1);
		return;
	}
	if(sd->deposit > MAX_ZENY - zeny) {
		clif_bank_deposit(sd, 3);
		return;
	}
	if(zeny > sd->status.zeny) {
		clif_bank_deposit(sd, 2);
		return;
	}

	// Zenyの支払い
	pc_payzeny(sd, zeny);
	sd->deposit += zeny;

	// 預金額変数の保存
	pc_setaccountreg(sd,"#PC_DEPOSIT",sd->deposit);

	// 取引結果送信
	clif_bank_deposit(sd, 0);

	return;
}

/*==========================================
 * 引き出し
 *------------------------------------------
 */
void bank_withdraw(struct map_session_data *sd, int target_id, int zeny)
{
	struct map_session_data *tmpsd = map_id2sd(target_id);

	nullpo_retv(sd);

	// anti hacker
	if(!tmpsd || sd != tmpsd)
		return;

	// 取引不可チェック
	if( sd->npc_id != 0 || sd->state.storage_flag || sd->state.store || sd->state.deal_mode != 0 ||
	    sd->state.mail_appending || sd->chatID != 0 )
		return;

	// Zenyチェック
	if(zeny <= 0) {
		clif_bank_withdraw(sd, 2);
		return;
	}
	if(zeny > sd->deposit) {
		clif_bank_withdraw(sd, 1);
		return;
	}
	if(sd->status.zeny > MAX_ZENY - zeny)
		return;

	// Zenyの支払い
	pc_getzeny(sd, zeny);
	sd->deposit -= zeny;

	// 預金額変数の保存
	pc_setaccountreg(sd,"#PC_DEPOSIT",sd->deposit);

	// 取引結果送信
	clif_bank_withdraw(sd, 0);

	return;
}
