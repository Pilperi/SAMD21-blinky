/*
SAMD21 initti, muokattu lähteestä
https://github.com/fduignan/samd20_examples/tree/master/Blinky
(https://ioprog.com/2018/04/08/bare-metal-blinky-on-the-samd20/ Bare metal blinky)
ja lisätty kommentteja selventämään kuviota.
*/

/* Funktioprototyypit, main mapataan linkkerivaiheessa main.c main-funktioon */
void init(void);
void Default_Handler(void);
int main(void);

/*
  Kasa kutsuosotteita eri interrupteille, käytännössä lista funktiopointtereita.
  Menee pikkasen eri tavalla kuin AVR-assemblyssä,
  hommaa avattu esim. https://stackoverflow.com/a/68035664 (erit top of stack)
  ja tosi pitkä selitys ät
  https://interrupt.memfault.com/blog/arm-cortex-m-exceptions-and-nvic
  
  Lyhyesti:
  ---------
  Jos interrupti on laitettu aktiiviseksi, tapahtuman sattuessa hypätään tässä
  taulukossa oikean rivin kohdalle ja katsotaan mitä pitää tehdä.
  Ja yleensä halutaan tehdä niin että hypätään johonkin erilliseen
  funktioon joka tekee jotain. Esim. jos halutaan että aina kun
  Timer Counter 0 menee täyteen (n kellosykliä kulunut), vilautetaan lediä,
  laitetaan tuohon riville 13 pointteri funktioon `vilauta_lediä`.
  Tässä tapauksessa mitään interrupteja ei haluta käyttää,
  mutta reset on aina aktiivinen (virrat päälle tai reset maassa).
  Tällöin hypätään funktioon `init` jossa alustetaan muuttujat ja hypätään main.
  
  Homma laitettu osioon .vectors, josta se voidaan
  linkkausvaiheessa helposti noukkia käännöksen alkuun.
  https://developer.arm.com/documentation/dui0662/b/The-Cortex-M0--Processor/Exception-model/Vector-table
*/
const void * Vectors[] __attribute__((section(".vectors"))) ={
	(void *)0x20002000, 	/* Top of stack (20k) */
	init,   		     /* Reset Handler */
	Default_Handler,	/* NMI */
	Default_Handler,	/* Hard Fault */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* SVCall */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* PendSV */
	Default_Handler,	/* SysTick */
/* External interrupt handlers follow */
	Default_Handler, 	/* 0: EIC NMI */
	Default_Handler, 	/* 1: Power manager */
	Default_Handler, 	/* 2: System control */
	Default_Handler, 	/* 3: WDT */
	Default_Handler, 	/* 4: Real-Time Counter */
	Default_Handler, 	/* 5: Non-volatile memory control */
	Default_Handler, 	/* 6: DMAC */
	Default_Handler, 	/* 7: USB */
	Default_Handler, 	/* 8: EVSYS */
	Default_Handler, 	/* 9: SERCOM0 */
	Default_Handler, 	/* 10: SERCOM1 */
	Default_Handler, 	/* 11: SERCOM2 */
	Default_Handler, 	/* 12: SERCOM3 */
	Default_Handler, 	/* 13: SERCOM4 */
	Default_Handler, 	/* 14: SERCOM5 */
	Default_Handler, 	/* 15: Timer Counter 0 */
	Default_Handler, 	/* 16: Timer Counter 1 */
	Default_Handler, 	/* 17: Timer Counter 2 */
	Default_Handler, 	/* 18: Timer Counter 3 */
	Default_Handler, 	/* 19: Timer Counter 4 */
	Default_Handler, 	/* 20: Timer Counter 5 */
	Default_Handler, 	/* 21: Timer Counter 6 */
	Default_Handler, 	/* 22: Timer Counter 7 */
	Default_Handler, 	/* 23: ADC */
	Default_Handler, 	/* 24: Analogue comparator */
	Default_Handler, 	/* 25: DAC */
	Default_Handler, 	/* 26: Peripheral Touch Controller */
	Default_Handler, 	/* 27: I2S */
	Default_Handler, 	/* 28: AC1 */
	Default_Handler, 	/* 29: TCC3 */
};

/*
  Init-interrupti, esim. virtojen mennessä päälle.
  Tähän on mahdollista laittaa kaiken maailman alustushommeleita.
*/
void init()
{
	main();
}

/* Tyhjä interrupti (RETI), palaa vain takaisin */
void Default_Handler()
{
	return;
}
