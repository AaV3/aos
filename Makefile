CC  := arm-miosix-eabi-gcc
CXX := arm-miosix-eabi-g++
AS  := arm-miosix-eabi-as
CP  := arm-miosix-eabi-objcopy

CPU := -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

AFLAGS   := $(CPU)
CFLAGS   := $(CPU) -O0 -g -c
CXXFLAGS := $(CPU) -O0 -fno-exceptions -fno-rtti -g -c
LFLAGS   := $(CPU) -Wl,-T./linker.ld,-Map,main.map -nostdlib

SRC := startup.s main.cpp serial.cpp
OBJ := $(addsuffix .o, $(basename $(SRC)))

all: $(OBJ)
	$(CXX) $(LFLAGS) -o main.elf $(OBJ)
	$(CP) -O binary main.elf main.bin

clean:
	-rm $(OBJ) main.elf main.bin main.map

%.o : %.s
	$(AS) $(AFLAGS) $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
