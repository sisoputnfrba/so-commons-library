RM=rm -rf
CC=gcc

C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)

all: build/commons-unit-test

create-dirs:
	mkdir -p build

build/commons-unit-test: dependents create-dirs $(OBJS)
	$(CC) -L"../../src/build" -o "build/commons-unit-test" $(OBJS) -lcommons -lcunit

build/%.o: ./%.c
	$(CC) -I"../../src" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build

test: all
	LD_LIBRARY_PATH=../../src/build/ build/commons-unit-test

dependents:
	-cd ../../src/ && $(MAKE) all

.PHONY: all create-dirs clean
