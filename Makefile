.PHONY: clean build

DOCKER := $(shell which docker)

all: build

docker:
	${DOCKER} build -t gendev .

build:
	${DOCKER} run --rm -it -v $(PWD):/game gendev make -f /opt/gendev/sgdk/mkfiles/makefile.gen all

clean:
	${DOCKER} run --rm -it -v $(PWD):/game gendev make -f /opt/gendev/sgdk/mkfiles/makefile.gen clean
	rm src/boot/rom_head.h
	rm src/boot/sega.s