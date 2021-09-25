ARTIFACT_DIR=bin
ARTIFACT_EXT=
TARGET_FLAG=
PREFIXES=
LIBRARY_PATHS=
SYSROOT_FLAG=
STATIC_FLAG=-static

ifdef TARGET
	ifneq (,$(findstring w64,$(TARGET)))
		CC=$(TARGET)-gcc-9.3-posix
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
				else
					ifneq (,$(findstring dragonflybsd,$(TARGET)))
						DFLY_PATHS=/usr/local/$(TARGET)/lib \
							/usr/local/$(TARGET)/usr/lib \
							/usr/local/$(TARGET)/usr/lib/gcc80

						PREFIXES=$(foreach DFLY_PATH, $(DFLY_PATHS), -B $(DFLY_PATH))
						LIBRARY_PATHS=$(foreach DFLY_PATH, $(DFLY_PATHS), -L $(DFLY_PATH))
					endif
				endif
			endif

			TARGET_FLAG=-target $(TARGET)
			export CPATH=/usr/$(TARGET)/include:/usr/local/$(TARGET)/usr/include
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
		$(STATIC_FLAG) \
		$(PREFIXES) \
		$(LIBRARY_PATHS) \
		hello.c

clean:
	-rm -rf bin
