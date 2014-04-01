RM=rm -rf
CC=gcc

C_SRCS=./main.c

OBJS=build/main.o

all: build/commons-integration-test-logger

create-dirs:
	mkdir -p build/.

build/commons-integration-test-logger: dependents create-dirs $(OBJS)
	$(CC) -L"../../../src/build" -o "build/commons-integration-test-logger" $(OBJS) -lcommons -lpthread

build/%.o: ./%.c
	$(CC) -I"../../../src" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build

dependents:
	-cd ../../../src/ && $(MAKE) all

.PHONY: all create-dirs clean
