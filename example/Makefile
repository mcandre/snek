ifdef TARGET
ifneq (,$(findstring windows,$(TARGET)))
ARTIFACT_EXT=.exe
else
ARTIFACT_EXT=
endif

ARTIFACT_DIR=bin/$(TARGET)
TARGET_FLAG=-target $(TARGET)
INCLUDE_FLAG=-I /usr/$(TARGET)/include
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
	mkdir -p $(ARTIFACT_DIR)
	$(CC) \
		-o $(ARTIFACT) \
		$(TARGET_FLAG) \
		$(INCLUDE_FLAG) \
		hello.c

clean:
	-rm -rf bin
