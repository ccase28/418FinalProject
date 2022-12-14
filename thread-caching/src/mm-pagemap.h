#ifndef _MM_PAGEMAP_H
#define _MM_PAGEMAP_H

#include "mm-comm.h"
#include "mm-cache-defines.h"
#include "mm-frontend-aux.h"

#define PM_LEVELS (4)
#define PM_INDEX_WIDTH (12)
#define PM_BLOCK_INDICES (1UL << PM_INDEX_WIDTH)
#define PM_NOEXIST (NULL)

typedef struct superblock_descriptor *sb_desc_pair[2];

typedef struct pagemap_block pagemap_block_t;
struct pagemap_block {
  pagemap_block_t *next_nonterminal[PM_BLOCK_INDICES];
};

/* Return size class of the  */
struct superblock_descriptor *pagemap_lookup(void *ptr);

/* Initialize lookup location, or transfer ownership if already used */
void pagemap_reallocate(void *ptr, struct superblock_descriptor *owner);


#endif // _MM_PAGEMAP_H