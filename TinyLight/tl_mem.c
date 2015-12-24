

#include "tl_mem.h"

sMEM_QUEUE tl_mem={0};

sMEM_QUEUE* tl_init(void)
{
	tl_mem.head=1;
	tl_mem.tail=1;
	tl_mem.length=1;

	tl_mem.node[1]=(sMEM_NODE){NT_FREE,0,2<<TL_POOL_SIZE,0,0};
	tl_mem.isInit=true;

	return &tl_mem;
}

// 在LL尾部增加一个node
// 若成功则返回node idx
// 否则返回0
unsigned char tl_mem_node_add(void)
{
	// 如果LL为空
	if(tl_mem.head==0){
		tl_mem.head=1;
		tl_mem.tail=1;
		return 1;
	}
	// 如果LL不满
	if(tl_mem.length<NODE_LENGTH-1){
		// 搜索空node
		{
			unsigned char i=0;
			unsigned char _=tl_mem.tail+1;
			while(i++<NODE_LENGTH){
				if(_>=NODE_LENGTH)_=1;
				if(tl_mem.node[_].length==0){
					tl_mem.node[tl_mem.tail].next=_;
					tl_mem.node[_].prev=tl_mem.tail;
					tl_mem.node[_].next=0;
					tl_mem.tail=_;
					return _;
				}
				_+=1;
			}
		}
	}
	return 0;
}

// 删除一个node
int tl_mem_node_del(sMEM_NODE* node)
{
	if(node->next>0){
		tl_mem.node[node->next].prev=node->prev;
	}else{
		// 是LL尾
		tl_mem.tail=node->prev;
	}
	node->length=0;
	if(node->prev>0){
		tl_mem.node[node->prev].next=0;
	}else{
		// 是LL头
		tl_mem.head=node->next;
	}
}

// 将一个node所占用空间释放，并与邻近的空闲node进行合并
// 若成功则返回0
// 否则返回错误代码
int tl_mem_node_free(sMEM_NODE* node)
{
	// 当前node空间标记为free
	node->type = NT_FREE;

	// 检查后向邻近node
	if(tl_mem.node[node->next].length>0 && tl_mem.node[node->next].type==NT_FREE){
		node->length+=tl_mem.node[node->next].length;
		tl_mem_node_del(&(tl_mem.node[node->next]));
	}

	// 检查前向邻近node
	if(tl_mem.node[node->prev].length>0 && tl_mem.node[node->prev].type==NT_FREE){
		tl_mem.node[node->prev].length+=node.length;
		tl_mem_node_del(node);
	}
	return 0;
}

// 垃圾回收
// 合并相邻的空闲node
void tl_mem_gc(void)
{
	unsigned char node_idx=tl_mem.head;
	while(tl_mem.node[node_idx].next>0){
		if(tl_mem.node[node_idx].length>0 && tl_mem.node[node_idx].type==NT_FREE){
			tl_mem_node_free(&(tl_mem.node[node_idx]));
		}
		node_idx = tl_mem.node[node_idx].next;
	}
}

// 从指定空闲node中分配node
void tl_node_malloc(unsigned short size,unsigned char idx)
{
	unsigned short free_after=tl_mem.node[idx].length-size;
	unsigned char _;
	// 将当前node空间收缩至匹配需求
	tl_mem.node[idx].length = size;
	tl_mem.node[idx].type = NT_USED;
	// 插入新的空闲node管理剩余空间(如果有)
	if(free_after==0) return;
	_=tl_mem_node_add();
	if(_==0){
		// 插入node失败，应当捕获
	}
	tl_mem.node[_].offset = tl_mem.node[idx].offset + size;
	tl_mem.node[_].length = free_after;
	tl_mem.node[_].type = NT_FREE;
}

// 在内存池中申请size大小的内存,并传入指针的引用
// 成功返回0
int tl_malloc(unsigned short size,void** ptr)
{
	unsigned char unalign=size & (sizeof(long)-1);
	// 内存对齐
	if(unalign > 0){
		size+=sizeof(long)-unalign;
	}
	// 执行gc
	// tl_mem_gc();
	// 搜索空闲内存
	{
		unsigned char idx=tl_mem.tail;
		if( (tl_mem.node[idx].type!=NT_FREE) || (tl_mem.node[idx].length<size) ){
			idx = tl_mem.head;
			while(idx>0 && idx!=tl_mem.tail){
				idx = tl_mem.node[idx].next;
				if( (tl_mem.node[idx].type==NT_FREE) && (tl_mem.node[idx].length>=size) ){
					tl_node_malloc(size,idx);
					*ptr=&(tl_mem.ram.pool[tl_mem.node[idx].offset]);
					return 0;
				}
			}
			return -1;
		}else{
			tl_node_malloc(size,idx);
			*ptr=&(tl_mem.ram.pool[tl_mem.node[idx].offset]);
			return 0;
		}
	}
	return -1;
}

// 遍历LL,释放掉ptr对应的node
int tl_free(void** ptr)
{


}

