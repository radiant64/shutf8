OBJECTS = test_shutf8.o test_decode_alloc.o test_decode_codepoint.o\
		  test_encode_alloc.o test_encode_codepoint.o test_step.o

CFLAGS += -std=c89 -g

.PHONY : all
all : test_shutf8

.PHONY : run_tests
run_tests : test_shutf8
	./test_shutf8

test_shutf8 : shutf8.o $(OBJECTS)
	$(CC) -std=c89 -o $@ -g $^

shutf8.o : ../shutf8.c ../shutf8.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJECTS) : tesht.h ../shutf8.h

test_decode_alloc.o : test_decode_alloc.h
test_decode_codepoint.o : test_decode_codepoint.h
test_encode_alloc.o : test_encode_alloc.h
test_encode_codepoint.o : test_encode_codepoint.h
test_step.o : test_step.h

.PHONY: clean
clean :
	rm -f test_shutf8 $(OBJECTS)

