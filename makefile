
VPATH = TinyLight
objects = TinyLight.o sample.o dispatch_example.o ./$(VPATH)/tl_mem.o ./$(VPATH)/tl_dispatch.o
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
	rm -f ./$(VPATH)/*.o

run: compile
	mingw32-make clear
	mingw32-make compile
	test.exe

sample.o: TinyLight.o dispatch_example.o
	gcc -c sample.c

dispatch_example.o: dispatch_example.h TinyLight.o
	gcc -c dispatch_example.c dispatch_example.h
TinyLight.o: ./$(VPATH)/TinyLight.h ./$(VPATH)/tl_mem.o ./$(VPATH)/tl_dispatch.o
	gcc -c ./$(VPATH)/TinyLight.c ./$(VPATH)/TinyLight.h
tl_mem.o:
	gcc -c ./$(VPATH)/tl_mem.c ./$(VPATH)/tl_mem.h
tl_dispatch.o:
	gcc -c ./$(VPATH)/tl_dispatch.c ./$(VPATH)/tl_dispatch.h

