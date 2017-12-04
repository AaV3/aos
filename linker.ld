
ENTRY(Reset_Handler)

MEMORY
{
    flash(rx) : ORIGIN = 0x00000000, LENGTH =   1M
    ram(wx)   : ORIGIN = 0x20000000, LENGTH = 128K
}

_stack_top = 0x20000000+128*1024;

SECTIONS
{
    . = 0;
    
    .text :
    {
        /* Startup code must go at address 0 */
        KEEP(*(.isr_vector))
        *(.text)
        . = ALIGN(4);
        *(.rodata)
    } > flash

    . = ALIGN(8);
    _etext = .;

    .data :
    {
        _data = .;
        *(.data)
        . = ALIGN(8);
        _edata = .;
    } > ram AT > flash

    _bss_start = .;
    .bss :
    {
        *(.bss)
        . = ALIGN(8);
    } > ram
    _bss_end = .;

    _end = .;
}
