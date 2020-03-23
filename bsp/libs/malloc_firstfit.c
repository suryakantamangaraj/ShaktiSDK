/***************************************************************************
* Project               	    		: shakti devt board
* Name of the file	            	: malloc_firstfit.c
* Brief Description of file       : Malloc using First-fit algorithm code.
* Name of Author    	            : Abhinav Ramnath
* Email ID                        : abhinavramnath13@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
***************************************************************************/
#include<unistd.h>
#include<sys/types.h>
#include "platform.h"
#include "log.h"

extern char* _HEAP_SIZE[];
char* HEAP_SIZE = (char *)&_HEAP_SIZE;


//Header block denotes start of the segment
struct Header
{
size_t size;
int free;
struct Header* next;
};

struct Header* global_base=NULL;

struct Header* allocate_block(struct Header* last, size_t size)
{
if(last->size>size)
{
log_info("\n allocating space");
struct Header* newblock;
void *p = last;
p+=size+sizeof(struct Header);
newblock=p;
newblock->size=last->size - size - sizeof(struct Header);
last->size=size;
last->free=0;
last->next=newblock;
newblock->free=1;
newblock->next=NULL;
return last;
}
else
return NULL;
}

//We search for free blocks
/** @fn  
 * @brief  
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
struct Header *find_free_block(struct Header **last, size_t size) {
log_info("\nfind free");  
struct Header *current = global_base;
  while (current && !(current->free && current->size >= size)) {
	log_info("\n Inside Loop %d %d %x %x",current->size,size,current,*last);
    *last = current;
    current = current->next;
  }
log_info("\n After Loop %d %d %x %x",current->size,size,current,*last);
  if(current && current->size>=size)
  {
	*last=current;
	return current;
  }
  else
	return NULL;
  
}

//Creating a new block
/** @fn  
 * @brief  
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
struct Header* request_heap()
{
struct Header *block;
  
  block = m_sbrk(0);
  void *request = m_sbrk(HEAP_SIZE);
  if((void*)block == request); // Not thread safe.
  block=request;
  log_info("\nInitial Heap start address =%x",block); 
  if (request == (void*) -1) {
    log_error("\nNo space left to allocate memory");
    return NULL; // sbrk failed.
  }
  
  block->size = HEAP_SIZE;	  
  block->next = NULL;
  block->free = 1;
  log_info("\nBlock Assigned");
  return block;
}

//malloc function to allocate space
/** @fn  
 * @brief  
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void *malloc(size_t size) {
  struct Header *block;

  if (size <= 0) {
    return NULL;
  }
  log_info("\n global_base: %x",global_base);
  if(global_base==0x00000000) 
  { // First call. global_base is empty
    	log_info("\n Requesting block");
    	block = request_heap();
    	log_info("\n block=%x",block);
    	if (!block) 
	{
      		return NULL;
    	}
    	global_base = block;
    	
 }
	
    	struct Header *last = global_base; 
    	block = find_free_block(&last, size);
	if(!block)
	{
	log_error("\n No free blocks");
	return NULL;
	}    	
	log_info("\nBlock = %x Block Size = %d Size = %d",block,block->size,size);
	if (block->size>size) 	
	{ // Failed to find free block.
     		block = allocate_block(last,size);
      		if (!block) 
		{
			return NULL;
      		}
  	} 
  	else if(block->size==size)
	{      // Found free block
		log_info("\nFound free block of same size");
      		block->free = 0;
  	}
	
  return(block+1);
}

struct Header *get_block_ptr(void *ptr) {
  return (struct Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  
 * @brief  
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void free(void *ptr) {
  if (!ptr) {
    log_error("\n Wrong value passed to free");
    return;
  }
  struct Header* block_ptr = get_block_ptr(ptr);
  log_info("\n %x is freed",block_ptr);
  if(block_ptr->free==0)
  block_ptr->free = 1;
    
}

