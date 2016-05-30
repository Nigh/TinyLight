
#include "tl_mem.h"

#define DEPTH2 5
#define WIDTH2 4
#define MEM_DEPTH (0x1<<DEPTH2)
#define MEM_WIDTH (0x1<<WIDTH2)

unsigned char mem[MEM_DEPTH][MEM_WIDTH];
unsigned char mem_ptr;	// 内存分配指针

void tl_init(void)
{
	mem_ptr = 0;
}

// 在内存池中申请size大小的内存
// 通过ptr回传申请内存的首地址
// 成功返回0
int tl_malloc(unsigned short size, void **ptr)
{
	unsigned char d=size>>WIDTH2;
	if(d) mem_ptr += d;
	else mem_ptr += 1;
	mem_ptr &= (MEM_DEPTH-1);
	*ptr = mem[mem_ptr];
	return 0;
}

// 释放掉ptr对应的node所占用空间
int tl_free(void *ptr)
{
	return 0;
}

