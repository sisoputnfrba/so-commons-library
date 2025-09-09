RM=rm -rf
CC=gcc

TAD=temporal
BIN=build/commons-integration-test-$(TAD)

C_SRCS=./main.c
OBJS=build/main.o

all: $(BIN)

run:
	LD_LIBRARY_PATH="../../../src/build" ./$(BIN)

valgrind:
	LD_LIBRARY_PATH="../../../src/build" valgrind ./$(BIN)

create-dirs:
	mkdir -p build/.

$(BIN): dependents create-dirs $(OBJS)
	$(CC) -L"../../../src/build" -o "$(BIN)" $(OBJS) -lcommons -lpthread

build/%.o: ./%.c
	$(CC) -I"../../../src" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build

dependents:
	-cd ../../../src/ && $(MAKE) all

.PHONY: all create-dirs clean
