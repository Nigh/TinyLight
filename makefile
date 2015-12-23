
objects = TinyLight.o sample.o
VPATH = TinyLight
.PHONY : clear run
# vpath %.c TinyLight
# vpath %.h TinyLight


compile: $(objects)
	gcc $(objects) -o test.exe

clear: 
	del $(objects)
	del *.exe

run: compile
	mingw32-make clear
	mingw32-make compile
	test.exe

sample.o: 
	gcc -c ./TinyLight/TinyLight.c sample.c

TinyLight.o: ./TinyLight/TinyLight.h ./TinyLight/tl_mem.o ./TinyLight/tl_dispatch.o
	gcc -c ./TinyLight/TinyLight.c ./TinyLight/TinyLight.h
tl_mem.o:
	gcc -c ./$(VPATH)/tl_mem.c ./$(VPATH)/tl_mem.h

tl_dispatch.o:
	gcc -c ./$(VPATH)/tl_dispatch.c ./$(VPATH)/tl_dispatch.h

