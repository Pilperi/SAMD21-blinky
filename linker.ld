/*
Linker-skripti SAMD21-perheen tuotteille, muokattu lähteestä
https://github.com/fduignan/samd20_examples/tree/master/Blinky
(https://ioprog.com/2018/04/08/bare-metal-blinky-on-the-samd20/ Bare metal blinky)

Ottaa interrupt-vektorin osoitteet ja funktiomääritelmät init.o:sta,
ja kaiken muun koodin main.o:sta. Datat kaikista, mikäli tarjolla.
.o-tiedostojen kuuluu olla build-kansion alla.

Näiden kasaamiseen on hyvä dokumentti esim.:
https://users.informatik.haw-hamburg.de/~krabat/FH-Labor/gnupro/5_GNUPro_Utilities/c_Using_LD/ldLinker_scripts.html
*/

/* Muistirakenne, vaihtelee mallin mukaan */
MEMORY
{
    flash : org = 0x00000000, len = 256k
    ram : org = 0x20000000, len = 32k
}

SECTIONS
{
    /* Suoritettava koodi */
	. = ORIGIN(flash);
        .text : {
		  build/init.o(.vectors); /* Koodin alussa interruptiosoitteet ymv */
		  build/init.o(.text);    /* Interruptien handlerit alkuun */
		  build/main.o(.text);    /* Vasta sitten itse funktiot */
        } >flash
	/* Alustettu data */
    . = ORIGIN(ram);
        .data : {
	  INIT_DATA_VALUES = LOADADDR(.data);
	  INIT_DATA_START = .;
	    build/*(.data);
	  INIT_DATA_END = .;
	  . = ALIGN(4);
        } >ram AT>flash
	/* Alustamaton data */
    BSS_START = .;
	.bss : {	  
	    build/*(.bss);
	    . = ALIGN(4);
	} > ram
	BSS_END = .;
}
