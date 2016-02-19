from distutils.core import setup, Extension

_typed_ast = Extension(
    '_typed_ast_27',
    include_dirs = ['Include'],
    sources = [
        'Parser/acceler.c',
        'Parser/bitset.c',
        'Parser/grammar.c',
        'Parser/grammar1.c',
        'Parser/node.c',
        'Parser/parser.c',
        'Parser/parsetok.c',
        'Parser/tokenizer.c',
        'Python/ast.c',
        'Python/graminit.c',
        'Python/Python-ast.c',
        'Custom/typed_ast.c'
    ])


setup (name = 'Typed AST Module',
       version = '0.1',
       description = '',
       package_dir = {'': 'Lib'},
       py_modules = [],
       ext_modules = [_typed_ast])
