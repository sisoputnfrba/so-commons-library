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

serve: docs
	cd build/html && python3 -m http.server

docs: | doxygen-awesome-css
	doxygen

doxygen-awesome-css:
	mkdir -p doxygen-awesome-css
	curl -fsSL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.3.3.tar.gz \
		| tar -xvzC doxygen-awesome-css --wildcards --strip-components=1 'doxygen-awesome-css-*/doxygen-awesome*'

.PHONY: all clean debug test install uninstall valgrind serve docs
