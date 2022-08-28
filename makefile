BUILD_DIR=build
CMAKE_BUILD_TYPE=Release
INSTALL_PREFIX=/usr

ifneq ($(shell id -un),root)
SUDO=sudo
endif

all: | $(BUILD_DIR)
	cd $(BUILD_DIR); cmake --build .

$(BUILD_DIR):
	cmake -S . -B $@ -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX)

clean:
	rm -rf $(BUILD_DIR)

debug: CMAKE_BUILD_TYPE = Debug
debug: all

test: all
	cd $(BUILD_DIR)/tests/unit-tests; ./commons-unit-test

install: test
	cd $(BUILD_DIR); $(SUDO) make install

uninstall:
	$(SUDO) rm -vf /usr/lib/libcommons.so
	$(SUDO) rm -rvf /usr/include/commons

valgrind: debug
	cd $(BUILD_DIR)/tests/unit-tests; valgrind --error-exitcode=42 --leak-check=full -v ./commons-unit-test

.PHONY: all clean debug test install uninstall valgrind
