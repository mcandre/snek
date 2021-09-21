ARTIFACT_DIR=bin
ARTIFACT_EXT=
TARGET_FLAG=
INCLUDE_FLAG=
PREFIX_FLAG=
LINK_FLAG=
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
				SYSROOT_FLAG=--sysroot /usr/local/$(TARGET)

				ifneq (,$(findstring dragonflybsd,$(TARGET)))
					PREFIX_FLAG=\
                        -B /usr/local/$(TARGET)/lib \
                        -B /usr/local/$(TARGET)/usr/lib \
                        -B /usr/local/$(TARGET)/usr/lib/gcc80
					LINK_FLAG=\
                        -L /usr/local/$(TARGET)/lib \
                        -L /usr/local/$(TARGET)/usr/lib \
                        -L /usr/local/$(TARGET)/usr/lib/gcc80
				endif
			endif

			TARGET_FLAG=-target $(TARGET)
			INCLUDE_FLAG=\
				-I /usr/$(TARGET)/include \
				-I /usr/local/$(TARGET)/usr/include
		endif
	endif

	ARTIFACT_DIR=bin/$(TARGET)
endif

ARTIFACT=$(ARTIFACT_DIR)/hello$(ARTIFACT_EXT)

all: $(ARTIFACT)

$(ARTIFACT): hello.c
	@mkdir -p $(ARTIFACT_DIR)
	@$(CC) \
		-o $(ARTIFACT) \
		$(TARGET_FLAG) \
		$(SYSROOT_FLAG) \
		$(INCLUDE_FLAG) \
		$(PREFIX_FLAG) \
		$(LINK_FLAG) \
		hello.c

clean:
	-rm -rf bin
