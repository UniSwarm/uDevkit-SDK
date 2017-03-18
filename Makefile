
SRC_FILES = $(shell find support/ include/ \( -name '*.h' -o -name '*.c' -o -name '*.mk' \))
MD_FILES = $(shell find support/ -name '*.md')

doc: doc/html/index.html
doc/html/index.html: Doxyfile $(SRC_FILES) $(MD_FILES)
	@test -d doc || mkdir -p doc
	doxygen > /dev/null

init:
	git submodule init
	git submodule update
	
tools:
	cd tool && make all

tests:
	cd test && make all

lines:
	@wc -l $(SRC_FILES)| sort -n -k1
