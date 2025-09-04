all:
	cd src && $(MAKE) all
	cd tests/unit-tests && $(MAKE) all

clean:
	cd src && $(MAKE) clean
	cd tests/unit-tests && $(MAKE) clean
	cd docs && $(MAKE) clean

debug:
	cd src && $(MAKE) debug
	cd tests/unit-tests && $(MAKE) debug

test: all
	cd tests/unit-tests && $(MAKE) test

install: test
	cd src && $(MAKE) install

uninstall:
	cd src && $(MAKE) uninstall

valgrind: debug
	cd tests/unit-tests && $(MAKE) valgrind

docs:
	cd docs && $(MAKE) all

.PHONY: all clean debug test install uninstall valgrind docs
