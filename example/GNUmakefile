.SILENT:
.IGNORE: clean
.PHONY: \
	all \
	clean \
	lint \
	test

BANNER=hello-0.0.1
ARTIFACT_DIR=bin

ifdef TARGET
	ARTIFACT_DIR=bin/$(BANNER)/$(TARGET)
endif

ARTIFACT=$(ARTIFACT_DIR)/hello$(SNEK_EXECUTABLE_FILE_EXTENSION)

all: $(ARTIFACT)

$(ARTIFACT): hello.c
	mkdir -p $(ARTIFACT_DIR)
	$(CC) \
		-o $(ARTIFACT) \
		$(CPPFLAGS) \
		hello.c

test:
	ls $(ARTIFACT_DIR)

clean:
	rm -rf bin
