_stack_base = 0x20005000;

MEMORY
{
	flash	(rx)	: ORIGIN = 0x08000000, LENGTH = 128K
	ram		(xrw)	: ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{

	.text :
	{
		*(.text)
		*(.text*)
	} > flash

	.rodata :
	{
		*(.rodata)
		*(.rodata*)
	} > flash

	_InitDataStart = LOADADDR(.data);

	.data :
	{
		_DataStart = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_DataEnd = .;
	} > ram AT > flash

	.bss :
	{
		_BssStart = .;
		*(.bss)
		*(.bss*)
		. = ALIGN(4);
		_BssEnd = .;
	} > ram

}


