SRCS := Doxyfile $(shell find ../src/commons -name "*.h") ../README.md

all: html

clean:
	rm -rf html

serve: all
	python3 -m http.server -d html

watch:
	echo "$(SRCS)" | tr ' ' '\n' | entr -r make serve

.PHONY: all clean serve watch

html: $(SRCS)
	doxygen
