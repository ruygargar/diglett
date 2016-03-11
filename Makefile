#
# This makefile allows you to build sketches from the command line
# without the Arduino environment (or Java).
#

################################################################################
### Makefile variables
################################################################################

LOG ?= n
ifeq ($(LOG), n)
	L = @
endif

################################################################################
### Directories and Targets
################################################################################

# Build directory:
BUILD_DIR          = build

# Binary output name:
TARGET             = tmp



################################################################################
### Hardware
################################################################################

MCU_TYPE           = atmega2560
MCU_CLOCK          = 16000000


################################################################################
### Toolchain
################################################################################

#
# AVR Tools
#

# AVR tools path:
AVR_TOOLS_PATH     = arduino/hardware/tools/avr/bin

# AVR C Compiler path:
CC                 = $(AVR_TOOLS_PATH)$(PATHSEP)/avr-gcc
# AVR C Compiler flags:
CDEFS              = -DF_CPU=$(MCU_CLOCK) -DARDUINO=164
CSTANDARD          = -std=c11
CDEBUG             = -g
CWARN              = -Wall -Wstrict-prototypes
CTUNING            = -funsigned-char -funsigned-bitfields -fpack-struct \
                     -fshort-enums -w -ffunction-sections -fdata-sections \
                     -fno-use-cxa-atexit
CFLAGS   := -mmcu=$(MCU_TYPE) -O $(CDEFS) $(CSTANDARD) $(CDEBUG) $(CWARN) $(CTUNING)

# AVR C++ Compiler path:
CXX                = $(AVR_TOOLS_PATH)$(PATHSEP)/avr-g++
# AVR C++ Compiler flags:
CXXDEFS            = -DF_CPU=$(MCU_CLOCK) -DARDUINO=164
CXXSTANDARD        = -std=c++11
CXXDEBUG           = -g
CXXWARN            = -Wall
CXXTUNING          = -funsigned-char -funsigned-bitfields -fpack-struct \
                     -fshort-enums -w -ffunction-sections -fdata-sections \
                     -fno-use-cxa-atexit
CXXFLAGS := -mmcu=$(MCU_TYPE) -O $(CXXDEFS) $(CXXSTANDARD) $(CXXDEBUG) $(CXXWARN) $(CXXTUNING)

# AVR C Linker flags:
LDFLAGS   = -mmcu=atmega2560 -DARDUINO=164 -DF_CPU=16000000 -DLANGUAGE=EN -O -Wall -std=c++11 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -w -ffunction-sections -fdata-sections -fno-use-cxa-atexit -Wl,--gc-sections

# AVR Objcopy path:
OBJCOPY            = $(AVR_TOOLS_PATH)/avr-objcopy

# AVR Size path:
SIZE               = $(AVR_TOOLS_PATH)$(PATHSEP)/avr-size

# AVR Programmer:
AVRDUDE            = $(AVR_TOOLS_PATH)/avrdude
# AVR Programmer configuration:
AVRDUDE_PORT       = /dev/ttyUSB*
AVRDUDE_PROGRAMMER = wiring
AVRDUDE_BAUDRATE   = 115200
AVRDUDE_CONF       = arduino/hardware/tools/avr/etc/avrdude.conf
AVRDUDE_FLASH      = -D -U flash:w:$(BUILD_DIR)/$(TARGET).hex:i
AVRDUDE_FLAGS      = -v -C $(AVRDUDE_CONF) -p $(MCU_TYPE) -P $(AVRDUDE_PORT) \
                     -c $(AVRDUDE_PROGRAMMER) -b $(AVRDUDE_BAUDRATE) \
                     $(AVRDUDE_FLASH)

#
# Other system tools
#

MAKE_DIR = mkdir -p
MOVE = mv -f
COPY = cp
REMOVE = rm -f
REMOVE_DIR = rm -fr
ECHO = echo


################################################################################
### Project Files
################################################################################

#
# Include files list:
#

# Project includes
VPATH = .

# Core includes
VPATH += arduino/hardware/arduino/avr/cores/arduino
VPATH += arduino/hardware/arduino/avr/variants/mega

# SD library includes
VPATH += arduino/hardware/arduino/avr/libraries/SPI
VPATH += arduino/libraries/SD/src
VPATH += arduino/libraries/SD/src/utility

# LCD library includes
VPATH += arduino/libraries/LiquidCrystal/src

# Expand includes
CINCS = ${addprefix -I ,${VPATH}}
CXXINCS = ${addprefix -I ,${VPATH}}


#
# Source files list:
#

# Core sources
CSRC = hooks.c wiring.c wiring_digital.c
CXXSRC = HardwareSerial.cpp HardwareSerial0.cpp Stream.cpp Print.cpp SPI.cpp

# SD library sources
CXXSRC += SD.cpp File.cpp Sd2Card.cpp SdFile.cpp SdVolume.cpp

# LCD library sources
CXXSRC += LiquidCrystal.cpp

# Encoder
CXXSRC += Encoder.cpp

# Main
CXXSRC += main.cpp


#
# Objects lists:
#

OBJ = ${patsubst %.c,$(BUILD_DIR)/%.o,${CSRC}}
OBJ += ${patsubst %.cpp,$(BUILD_DIR)/%.o,${CXXSRC}}


# Targets
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf 
	@ $(ECHO) "  COPY  $@"
	$(L) $(OBJCOPY) -O ihex -R .eeprom $< $@

$(BUILD_DIR)/$(TARGET).elf: $(BUILD_DIR) $(OBJ)
	@ $(ECHO) "  CC    $@"
	$(L) $(CC) $(LDFLAGS) -o $@ -L. $(OBJ) -lm

# Creates the object directory
$(BUILD_DIR):
	$(L) $(MAKE_DIR) $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	@ $(ECHO) "  CC    $<"
	$(L) $(CC) -c -MMD $(CINCS) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@ $(ECHO) "  CXX   $<"
	$(L) $(CXX) -c -MMD $(CXXINCS) $(CXXFLAGS) $< -o $@

# Flash the device
upload: $(BUILD_DIR)/$(TARGET).hex
ifeq (${AVRDUDE_PROGRAMMER}, arduino)
	stty hup < $(UPLOAD_PORT); true
endif
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)
ifeq (${AVRDUDE_PROGRAMMER}, arduino)
	stty -hup < $(UPLOAD_PORT); true
endif

clean:
	@ $(ECHO) "  RMDIR $(BUILD_DIR)/"
	$(L) $(REMOVE_DIR) $(BUILD_DIR)