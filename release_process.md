# Typed AST PyPI Release Process
0. Thoroughly test the prospective release.
1. Make a commit titled "Release version \[version number\]" which removes the
   `-dev0` suffix of the version string in
   [`typed_ast/__init__.py`](https://github.com/python/typed_ast/blob/master/typed_ast/__init__.py).
   Switch the version to a new minor version if there have been
   backwards-incompatible changes.
2. Make a git tag pointing to this commit with the version number as the name
   of the tag.
3. Push the commit and the tag.
4. Wait for the Travis CI and Appveyor builds to complete.
5. Make sure there's nothing in your `typed_ast/dist` directory.
6. Run `python3 setup.py sdist` (this creates `dist/typed-ast-VERSION.tar.gz`).
7. Download the wheels from Travis-CI and Appveyor.  This can be done using
   `tools/download_typed_ast.py`, or manually:

   1. Find the Appveyor build for the tag
      [here](https://ci.appveyor.com/project/ddfisher/typed-ast-a4xqu/history) and
      download the artifact produced by each job into the `dist` directory.
   2. Download [the latest manylinux
      wheels](https://console.cloud.google.com/storage/browser/typed-ast) into the
      `dist` directory.  (You will have to sign in with your Google account to
      access these wheels, but all Google accounts have access.)

8. On a Mac with Python 3.6, 3.7, and 3.8 installed, run
  `python3.6 setup.py bdist_wheel`, `python3.7 setup.py bdist_wheel`,
  and `python3.8 setup.py bdist_wheel` (this creates wheels in `dist`).
9. Upload the sdist and wheels to PyPI with `twine upload dist/*`.
10. If possible, verify the final `typed_ast` wheels work on Windows, MacOS,
    and Linux platforms.
11. Make a commit which bumps the bugfix version and adds back the `.dev0`
    suffix.
