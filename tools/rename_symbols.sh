rm -rf build
grep -v ast3/Custom setup.py | python3 - build

./tools/find_exported_symbols 3
./tools/update_exported_symbols 3

patch ast3/Parser/asdl_c.py <tools/asdl_c.patch

python3 ast3/Parser/asdl_c.py -h ast3/Include/Python-ast.h ast3/Parser/Python.asdl
python3 ast3/Parser/asdl_c.py -c ast3/Python/Python-ast.c ast3/Parser/Python.asdl

./tools/update_compiler_flags.sh 3

./tools/regen_parse.sh
rm -rf build
python3 setup.py build

# Lots of manual changes go here...