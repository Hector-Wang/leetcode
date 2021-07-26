
cc := gcc
srcs = $(wildcard *.c)  
objs = $(patsubst %c, %o, $(srcs))  
cflags = -fsanitize=address -O1 -fno-omit-frame-pointer -g -lm

all: $(objs)
	@echo Generating target file a.out...done!
	$(cc) $(cflags) -o a.out $(objs)
	@rm -f *.o

%.o : %.c
	@echo compiling $<...done!
	$(cc) -c $(cflags) -o $@ $<

.PHONY: clean
clean:
	rm -f *.o *.out

