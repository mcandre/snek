.PHONY: all

all:
	@cargo install --force unmake@0.0.4

	@go install github.com/mcandre/tug/cmd/tug@v0.0.4
	@go mod tidy

	@npm install -g snyk@1.1140.0

	@python -m pip install --user --upgrade pip setuptools
	@pip install --user -r requirements-dev.txt
