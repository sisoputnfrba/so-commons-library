RM=rm -rf
CC=gcc

C_SRCS=./test_queue.c ./tests.c ./test_dictionary.c ./test_string.c ./test_bitarray.c ./test_config.c ./test_list.c

OBJS=build/test_queue.o build/tests.o build/test_dictionary.o build/test_string.o build/test_bitarray.o build/test_config.o build/test_list.o

all: build/commons-unit-test

create-dirs:
	mkdir -p build/.

build/commons-unit-test: dependents create-dirs $(OBJS)
	$(CC) -L"../../src/build" -o "build/commons-unit-test" $(OBJS) -lcommons -lcunit

build/%.o: ./%.c
	$(CC) -I"../../src" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build

dependents:
	-cd ../../src/ && $(MAKE) all

.PHONY: all create-dirs clean
