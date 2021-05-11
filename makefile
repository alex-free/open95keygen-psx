# Assumes that sdk is /usr/local/mipsel-unknown-elf/psn00bsdk and toolchain is at /usr/local/mipsel-unknown-elf, and that mkpsxiso is somewhere in $PATH
VER         = 1.0
TARGET      = o95kg.elf
SDK         = /usr/local/mipsel-unknown-elf

CC			= $(SDK)/bin/mipsel-unknown-elf-gcc
CXX			= $(SDK)/bin/mipsel-unknown-elf-g++
AS			= $(SDK)/bin/mipsel-unknown-elf-as
AR			= $(SDK)/bin/mipsel-unknown-elf-ar
LD			= $(SDK)/bin/mipsel-unknown-elf-ld
RANLIB		= $(SDK)/bin/mipsel-unknown-elf-ranlib
ELF2X       = $(SDK)/psn00bsdk/tools/bin/elf2x

CFILES		= $(notdir $(wildcard *.c))
AFILES		= $(notdir $(wildcard *.s))
OFILES		= $(addprefix build/,$(CFILES:.c=.o)) \
			$(addprefix build/,$(CPPFILES:.cpp=.o)) \
			$(addprefix build/,$(AFILES:.s=.o))

INCLUDE	 	+= -I$(SDK)/psn00bsdk/libpsn00b/include
LIBDIRS		+= -L$(SDK)/psn00bsdk/libpsn00b
LIBS		= -lpsxgpu -lpsxgte -lpsxspu -lpsxetc -lpsxapi -lc


CFLAGS		= -g -O2 -fno-builtin -fdata-sections -ffunction-sections
AFLAGS		= -g -msoft-float
LDFLAGS		= -g -Ttext=0x80010000 -gc-sections \
			-T $(SDK)/mipsel-unknown-elf/lib/ldscripts/elf32elmip.x

all: clean $(OFILES)
	$(LD) $(LDFLAGS) $(LIBDIRS) $(OFILES) $(LIBS) -o $(TARGET)
	$(ELF2X) -q $(TARGET)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

build/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(AFLAGS) $(INCLUDE) -c $< -o $@

us-cd: all
	mkpsxiso us-cd.xml
	mkdir open95keygen-psx_$(VER)_us
	cp -rv o95kg-$(VER).bin o95kg-$(VER).cue readme.html open95keygen-psx_$(VER)_us

jp-cd: all
	mkpsxiso jp-cd.xml
	mkdir open95keygen-psx_$(VER)_jp
	cp -rv o95kg-$(VER).bin o95kg-$(VER).cue readme.html open95keygen-psx_$(VER)_jp

exe-release: all
	mkdir open95keygen-psx_$(VER)_exe
	cp -rv o95kg.exe readme.html open95keygen-psx_$(VER)_exe

test:
	pcsxr -cdfile *.cue

clean:
	rm -rf build $(TARGET) $(TARGET:.elf=.exe) o95kg-$(VER).bin o95kg-$(VER).cue open95keygen-psx_$(VER)_jp open95keygen-psx_$(VER)_us open95keygen-psx_$(VER)_exe
