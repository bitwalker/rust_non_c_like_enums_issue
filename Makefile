.PHONY: help

NAME ?= test
CWD ?= `pwd`

help:
	@echo "$(NAME)"
	@perl -nle'print $& if m{^[a-zA-Z_-]+:.*?## .*$$}' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

run: build ## Run the executable
	@./test.out || true

build: test.out ## Build executable

test.out: test.rs _build/lib/libtestlib.dylib
	rustc -Z verbose \
		test.rs \
		-o test.out \
		-l dylib=testlib \
		-L native=$(CWD)/_build/lib \
		--crate-type=bin \
		--edition=2018 \
		-g \
		-C link-args="-Wl,-rpath,"$(CWD)/_build/lib

_build/lib/libtestlib.dylib: test.cpp
	@mkdir -p _build/lib
	clang++ -Wall -std=c++17 -shared \
		-o _build/lib/libtestlib.dylib \
		test.cpp
