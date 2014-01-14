RM=rm -rf
CC=gcc

C_SRCS=./commons/txt.c ./commons/process.c ./commons/temporal.c ./commons/log.c ./commons/string.c ./commons/config.c ./commons/bitarray.c ./commons/error.c ./commons/collections/list.c ./commons/collections/dictionary.c ./commons/collections/queue.c

OBJS=build/commons/txt.o build/commons/process.o build/commons/temporal.o build/commons/log.o build/commons/string.o build/commons/config.o build/commons/bitarray.o build/commons/error.o build/commons/collections/list.o build/commons/collections/dictionary.o build/commons/collections/queue.o

all: build/libcommons.so

create-dirs:
	mkdir -p build/commons
	mkdir -p build/commons/collections

build/libcommons.so: create-dirs $(OBJS)
	$(CC) -shared -o "build/libcommons.so" $(OBJS)

build/commons/%.o: commons/%.c
	$(CC) -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
build/commons/collections/%.o: commons/collections/%.c
	$(CC) -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build


.PHONY: all create-dirs clean