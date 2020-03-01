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

#define _INT_PET_C_

#include <stdio.h>
#include <stdlib.h>

#include "mmo.h"
#include "socket.h"
#include "malloc.h"
#include "utils.h"

#include "int_pet.h"

int mapif_pet_created(int fd,int account_id,struct s_pet *p)
{
	WFIFOW(fd,0)=0x3880;
	WFIFOL(fd,2)=account_id;
	if(p!=NULL){
		WFIFOB(fd,6)=0;
		WFIFOL(fd,7)=p->pet_id;
		printf("int_pet: created! %d %s\n",p->pet_id,p->name);
	}else{
		WFIFOB(fd,6)=1;
		WFIFOL(fd,7)=0;
	}
	WFIFOSET(fd,11);

	return 0;
}

int mapif_pet_info(int fd,int account_id,const struct s_pet *p)
{
	WFIFOW(fd,0)=0x3881;
	WFIFOW(fd,2)=sizeof(struct s_pet) + 9;
	WFIFOL(fd,4)=account_id;
	WFIFOB(fd,8)=0;
	memcpy(WFIFOP(fd,9),p,sizeof(struct s_pet));
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

int mapif_pet_noinfo(int fd,int account_id)
{
	WFIFOW(fd,0)=0x3881;
	WFIFOW(fd,2)=sizeof(struct s_pet) + 9;
	WFIFOL(fd,4)=account_id;
	WFIFOB(fd,8)=1;
	memset(WFIFOP(fd,9),0,sizeof(struct s_pet));
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

int mapif_save_pet_ack(int fd,int account_id,int flag)
{
	WFIFOW(fd,0)=0x3882;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);

	return 0;
}

int mapif_delete_pet_ack(int fd,int flag)
{
	WFIFOW(fd,0)=0x3883;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,3);

	return 0;
}

int mapif_create_pet(int fd,int account_id,int char_id,short pet_class,unsigned short pet_lv,short pet_egg_id,
	short pet_equip,short intimate,short hungry,char rename_flag,char incubate,const char *pet_name)
{
	struct s_pet *p;

	p=(struct s_pet *)aCalloc(1,sizeof(struct s_pet));
	memcpy(p->name,pet_name,24);
	if(incubate == 1) {
		p->account_id = 0;
		p->char_id    = 0;
	} else {
		p->account_id = account_id;
		p->char_id    = char_id;
	}
	p->class_      = pet_class;
	p->level       = pet_lv;
	p->egg_id      = pet_egg_id;
	p->equip       = pet_equip;
	p->intimate    = intimate;
	p->hungry      = hungry;
	p->rename_flag = rename_flag;
	p->incubate    = incubate;

	if(p->hungry < 0)
		p->hungry = 0;
	else if(p->hungry > 100)
		p->hungry = 100;
	if(p->intimate < 0)
		p->intimate = 0;
	else if(p->intimate > 1000)
		p->intimate = 1000;

	if(petdb_new(p) == true) {
		mapif_pet_created(fd,account_id,p);
	} else {
		aFree(p);
	}
	return 0;
}

int mapif_load_pet(int fd,int account_id,int char_id,int pet_id)
{
	const struct s_pet *p = petdb_load(pet_id);

	if(p!=NULL) {
		if(p->incubate == 1)
			mapif_pet_info(fd,account_id,p);
		else if(account_id == p->account_id && char_id == p->char_id)
			mapif_pet_info(fd,account_id,p);
		else
			mapif_pet_noinfo(fd,account_id);
	} else {
		mapif_pet_noinfo(fd,account_id);
	}

	return 0;
}

int mapif_save_pet(int fd,int account_id,struct s_pet *data)
{
	if(sizeof(struct s_pet) != RFIFOW(fd,2) - 8) {
		printf("inter pet: data size error %lu %d\n",(unsigned long)sizeof(struct s_pet),RFIFOW(fd,2)-8);
		return 0;
	}

	if(petdb_load(data->pet_id)) {
		if(data->hungry < 0)
			data->hungry = 0;
		else if(data->hungry > 100)
			data->hungry = 100;
		if(data->intimate < 0)
			data->intimate = 0;
		else if(data->intimate > 1000)
			data->intimate = 1000;
		if(data->incubate == 1)
			data->account_id = data->char_id = 0;
		petdb_save(data);
		mapif_save_pet_ack(fd,account_id,0);
	}

	return 0;
}

int mapif_delete_pet(int fd,int pet_id)
{
	mapif_delete_pet_ack(fd,petdb_delete(pet_id));

	return 0;
}

int mapif_parse_CreatePet(int fd)
{
	mapif_create_pet(
		fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOW(fd,10),RFIFOW(fd,12),RFIFOW(fd,14),
		RFIFOW(fd,16),RFIFOW(fd,18),RFIFOW(fd,20),RFIFOB(fd,22),RFIFOB(fd,23),RFIFOP(fd,24)
	);
	return 0;
}

int mapif_parse_LoadPet(int fd)
{
	mapif_load_pet(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10));
	return 0;
}

int mapif_parse_SavePet(int fd)
{
	mapif_save_pet(fd,RFIFOL(fd,4),(struct s_pet *)RFIFOP(fd,8));
	return 0;
}

int mapif_parse_DeletePet(int fd)
{
	mapif_delete_pet(fd,RFIFOL(fd,2));
	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_pet_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3080: mapif_parse_CreatePet(fd); break;
	case 0x3081: mapif_parse_LoadPet(fd); break;
	case 0x3082: mapif_parse_SavePet(fd); break;
	case 0x3083: mapif_parse_DeletePet(fd); break;
	default:
		return 0;
	}
	return 1;
}
