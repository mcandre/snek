.POSIX:
.SILENT:
.PHONY: all

all:
	cargo install --force unmake@0.0.17

	go install github.com/mcandre/tug/cmd/tug@v0.0.8
	go mod tidy

	npm install -g snyk

	python -m pip install --user --upgrade pip setuptools
	pip install --user -r requirements.txt
