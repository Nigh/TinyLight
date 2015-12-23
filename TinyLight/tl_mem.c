

#include "tl_mem.h"

typedef enum sNodeType
{
	NT_FREE,
	NT_USED
}eNODE_TYPE;

static struct sMEM_QUEUE
{
	struct sMEM_POOL
	{
		unsigned char pool[2<<TL_POOL_SIZE];
	}ram;
	// warning:node[0]不要使用
	// 因为此LL使用了unsigned char作为索引
	// 0在这里起到了一个显式的NULL的作用
	// length为0的node会在gc中被释放掉
	struct sMEM_NODE
	{
		eNODE_TYPE type;		// node所指向的内存类型
		unsigned short offset;	// node所指向的内存偏移
		unsigned short length;	// node所占用的内存长度(对齐后的长度)
		unsigned char next,prev;	// LL双向索引
	}node[NODE_LENGTH];
	unsigned char head;	// head of LL
	unsigned char tail;	// tail of LL
	unsigned char length;	// length of LL
	bool isInit;
}tl_mem={0};

void tl_init(void)
{
	tl_mem.head=1;
	tl_mem.tail=1;
	tl_mem.length=1;

	tl_mem.node[1]=(struct sMEM_NODE){NT_FREE,0,2<<TL_POOL_SIZE,0,0};
	tl_mem.isInit=true;
}

// 在LL尾部增加一个node
// 若成功则返回node地址
// 否则返回NULL
struct sMEM_NODE* tl_mem_node_add(void)
{
	// 如果LL为空
	if(tl_mem.head==0){
		tl_mem.head=1;
		tl_mem.tail=1;
		return &(tl_mem.node[1]);
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
					return &(tl_mem.node[_]);
				}
				_+=1;
			}
		}
	}
	return NULL;
}

// 删除一个node并将其所占用空间与邻近的空闲node进行合并
// 若成功则返回0
// 否则返回错误代码
int tl_mem_node_free(struct sMEM_NODE* node)
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
	return 0;
}

// 垃圾回收
// 合并相邻的空闲node
void tl_mem_gc(void)
{
	// unsigned char node_idx=tl_mem.head;
	// if(node_idx==1 && tl_mem.node[1].type==NT_FREE) return;
	// do {
	// 	if(tl_mem.node[node_idx].length==0){
	// 		tl_mem_node_free(&tl_mem.node[node_idx]);
	// 		node_idx=tl_mem.node[node_idx].next;
	// 	}
	// } while(tl_mem.node[node_idx].next>0);
}

// 从指定空闲node中分配node
void tl_node_malloc(unsigned short size,unsigned char idx)
{
	// 将当前node空间收缩至于需求匹配
	// 插入新的空闲node管理剩余空间(如果有)
}

// 在内存池中申请size大小的内存
// 成功返回0
int tl_malloc(unsigned short size,void** ptr)
{
	unsigned char unalign=size & (sizeof(long)-1);
	// 内存对齐
	if(unalign > 0){
		size+=unalign-sizeof(long);
	}
	// 执行gc
	tl_mem_gc();
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

int tl_free(unsigned short size,void** ptr)
{
	
}

