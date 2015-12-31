
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
void printNodes(void)
{
	sMEM_NODE *pNode = TinyLight.mem->head;
	printf("------------------------printNodes:-------------------------\n");
	do{
		printNode(pNode);
	}while( (pNode = pNode->next) != TinyLight.mem->head );
}

void mem_test(void)
{
	unsigned char* ptr1;
	unsigned char* ptr2;
	unsigned char* ptr3;
	unsigned char* ptr4;
	unsigned char* ptr5;
	unsigned char* ptr6;
	printf("------------------------mem_test:-------------------------\n");
	printNodes();
	printf("ret=%d\n",tl_malloc(111,(void*)&ptr1));
	printf("ret=%d\n",tl_malloc(11,(void*)&ptr2));
	printf("ret=%d\n",tl_malloc(131,(void*)&ptr3));
	printf("ret=%d\n",tl_malloc(1131,(void*)&ptr4));
	printf("ret=%d\n",tl_malloc(531,(void*)&ptr5));
	printNodes();
	printf("ret=%d\n",tl_free((void*)ptr2));
	printNodes();
	printf("ret=%d\n",tl_free((void*)ptr3));
	printNodes();
	printf("ret=%d\n",tl_malloc(121,(void*)&ptr6));
	printNodes();
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
	TinyLight.init();
	printf("%s %s",TinyLight.getName(),TinyLight.getVersion());
	printf("\n");
	// mem_test();
	dispatch_test();
	return 0;
}
