MAKE=make
.PHONY : all example lib clean dep


all: lib example

example:
	cd example && $(MAKE)

lib:
	cd src && $(MAKE)

clean:
	cd src && $(MAKE) clean
	cd example && $(MAKE) clean

dep:
	cd src && $(MAKE) dep
	cd example && $(MAKE) dep






