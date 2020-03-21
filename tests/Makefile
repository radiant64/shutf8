CFLAGS += -std=c89 -g

.PHONY : all
all : test_shutf8

.PHONY : run_tests
run_tests : test_shutf8
	./test_shutf8

test_shutf8 : test_shutf8.o test_decode_codepoint.o
	$(CC) -std=c89 -o $@ -g $^

test_decode_codepoint.o : shtest.h ../shutf8.h

.PHONY: clean
clean :
	rm -f test_shutf8 test_shutf8.o test_decode_codepoint.o

