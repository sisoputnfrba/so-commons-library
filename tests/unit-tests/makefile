RM=rm -rf
CC=gcc

BASE_DIR=../..

COMMONS=$(BASE_DIR)/src
COMMONS_BIN=$(COMMONS)/build
COMMONS_SO=$(COMMONS_BIN)/libcommons.so
COMMONS_SRCS=$(patsubst ./%,$(COMMONS)/%,$(shell make --no-print-directory -C $(COMMONS) sources))

C_SRCS=$(wildcard *.c)
OBJS=$(C_SRCS:%.c=build/%.o)

BIN_DIR=build
BIN=$(BIN_DIR)/commons-unit-test

CSPEC_REPO=https://github.com/mumuki/cspec
CSPEC_VERSION=043089d9c55871526f1d6728af4d0febdbe8c38a
CSPEC=$(BIN_DIR)/cspec-$(CSPEC_VERSION)
CSPEC_BIN=$(CSPEC)/release
CSPEC_SO=$(CSPEC_BIN)/libcspecs.so

all: $(BIN)

$(BIN_DIR):
	mkdir -p $@

$(BIN): $(COMMONS_SO) $(OBJS) | $(BIN_DIR) $(CSPEC_SO)
	$(CC) -L"$(COMMONS_BIN)" -L"$(CSPEC_BIN)" -o "$@" $(OBJS) -lcommons -lcspecs

build/%.o: ./%.c $(CSPEC_SO) | $(BIN_DIR)
	$(CC) -I"$(COMMONS)" -I"$(CSPEC)" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build

test: all
	LD_LIBRARY_PATH="$(COMMONS_BIN):$(CSPEC_BIN)" ./$(BIN)

$(COMMONS_SO): $(COMMONS_SRCS)
	-cd $(COMMONS) && $(MAKE) all

$(CSPEC_SO): $(CSPEC)
	$(MAKE) -C $(CSPEC)

$(CSPEC): | $(BIN_DIR)
	curl -fsSL "$(CSPEC_REPO)/archive/$(CSPEC_VERSION).tar.gz" | tar -xzC $(BIN_DIR)

valgrind: debug
	LD_LIBRARY_PATH="$(COMMONS_BIN):$(CSPEC_BIN)" valgrind --error-exitcode=42 --leak-check=full -v ./$(BIN)

.PHONY: all debug clean test valgrind
