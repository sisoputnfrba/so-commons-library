RM=rm -rf
CC=gcc

BASE_DIR=../..

C_SPEC=$(BASE_DIR)/cspec
C_SPEC_BIN=$(C_SPEC)/release
C_SPEC_SO=$(C_SPEC_BIN)/libcspecs.so

COMMONS=$(BASE_DIR)/src
COMMONS_BIN=$(COMMONS)/build
COMMONS_SO=$(COMMONS_BIN)/libcommons.so
COMMONS_SRCS=$(patsubst ./%,$(COMMONS)/%,$(shell make --no-print-directory -C $(COMMONS) sources)) 

C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)

BIN_DIR=build
BIN=$(BIN_DIR)/commons-unit-test

all: $(BIN)

$(BIN_DIR):
	mkdir -p $@

$(BIN): $(C_SPEC_SO) $(COMMONS_SO) $(BIN_DIR) $(OBJS)
	$(CC) -L"$(COMMONS_BIN)" -L"$(C_SPEC_BIN)" -o "$@" $(OBJS) -lcommons -lcspecs

build/%.o: ./%.c
	$(CC) -I"$(COMMONS)" -I"$(C_SPEC)" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build

test: all
	LD_LIBRARY_PATH="$(COMMONS_BIN):$(C_SPEC_BIN)" ./$(BIN)

$(COMMONS_SO): $(COMMONS_SRCS)
	-cd $(COMMONS) && $(MAKE) all

$(C_SPEC_SO):
	-cd $(BASE_DIR) && git submodule init && git submodule update
	-cd $(C_SPEC) && $(MAKE) all

valgrind: debug
	LD_LIBRARY_PATH="$(COMMONS_BIN)/:$(C_SPEC_BIN)" valgrind --error-exitcode=42 --leak-check=full -v ./$(BIN)

.PHONY: all debug clean test valgrind
