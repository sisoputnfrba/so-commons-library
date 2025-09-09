RM=rm -rf
CC=gcc

BASE_DIR=../..

COMMONS=$(BASE_DIR)/src
COMMONS_BIN=$(COMMONS)/build
COMMONS_SO=$(COMMONS_BIN)/libcommons.so
COMMONS_SRCS=$(patsubst ./%,$(COMMONS)/%,$(shell make --no-print-directory -C $(COMMONS) sources))

C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)
DEPS=/usr/include/cspecs/cspec.h

BIN_DIR=build
BIN=$(BIN_DIR)/commons-unit-test

all: $(BIN)

$(BIN_DIR):
	mkdir -p $@

$(BIN): $(COMMONS_SO) $(BIN_DIR) $(OBJS)
	$(CC) -L"$(COMMONS_BIN)" -o "$@" $(OBJS) -lcommons -lcspecs

build/%.o: ./%.c | $(DEPS)
	$(CC) -I"$(COMMONS)" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

/usr/include/cspecs/%.h:
	$(eval TMP := $(shell mktemp -d))
	curl -fsSL "https://github.com/mumuki/cspec/archive/043089d9c55871526f1d6728af4d0febdbe8c38a.tar.gz" \
		| tar -xzC $(TMP) --strip-components=1
	$(MAKE) --no-print-directory -C $(TMP) install
	$(RM) $(TMP)

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build

test: all
	LD_LIBRARY_PATH="$(COMMONS_BIN)" ./$(BIN)

$(COMMONS_SO): $(COMMONS_SRCS)
	-cd $(COMMONS) && $(MAKE) all

valgrind: debug
	LD_LIBRARY_PATH="$(COMMONS_BIN)" valgrind --error-exitcode=42 --leak-check=full -v ./$(BIN)

.PHONY: all debug clean test valgrind

.PRECIOUS: $(DEPS)
