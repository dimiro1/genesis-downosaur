.PHONY: clean build run

all: build

docker:
	docker build -t gendev .

run:
	blastem out/rom.bin 320 224

build:
	docker run --rm -it -v $(PWD):/game gendev make -f /opt/gendev/sgdk/mkfiles/makefile.gen all

clean:
	docker run --rm -it -v $(PWD):/game gendev make -f /opt/gendev/sgdk/mkfiles/makefile.gen clean
	rm -f src/boot/rom_head.h
	rm -f src/boot/sega.s