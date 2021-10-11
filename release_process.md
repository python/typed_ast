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
4. Wait for the GitHub Actions build to complete.
5. Download all assets from the release made by the GitHub build.
6. Compare the wheels produced with the previous release of typed-ast to make sure
   you have the full matrix.
7. If possible, verify the final `typed_ast` wheels work on Windows, macOS,
   and Linux platforms.
8. Upload the sdist and wheels to PyPI with `twine upload dist/*`.
9. Make a commit which bumps the bugfix version and adds back the `.dev0`
   suffix.
