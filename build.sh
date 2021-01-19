#!/bin/bash


CFLAGS="-j -O0 -ggdb -Wall"

SOURCE_FILES="stream_parser.c ../include/sti/sti.c"
OUT_BINARY="ccss"

# for sti/etc.
INCLUDE_HACK="-I../include/"


gcc $CFLAGS $INCLUDE_HACK -o $OUT_BINARY $SOURCE_FILES

 



