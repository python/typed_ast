#!/bin/bash -eux

# Run after changing `Grammar/Grammar`

PROJ_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."

echo 'Copying pgen'
cp ~/src/cpython37/Parser/pgen tools/pgen3

echo 'Updating graminit files'
tools/pgen3 ast3/Grammar/Grammar ast3/Include/graminit.h ast3/Python/graminit.c

echo 'Grammar file update complete'
