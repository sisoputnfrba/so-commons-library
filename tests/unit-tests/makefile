RM=rm -rf
CC=gcc

C_SPEC=../../cspec
C_SPEC_BIN=$(C_SPEC)/release

C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)

all: build/commons-unit-test

create-dirs:
	mkdir -p build

build/commons-unit-test: dependents create-dirs $(OBJS)
	$(CC) -L"../../src/build" -L"$(C_SPEC_BIN)" -o "build/commons-unit-test" $(OBJS) -lcommons -lcspecs

build/%.o: ./%.c
	$(CC) -I"../../src" -I"$(C_SPEC)" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build

test: all
	LD_LIBRARY_PATH="../../src/build/:$(C_SPEC_BIN)" build/commons-unit-test

dependents: install-cspec
	-cd ../../src/ && $(MAKE) all

install-cspec:
	-cd ../../ && git submodule init && git submodule update
	-cd ../../cspec && $(MAKE) all

.PHONY: all create-dirs clean install-cspec
