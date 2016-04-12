#!/bin/bash
PROJ_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."

gobjdump -t $PROJ_DIR/build/lib*/_ast${1}.*.so | grep ' g ' | grep -v UND > "exported_symbols${1}.txt"
echo "Symbols written to exported_symbols${1}.txt.  You should edit this file to "
echo "remove any symbols you still want to export (like PyInit functions) "
echo "and to make each line contain only a function name you want updated "
echo "(and none of the other output) before running update_exported_symbols."
