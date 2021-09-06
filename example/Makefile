ifdef TARGET
ARTIFACT_DIR=bin/$(TARGET)
TARGET_FLAG=-target $(TARGET)
else
ARTIFACT_DIR=bin
TARGET_FLAG=
endif

ARTIFACT=$(ARTIFACT_DIR)/hello

all: $(ARTIFACT)

$(ARTIFACT): hello.c
	mkdir -p $(ARTIFACT_DIR)
	$(CC) \
		-o $(ARTIFACT) \
		$(TARGET_FLAG) \
		hello.c

clean:
	-rm -rf bin
