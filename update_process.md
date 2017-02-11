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
troubleshoot problems and use your own intuition along the way.

1. Copy over the parser files from CPython.  The set of files you want is
   likely the set currently present in `ast3`.
2. Update the #ifndef guards in the header files.  You can do this with
   `./tools/update_header_guards 3`.
3. Temporarily remove `Custom/typed_ast.c` from the set of files to compile in
   setup.py.  This should allow the module to compile (though only against the
   version of Python it was copied from).
4. Update exported symbols: To avoid dynamic linker conflicts, exported `ast3`
   functions need their own unique prefix.
  1. Compile the module with `python3 setup.py build`.
  2. Generate the list of exported symbols with `./tools/find_exported_symbols 3`.
     The script may require updating to work on your platform, but should serve
     as a useful guide at minimum.
  3. The exported symbols will be written to `exported_symbols3.txt`.  Make
     sure this file looks sane, then remove `_PyInit__ast3` (which we want to
     export) and delete the excess output at the beginning of each line (including
     the leading `_` of each symbol) to end up with a list of function names to
     change.
  4. Run `./tools/update_exported_symbols 3`, which updates the exported
     symbols in all the `ast3` files with sed.  It may take a few seconds to run.
     If you're on Linux, the script will need some very slight modification to
     work properly (due to cross-platform sed argument differences).  Verify the
     changes look sane.
  5. Update `Parser/asdl_c.py`.  Use the changes from git history to guide you.
5. Make a commit.  You've likely been making commits along the way, but it's
   vitally important that there be a commit here so there can be a clean diff for
   the next time an update needs to be written (without the noise of the function
   prefix rewriting, etc).
6. Add `Custom/typed_ast.c` back to setup.py.  Temporarily remove references to
   `TYPE_COMMENT` and `Py_func_type_input` from `Custom/typed_ast.c` to allow it
   to compile.
7. Check that things seem to be working so far.  At this point, if you add the
   `_parse` function to the ast module in `Python-ast.c`, `ast3` should be able
   to compile and parse things without type information.
8. Port over the changes related to parsing type comments.  Use git history to
   guide you here.  Diffing the previous `ast3` against it's external symbol
   update commit  will show you which changes you need to make, and diffing the
   previous `ast3` against the current work in progress can be helpful for
   quickly finding where to put them.  You'll need to make `Python.asdl`
   changes, which can be built with `./tools/update_ast3_asdl`, and `Grammar`
   changes, which can be built with `./tools/update_ast3_grammar` (though the
   part that compiles pgen may need tweaking to work on your machine).  Check
   that things work before moving on.
9. Port over the changes for enforcing `feature_version`.  Check this works.
10. Add `feature_version` checks for any new syntax features in the Python
    version you're updating to.  Check these work.
11. Make the changes necessary so `ast3` can compile on the previous Python
    version.  This is new territory every time.  Spelunking in the rest of the
    CPython source can often be helpful here.
12. Port compatilibity with older Python versions.  See git history for
    details.  The changes in the previous `ast3` should likely suffice here.
13. Port compatility with Windows.  This largely involves replacing
    `PyAPI_FUNC` and `PyAPI_DATA` with `extern`.  See the git history for details.
    The changes in the previous `ast3` should likely suffice here as well.
14. Port compatility with Linux  This mainly involves making the code C89
    compatible.  See the git history for details.
15. Clean up your commit history to make sure your changes are easy to
    understand and diff for the next update.
