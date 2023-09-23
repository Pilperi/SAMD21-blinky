# Simppeli makefile

# C-kääntäjä ja sen vaatimat vakiargumentit (suorittimen tyyppi ymv)
COMP=arm-none-eabi-gcc
COMPFLAGS=-c -x c -static -mthumb -g -mcpu=cortex-m0plus -MD -specs=nosys.specs -nostartfiles

# Linkkeri ja linkkerin vakiargumentit
LINKER=arm-none-eabi-ld
LINKERFLAGS=-T linker.ld

# Kopiointi toiseenkin kansioon, binääri kaveriksi
BINCOPY=arm-none-eabi-objcopy
BINFLAGS=-g -O binary
KOHDEKANSIO=/home/taira/Elektroniikka/testi

all: build build/ulostulo.bin

# Build-kansion luonti jos uupuu
build:
	mkdir build

# ulostulo.bin tuotto tarvitsee build/ulostulo.elf, luodaan kopiointiohjelmalla
build/ulostulo.bin: build/ulostulo.elf
	$(BINCOPY) $(BINFLAGS) build/ulostulo.elf build/ulostulo.bin

# Linkkaa .o-tiedostot linkkeriskriptillä
build/ulostulo.elf: build/init.o build/main.o
	$(LINKER) $(LINKERFLAGS) -o build/ulostulo.elf build/init.o build/main.o

# Käännä main.c main.o:ksi
build/main.o: src/main.c
	$(COMP) $(COMPFLAGS) -o build/main.o src/main.c

# Käännä init.c init.o:ksi
build/init.o: src/init.c
	$(COMP) $(COMPFLAGS) -o build/init.o src/init.c
