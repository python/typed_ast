import os

import pytest

import _ast3

# Lowest and highest supported Python 3 minor version (inclusive)
MIN_VER = 4
MAX_VER = 7
NEXT_VER = MAX_VER + 1


basics = """\
def foo():
    # type: () -> int
    pass

def bar():  # type: () -> None
    pass
"""
def test_basics():
    for version in range(MIN_VER, NEXT_VER):
        tree = _ast3._parse(basics, "<basics>", "exec", version)
        assert tree.body[0].type_comment == "() -> int"
        assert tree.body[1].type_comment == "() -> None"


# TODO: type comment on new line (currently fails)
asyncfunc = """\
async def foo():  # type: () -> int
    return await bar()
"""
def test_asyncfunc():
    for version in range(3, 5):
        with pytest.raises(SyntaxError):
            _ast3._parse(asyncfunc, "<asyncfunc>", "exec", version)
    for version in range(5, NEXT_VER):
        tree = _ast3._parse(asyncfunc, "<asyncfunc>", "exec", version)
        assert tree.body[0].type_comment == "() -> int"


asyncvar = """\
async = 12
await = 13
"""
def test_asyncvar():
    for version in range(3, 7):
        tree = _ast3._parse(asyncvar, "<asyncvar>", "exec", version)
    for version in range(7, NEXT_VER):
        with pytest.raises(SyntaxError):
            _ast3._parse(asyncvar, "<asyncvar>", "exec", version)


asynccomp = """\
async def foo(xs):
    [x async for x in xs]
"""
def test_asynccomp():
    for version in range(3, 6):
        with pytest.raises(SyntaxError):
            tree = _ast3._parse(asynccomp, "<asynccomp>", "exec", version)
    for version in range(6, NEXT_VER):
            _ast3._parse(asynccomp, "<asynccomp>", "exec", version)


matmul = """\
a = b @ c
"""
def test_matmul():
    for version in range(3, 5):
        with pytest.raises(SyntaxError):
            tree = _ast3._parse(matmul, "<matmul>", "exec", version)
    for version in range(5, NEXT_VER):
        tree = _ast3._parse(matmul, "<matmul>", "exec", version)
