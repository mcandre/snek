.POSIX:
.SILENT:
.PHONY: \
	all \
	go \
	python \
	rust

all: go python rust

go:
	go install github.com/mcandre/tug/cmd/tug@v0.0.8
	go mod tidy

python:
	python -m pip install --user --upgrade pip setuptools
	pip install --user -r requirements.txt

rust:
	cargo install --force unmake@0.0.17
