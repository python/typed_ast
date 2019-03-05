# Typed AST

[![Build Status](https://travis-ci.org/python/typed_ast.svg?branch=master)](https://travis-ci.org/python/typed_ast)
[![Chat at https://gitter.im/python/typed_ast](https://badges.gitter.im/python/typed_ast.svg)](https://gitter.im/python/typed_ast)

`typed_ast` is a Python 3 package that provides a Python 2.7 and Python 3
parser similar to the standard `ast` library.  Unlike `ast`, the parsers in
`typed_ast` include [PEP 484](https://www.python.org/dev/peps/pep-0484/) type
comments and are independent of the version of Python under which they are run.
The `typed_ast` parsers produce the standard Python AST (plus type comments),
and are both fast and correct, as they are based on the CPython 2.7 and 3.6
parsers.  `typed_ast` runs on Python 3.3-3.7 on Linux, OS X and Windows.

## Development Philosophy

This project is a (mostly) drop-in replacement for the builtin `ast` module.  It is
intended to be bug-for-bug compatible and behave identically, except for the
presence of a few additional fields on the returned classes and a few
additional optional arguments to the `parse` call.  Therefore, `typed_ast` will
not accept any bugfixes for bugs in `ast` -- they should be fixed upstream
instead.  To avoid feature bloat, any new features for `typed_ast` should have
the potential to be broadly useful and not be built just for one niche usecase
or in a manner such that only one project can use them.

### Incompatibilities

For the purposes of *consuming* syntax trees, this should be a drop-in replacement.
It is not a drop-in replacement for users that wish to create or transform ASTs,
as a number of syntax tree classes have additional fields that must be populated
when constructing them.

### Python 3.7

`typed_ast` has not yet been updated to be based on the Python 3.7
parser. The main consequence of this that `await` and `async` are
not treated as keywords.

## Submodules
### ast3
The `ast3` parser produces the AST from a recent version of Python 3
(currently Python 3.6).  When new versions of Python 3 are released, it will be
updated to match any changes in their AST.  (For rationale and technical
details, see [here](update_process.md).)  The AST it currently produces is described in
[ast3/Parser/Python.asdl](ast3/Parser/Python.asdl).  If you wish to limit
parsing to older versions of Python 3, `ast3` can be configured to to give a
SyntaxError for new syntax features introduced beyond a given Python version.
For more information, see the module docstring in
[typed\_ast/ast3.py](typed_ast/ast3.py).

### ast27
The `ast27` parser tracks the standard Python 2.7 AST, which is expected to
never receive further updates. The AST it produces is described in
[ast27/Parser/Python.asdl](ast27/Parser/Python.asdl).  For more information,
see the module docstring in [typed\_ast/ast27.py](typed_ast/ast27.py).

### conversions
`typed_ast` also provides a `conversions` module which converts `ast27` ASTs
into `ast3` ASTs.  This functionality is somewhat experimental, however.  For
more information, see the `py2to3` docstring in
[typed\_ast/conversions](typed_ast/conversions.py).


Note: as these parsers consider type comments part of the grammar, incorrectly
placed type comments are considered syntax errors.

## Updates and Releases
To update `typed_ast` for new major Python releases, see [`update_process.md`](update_process.md).

To make a new `typed_ast` release, see [`release_process.md`](release_process.md).
