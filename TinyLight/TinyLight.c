
#include "TinyLight.h"



#define NODE_LENGTH (64)
static struct sMEM_QUEUE
{
	struct sMEM_POOL
	{
		unsigned char pool[2<<TL_POOL_SIZE];
		bool isInit;
	}pool;
	// warning:node[0]不要使用
	// 因为此LL使用了unsigned char作为索引
	// 0在这里起到了一个显式的NULL的作用
	// length为0的node会在gc中被释放掉
	struct sMEM_NODE
	{
		unsigned short offset;	// node所指向的内存偏移
		unsigned char length;	// node所占用的内存长度(对齐后的长度)
		unsigned char next,prev;	// LL双向索引
	}node[NODE_LENGTH];
	unsigned char head;	// head of LL
	unsigned char tail;	// tail of LL
	unsigned char length;	// length of LL
}tl_mem={0};

// 在LL尾部增加一个node
// 若成功则返回node地址
// 否则返回NULL
void* tl_mem_node_add(void)
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

// 删除一个node并释放所占用的内存
// 若成功则返回0
// 否则返回错误代码
int tl_mem_node_del(void* node)
{
	node=(struct sMEM_NODE*)node;
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

int tl_malloc(unsigned int size,void** ptr)
{
	if((size & (sizeof(int)-1)) > 0){
		size+=size&(sizeof(int)-1);
	}
	return 0;
}

int tl_free(unsigned int size,void** ptr)
{
	
}

static int isAvaliable(void);
CONST_STR(str1,"test01\n");
CONST_STR(str2,"test02\n");
CONST_STR(version,"beta 0.1");
CONST_STR(name,"TinyLight");

#define self TinyLight

static void init(void)
{
	self.str1=str1;
	self.str2=str2;
	self.getVersion=version;
	self.getName=name;
}

static int isAvaliable(void)
{
	return 1;
}
#undef self

struct TINYLIGHT_STRUCT TinyLight={.init=init};

