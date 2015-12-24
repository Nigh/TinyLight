
objects = TinyLight.o sample.o ./TinyLight/tl_mem.o ./TinyLight/tl_dispatch.o
VPATH = TinyLight
.PHONY : clear run
# vpath %.c TinyLight
# vpath %.h TinyLight

top:
	make clear
	make compile

tinylight:
	

compile: $(objects)
	gcc $(objects) -o debug.out

clear: 
	rm -f $(objects)
	rm -f *.out
	rm -f ./TinyLight/*.o

run: compile
	mingw32-make clear
	mingw32-make compile
	test.exe

sample.o: TinyLight.o
	gcc -c sample.c

TinyLight.o: ./TinyLight/TinyLight.h ./TinyLight/tl_mem.o ./TinyLight/tl_dispatch.o
	gcc -c ./TinyLight/TinyLight.c ./TinyLight/TinyLight.h
tl_mem.o:
	gcc -c ./$(VPATH)/tl_mem.c ./$(VPATH)/tl_mem.h
tl_dispatch.o:
	gcc -c ./$(VPATH)/tl_dispatch.c ./$(VPATH)/tl_dispatch.h

