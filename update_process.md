# New Python Version Update Process for Typed AST

When a new minor version of Python 3 is released, `typed_ast` will be updated
by forking the new `ast` module and porting the `typed_ast` changes on top of
it.  The old `ast3` code will be thrown away and replaced by this fresh fork.
For point releases, in the unlikely event that they contain an important parser
fix, this fix will be ported on top of the current code.


## Rationale

Initially, `typed_ast` was designed to have a new `ast3` version for every
Python 3 minor version, i.e. `ast35`, `ast36`, etc.  However, we've since
decided to have only one `ast3`, which is kept up to date with the latest
Python 3.  The primary reason for this is that we don't want clients to have to
deal with many different subtly different ASTs if they wish to support multiple
Python 3 versions.  We'd also prefer not to have to support an ever-growing
number of AST modules.  We think the downside to this approach is small: we
expect clients to be primarily interested in restricting use of new Python
syntax features (which we can and do support with the current system) rather
than in the specifics of the old AST.

We choose to make `typed_ast` updates afresh on new minor Python versions
because we've found that much easier than porting potentially large changes on
top of the `typed_ast` codebase.


## Pre-release Python Versions
It's sometimes desirable to be able to parse upcomming Python versions before
they're released.  To support this, we will add an `astnext` module, which will
liberally accept PRs for ports of new Python features.


# Technical Details

Following are the general steps to follow to update `typed_ast` for a new minor
version of Python.  They are not meant to be comprehensive -- you'll have to
troubleshoot problems and use your own intuition along the way.  Most steps have
an example commit hash in parentheses from the Python 3.6 update.

(At a high level, steps 1-4 alter the code so it uses `Ta3` instead of
`Py` as a prefix for globals; the next few steps add support for type
comments to the lexer, grammar and "asdl" machinery; then we add
support for `feature_version`; finally we work on making the code
compatible with older Python versions and other platforms.)

Note that steps 1-4 can be automated using tools/script and various
other files in tools/.  You need to install GNU binutils in order
to be able to use gobjdump in tools/find_exported_symbols
(e.g. `brew install binutils`).  The script assumes you're on a Mac
and your CPython source tree is at `~/src/cpython37`.

1. Copy over the parser files from CPython.  The set of files you want is
   likely the set currently present in `ast3`.
   ([a377f1e](https://github.com/python/typed_ast/commit/a377f1e3deb332bfbec3f3bb0d4c42768626d8d4))
2. Update the #ifndef guards in the header files.  You can do this with
   `./tools/update_header_guards 3`.
   ([82a19dd](https://github.com/python/typed_ast/commit/82a19ddddf35170e9ef36c62fbfc1f01c3bce145))
3. Temporarily remove `Custom/typed_ast.c` from the set of files to compile in
   setup.py.  This should allow the module to compile (though only against the
   version of Python it was copied from).
4. Update exported symbols: To avoid dynamic linker conflicts, exported `ast3`
   functions need their own unique prefix.

   1. Starting with an empty `build` directory, compile the module with `python3 setup.py build`.
   2. Generate the list of exported symbols with `./tools/find_exported_symbols 3`.
      The script may require updating to work on your platform, but should serve
      as a useful guide at minimum.
   3. The exported symbols will be written to `exported_symbols3.txt`.  Make
      sure this file looks sane, then remove `_PyInit__ast3` (which we want to
      export) to end up with a list of function names to change.
   4. Run `./tools/update_exported_symbols 3`, which updates the exported
      symbols in all the `ast3` files with sed.  It may take a few seconds to run.
      If you're on Linux, the script will need some very slight modification to
      work properly (due to cross-platform sed argument differences).  Verify the
      changes look sane.
      ([d1ec7d0](https://github.com/python/typed_ast/commit/d1ec7d07cb6a7fe016d9446a196dfa3b86c5acf6))
   5. Update `Parser/asdl_c.py`.  Use the changes from git history to guide you.
      (Don't be distracted by the generated files in that commit; look at asdl_c.py only.
      Much of this renames _ast to _ast3 and substitutes certain _Py_ prefixes with _Ta3_.)
      Update the generated files with `tools/update_ast3_asdl`.
      ([29dbec4](https://github.com/python/typed_ast/commit/29dbec47aa145d84e5faaa431ce3b3afca233b3d))

5. Make a commit.  You've likely been making commits along the way, but it's
   vitally important that there be a commit here so there can be a clean diff for
   the next time an update needs to be written (without the noise of the function
   prefix rewriting, etc).
6. Add `Custom/typed_ast.c` back to setup.py.  To allow it to compile,
   temporarily comment out references to `TYPE_COMMENT` and `Py_func_type_input` and
   also the `feature_version` argument in the call to `Ta3AST_FromNodeObject()`.
   ([b7a034b](https://github.com/python/typed_ast/commit/b7a034bc657dcfd5681b505f3949603fa6597116))
7. Check that things seem to be working so far.  At this point, if you add the
   `_parse` function to the ast module in `Python-ast.c`, `ast3` should be able
   to compile and parse things without type information.
   ([5e1885c](https://github.com/python/typed_ast/commit/5e1885cf54e1434a9422f3f797ecb1ed6fb42fb6))
8. Port over the changes related to parsing type comments.  Use git history to
   guide you here.  Diffing the previous `ast3` against its external symbol
   update commit  will show you which changes you need to make, and diffing the
   previous `ast3` against the current work in progress can be helpful for
   quickly finding where to put them.  You'll need to make `Python.asdl`
   changes, which can be built with `./tools/update_ast3_asdl`, and `Grammar`
   changes, which can be built with `./tools/update_ast3_grammar` (though the
   part that compiles pgen may need tweaking to work on your machine).  Check
   that things work before moving on.
   ([f74d9f3](https://github.com/python/typed_ast/commit/f74d9f3f231110639752c30c0ae5fbebe870ebc6))
   A bit more detail:

   - Add the `TYPE_IGNORE` and `TYPE_COMMENT` symbols to `Include/token.h`, and updating `N_TOKENS`;
     also add theze to the list of strings in `Parser/tokenizer.c` (in the same order!)
   - NOTE: As of Python 3.7, the `ASYNC` and `AWAIT` symbols also need to be added to both places
   - Update `Parser/Python.asdl` to add `type_comments` and `type_ignores` to various definitions
     and run `tools/update_ast3_asdl`; this updates `Include/Python-ast.h` and `Python/Python-ast.c`
   - Reapply other patches to `Parser/parsetok.c` and `Parser/tokenizer.c` (these implement
     recognition of type comments)
   - Add `[TYPE_COMMENT]` to various places in `Grammar/Grammar`, and then run
     `tools/update_ast3_grammar`; this updates `Python/graminit.c` and `Include/graminit.h`
   - NOTE: As of Python 3.7, this is problematic because the upstream developers like to add
     dependencies on CPython internals to pgen.  I ended up copying some files into CPython,
     running pgen there (`make regen-grammar`), and copying the results back
   - Copy the definition of `Py_func_type_input` from `Python/graminit.h` to `Include/compile.h`
   - NOTE: As of Python 3.7, compile.h depends on CPython internals; I ended up creating a small
     file compile-ast3.h with just the four symbols we need (maybe we even only need the one)
   - Attempt compilation and fix errors, e.g. add an extra argument to `Module(stmts, arena)`
     to pass `type_ignores`

9. Port over the changes for enforcing `feature_version`.  Check this works.
   ([89aebce](https://github.com/python/typed_ast/commit/89aebcefb612c113446e3a877f78b93e4cf142b3))
10. Add `feature_version` checks for any new syntax features in the Python
    version you're updating to.  Check these work.
11. Make the changes necessary so `ast3` can compile on previous Python
    versions.  This is new territory every time.  Spelunking in the rest of the
    CPython source can often be helpful here.
    ([5ea3eb8](https://github.com/python/typed_ast/commit/5ea3eb8447fd5c72c6f390014b1f7ea7cd6119ea))
12. Port compatilibity with older Python versions.  See git history for
    details.
    ([8d2aeae](https://github.com/python/typed_ast/commit/8d2aeae8651c7e86ac51d7abefb91cb563c94555))
13. Port compatility with Windows.  This largely involves replacing
    `PyAPI_FUNC` and `PyAPI_DATA` with `extern`.  See the git history for details.
    The changes in the previous `ast3` should likely suffice here as well.
    ([99b5770](https://github.com/python/typed_ast/commit/99b577060eecd5bdbbfa8e590399c619d026366f))
14. Port compatility with Linux  This mainly involves making the code C89
    compatible.  See the git history for details.
    ([b37529e](https://github.com/python/typed_ast/commit/b37529e1fd02f3556374f9078458c19d3e6d937a))
15. Clean up your commit history to make sure your changes are easy to
    understand and diff for the next update.
