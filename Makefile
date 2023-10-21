all: clean run

clean:
	rm -rf build/*

run: build/lz.img
	qemu-system-i386 -fda build/lz.img

build/lz.img: build/bootstrap.bin build/kernel.bin
	cat build/bootstrap.bin > build/lz.img
	truncate --size 2048 build/lz.img
	
	cat build/kernel.bin >> build/lz.img

build/%.bin: src/%/main.s
	nasm $< -o $@

bochs-debug: clean build/lz.img
	bochs -f bochs_config_debug

bochs: clean build/lz.img
	bochs -f bochs_config

commit: clean build/lz.img
	bash ./commit.sh $(V)