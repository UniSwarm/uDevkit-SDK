
tools:
	@test -d build/ || mkdir -p build/
	cd tool && make all