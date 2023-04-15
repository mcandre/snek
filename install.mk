.PHONY: all

all:
	@cargo install --force unmake@0.0.4

	@go install github.com/mcandre/tug/cmd/tug@v0.0.4
	@go mod tidy

	@npm install -g snyk@1.1140.0

	@pip3 install --upgrade pip setuptools
	@pip3 install -r requirements-dev.txt
