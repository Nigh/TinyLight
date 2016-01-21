
#include "tl_dispatch.h"
#include "tl_mem.h"

static void *taskHead = NULL;
static void *taskTail = NULL;

sTASK *tl_taskNew(fTask *func, unsigned short size)
{
	// 申请空间
	sTASK *pTask;
	// tl_malloc(size,(void*)&(task->content));
	tl_malloc(size, (void *)&pTask);
	// 方法attach
	pTask->func = func;
	// 将content指针指向content内容头部
	pTask->content = (char *)pTask + sizeof(sTASK);
	return pTask;
}

int tl_taskInsert(sTASK *task)
{
	if (taskTail != NULL) {
		((sTASK *)(taskTail))->next = (void *)task;
		taskTail = task;
	} else {
		// 由空建立新任务
		taskHead = (void *)task;
		taskTail = (void *)task;
	}
	task->next = NULL;
	return 0;
}

int tl_taskExec(sTASK *task)
{
	task->func(task->content);
	taskHead = task->next;
	tl_free((void *)task);
	if (taskHead == NULL) {
		taskTail = NULL;
		return -1;	// 队列空
	}
	return 0;
}

int tl_taskDispatch(void)
{
	if (taskHead != NULL) {
		return tl_taskExec((sTASK *)taskHead);
	}
	return -2;	// 无任务执行
}
