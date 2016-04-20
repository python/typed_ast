from distutils.core import setup, Extension

_ast27 = Extension(
    '_ast27',
    include_dirs = ['ast27/Include'],
    sources = [
        'ast27/Parser/acceler.c',
        'ast27/Parser/bitset.c',
        'ast27/Parser/grammar.c',
        'ast27/Parser/grammar1.c',
        'ast27/Parser/node.c',
        'ast27/Parser/parser.c',
        'ast27/Parser/parsetok.c',
        'ast27/Parser/tokenizer.c',
        'ast27/Python/ast.c',
        'ast27/Python/graminit.c',
        'ast27/Python/mystrtoul.c',
        'ast27/Python/Python-ast.c',
        'ast27/Custom/typed_ast.c'
    ])

_ast35 = Extension(
    '_ast35',
    include_dirs = ['ast35/Include'],
    sources = [
        'ast35/Parser/acceler.c',
        'ast35/Parser/bitset.c',
        'ast35/Parser/grammar.c',
        'ast35/Parser/grammar1.c',
        'ast35/Parser/node.c',
        'ast35/Parser/parser.c',
        'ast35/Parser/parsetok.c',
        'ast35/Parser/tokenizer.c',
        'ast35/Python/ast.c',
        'ast35/Python/graminit.c',
        'ast35/Python/Python-ast.c',
        'ast35/Custom/typed_ast.c'
    ])


setup (name = 'Typed AST Module',
       version = '0.1',
       description = '',
       packages = ['typed_ast'],
       ext_modules = [_ast27, _ast35])
