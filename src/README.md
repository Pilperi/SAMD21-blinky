2023-09-23

# Lähdekoodi

Lähdekoodi, joka käännetään ja ohjelmoidaan sirulle. Kääntäjänä `arm-none-eabi-gcc`, ja lisäargumentteja tarvitsee kunnon litanian. Ks. `Makefile`.

## init.c
Sisältää sirun alustustoimenpiteet. Interruptien vektoritaulu kertoo, mihin pitää hypätä kun virrat menee päälle tai siru resetoidaan.
Käännettäessä taulu menee ulostulon `.vectors`-osioon, joka täytyy sitten laittaa sirulla koodin ihan alkuun (`.text`-osioon ekaksi).

## main.c
Suoritettavan funktion `main` määritelmä. Tökkii pinnisäätörekisterejä siten, että pinniin PA00 laitettu LED vilkkuu ensin vinhaan tahtiin ja ajan kanssa yhä vähemmän vinhaan tahtiin.
