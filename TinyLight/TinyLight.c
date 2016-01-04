
#include "TinyLight.h"


static int isAvaliable(void);
CONST_STR(str1,"test01\n");
CONST_STR(str2,"test02\n");
CONST_STR(version,"v0.9.5");
CONST_STR(name,"TinyLight");

#define self TL

static void init(void)
{
	self.memq=tl_init();
	self.str1=str1;
	self.str2=str2;
	self.getVersion=version;
	self.getName=name;

	self.mem.init=tl_init;
	self.mem.malloc=tl_malloc;
	self.mem.free=tl_free;

	self.task.new=tl_taskNew;
	self.task.insert=tl_taskInsert;
	self.task.exec=tl_taskExec;
	self.task.dispatch=tl_taskDispatch;
}

static int isAvaliable(void)
{
	return 1;
}
#undef self

struct TINYLIGHT_STRUCT TL={.init=init};

