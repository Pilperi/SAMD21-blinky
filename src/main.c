/*
  Suoritettava koodi.
  Vilkuta lediä pinnissä PINNI niin, että se on aina päällä PAALLA kellosykliä,
  jonka jälkeen pimeänä kasvavan pituisen ajan (=vilkkuu hiipuvaan tahtiin).
  Kun pimeänäolon pituus saavuttaa PIMEE_MAX, hypätään alkuun.
  Suorittimen taajuus on 48 MHz
*/

const unsigned int PINNI = 0;
const unsigned int PAALLA = 5000;
const unsigned int PIMEE_MAX = 30000;

/* Viivästysfunktio, odota dly kellosykliä */
void delay(unsigned int dly)
{
    while(dly--);
}

int main(void)
{
    /* Maski joka operoi pinniin */
    const unsigned int togglemask = (1 << PINNI);

    /* ABH portti A rekisteri */
	//unsigned int PORTA = 0x41004400;

	/* Nopean väylän IOBUS port A pohjaosoite */
    unsigned int PORTA = 0x60000000;

	/*
    Pinnien suuntarekisteri DIRSET, laittaa monta pinniä kerralla ulostuloksi
    ks. SAM-D21-DA1-Family-Data-Sheet-DS40001882H.pdf sivu 375
    */
    unsigned int *DIRSET_ptr;
	DIRSET_ptr = (unsigned int *)(PORTA + 0x08);
	*DIRSET_ptr = togglemask;

	/* OUTSET-rekisteri laittaa kaikki määritellyt pinnit ylös */
    unsigned int *OUTSET_ptr;
	OUTSET_ptr = (unsigned int *)(PORTA + 0x18);

	/* ...ja OUTCLR vastaavasti kaikki pinnit alas */
    unsigned int *OUTCLR_ptr;
	OUTCLR_ptr = (unsigned int *)(PORTA + 0x14);
	*OUTCLR_ptr = togglemask;

	/* Aloitetaan viemällä pinni ylös */
    *OUTSET_ptr = togglemask;
	unsigned int dlyoffset = 0;
    while(1)
    {
	*OUTCLR_ptr = togglemask;
    delay(dlyoffset);
    *OUTSET_ptr = togglemask;
    delay(PAALLA);
    dlyoffset += 1000;
    if(dlyoffset > PIMEE_MAX){dlyoffset=0;}
	}
}
