#ifndef SAPPHIRE_ITEMS_H
#define SAPPHIRE_ITEMS_H

#include "sapphire-mem.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __sapphire_item {
	const char* left_val;
	const char* connection;
	const char* right_val;
} sapphire_item_t;

static const unsigned SAPPHIRE_ITEM_FLAG_EQ_L = 1; /* Used to compare the left values*/
static const unsigned SAPPHIRE_ITEM_FLAG_EQ_R = 2; /* Used to compare the right values*/
static const unsigned SAPPHIRE_ITEM_FLAG_EQ_C = 4; /* Used to compare the conneciton */

extern int sapphire_item_equals(const sapphire_item_t* i1, 
	                       const sapphire_item_t* i2, 
	                       unsigned flags);

#ifdef __cplusplus
}
#endif


#endif // SAPPHIRE_ITEMS_H
