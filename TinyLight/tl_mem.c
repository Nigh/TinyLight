
#include "tl_mem.h"

sMEM_QUEUE tl_mem = {0};

sMEM_QUEUE *tl_init(void)
{
	tl_mem.head = &(tl_mem.ram.pool[0]);
	tl_mem.tail = &(tl_mem.ram.pool[0]);
	tl_mem.length = 1;
	tl_mem.isInit = true;
	((sMEM_NODE*)(tl_mem.tail))->type = NT_FREE;
	((sMEM_NODE*)(tl_mem.tail))->offset = 0;
	((sMEM_NODE*)(tl_mem.tail))->length = 2<<TL_POOL_SIZE;
	((sMEM_NODE*)(tl_mem.tail))->prev = tl_mem.tail;
	((sMEM_NODE*)(tl_mem.tail))->next = tl_mem.tail;
	return &tl_mem;
}

// 垃圾回收
// 合并相邻的空闲node
void tl_gc(void)
{
	sMEM_NODE *pNode = tl_mem.head;
	do{
		if(pNode->type == NT_FREE){
			// 后向搜索合并
			while ( (void*)(pNode->next) > (void*)pNode && ((sMEM_NODE *)(pNode->next))->type == NT_FREE ) {
				((sMEM_NODE *)((sMEM_NODE *)(pNode->next))->next)->prev = pNode;
				pNode->length += ((sMEM_NODE *)(pNode->next))->length;
				pNode->next = ((sMEM_NODE *)(pNode->next))->next;
			}
			// 前向搜索合并
			// while ( (void*)pNode > (void*)(pNode->prev) && ((sMEM_NODE *)(pNode->prev))->type == NT_FREE ) {
			// 	pNode = (sMEM_NODE *)(pNode->prev);
			// 	((sMEM_NODE *)((sMEM_NODE *)(pNode->next))->next)->prev = pNode;
			// 	pNode->length += ((sMEM_NODE *)(pNode->next))->length;
			// 	pNode->next = ((sMEM_NODE *)(pNode->next))->next;
			// }
		}
	}while( (pNode = pNode->next) != tl_mem.head );
}

// 在内存池中申请size大小的内存
// 通过ptr回传申请内存的首地址
// 成功返回0
int tl_malloc(unsigned short size, void **ptr)
{
	unsigned short free_after;
	sMEM_NODE *pNode = (sMEM_NODE *)tl_mem.head;
	sMEM_NODE *pNodeNew;
	size += _ALIGN_L(sizeof(sMEM_NODE));
	size = _ALIGN_L(size);
	// 执行gc
	// tl_mem_gc();
	// 搜索空闲内存
	while ( (pNode->type != NT_FREE) || (pNode->length < size) ) {
		pNode = pNode->next;
		if (pNode == tl_mem.head) {
			return -1;	// 申请失败
		}
	}
	// 如果剩余碎片太小，不足存放1个node，则合并至当前node
	free_after = pNode->length - size;
	if (free_after <= _ALIGN_L(sizeof(sMEM_NODE))) {
		size += _ALIGN_L(sizeof(sMEM_NODE));
		free_after = 0;
	}
	// 管理剩余空间
	if (free_after > 0) {
		pNodeNew = (sMEM_NODE*)((char*)pNode + size);
		pNodeNew->type = NT_FREE;
		pNodeNew->length = free_after;
		pNodeNew->next = pNode->next;
		pNodeNew->prev = (void *)pNode;
		pNode->next = pNodeNew;
		((sMEM_NODE *)(pNodeNew->next))->prev = pNodeNew;
		tl_mem.tail = pNodeNew;
	}
	pNode->type = NT_USED;
	pNode->length = size;
	*ptr = (void *)((char*)pNode + _ALIGN_L(sizeof(sMEM_NODE)));
	return 0;
}

// 释放掉ptr对应的node所占用空间
int tl_free(void *ptr)
{
	sMEM_NODE *nodePtr = (sMEM_NODE *)((char*)ptr - _ALIGN_L(sizeof(sMEM_NODE)));
	if(nodePtr->type != NT_FREE && nodePtr->type != NT_USED){
		return -1;
	}
	nodePtr->type = NT_FREE;
	return 0;
}

