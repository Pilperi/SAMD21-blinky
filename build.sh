PATH_OUT=/home/taira/Elektroniikka/testi
arm-none-eabi-gcc -x c -static -mthumb -g -mcpu=cortex-m0plus *.c -T ./linker_script.ld -o $PATH_OUT/main_oma.elf -MD -specs=nosys.specs -nostartfiles
arm-none-eabi-objcopy -g -O binary $PATH_OUT/main_oma.elf $PATH_OUT/main_oma.bin
