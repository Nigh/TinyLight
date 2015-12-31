
#ifndef TL_DISPATCH_H
#define TL_DISPATCH_H


// int tl_taskAdd(fTask* func,struct*)
#define tl_taskNews(A,B) tl_taskNew((A),(sizeof(B)+sizeof(sTASK)))

typedef void fTask(void*);
typedef struct sTasks
{
	fTask* func;
	void* next;
	void* content;
}sTASK;

sTASK* tl_taskNew(fTask* func,unsigned short size);
int tl_taskInsert(sTASK* task);
int tl_taskExec(sTASK* task);
int tl_taskDispatch(void);

#endif

