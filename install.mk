.POSIX:
.SILENT:
.PHONY: all

all:
	cargo install --force unmake@0.0.12

	go install github.com/mcandre/tug/cmd/tug@v0.0.6
	go mod tidy

	npm install -g snyk

	python -m pip install --user --upgrade pip setuptools
	pip install --user -r requirements-dev.txt
