#!/bin/bash -ex

# Automate steps 1-4 of update_process.md (Mac).

HERE=$(dirname ${BASH_SOURCE[0]})
cd $HERE/..
pwd

CPYTHON=~/cpython

DIRS="Grammar Include Parser Python Tools Parser/pegen"
C_FILES="Parser/pegen/parse.c Parser/pegen/parse_string.c Parser/pegen/peg_api.c Parser/pegen/pegen.c Parser/tokenizer.c Python/asdl.c Python/Python-ast.c"
H_FILES="Include/asdl.h Include/Python-ast.h Include/token.h Parser/tokenizer.h Parser/pegen/parse_string.h Parser/pegen/pegen.h"
OTHER_FILES="Grammar/python.gram Grammar/Tokens Parser/Python.asdl Parser/asdl.py Parser/asdl_c.py Tools/peg_generator"

for dir in $DIRS
do
    rm -rf ast3/$dir
    mkdir -p ast3/$dir
done

for file in $C_FILES $H_FILES $OTHER_FILES
do
    cp -r $CPYTHON/$file ast3/$file
done

cp $CPYTHON/Include/internal/pegen_interface.h ast3/Include/pegen_interface.h