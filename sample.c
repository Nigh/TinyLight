
#include <stdio.h>
#include "./TinyLight/TinyLight.h"

int main(int argc, char const *argv[])
{
	TinyLight.init();
	printf("%s %s",TinyLight.getName(),TinyLight.getVersion());
	printf("\n");
	printf(TinyLight.str1());
	printf(TinyLight.str2());
	return 0;
}

void test(void)
{
	
}
