
SRC_FILES = $(shell find support/ \( -name '*.h' -o -name '*.c' \))
MD_FILES = $(shell find support/ -name '*.md')

doc: doc/html/index.html
doc/html/index.html: Doxyfile $(SRC_FILES) $(MD_FILES)
	@test -d doc || mkdir -p doc
	doxygen > /dev/null

tools:
	cd tool && make all

tests:
	cd test && make all

lines:
	wc -l $(SRC_FILES)| sort -n -k1
