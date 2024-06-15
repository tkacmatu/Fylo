# Author: Radek Hušek
LOGIN = tkacmatu
CXX = g++
BASIC_FLAGS = -std=c++17 -O2 -g -fsanitize=undefined -Wall -pedantic
FLAGS =

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, ${SOURCES})
DEPS = $(patsubst src/%.cpp, build/%.dep, ${SOURCES})

.PHONY: all compile run valgrind doc clean count zip

all: clean compile doc

compile: ${LOGIN}

${LOGIN}: ${OBJECTS}
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} $^ -o $@

build/%.o: src/%.cpp
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} -c $< -o $@

run: compile
	./${LOGIN}

valgrind: compile
	valgrind ./${LOGIN}

doc: doc/index.html

doc/index.html: Doxyfile $(wildcard src/*)
	doxygen Doxyfile

clean:
	rm -rf build doc
	rm -f ${LOGIN} ${LOGIN}.zip

build/%.dep: src/%.cpp src/*
	@mkdir -p build/
	${CXX} -MM -MT $(patsubst src/%.cpp, build/%.o, $<) $< > $@

include ${DEPS}

