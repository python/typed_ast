# Typed AST
`typed_ast` is a Python 3 package that provides a Python 2.7 and Python 3
parser similar to the standard `ast` library.  Unlike `ast`, the parsers in
`typed_ast` include [PEP 484](https://www.python.org/dev/peps/pep-0484/) type
comments and are independent of the version of Python under which they are run.
The `typed_ast` parsers produce the standard Python AST (plus type comments),
and are both fast and correct, as they are based on the CPython 2.7 and 3.6
parsers.  `typed_ast` runs on Python 3.3-3.6 on Linux and OS X, and on Python
3.5-3.6 on Windows.

## Submodules
### ast3
The `ast3` parser produces the AST from the latest version of Python 3
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
