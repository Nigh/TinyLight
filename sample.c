
#include <stdio.h>
#include "./TinyLight/TinyLight.h"
#include "./dispatch_example.h"

void mem_test(void)
{
	unsigned char* ptr1;
	unsigned char* ptr2;
	unsigned char* ptr3;
	unsigned char* ptr4;
	unsigned char* ptr5;
	unsigned char* ptr6;
	printf("------------------------mem_test:-------------------------\n");
	printf("ret=%d\n",tl_malloc(11,(void*)&ptr1));
	printf("ret=%d\n",tl_malloc(11,(void*)&ptr2));
	printf("ret=%d\n",tl_malloc(13,(void*)&ptr3));
	printf("ret=%d\n",tl_malloc(113,(void*)&ptr4));
	printf("ret=%d\n",tl_malloc(53,(void*)&ptr5));
	printf("ret=%d\n",tl_malloc(121,(void*)&ptr6));
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
	dispatch_test();
	return 0;
}
