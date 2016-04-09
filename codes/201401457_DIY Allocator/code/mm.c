/* 
 * Here we have implemented 32-bit and 64-bit clean allocator based on an address ordered segregate free list with range of size 2^k 
 * where k = 5 to 14, best fit placement, and boundary tag coalescing.
					   ________ _________________________ _________________________ _____________________ ________
 * Every free block looks like      ----> | Header | prev free block pointer | next free block pointer | Remaining free size | Footer |
					  |________|_________________________|_________________________|_____________________|________|
 					   ________ ______________ ________	
 * Every allocated block looks like ----> | Header | Payload      | Footer |
					  |________|______________|________|
				   	
 * Blocks are aligned to double-word boundaries. This
 * yields 8-byte aligned blocks on a 32-bit processor, and 16-byte aligned
 * blocks on a 64-bit processor.
 * This allocator uses the size of a pointer, e.g., sizeof(void *), to
 * define the size of a word.  This allocator also uses the standard
 * type uintptr_t to define unsigned integers that are the same size
 * as a pointer, i.e., sizeof(uintptr_t) == sizeof(void *).
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "memlib.h"
#include "mm.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
	/* Team name */
	"LoveToCode",
	/* First member's full name */
	"Uttam Chaudhari",
	/* First member's email address */
	"201401457@daiict.ac.in",
	/* Second member's full name (leave blank if none) */
	"Harsh Chaudhari",
	/* Second member's email address (leave blank if none) */
	"201401424@daiict.ac.in"
};

/* Basic constants and macros: */
#define WSIZE      sizeof(void *) /* Word and header/footer size (bytes) */
#define DSIZE      (2 * WSIZE)    /* Doubleword size (bytes) */
#define CHUNKSIZE  (1 << 12)      /* Extend heap by this amount (bytes) */
#define LIST_SIZE  10
#define MAX(x, y)  ((x) > (y) ? (x) : (y))  

/* Pack a size and allocated bit into a word. */
#define PACK(size, alloc)  ((size) | (alloc))

/* Read and write a word at address p. */
#define GET(p)       (*(uintptr_t *)(p))
#define PUT(p, val)  (*(uintptr_t *)(p) = (val))

/* Read the size and allocated fields from address p. */
#define GET_SIZE(p)   (GET(p) & ~(DSIZE - 1))
#define GET_ALLOC(p)  (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer. */
#define HDRP(bp)  ((char *)(bp) - WSIZE)
#define FTRP(bp)  ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks. */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/* Given block ptr bp, compute address of next free block and previous free blocks. */					
#define PREV_FREE_BLKP(bp) (*(void **) (bp))
#define NEXT_FREE_BLKP(bp) (*(void **) (bp + WSIZE))

/* Given block ptr bp and prev or next pointer set previous or next pointer */					
#define SET_PREV_FREE(bp, prev) (*((void **)(bp)) = prev)
#define SET_NEXT_FREE(bp, next) (*((void **)(bp + WSIZE)) = next)

/* Global variables: */
static char *heap_listp; /* Pointer to first block */  

/* Function prototypes for internal helper routines: */
static void *coalesce(void *bp);
static void *extend_heap(size_t words);
static void *best_fit(size_t asize);
static void place(void *bp, size_t asize);

/* Function prototypes for heap consistency checker routines: */
static void checkblock(void *bp);
static void checkheap(bool verbose);
static void printblock(void *bp);
static void delete_block(void *bp);    /* for deleting block in segregate free list */
static void insert_block(void *bp);    /* for inserting block in segregate free list */
static bool is_inlist(void *bp);  
static void **list;	       /* Holds the pointers in segregate free list */
/* 
 * Requires:
 *   None.
 *
 * Effects:
 *   Initialize the memory manager.  Returns 0 if the memory manager was
 *   successfully initialized and -1 otherwise.
 */
int
mm_init(void) 
{
	
	/* Create the initial empty heap. */
	if((list = mem_sbrk(LIST_SIZE*WSIZE)) == (void *)-1)
		return (-1);
	if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
		return (-1);
	PUT(heap_listp, 0);                            /* Alignment padding */
	PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); /* Prologue header */ 
	PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); /* Prologue footer */ 
	PUT(heap_listp + (3 * WSIZE), PACK(0, 1));     /* Epilogue header */
	heap_listp += (2 * WSIZE);
	
	/* Initializing list pointers */

	/* Here each pointer points to starting free block of defined range size
	   i.e list[0] points to free block which has size in range of 16 to 32 byte, list[1]
		points to size in range of 32 to 64 byte and so on...	  */ 
	int pos = 0;
	for(pos=0;pos<LIST_SIZE;pos++)
		list[pos] = NULL;

	/* Extend the empty heap with a free block of CHUNKSIZE bytes. */
	if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
		return (-1);
	
	return (0);
}

/* 
 * Requires:
 *   block pointer which is going to be insert.
 *
 * Effects:
 *   Insert a free block in segregate list in address order manner and set its previous and next free block pointers accordingly.  
 */
static void insert_block(void *bp)
{	
	size_t size = GET_SIZE(HDRP(bp));
	
	/* Getting appropriate list pointer for given size block */
	int pos=0;
	while(pos<(LIST_SIZE-1) && size>32)
	{
		size>>=1;
		pos++;
	}	
	
    /* Finding appropriate position for block pointer 'bp' to insert in free list */
    void *curr = list[pos];
    void *saved = curr;
    void *prev = NULL;
    while (curr != NULL && bp < curr) {
        prev = PREV_FREE_BLKP(curr);
        saved = curr;
        curr = NEXT_FREE_BLKP(curr);
    }
    
    /* Setting previous and Next free block pointer in bp */
    SET_PREV_FREE(bp, prev);
    SET_NEXT_FREE(bp, saved);

    /* If prev is NULL then bp must be head of free list, otherwise set Next free block of prev to bp */ 
    if (prev != NULL) 
        SET_NEXT_FREE(prev, bp);
    else  
        list[pos] = bp;
         
    /* if saved is not NULL then set Previous free block of saved to bp */ 
    if (saved != NULL) 
        SET_PREV_FREE(saved, bp);
    
	
}

/* 
 * Requires:
 *   block pointer which is going to be delete.
 *
 * Effects:
 *   Delete a free block from segregatelist and set its previous and next free block accordingly.  
 */
static void delete_block(void *bp)
{
	size_t size = GET_SIZE(HDRP(bp));

	/* Getting appropriate list pointer for given size block */
	int pos=0;
	while(pos<(LIST_SIZE-1) && size>32)
	{
		size>>=1;
		pos++;
	}	
	
	/* Hold prev and next free block of node which is going to be delete */
	void *prv = (void *)PREV_FREE_BLKP(bp);
	void *nxt = (void *)NEXT_FREE_BLKP(bp);
        
	if (prv == NULL)  /* Beggining of the list */	
	    list[pos] = nxt;
		
        else 
	    SET_NEXT_FREE(prv, nxt);
   
    
    	if (nxt != NULL)  /* Not the end of list */
    	    SET_PREV_FREE(nxt, prv);
   
}
/* 
 * Requires:
 *   None.
 *
 * Effects:
 *   Allocate a block with at least "size" bytes of payload, unless "size" is
 *   zero.  Returns the address of this block if the allocation was successful
 *   and NULL otherwise.
 */
void *
mm_malloc(size_t size) 
{
	size_t asize;      /* Adjusted block size */
	size_t extendsize; /* Amount to extend heap if no fit */
	void *bp;

	/* Ignore spurious requests. */
	if (size == 0)
		return (NULL);

	/* Adjust block size to include overhead and alignment reqs. */
	if (size <= DSIZE)
		asize = 2 * DSIZE;
	else
		asize = DSIZE * ((size + DSIZE + (DSIZE - 1)) / DSIZE);

	/* Search the best free block of a given size in segregate free list. */
	if ((bp = best_fit(asize)) != NULL)                        
	{
		place(bp, asize);							
		return (bp);
	}

	/* No fit found.  Get more memory and place the block. */
	extendsize = MAX(asize, CHUNKSIZE);
	if ((bp = extend_heap(extendsize / WSIZE)) == NULL)  
		return (NULL);
	place(bp, asize);
	return (bp);
} 

/* 
 * Requires:
 *   "bp" is either the address of an allocated block or NULL.
 *
 * Effects:
 *   Free a block.
 */
void
mm_free(void *bp)
{
	size_t size;

	/* Ignore spurious requests. */
	if (bp == NULL)
		return;

	/* Free and coalesce the block. */
	size = GET_SIZE(HDRP(bp));
	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	coalesce(bp);
}

/*
 * Requires:
 *   "ptr" is either the address of an allocated block or NULL.
 *
 * Effects:
 *   Reallocates the block "ptr" to a block with at least "size" bytes of
 *   payload, unless "size" is zero.  If "size" is zero, frees the block
 *   "ptr" and returns NULL.  If the block "ptr" is already a block with at
 *   least "size" bytes of payload, then "ptr" is returned.
 *   If next block of 'ptr' is free and combining them make payload of size
 *   greater than "size" then extend that block and return the 'ptr'.
 *   Otherwise, a new block is allocated and the contents of the old block
 *   "ptr" are copied to that new block.  Returns the address of this new
 *   block if the allocation was successful and NULL otherwise.
 */
void *
mm_realloc(void *ptr, size_t size)
{
	size_t oldsize;
	void *newptr;

	/* If size == 0 then this is just free, and we return NULL. */
	if (size == 0) 
	{
		mm_free(ptr);
		return (NULL);
	}

	/* If oldptr is NULL, then this is just malloc. */
	if (ptr == NULL)
		return (mm_malloc(size));

	size_t nextsize = GET_SIZE(HDRP(NEXT_BLKP(ptr)));
	oldsize = GET_SIZE(HDRP(ptr));
	
	/* If size+DSIZE is less than oldsize then no need to memcopy or new malloc just return the old pointer
	   old data is still valid for that block and no need to remove additional data */
	if (size + DSIZE < oldsize)	
		return ptr;

	/* If next block of ptr is free then just extend that block, make changes in segregate list accordinly
	   and return ptr. old data is still there */
	if(!GET_ALLOC(HDRP(NEXT_BLKP(ptr))) && size<=nextsize+oldsize)
	{
		delete_block(NEXT_BLKP(ptr));
		PUT(HDRP(ptr),PACK(nextsize+oldsize,1));
		PUT(FTRP(ptr),PACK(nextsize+oldsize,1));		
		return ptr;
	}	
	
	/* This is for those size which is less than old size but it becomes greater when header and footer are added, so 
	   we must need to get newptr by calling mm_malloc and memcopy from old ptr */
	if(size<oldsize)
		oldsize = size;

	newptr = mm_malloc(size);
	

	/* If realloc() fails the original block is left untouched  */
	if (newptr == NULL)
		return (NULL);
	
	/* Copy the old data. */
	memcpy(newptr, ptr, oldsize);

	/* Free the old block. */
	mm_free(ptr);
	return (newptr);
}

/*
 * The following routines are internal helper routines.
 */

/*
 * Requires:
 *   "bp" is the address of a newly freed block.
 *
 * Effects:
 *   Perform boundary tag coalescing.  Returns the address of the coalesced
 *   block.
 */

static void *
coalesce(void *bp) 
{
		
	bool prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
	bool next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
	size_t size = GET_SIZE(HDRP(bp));
	
	if (prev_alloc && next_alloc) {                 /* Case 1 */
		insert_block(bp);		        /* Insert free block in list */
		return (bp);
	} else if (prev_alloc && !next_alloc) {         /* Case 2 */
		delete_block(NEXT_BLKP(bp));		/* delete next block of bp and then after combining both block
							   insert combined block in segregate free list */
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
		insert_block(bp);
	} else if (!prev_alloc && next_alloc) {         /* Case 3 */
		delete_block(PREV_BLKP(bp));		/* delete prev block of bp and then after combining both block
							   insert combined block in segregate free list */
		size += GET_SIZE(HDRP(PREV_BLKP(bp)));
		PUT(FTRP(bp), PACK(size, 0));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
		insert_block(bp);
	} else {                                        /* Case 4 */
		delete_block(NEXT_BLKP(bp));            /* delete both block and after combining blocks insert 
							   combined block in segregate free list  */  
		delete_block(PREV_BLKP(bp));		
		size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
		    GET_SIZE(FTRP(NEXT_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
		insert_block(bp);
	}
	
	
	return (bp);
}

/* 
 * Requires:
 *   None.
 *
 * Effects:
 *   Extend the heap with a free block and return that block's address.
 */
static void *extend_heap(size_t words) 
{
	void *bp;
	size_t size;

	/* Allocate an even number of words to maintain alignment. */
	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
	if ((bp = mem_sbrk(size)) == (void *)-1)  
		return (NULL);

	/* Initialize free block header/footer and the epilogue header. */
	PUT(HDRP(bp), PACK(size, 0));         /* Free block header */
	PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */

	/* Coalesce if the previous block was free. */
	return (coalesce(bp));
}

/*
 * Requires:
 *   None.
 *
 * Effects:
 *   Find a minimum size of block which is at least of "asize" size
 *   in segregate free list. Returns that block's address
 *   or NULL if no suitable block was found. 
 */
static void *best_fit(size_t asize)
{
	void *bp=NULL,*tmp;
	int min ;
	size_t size = asize;
	
	/* Getting appropriate list pointer for given size block */
	int pos=0;
	while(pos<(LIST_SIZE-1) && size>32)
	{
		size>>=1;
		pos++;
	}		
	
	/* Search for block in all the list which contains block size greater than asize */
	for(;pos<LIST_SIZE;pos++)
	for(tmp = list[pos] ;tmp!=NULL;tmp = NEXT_FREE_BLKP(tmp))
	{
		if(asize <= GET_SIZE(HDRP(tmp)))
		{
			int diff = GET_SIZE(HDRP(tmp));
			if(bp==NULL)
			{
				min  = diff;
				bp = tmp;
			}
			if(diff<min)
			{
				min=diff;
				bp=tmp;
 			}
		}
			
	}
return (bp);
	
}
/* 
 * Requires:
 *   "bp" is the address of a free block that is at least "asize" bytes.
 *
 * Effects:
 *   Place a block of "asize" bytes at the start of the free block "bp" and
 *   split that block if the remainder would be at least the minimum block
 *   size. 
 */
static void place(void *bp, size_t asize)
{
	size_t csize = GET_SIZE(HDRP(bp));   

	if ((csize - asize) >= (2 * DSIZE)) { 
		delete_block(bp);
		PUT(HDRP(bp), PACK(asize, 1));
		PUT(FTRP(bp), PACK(asize, 1));
		bp = NEXT_BLKP(bp);
		PUT(HDRP(bp), PACK(csize - asize, 0));
		PUT(FTRP(bp), PACK(csize - asize, 0));
		insert_block(bp);
	} else {
		PUT(HDRP(bp), PACK(csize, 1));
		PUT(FTRP(bp), PACK(csize, 1));
		delete_block(bp);
	}
}

/* 
 * The remaining routines are heap consistency checker routines. 
 */

/*
 * Requires:
 *   "bp" is the address of a block.
 *
 * Effects:
 *   Perform a minimal check on the block "bp".
 */
static void checkblock(void *bp) 
{

	if ((uintptr_t)bp % DSIZE)
		printf("Error: %p is not doubleword aligned\n", bp);
	if (GET(HDRP(bp)) != GET(FTRP(bp)))
		printf("Error: header does not match footer\n");
}

/* 
 * Requires:
 *   None.
 *
 * Effects:
 *   Perform a minimal check of the heap for consistency. 
 */
void checkheap(bool verbose) 
{
	void *bp;

	if (verbose)
		printf("Heap (%p):\n", heap_listp);

	if (GET_SIZE(HDRP(heap_listp)) != DSIZE ||
	    !GET_ALLOC(HDRP(heap_listp)))
		printf("Bad prologue header\n");
	checkblock(heap_listp);
	
	/* check if every free block in segregate free list is free, if not print Error msg */
	int pos=0;
	for(;pos<LIST_SIZE;pos++)
	{ 
		for (bp = list[pos];bp!=NULL; bp = NEXT_FREE_BLKP(bp)) 
		{
			if(GET_ALLOC(HDRP(bp)))
				printf("Error: block at %p is allocated but it is in free list\n",bp); 
		}
	}
	
	/* check if there are contiguos free block which escaped coalescing, if so print Error msg */
	int flag=0;
	for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) 
	{
		if (verbose)
			printblock(bp);
		if(!GET_ALLOC(HDRP(bp)) && flag==1)
			printf("Error: block at %p and %p are not coalesce\n",PREV_BLKP(bp),bp);
		else if(!GET_ALLOC(HDRP(bp)))
			flag = 1;
		else
			flag = 0;
	}
	
	/* check is every free block actually in segregate free list, if not print Erro msg */
	for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) 
		if(!GET_ALLOC(HDRP(bp)) && !is_inlist(bp))
			printf("Error: block at %p is free but it is not in segregate free list\n",bp);  
		
	/* check do the pointers in the heap block point to valid heap address, if not print Error msg */
	for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp))
		checkblock(bp); 		
	
	if (verbose)
		printblock(bp);
	if (GET_SIZE(HDRP(bp)) != 0 || !GET_ALLOC(HDRP(bp)))
		printf("Bad epilogue header\n");

	/* check do the pointer in segregate free list point to valid address, if not print Error msg */
	for(pos=0;pos<LIST_SIZE;pos++)
		for (bp = list[pos];bp!=NULL; bp = NEXT_FREE_BLKP(bp))
			checkblock(bp);
	
	
}

/*
 * Requires:
 *   "bp" is the address of a block.
 *
 * Effects:
 *   Print the block "bp".
 */
static void printblock(void *bp) 
{
	bool halloc, falloc;
	size_t hsize, fsize;

	checkheap(false);
	hsize = GET_SIZE(HDRP(bp));
	halloc = GET_ALLOC(HDRP(bp));  
	fsize = GET_SIZE(FTRP(bp));
	falloc = GET_ALLOC(FTRP(bp));  

	if (hsize == 0) {
		printf("%p: end of heap\n", bp);
		return;
	}

	printf("%p: header: [%zu:%c] footer: [%zu:%c]\n", bp, 
	     hsize, (halloc ? 'a' : 'f'), 
	    fsize, (falloc ? 'a' : 'f'));
}
/*
 * Requires:
 *   "bp" is the address of a block.
 *
 * Effects:
 *   Search for that block in segregate free list and
 *   if found return true otherwise return false.
 */
static bool is_inlist(void *bp)
{
	if(GET_ALLOC(HDRP(bp)))
		return 0;
	size_t size = GET_SIZE(HDRP(bp));
	int pos=0;
	while(pos<(LIST_SIZE-1) && size>32)
	{
		size>>=1;
		pos++;
	}
	void *tmp = list[pos];	
	while(tmp!=NULL)
	{
		if(tmp==bp)
			return 1;
		tmp = NEXT_FREE_BLKP(tmp);
	}
	return 0;
}
/*
 * The last lines of this file configures the behavior of the "Tab" key in
 * emacs.  Emacs has a rudimentary understanding of C syntax and style.  In
 * particular, depressing the "Tab" key once at the start of a new line will
 * insert as many tabs and/or spaces as are needed for proper indentation.
 */

/* Local Variables: */
/* mode: c */
/* c-default-style: "bsd" */
/* c-basic-offset: 8 */
/* c-continued-statement-offset: 4 */
/* indent-tabs-mode: t */
/* End: */
