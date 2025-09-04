RM=rm -rf
CC=gcc

C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
H_SRCS=$(shell find . -iname "*.h" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)

ifneq ($(shell id -un),root)
SUDO=sudo
endif

DEPS=openssl/evp.h

define check_deps
  $(shell echo '#include <$(1)>' | $(CC) -E -xc - > /dev/null 2>&1 || echo "$(1)")
endef

MISSING_DEPS=$(strip $(foreach hdr,$(DEPS),$(call check_deps,$(hdr))))

ifneq ($(MISSING_DEPS),)
$(error Missing dependencies: $(MISSING_DEPS). See README.md for dependency setup.)
endif

# Clean and compile .so
all: build/libcommons.so

build/commons/collections:
	mkdir -p $@

build/libcommons.so: build/commons/collections $(OBJS)
	$(CC) -shared -o "$@" $(OBJS)

build/%.o: %.c | $(DEPS)
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
	$(SUDO) cp -u build/libcommons.so /usr/lib
	$(SUDO) cp --parents -u $(H_SRCS) /usr/include

uninstall:
	$(SUDO) rm -f /usr/lib/libcommons.so
	$(SUDO) rm -rf /usr/include/commons

.PHONY: all debug sources clean install uninstall

.PRECIOUS: $(DEPS)
