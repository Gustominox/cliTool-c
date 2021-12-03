#!/bin/sh

set -xe

gcc -o box -Wall -Wpedantic -I headers ./src/box.c
