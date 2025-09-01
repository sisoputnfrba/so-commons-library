RM=rm -rf
CC=gcc

C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
H_SRCS=$(shell find . -iname "*.h" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)
DEPS=/usr/include/openssl/evp.h

ifneq ($(shell id -un),root)
SUDO=sudo
endif

ifneq ($(shell which apt-get 2>/dev/null),)
OPENSSL=apt-get update && apt-get install -y libssl-dev
else ifneq ($(shell which dnf 2>/dev/null),)
OPENSSL=dnf install -y openssl-devel
else ifneq ($(shell which yum 2>/dev/null),)
OPENSSL=yum install -y openssl-devel
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

# Install OpenSSL development package with apt, dnf or yum
/usr/include/openssl/%.h:
	$(SUDO) $(OPENSSL)

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
