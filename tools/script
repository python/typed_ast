#!/bin/bash -ex

# Automate steps 1-4 of update_process.md (Mac).

HERE=$(dirname ${BASH_SOURCE[0]})
cd $HERE/..
pwd

CPYTHON=~/src/cpython37

DIRS="Grammar Include Parser Python"
C_FILES="Parser/acceler.c Parser/bitset.c Parser/grammar.c Parser/grammar1.c Parser/node.c Parser/parser.c Parser/parsetok.c Parser/tokenizer.c Python/asdl.c Python/ast.c Python/graminit.c Python/Python-ast.c"
H_FILES="Include/asdl.h Include/ast.h Include/bitset.h Include/errcode.h Include/graminit.h Include/grammar.h Include/node.h Include/parsetok.h Include/Python-ast.h Include/token.h Parser/parser.h Parser/tokenizer.h"
OTHER_FILES="Grammar/Grammar Parser/Python.asdl Parser/asdl.py Parser/asdl_c.py"

for dir in $DIRS
do
    rm -rf ast3/$dir
    mkdir -p ast3/$dir
done

for file in $C_FILES $H_FILES $OTHER_FILES
do
    cp $CPYTHON/$file ast3/$file
done

./tools/update_header_guards 3

rm -rf build
grep -v ast3/Custom setup.py | python3.7 - build

./tools/find_exported_symbols 3
./tools/update_exported_symbols 3

patch ast3/Parser/asdl_c.py <tools/asdl_c.patch

python3.7 ast3/Parser/asdl_c.py -h ast3/Include/Python-ast.h ast3/Parser/Python.asdl
python3.7 ast3/Parser/asdl_c.py -c ast3/Python/Python-ast.c ast3/Parser/Python.asdl

python3.7 setup.py build

# Lots of manual changes go here...

##PYTHONPATH=build/lib.macosx-10.9-x86_64-3.7/ python3.7 -m pytest -s ast3/tests
