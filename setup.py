try:
    from setuptools import setup, Extension
except ImportError:
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
        'ast27/Custom/typed_ast.c',
    ],
    depends = [
        'ast27/Include/asdl.h',
        'ast27/Include/ast.h',
        'ast27/Include/bitset.h',
        'ast27/Include/compile.h',
        'ast27/Include/errcode.h',
        'ast27/Include/graminit.h',
        'ast27/Include/grammar.h',
        'ast27/Include/node.h',
        'ast27/Include/parsetok.h',
        'ast27/Include/Python-ast.h',
        'ast27/Include/token.h',
        'ast27/Parser/parser.h',
        'ast27/Parser/tokenizer.h',
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
        'ast35/Custom/typed_ast.c',
    ],
    depends = [
        'ast35/Include/asdl.h',
        'ast35/Include/ast.h',
        'ast35/Include/bitset.h',
        'ast35/Include/compile.h',
        'ast35/Include/errcode.h',
        'ast35/Include/graminit.h',
        'ast35/Include/grammar.h',
        'ast35/Include/node.h',
        'ast35/Include/parsetok.h',
        'ast35/Include/Python-ast.h',
        'ast35/Include/token.h',
        'ast35/Parser/parser.h',
        'ast35/Parser/tokenizer.h',
    ])

long_description = """
This package is a fork of the CPython 2.7 and 3.5 `ast` modules with the
ability to parse PEP 484 (https://www.python.org/dev/peps/pep-0484/) type
comments.  The primary goals of this package are correctness and speed.
""".strip()

setup (name = 'typed-ast',
       version = '0.5.2',
       description = 'fork of Python 2 and 3 ast modules with type comment support',
       long_description = long_description,
       author = 'David Fisher',
       author_email = 'ddfisher@dropbox.com',
       url = 'https://github.com/dropbox/typed_ast',
       license='Apache License 2.0',
       platforms = ['POSIX'],
       classifiers = [
           'Development Status :: 3 - Alpha',
           'Environment :: Console',
           'Intended Audience :: Developers',
           'Operating System :: POSIX',
           'Programming Language :: Python :: 3.3',
           'Programming Language :: Python :: 3.4',
           'Programming Language :: Python :: 3.5',
           'Topic :: Software Development',
       ],
       packages = ['typed_ast'],
       ext_modules = [_ast27, _ast35])
