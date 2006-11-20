#ifndef _CHAR_CONVERTER_H_
#define _CHAR_CONVERTER_H_

#include "../common/mmo.h"

int char_convert(void);

// char.hより
struct mmo_chardata {
	struct mmo_charstatus st;
	struct registry reg;
};

enum {
	TABLE_INVENTORY,
	TABLE_CART,
	TABLE_STORAGE,
	TABLE_GUILD_STORAGE,
};

#endif /* _CHAR_CONVERTER_H_ */
