ARTIFACT_DIR=bin
ARTIFACT_EXT=
TARGET_FLAG=
INCLUDE_FLAG=
SYSROOT_FLAG=

ifdef TARGET
	ifneq (,$(findstring w64,$(TARGET)))
		CC=$(TARGET)-gcc-9.3-posix
		ARTIFACT_EXT=.exe
	else
		ifneq (,$(findstring darwin,$(TARGET)))
			CC=$(TARGET)20.4-clang
			CROSSBUILD=$(TARGET)
		else
			ifneq (,$(findstring bsd,$(TARGET)))
				ifneq (,$(findstring dragonflybsd,$(TARGET)))
					SYSROOT_FLAG=--sysroot /dfly-x86_64-6.0.0_REL
				else
					SYSROOT_FLAG=--sysroot /usr/local/$(TARGET)
				endif
			endif

			TARGET_FLAG=-target $(TARGET)
			INCLUDE_FLAG=\
				-I /usr/$(TARGET)/include \
				-I /dfly-x86_64-6.0.0_REL/usr/include
		endif
	endif

	ARTIFACT_DIR=bin/$(TARGET)
endif

ARTIFACT=$(ARTIFACT_DIR)/hello$(ARTIFACT_EXT)

all: $(ARTIFACT)

$(ARTIFACT): hello.c
	@mkdir -p $(ARTIFACT_DIR)
	$(CC) \
		-I/dfly-x86_64-6.0.0_REL/usr/include \
		-L/dfly-x86_64-6.0.0_REL/usr/lib \
		-L/dfly-x86_64-6.0.0_REL/usr/lib/gcc47 \
		-B/dfly-x86_64-6.0.0_REL/usr/lib \
		-B/dfly-x86_64-6.0.0_REL/usr/lib/gcc47 \
		-target x86_64-pc-dragonfly-elf \
		$(SYSROOT_FLAG) \
		hello.c

clean:
	-rm -rf bin
