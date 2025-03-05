.POSIX:
# .SILENT:
.IGNORE: \
	clean \
	clean-bin \
	clean-cmake \
	clean-doc \
	uninstall
.PHONY: \
	all \
	audit \
	build \
	clean \
	doc \
	cmake-init \
	docker-build \
	docker-load \
	docker-publish \
	docker-scout \
	install \
	lint \
	port \
	test \
	uninstall

BANNER=snek-0.0.5

ifneq (,$(TARGET))
	ifneq (,$(findstring w64,$(TARGET)))
		CONAN_FLAGS=-pr:b=default -pr:h=/profile.ini
	else
		CONAN_FLAGS=-pr=/profile.ini
	endif
else
	COMPILER_BANNER=$(shell c++ --version)
	COMPILER_NAME=clang

	ifneq (,$(findstring Apple,$(COMPILER_BANNER)))
		COMPILER_NAME=apple-clang
	else
		ifneq (,$(findstring gcc,$(shell c++ --version)))
			COMPILER_NAME=gcc
		endif
	endif

	COMPILER_VERSION=$(shell echo "$(COMPILER_BANNER)" | gawk "match(\$$0, /version\s+([0-9]+)/, version) { print version[1]; exit; }")

	CONAN_FLAGS=-s compiler=$(COMPILER_NAME) \
		-s compiler.version=$(COMPILER_VERSION)
endif

all: build

audit: cmake-init
	cmake --build build --target audit

build: cmake-init
	cmake --build build --config Release
	mkdir -p bin/$(BANNER)/$(TARGET)
	cp build/bin/* bin/$(BANNER)/$(TARGET)

build/conaninfo.txt:
	.venv/bin/conan install \
		$(CONAN_FLAGS) \
		-s compiler.cppstd=17 \
		--build missing . \
		--output-folder build

cmake-init: build/conaninfo.txt
	BANNER="$(BANNER)" cmake -B build -G "Unix Makefiles"

doc: cmake-init
	BANNER=$(BANNER) cmake --build build --target doc

docker-build: cmake-init
	cmake --build build --target docker-build

docker-load: cmake-init
	cmake --build build --target docker-load

docker-publish: cmake-init
	cmake --build build --target docker-publish

docker-scout: cmake-init
	cmake --build build --target docker-scout

lint: cmake-init
	cmake --build build --target lint

install: build
	cmake --build build --target install

port:
	snek
	sh -c "cd bin && tar czf $(BANNER).tgz $(BANNER)"

uninstall: cmake-init
	cmake --build build --target uninstall

clean: clean-bin clean-cmake clean-doc

clean-bin:
	rm -rf bin

clean-cmake:
	rm -rf build

clean-doc:
	rm -rf html
	rm -rf latex
