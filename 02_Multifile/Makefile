GENERATES = prog prog-a prog-so *.a *.so README
TRASH = *.o *~ o.* __test*
CFLAGS = -Wall
ARFLAGS = rcs
GREEN = \033[0;32m
RESET = \033[0m

all: test

test: __test-no-arg __test-1-arg __test-3-args

__test-no-arg: prog prog-a prog-so
	$(shell ./prog 2>&1 | sed 's/prog//g' > $@_prog)
	$(shell ./prog-a 2>&1 | sed 's/prog-a//g' > $@_prog_a)
	$(shell LD_LIBRARY_PATH=`pwd` ./prog-so 2>&1 | sed 's/prog-so//g' > $@_prog_so)
	@cmp $@_prog $@_prog_a
	@cmp $@_prog_so $@_prog_a
	@echo "$(GREEN)$@ passed$(RESET)"

__test-1-arg: prog prog-a prog-so
	$(shell ./prog 1 > $@_prog)
	$(shell ./prog-a 1 > $@_prog_a)
	$(shell LD_LIBRARY_PATH=`pwd` ./prog-so 1 > $@_prog_so)
	@cmp $@_prog $@_prog_a
	@cmp $@_prog_so $@_prog_a
	@echo "$(GREEN)$@ passed$(RESET)"

__test-3-args: prog prog-a prog-so
	$(shell ./prog 1 1 1 > $@_prog)
	$(shell ./prog-a 1 1 1 > $@_prog_a)
	$(shell LD_LIBRARY_PATH=`pwd` ./prog-so 1 1 1 > $@_prog_so)
	@cmp $@_prog $@_prog_a
	@cmp $@_prog_so $@_prog_a
	@echo "$(GREEN)$@ passed$(RESET)"

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	$(CC) $(CFLAGS) -L. -loutput_static $< -o $@

prog-so: prog.o liboutput.so
	$(CC) $(CFLAGS) -L. -loutput $< -o $@

liboutput.so: fun.o const.o
	$(CC) $(CFLAGS) -shared $^ -o $@

liboutput_static.a: fun.o const.o
	 $(AR) $(ARFLAGS) $@ $^

README:  prog
	./$< 2> $@

fun.o:   outlib.h

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
