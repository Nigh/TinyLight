
#include "tl_dispatch.h"
#include "tl_mem.h"


static void* taskHead=NULL;

sTASK* tl_taskNew(fTask* func,unsigned short size)
{
	// 申请空间
	sTASK* pTask;
	// tl_malloc(size,(void*)&(task->content));
	tl_malloc(size+sizeof(sTASK),(void*)&pTask);
	// 方法attach
	pTask->func = func;
	// 将content指针指向content内容头部
	pTask->content = (void*)pTask+sizeof(sTASK);
	return pTask;
}

int tl_taskInsert(sTASK* task)
{
	sTASK *pTask=taskHead;
	if(taskHead!=NULL){
		while(pTask->next!=NULL) pTask=pTask->next;
		pTask->next = task;
	}else{
		// 由空建立新任务
		taskHead = (void*)task;
	}
	task->next = NULL;
	return 0;
}

int tl_taskExec(sTASK* task)
{
	task->func(task->content);
	taskHead = task->next;
	tl_free((void*)task);
	if(taskHead==NULL){
		return -1;	// 队列空
	}
	return 0;
}

int tl_taskDispatch(void)
{
	if(taskHead!=NULL){
		return tl_taskExec((sTASK*)taskHead);
	}
	return -2;	// 无任务执行
}
