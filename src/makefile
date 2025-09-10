RM=rm -rf
CC=gcc
DEPS=openssl

C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
H_SRCS=$(shell find . -iname "*.h" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)

ifneq ($(shell id -un),root)
SUDO=sudo
endif

# Clean and compile .so
all: build/libcommons.so

build/commons/collections:
	mkdir -p $@

build/libcommons.so: build/commons/collections $(OBJS)
	$(CC) $(shell pkg-config --libs $(DEPS)) -shared -o "$@" $(OBJS)

build/%.o: %.c
ifeq ($(shell pkg-config --exists $(DEPS); echo $$?),0)
	$(CC) $(shell pkg-config --cflags $(DEPS)) -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
else
	$(error "Dependencies not found. Please check README.md for installation instructions.")
endif

# Add debug parameters and compile
debug: CC += -DDEBUG -g
debug: all

# Print all sources
sources:
	@echo $(C_SRCS) $(H_SRCS)

# Clean build files
clean:
	$(RM) build

install: all
	$(SUDO) cp -u build/libcommons.so /usr/lib
	$(SUDO) cp --parents -u $(H_SRCS) /usr/include

uninstall:
	$(SUDO) rm -f /usr/lib/libcommons.so
	$(SUDO) rm -rf /usr/include/commons

.PHONY: all debug sources clean install uninstall
