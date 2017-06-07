
MAKE?=make

SRC_FILES = $(shell find support/ include/ \( -name '*.h' -o -name '*.c' -o -name '*.mk' \)) README.md
MD_FILES = $(shell find support/ -name '*.md')

doc: doc/html/index.html
doc/html/index.html: Doxyfile $(SRC_FILES) $(MD_FILES)
	@test -d doc || mkdir -p doc
	doxygen > /dev/null

init:
	git submodule init
	git submodule update
	
tools:
	cd tool && $(MAKE) all

tests:
	cd test && $(MAKE) all

lines:
	@wc -l $(SRC_FILES)| sort -n -k1

checks:
	find . -type f -exec file {} \; | grep "CRLF line terminators" | awk -F ':' '{ print $1 }'
