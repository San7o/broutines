include test/make.config

CFLAGS:=$(CFLAGS) -Wall -Werror -Wconversion -Wpedantic -ggdb
TEST_OBJS?=
CC?=gcc

.PHONY: clean

tests: $(TEST_OBJS)
	@echo " * [CC] tests"
	@$(CC) $(TEST_OBJS) -o tests

.c.o:
	@echo " * [CC] $@"
	@$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

all: check

check: # compile and run the tests
check: tests
	@chmod +x tests
	@./tests

clean: # clean the project
	@rm tests test/*.o test/*.d || :
