ifdef TARGET
	ifneq (,$(findstring windows,$(TARGET)))
		ARTIFACT_EXT=.exe
	else
		ARTIFACT_EXT=

		ifneq (,$(findstring darwin,$(TARGET)))
			CC=$(TARGET)20.4-clang
			CROSSBUILD=$(TARGET)
			TARGET_FLAG=
			INCLUDE_FLAG=
		else
			TARGET_FLAG=-target $(TARGET)
			INCLUDE_FLAG=-I /usr/$(TARGET)/include
		endif
	endif

	ARTIFACT_DIR=bin/$(TARGET)
else
	ARTIFACT_DIR=bin
	ARTIFACT_EXT=
	TARGET_FLAG=
	SYSROOT_FLAG=
	INCLUDE_FLAG=
endif

ARTIFACT=$(ARTIFACT_DIR)/hello$(ARTIFACT_EXT)

all: $(ARTIFACT)

$(ARTIFACT): hello.c
	@mkdir -p $(ARTIFACT_DIR)
	@$(CC) \
		-o $(ARTIFACT) \
		$(TARGET_FLAG) \
		$(INCLUDE_FLAG) \
		hello.c

clean:
	-rm -rf bin
