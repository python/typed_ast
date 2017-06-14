import sys
if sys.version_info[0] < 3 or sys.version_info[1] < 3:
    sys.exit('Error: typed_ast only runs on Python 3.3 and above.')

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
        'ast27/Python/asdl.c',
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


_ast3 = Extension(
    '_ast3',
    include_dirs = ['ast3/Include'],
    sources = [
        'ast3/Parser/acceler.c',
        'ast3/Parser/bitset.c',
        'ast3/Parser/grammar.c',
        'ast3/Parser/grammar1.c',
        'ast3/Parser/node.c',
        'ast3/Parser/parser.c',
        'ast3/Parser/parsetok.c',
        'ast3/Parser/tokenizer.c',
        'ast3/Python/asdl.c',
        'ast3/Python/ast.c',
        'ast3/Python/graminit.c',
        'ast3/Python/Python-ast.c',
        'ast3/Custom/typed_ast.c',
    ],
    depends = [
        'ast3/Include/asdl.h',
        'ast3/Include/ast.h',
        'ast3/Include/bitset.h',
        'ast3/Include/compile.h',
        'ast3/Include/errcode.h',
        'ast3/Include/graminit.h',
        'ast3/Include/grammar.h',
        'ast3/Include/node.h',
        'ast3/Include/parsetok.h',
        'ast3/Include/Python-ast.h',
        'ast3/Include/token.h',
        'ast3/Parser/parser.h',
        'ast3/Parser/tokenizer.h',
    ])

long_description = """
`typed_ast` is a Python 3 package that provides a Python 2.7 and Python 3
parser similar to the standard `ast` library.  Unlike `ast`, the parsers in
`typed_ast` include PEP 484 type comments and are independent of the version of
Python under which they are run.  The `typed_ast` parsers produce the standard
Python AST (plus type comments), and are both fast and correct, as they are
based on the CPython 2.7 and 3.6 parsers.
""".strip()

setup (name = 'typed-ast',
       version = '1.0.4',
       description = 'a fork of Python 2 and 3 ast modules with type comment support',
       long_description = long_description,
       author = 'David Fisher',
       author_email = 'ddfisher@dropbox.com',
       url = 'https://github.com/python/typed_ast',
       license='Apache License 2.0',
       platforms = ['POSIX', 'Windows'],
       classifiers = [
           'Development Status :: 5 - Production/Stable',
           'Environment :: Console',
           'Intended Audience :: Developers',
           'Operating System :: POSIX',
           'Operating System :: Microsoft',
           'Programming Language :: Python :: 3.3',
           'Programming Language :: Python :: 3.4',
           'Programming Language :: Python :: 3.5',
           'Programming Language :: Python :: 3.6',
           'Topic :: Software Development',
       ],
       packages = ['typed_ast'],
       ext_modules = [_ast27, _ast3])
