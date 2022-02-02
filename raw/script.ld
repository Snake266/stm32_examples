/*. Entry Point */

ENTRY( Reset_Handler )

/* Memories definition */
MEMORY
{
  RAM (xrw)     : ORIGIN = 0x20000000, LENGTH = 20K
  ROM (rx)      : ORIGIN = 0x8000000, LENGTH = 128K
}

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);     /* end of RAM */

/* Sections */
SECTIONS
{
 .isr_vector : {
    KEEP(*(.isr_vector))
 } >ROM
  /* The program code and other data into ROM memory */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
  } >ROM

  /* Constant data into ROM memory*/
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
  } >ROM

  _sidata = LOADADDR(.data);
  /* Initialized data sections into RAM memory */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)           /* .data sections */
    . = ALIGN(4);
    _edata = .;
  } >RAM AT> ROM


  /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    /* *(COMMON) */

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    /* __bss_end__ = _ebss; */
  } >RAM

}
