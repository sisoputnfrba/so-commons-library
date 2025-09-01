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
UPDATE=apt-get update
INSTALL=apt-get install -y
OPENSSL=libssl-dev
else ifneq ($(shell which dnf 2>/dev/null),)
UPDATE=dnf check-update
INSTALL=dnf install -y
OPENSSL=openssl-devel
else ifneq ($(shell which yum 2>/dev/null),)
UPDATE=yum check-update
INSTALL=yum install -y
OPENSSL=openssl-devel
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
	$(SUDO) $(UPDATE)
	$(SUDO) $(INSTALL) $(OPENSSL)

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
