EMPTY:=
SPACE:=$(EMPTY) $(EMPTY)

ARTIFACT_DIR=bin
ARTIFACT_EXT=
TARGET_FLAG=
PREFIXES=
SYSROOT_FLAG=

ifdef TARGET
	STATIC_FLAG=-static

	ifneq (,$(findstring w64,$(TARGET)))
		CC=$(TARGET)-gcc-10-posix
		ARTIFACT_EXT=.exe
	else
		ifneq (,$(findstring darwin,$(TARGET)))
			CC=$(TARGET)20.4-clang
			CROSSBUILD=$(TARGET)
			STATIC_FLAG=
		else
			ifneq (,$(findstring bsd,$(TARGET)))
				SYSROOT_FLAG=--sysroot /usr/local/$(TARGET)

				ifneq (,$(findstring openbsd,$(TARGET)))
					STATIC_FLAG=
				endif
			endif

			TARGET_FLAG=-target $(TARGET)
			export CPATH=/usr/$(TARGET)/include:/usr/local/$(TARGET)/usr/include
		endif
	endif

	ARTIFACT_DIR=bin/$(TARGET)
	export CFLAGS=$(STATIC_FLAG)
endif

ARTIFACT=$(ARTIFACT_DIR)/hello$(ARTIFACT_EXT)

all: $(ARTIFACT)

$(ARTIFACT): hello.c
	@mkdir -p $(ARTIFACT_DIR)
	@$(CC) \
		-o $(ARTIFACT) \
		$(TARGET_FLAG) \
		$(SYSROOT_FLAG) \
		$(PREFIXES) \
		hello.c

clean:
	-rm -rf bin
