absolute 0xE000

drive_num: resb 1

buffer0: resb 16
buffer1: resb 16
buffer2: resb 16
buffer3: resb 16

large_buffer0: resb 512
large_buffer1: resb 512

absolute 0xE820

kernel_memmap_size: resw 1
kernel_memmap: resb 1024