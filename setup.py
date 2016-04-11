from distutils.core import setup, Extension

_ast35 = Extension(
    'typed_ast._ast35',
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
        'ast35/Python/Python-ast.c'
    ])


setup (name = 'Typed AST Module',
       version = '0.1',
       description = '',
       packages = ['typed_ast'],
       ext_modules = [_ast35])
