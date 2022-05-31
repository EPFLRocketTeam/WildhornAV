ENTRY(main)

SECTIONS
{
	. = 0x82000000;

	.head : {*(.head)}

	.text : {*(.text)}
	.data : {*(.data)}

	.bss : {
		__bss_start = .;
		*(.bss)
	}
	_end = .;
}
