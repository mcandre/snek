.POSIX:
.SILENT:
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
	safety \
	snyk \
	test \
	uninstall \
	unmake

BANNER=snek-0.0.3

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

all: build

audit: docker_scout safety snyk

build: cmake-init
	cmake --build build --config Release

build/conaninfo.txt:
	conan install -s compiler.cppstd=17 -s compiler=$(COMPILER_NAME) -s compiler.version=$(COMPILER_VERSION) --build missing . --install-folder build

cmake-init: build/conaninfo.txt
	BANNER="$(BANNER)" cmake -B build

docker-build: cmake-init
	cmake --build build --target docker-build

docker-load: cmake-init
	cmake --build build --target docker-load

docker-publish: cmake-init
	cmake --build build --target docker-publish

docker-scout: cmake-init
	cmake --build build --target docker-scout

lint: cmake-init unmake
	cmake --build build --target lint

install: build
	cmake --build build --target install

port:
	snek
	sh -c "cd bin && tar czf $(BANNER).tgz $(BANNER)"

safety:
	cmake --build build --target safety

snyk:
	cmake --build build --target snyk

uninstall: cmake-init
	cmake --build build --target uninstall

unmake:
	unmake .
	unmake -n .

clean: clean-bin clean-cmake clean-doc

clean-bin:
	rm -rf bin

clean-cmake:
	rm -rf build

clean-doc:
	rm -rf html
	rm -rf latex
