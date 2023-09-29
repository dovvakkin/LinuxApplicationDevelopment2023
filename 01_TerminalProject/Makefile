YELLOW := \033[1;33m
RESET := \033[0m

FORMATTER := $(shell which clang-format)
CC := clang

all: format show

format: .clang-format
ifdef FORMATTER
	$(FORMATTER) --style=file -i Show.c
else
	@echo "$(YELLOW)No formatter found. Skipping formatting.$(RESET)"
endif

show: Show.c
	$(CC) Show.c -lncurses -o Show

clean:
	rm Show
