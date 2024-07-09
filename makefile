all:
	-cd src && $(MAKE) all
	-cd tests/unit-tests && $(MAKE) all

clean:
	-cd src && $(MAKE) clean
	-cd tests/unit-tests && $(MAKE) clean

debug:
	-cd src && $(MAKE) debug
	-cd tests/unit-tests && $(MAKE) debug

test: all
	cd tests/unit-tests && $(MAKE) test

install: test
	-cd src && $(MAKE) install

uninstall:
	-cd src && $(MAKE) uninstall

valgrind: debug
	cd tests/unit-tests && $(MAKE) valgrind

docs: | /usr/local/share/doxygen-awesome-css/
	doxygen

/usr/local/share/doxygen-awesome-css/:
	curl -fsSL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.3.3.tar.gz | tar -xz
	sudo make install -C doxygen-awesome-css-*
	rm -rf doxygen-awesome-css-*

.PHONY: all clean debug test install uninstall valgrind docs
