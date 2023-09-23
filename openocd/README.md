2023-09-23

# OpenOCD-skriptit
Muutama esimerkkiskripti, ml. laitteistomääritelmät, sirun statuksen tarkistaminen, sekä koodin lähetys sirulle. Skriptitiedostojen kommenteissa infoa rakenteesta.
Skriptejä saa kutsuttua muodossa
```
openocd -s skriptikansio -f skriptinnimi.cfg
```
missä `-s` määrittelee lisäkansion mistä etsiä skriptejä. Ks. esim. ylemmän kansion `makebuild.sh`.
Huomaa että laitteistototeutus on sellainen, että sirun `RESET`-pinni tulee olla ylhäällä juttelun ajan.

## atsamd21.cfg
Kaikkiin jutteluskripteihin pätevät määritelmät. Raspin pinnit, raspin malli (erit. kellotaajuus) ymv.

## target.cfg
Skripti jolla saa tarkistettua, onko piuhan päässä juttelukelpoinen siru. Onnistuessaan antaa sirun perustiedot: mallin ja uniikin ID:n.
Käyttää `atsamd21.cfg` laitteistomääritykseen.

## openocd_oma.cfg
Skripti jolla saa ohjelmoitua tiedoston `ulostulo.elf` laitteelle.
Käyttää `atsamd21.cfg` laitteistomääritykseen.
