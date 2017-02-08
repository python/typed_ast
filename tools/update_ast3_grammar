#!/bin/bash -eux

# Run after changing `Grammar/Grammar`

PROJ_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."

echo 'Compiling pgen'
gcc -I ast3/Parser -I ast3/Include $(python3-config --includes) \
    -o tools/pgen3 \
    ast3/Parser/acceler.c \
    ast3/Parser/grammar1.c \
    ast3/Parser/node.c \
    ast3/Parser/parser.c \
    ast3/Parser/bitset.c \
    ast3/Parser/grammar.c \
    ast3/Pgen/listnode.c \
    ast3/Pgen/metagrammar.c \
    ast3/Pgen/firstsets.c \
    ast3/Pgen/pgen.c \
    ast3/Pgen/obmalloc.c \
    ast3/Pgen/dynamic_annotations.c \
    ast3/Pgen/mysnprintf.c \
    ast3/Pgen/pyctype.c \
    ast3/Pgen/tokenizer_pgen.c \
    ast3/Pgen/printgrammar.c \
    ast3/Pgen/parsetok_pgen.c \
    ast3/Pgen/pgenmain.c


echo 'Updating graminit files'
tools/pgen3 ast3/Grammar/Grammar ast3/Include/graminit.h ast3/Python/graminit.c

echo 'Grammar file update complete'
