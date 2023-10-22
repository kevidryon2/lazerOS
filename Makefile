all: clean run

CC="i686-linux-gnu-gcc-12"
STRIP="i686-linux-gnu-strip"
OBJCOPY="i686-linux-gnu-objcopy"

clean:
	rm -rf build/*

run: build/lz.img
	qemu-system-i386 -fda build/lz.img

build/lz.img: build/bootstrap.bin build/kernel.bin
	dd if=/dev/zero of=build/lz.img bs=1K count=1440
	
	dd if=build/bootstrap.bin of=build/lz.img conv=notrunc
	dd if=build/kernel.bin of=build/lz.img conv=notrunc bs=512 seek=4

build/kernel.bin:
	$(CC) src/kernel/*.c -o build/kernel -ffunction-sections -T src/kernel/kernel.ld \
										-nostartfiles -m32 -fno-pie -O0 -fdefer-pop \
										-fomit-frame-pointer -foptimize-sibling-calls \
										-fno-inline -finline-small-functions \
										-fmerge-all-constants -fno-function-cse \
										-Wl,-z,norelro -march=i386 -mfpmath=387 -nostdlib \
										-Wpedantic -nodefaultlibs
										
	$(CC) src/kernel/*.c -o build/kernel_debug -ffunction-sections -T src/kernel/kernel.ld \
										-nostartfiles -m32 -fno-pie -O0 -g -fdefer-pop \
										-fomit-frame-pointer -foptimize-sibling-calls \
										-fno-inline -finline-small-functions \
										-fmerge-all-constants -fno-function-cse \
										-Wl,-z,norelro -march=i386 -mfpmath=387 -nostdlib \
										-nodefaultlibs -Wpedantic
	
	$(STRIP) build/kernel   -R .comment -R .dynamic -R .eh_frame_hdr \
							-R .gnu.hash -R .dyn* -R .rel.dyn -R .eh_frame \
							-R .interp -R .note.gnu.build-id -R .plt
	
	mkdir build/sect
	$(OBJCOPY) build/kernel build/kernel.bin -O binary
	#$(OBJCOPY) build/kernel build/sect/start.bin -j .start -O binary
	#$(OBJCOPY) build/kernel build/sect/text.bin -j .text.* -O binary
	#$(OBJCOPY) build/kernel build/sect/rodata.bin -j .rodata -O binary
	#$(OBJCOPY) build/kernel build/sect/data.bin -j .data -O binary
	#$(OBJCOPY) build/kernel build/sect/sdata.bin -j .sdata -O binary
	
	#cat build/sect/start.bin > build/kernel.bin
	#cat build/sect/text.bin >> build/kernel.bin
	#cat build/sect/rodata.bin >> build/kernel.bin
	#cat build/sect/data.bin >> build/kernel.bin
	#cat build/sect/sdata.bin >> build/kernel.bin

build/%.bin: src/%/main.s
	nasm $< -o $@
	
burn: clean build/lz.img
	dd if=build/lz.img of=/dev/sdb

bochs-debug: clean build/lz.img
	bochs -f bochs_config_debug

bochs: clean build/lz.img
	bochs -f bochs_config

commit: clean build/lz.img
	bash ./commit.sh $(V)
	
push:
	git push -u codeberg master
	git push -u github master