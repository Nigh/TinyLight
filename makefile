
objects = TinyLight.o sample.o
VPATH = TinyLight
.PHONY : clear run
# vpath %.c TinyLight
# vpath %.h TinyLight

clear: 
	del $(objects)
	del *.exe

compile: $(objects)
	gcc $(objects) -o test.exe

run: compile
	mingw32-make clear
	mingw32-make compile
	test.exe

sample.o: 
	gcc -c ./TinyLight/TinyLight.c sample.c

TinyLight.o: ./TinyLight/TinyLight.h
	gcc -c ./TinyLight/TinyLight.c ./TinyLight/TinyLight.h
