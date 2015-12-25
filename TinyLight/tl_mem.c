

#include "tl_mem.h"

sMEM_QUEUE tl_mem = {0};

sMEM_QUEUE *tl_init(void)
{
	tl_mem.head = &(tl_mem.ram.pool);
	tl_mem.tail = &(tl_mem.ram.pool);
	tl_mem.length = 1;
	tl_mem.isInit = true;
	((sMEM_NODE*)(tl_mem.tail))->prev = tl_mem.tail;
	((sMEM_NODE*)(tl_mem.tail))->next = tl_mem.tail;
	return &tl_mem;
}

// 垃圾回收
// 合并相邻的空闲node
// void tl_mem_gc(void)
// {
// 	unsigned char node_idx = tl_mem.head;
// 	while (tl_mem.node[node_idx].next > 0) {
// 		if (tl_mem.node[node_idx].length > 0 && tl_mem.node[node_idx].type == NT_FREE) {
// 			tl_mem_node_free(&(tl_mem.node[node_idx]));
// 		}
// 		node_idx = tl_mem.node[node_idx].next;
// 	}
// }

// 在内存池中申请size大小的内存
// 通过ptr回传申请内存的首地址
// 成功返回0
int tl_malloc(unsigned short size, void **ptr)
{
	unsigned char unalign;
	unsigned short free_after;
	sMEM_NODE *pNode = (sMEM_NODE *)tl_mem.tail;
	sMEM_NODE *pNodeNew;
	size += sizeof(sMEM_NODE);
	unalign = size & (sizeof(long) - 1);
	// 内存对齐
	if (unalign > 0) {
		size += sizeof(long) - unalign;
	}
	// 执行gc
	// tl_mem_gc();
	// 搜索空闲内存
	while ( (pNode->type != NT_FREE) || (pNode->length < size) ) {
		pNode = (sMEM_NODE *)pNode->next;
		if (pNode == (sMEM_NODE *)tl_mem.tail) {
			return -1;	// 申请失败
		}
	}
	// 如果剩余碎片太小，不足存放1个node，则合并至当前node
	free_after = pNode->length - size;
	if (free_after <= sizeof(sMEM_NODE)) {
		size += sizeof(sMEM_NODE);
		free_after = 0;
	}
	// 管理剩余空间
	if (free_after > 0) {
		pNodeNew = (sMEM_NODE *)(pNode + pNode->length);
		pNodeNew->type = NT_FREE;
		pNodeNew->length = free_after;
		pNodeNew->next = pNode->next;
		pNodeNew->prev = (void *)pNode;
		pNode->next = pNodeNew;
		tl_mem.tail = pNodeNew;
	}
	pNode->type = NT_USED;
	pNode->length = size;
	*ptr = (void *)(pNode + sizeof(sMEM_NODE));
	return 0;
}

// 释放掉ptr对应的node所占用空间
int tl_free(void **ptr)
{
	sMEM_NODE *nodePtr = (*ptr - sizeof(sMEM_NODE));
	nodePtr->type = NT_FREE;

	// 后向搜索合并
	if ( nodePtr->next != nodePtr && ((sMEM_NODE *)(nodePtr->next))->type == NT_FREE ) {
		nodePtr->length += ((sMEM_NODE *)(nodePtr->next))->length;
		nodePtr->next = ((sMEM_NODE *)(nodePtr->next))->next;
	}

	// 前向搜索合并
	if ( (nodePtr)->prev != nodePtr && ((sMEM_NODE *)(nodePtr->prev))->type == NT_FREE ) {
		((sMEM_NODE *)(nodePtr->prev))->length += nodePtr->length;
		((sMEM_NODE *)(nodePtr->prev))->next = nodePtr->next;
	}
}

