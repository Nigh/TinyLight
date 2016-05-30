
#include <stdio.h>
#include "dispatch_example.h"


void printTime(sTIME* content)
{
	printf("%02d:%02d:%02d\n",content->hour,content->min,content->sec);
}

void taskAdd_example(void)
{
	// sTASK* pTask = tl_taskNews((fTask*)printTime,sTIME);
	sTASK* pTask;
	int i=0,p=0;
	while(p++<6){
		while(i++<6){
			pTask = tl_taskNew((fTask*)printTime,(sizeof(sTIME)+sizeof(sTASK)));
			((sTIME*)(pTask->content))->hour = 14;
			tl_taskInsert(pTask);
			printf("taskAddr=0x%lx\n",(unsigned long)pTask);

			pTask = tl_taskNew((fTask*)printTime,(sizeof(sTIME)+sizeof(sTASK)));
			((sTIME*)(pTask->content))->min = 16;
			tl_taskInsert(pTask);
			printf("taskAddr=0x%lx\n",(unsigned long)pTask);

			pTask = tl_taskNew((fTask*)printTime,(sizeof(sTIME)+sizeof(sTASK)));
			((sTIME*)(pTask->content))->sec = 55;
			tl_taskInsert(pTask);
			printf("taskAddr=0x%lx\n",(unsigned long)pTask);

			printf("ret=%d\n",tl_taskDispatch());
		}
		do{
			i=tl_taskDispatch();
			printf("ret=%d\n",i);
		}while(i>-2);
	}
}


