CFLAGS += -std=c89

.PHONY : all
all : test_shutf8

.PHONY : run_tests
run_tests : test_shutf8
	./test_shutf8

test_shutf8 : ../shutf8.h shtest.h test_shutf8.o
	$(CC) -std=c89 -o $@ -g test_shutf8.o

.PHONY: clean
clean :
	rm -f test_shutf8 test_shutf8.o

