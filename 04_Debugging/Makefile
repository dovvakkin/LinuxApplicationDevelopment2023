YELLOW := \033[1;33m
RESET := \033[0m

FORMATTER := $(shell which clang-format)
CC := clang

all: format range

format: .clang-format
ifdef FORMATTER
	$(FORMATTER) --style=file -i range.c
else
	@echo "$(YELLOW)No formatter found. Skipping formatting.$(RESET)"
endif

range: range.c
	$(CC) range.c -O0 -g -o range

test: range test/test.sh 
	bash test/test.sh

clean:
	rm -f range *.out
