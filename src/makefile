RM=rm -rf
CC=gcc
DEST=/usr

ifeq ($(shell uname -s),Linux)
    CC=gcc
    CP=cp
    DEST=/usr
else ifeq ($(shell uname -s),Darwin)
    CC=gcc-14
    CP=gcp
    DEST=/usr/local
else
    $(error 'OS not supported!')
endif

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
	$(CC) -shared -o "$@" $(OBJS)

build/%.o: %.c
	$(CC) -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

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
	$(SUDO) $(CP) -u build/libcommons.so $(DEST)/lib
	$(SUDO) $(CP) --parents -u $(H_SRCS) $(DEST)/include

uninstall:
	$(SUDO) rm -f $(DEST)/lib/libcommons.so
	$(SUDO) rm -rf $(DEST)/include/commons

.PHONY: all debug sources clean install uninstall
