BUILD_DIR=build
CMAKE_BUILD_TYPE=Release
INSTALL_PREFIX=/usr

ifneq ($(shell id -un),root)
SUDO=sudo
endif

all: | $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -S . -B $@ -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX)

clean:
	rm -rf $(BUILD_DIR)

debug: CMAKE_BUILD_TYPE = Debug
debug: all

test: all
	ctest --test-dir $(BUILD_DIR) --extra-verbose -R commons-unit-test

install: test
	$(SUDO) cmake --install $(BUILD_DIR)

uninstall:
	$(SUDO) rm -vf /usr/lib/libcommons.so
	$(SUDO) rm -rvf /usr/include/commons

valgrind: debug
	ctest --test-dir $(BUILD_DIR) --extra-verbose -R commons-unit-test-valgrind

.PHONY: all clean debug test install uninstall valgrind
