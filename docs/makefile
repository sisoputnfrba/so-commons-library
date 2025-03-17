SRCS := $(shell find . -not -path "./build**") $(shell find ../src/commons -name "*.h") ../README.md

all: build

clean:
	rm -rf build

serve: all
	python3 -m http.server -d build/html

watch:
	echo "$(SRCS)" | tr ' ' '\n' | entr -r make serve

.PHONY: all clean serve watch

build: $(SRCS)
	doxygen
	echo "var menudata = $$(cat navbar.config.json);" > build/html/menudata.js
