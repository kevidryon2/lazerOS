ENTRY( start )
SECTIONS
{
	. = 0x8400;
	.start : { *(.text.start) }
	.text : { *(.text) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	.sdata : { *(.data) }
}