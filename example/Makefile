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
			ifneq (,$(findstring freebsd,$(TARGET)))
				SYSROOT_FLAG=--sysroot /usr/local/$(TARGET)
			endif

			TARGET_FLAG=-target $(TARGET)
			INCLUDE_FLAG=-I /usr/$(TARGET)/include
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
		hello.c

clean:
	-rm -rf bin
