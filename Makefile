C_SRCS = ./src/commons/bitarray.c \
  ./src/commons/config.c \
  ./src/commons/error.c \
  ./src/commons/log.c \
  ./src/commons/string.c \
  ./src/commons/txt.c \
  ./src/commons/process.c \
  ./src/commons/temporal.c \
  ./src/commons/collections/dictionary.c \
  ./src/commons/collections/list.c \
  ./src/commons/collections/queue.c

OBJS = ./build/src/commons/bitarray.o \
  ./build/src/commons/config.o \
  ./build/src/commons/error.o \
  ./build/src/commons/log.o \
  ./build/src/commons/string.o \
  ./build/src/commons/txt.o \
  ./build/src/commons/process.o \
  ./build/src/commons/temporal.o \
  ./build/src/commons/collections/dictionary.o \
  ./build/src/commons/collections/list.o \
  ./build/src/commons/collections/queue.o

TEST_SRCS = ./tests/unit-tests/test_bitarray.c \
  ./tests/unit-tests/test_string.c \
  ./tests/unit-tests/test_queue.c \
  ./tests/unit-tests/test_config.c \
  ./tests/unit-tests/tests.c \
  ./tests/unit-tests/test_dictionary.c \
  ./tests/unit-tests/test_list.c

TEST_OBJS = ./build/tests/unit-tests/test_bitarray.o \
  ./build/tests/unit-tests/test_string.o \
  ./build/tests/unit-tests/test_queue.o \
  ./build/tests/unit-tests/test_config.o \
  ./build/tests/unit-tests/tests.o \
  ./build/tests/unit-tests/test_dictionary.o \
  ./build/tests/unit-tests/test_list.o


all: build/libcommons.so test

# TODO: provide release target

# TODO: rename as debug
build/libcommons.so: create-dirs $(OBJS)
	gcc -shared -Wall -o "build/libcommons.so" $(OBJS) -pthread

build/src/commons/%.o: ./src/commons/%.c
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

# TODO: include this target in previous one?
build/src/commons/collections/%.o: ./src/commons/collections/%.c
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

create-dirs:
	mkdir -p build/src/commons/collections

test: build/test-commons
	LD_LIBRARY_PATH=${PWD}/build build/test-commons

build/test-commons: create-test-dirs $(TEST_OBJS)
	gcc -L"./build/" -Wall -o "build/test-commons" $(TEST_OBJS) -lcommons -lcunit -pthread

build/tests/unit-tests/%.o: ./tests/unit-tests/%.c
	gcc -I"./src/" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

create-test-dirs:
	mkdir -p build/tests/unit-tests

clean:
	rm -rf build

.PHONY: all create-dirs clean test create-test-dirs