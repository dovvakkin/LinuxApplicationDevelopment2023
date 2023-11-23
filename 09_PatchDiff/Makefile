YELLOW := \033[1;33m
RESET := \033[0m

FORMATTER := $(shell which clang-format)
CC := clang

all: format range

format: .clang-format
ifdef FORMATTER
	$(FORMATTER) --style=file -i *.c
else
	@echo "$(YELLOW)No formatter found. Skipping formatting.$(RESET)"
endif

run: lbrnt lbrnt_size lbrnt_walls_size lbrnt_stable_random_walls_size
	./lbrnt
	./lbrnt_size 4
	./lbrnt_walls_size ' +' 5
	./lbrnt_stable_random_walls_size 42 '01' 3

lbrnt: lbrnt.c
	CC lbrnt.c -o lbrnt

lbrnt_size: lbrnt_size.c
	CC lbrnt_size.c -o lbrnt_size

lbrnt_walls_size: lbrnt_walls_size.c
	CC lbrnt_walls_size.c -o lbrnt_walls_size

lbrnt_stable_random_walls_size: lbrnt_stable_random_walls_size.c
	CC lbrnt_stable_random_walls_size.c -o lbrnt_stable_random_walls_size

lbrnt_size.c: lbrnt.c patch/size.patch
	cp lbrnt.c lbrnt_size.c
	patch lbrnt_size.c < patch/size.patch

lbrnt_walls_size.c: lbrnt_size.c patch/walls_size.patch
	cp lbrnt_size.c lbrnt_walls_size.c
	patch lbrnt_walls_size.c < patch/walls_size.patch

lbrnt_stable_random_walls_size.c: lbrnt_walls_size.c patch/stable_random_walls_size.patch
	cp lbrnt_walls_size.c lbrnt_stable_random_walls_size.c
	patch lbrnt_stable_random_walls_size.c < patch/stable_random_walls_size.patch

clean:
	rm -f lbrnt lbrnt_*
