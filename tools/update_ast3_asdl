#!/bin/bash -eux

# Run after changing `Parser/Python.asdl`

PROJ_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."

python3 ast3/Parser/asdl_c.py -h ast3/Include/ ast3/Parser/Python.asdl
python3 ast3/Parser/asdl_c.py -c ast3/Python/ ast3/Parser/Python.asdl
