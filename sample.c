
#include <stdio.h>
#include "./TinyLight/TinyLight.h"
#include "./dispatch_example.h"


void printNode(sMEM_NODE *node)
{
	printf("Node[0x%x]:\n",(unsigned long)node);
	printf("Type:");
	if(node->type==NT_FREE) printf("Free\n");
	else printf("Used\n");
	// printf("Offset:%d\n",node->offset);
	printf("length:%d\n",node->length);
	printf("[0x%x]<--[0x%x]-->[0x%x]\n\n",node->prev,node,node->next);
}

// 打印所有node信息
void printNodes(int n)
{
	sMEM_NODE *pNode = TL.memq->tail;
	int i=0;
	printf("------------------------printNodes[%d]:-------------------------\n",n);
	do{
		printNode(pNode);
		printf("0x%x\n", TL.memq->tail);
	}while( i++<10 && (pNode = pNode->next) != TL.memq->tail );
}

#define freePrint(x) printf("free(0x%x)\nret=%d\n",x-_ALIGN_L(sizeof(sMEM_NODE)),tl_free((void*)x))
void mem_test(void)
{
	unsigned char* ptr1;
	unsigned char* ptr2;
	unsigned char* ptr3;
	unsigned char* ptr4;
	unsigned char* ptr5;
	unsigned char* ptr6;
	printf("------------------------mem_test:-------------------------\n");
	printNodes(1);
	printf("ret=%d\n",tl_malloc(111,(void*)&ptr1));
	printf("ret=%d\n",tl_malloc(11,(void*)&ptr2));
	printf("ret=%d\n",tl_malloc(131,(void*)&ptr3));
	printf("ret=%d\n",tl_malloc(1131,(void*)&ptr4));
	printf("ret=%d\n",tl_malloc(531,(void*)&ptr5));
	printNodes(2);
	freePrint(ptr2);
	printNodes(3);
	freePrint(ptr3);
	printNodes(4);
	printf("ret=%d\n",tl_malloc(121,(void*)&ptr6));
	printNodes(5);
	freePrint(ptr1);
	printNodes(6);
	freePrint(ptr4);
	printNodes(7);
	freePrint(ptr5);
	printNodes(8);
	freePrint(ptr6);
	printNodes(8);
}

void dispatch_test(void)
{
	// sMEM_POOL* temp;
	printf("------------------------dispatch_test:-------------------------\n");
	// printf("size=%d\n",sizeof(*temp));
	taskAdd_example();
	
}

int main(int argc, char const *argv[])
{
	TL.init();
	printf("%s %s",TL.getName(),TL.getVersion());
	printf("\n");
	mem_test();
	// dispatch_test();
	return 0;
}
