cc=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -mthumb -gdwarf-2
INCS=-I 
LIBS=
SRC=$(wildcard *.c)
OBJ= $(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s=.o)
project_name = learn-in-depth-cortex-m3

all:$(project_name).bin
	@echo "================build is done=============="

%.o: %.s
	$(cc)as.exe $(CFLAGS) $< -o $@ 

%.o: %.c
	$(cc)gcc.exe $(INCS) $(CFLAGS)  -c $< -o $@	
	
$(project_name).elf: $(OBJ) $(ASOBJ)
	$(cc)ld.exe -T linker_script.ld  $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=Map_file.map
	
$(project_name).bin: $(project_name).elf
	$(cc)objcopy.exe -O binary $< $@
	
clean:
	rm -rf *.o *.bin *.elf	 *.map
	@echo "===========everything is clean=========="