
#include "TinyLight.h"

#define CONST_STR(n,str); static char* n(void) {return str;}


static int isAvaliable(void);
CONST_STR(str1,"test01\n");
CONST_STR(str2,"test02\n");
CONST_STR(version,"beta 0.1");
CONST_STR(name,"TinyLight");

#define self TinyLight

static void init(void)
{
	self.str1=str1;
	self.str2=str2;
	self.getVersion=version;
	self.getName=name;
}

static int isAvaliable(void)
{
	return 1;
}
#undef self

struct TINYLIGHT_STRUCT TinyLight={.init=init};
