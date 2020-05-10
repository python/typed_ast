cd ast3/Tools/peg_generator
python3 -m pegen -q c ../../Grammar/python.gram ../../Grammar/Tokens -o ../../Parser/pegen/parse.c
cd ../../..
