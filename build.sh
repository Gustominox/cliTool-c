#!/bin/sh

set -xe

# gcc -o $2 -ggdb -Wall -Wpedantic -I headers src/$1

gcc -o program -ggdb -Wall -Wpedantic -I headers/ src/input.c src/box.c src/$1