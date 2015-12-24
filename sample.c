
#include <stdio.h>
#include "./TinyLight/TinyLight.h"


void printNode(unsigned char idx)
{
	#define this (TinyLight.mem->node[idx])
	printf("Node[%d]:\n",idx);
	printf("Type:");
	if(this.type==NT_FREE) printf("Free\n");
	else printf("Used\n");
	printf("Offset:%d\n",this.offset);
	printf("length:%d\n",this.length);
	printf("[%02d]<--[%02d]-->[%02d]\n\n",this.prev,idx,this.next);
	#undef this
}

// 打印所有node信息
void printNodes(void)
{
	unsigned char idx=1;
	printf("------------------------printNodes:-------------------------\n");
	#define this (TinyLight.mem->node[idx])
	do{
		printNode(idx);
	}while( idx=this.next );
	#undef this
}

unsigned char pool[128];

void test(void)
{
	unsigned char* ptr1=pool;
	unsigned char* ptr2=pool;
	unsigned char* ptr3=pool;
	unsigned char* ptr4=pool;
	printNodes();
	tl_malloc(111,&ptr1);
	*ptr1=1;
	printNodes();
	tl_malloc(121,&ptr2);
	*ptr2=2;
	printNodes();
	tl_malloc(131,&ptr3);
	*ptr3=3;
	printNodes();
	tl_malloc(132,&ptr4);
	*ptr4=4;
	printNodes();
}

int main(int argc, char const *argv[])
{
	TinyLight.init();
	printf("%s %s",TinyLight.getName(),TinyLight.getVersion());
	printf("\n");
	test();
	return 0;
}
