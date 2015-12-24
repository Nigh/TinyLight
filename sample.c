
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
	printf("printNodes:\n");
	#define this (TinyLight.mem->node[idx])
	do{
		printNode(idx);
	}while( idx=this.next );
	#undef this
}

void test(void)
{
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
