import os

import pytest

import _ast3

# Lowest and highest supported Python 3 minor version (inclusive)
MIN_VER = 4
MAX_VER = 6
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


vardecl = """\
a = 0  # type: int
a  # type: int
"""
def test_vardecl():
    for version in range(MIN_VER, NEXT_VER):
        tree = _ast3._parse(vardecl, "<vardecl>", "exec", version)
        assert tree.body[0].type_comment == "int"
        # Curious fact: an expression can have a type comment
        # but it is lost in the AST.


forstmt = """\
for a in []:  # type: int
    pass
"""
def test_forstmt():
    for version in range(MIN_VER, NEXT_VER):
        tree = _ast3._parse(forstmt, "<forstmt>", "exec", version)
        assert tree.body[0].type_comment == "int"


withstmt = """\
with context():  # type: int
    pass
"""
def test_withstmt():
    for version in range(MIN_VER, NEXT_VER):
        tree = _ast3._parse(withstmt, "<withstmt>", "exec", version)
        assert tree.body[0].type_comment == "int"


# A test function named 'fabvk' would have two positional args, a and b,
# plus a var-arg *v, plus a kw-arg **k.  It is verified in test_longargs()
# that it has exactly these arguments, no more, no fewer.
longargs = """\
def fa(
    a = 1,  # type: A
):
    pass

def fa(
    a = 1  # type: A
):
    pass

def fab(
    a,  # type: A
    b,  # type: B
):
    pass

def fab(
    a,  # type: A
    b  # type: B
):
    pass

def fv(
    *v,  # type: V
):
    pass

def fv(
    *v  # type: V
):
    pass

def fk(
    **k,  # type: K
):
    pass

def fk(
    **k  # type: K
):
    pass

def fvk(
    *v,  # type: V
    **k,  # type: K
):
    pass

def fvk(
    *v,  # type: V
    **k  # type: K
):
    pass

def fav(
    a,  # type: A
    *v,  # type: V
):
    pass

def fav(
    a,  # type: A
    *v  # type: V
):
    pass

def fak(
    a,  # type: A
    **k,  # type: K
):
    pass

def fak(
    a,  # type: A
    **k  # type: K
):
    pass

def favk(
    a,  # type: A
    *v,  # type: V
    **k,  # type: K
):
    pass

def favk(
    a,  # type: A
    *v,  # type: V
    **k  # type: K
):
    pass

"""
def test_longargs():
    for version in range(MIN_VER, NEXT_VER):
        tree = _ast3._parse(longargs, "<longargs>", "exec", version)
        for t in tree.body:
            # The expected args are encoded in the function name
            todo = set(t.name[1:])
            assert len(t.args.args) == len(todo) - bool(t.args.vararg) - bool(t.args.kwarg)
            assert t.name.startswith('f')
            for c in t.name[1:]:
                todo.remove(c)
                if c == 'v':
                    arg = t.args.vararg
                elif c == 'k':
                    arg = t.args.kwarg
                else:
                    assert 0 <= ord(c) - ord('a') < len(t.args.args)
                    arg = t.args.args[ord(c) - ord('a')]
                assert arg.arg == c  # That's the argument name
                assert arg.type_comment == arg.arg.upper()
            assert not todo


ignores = """\
def foo():
    pass  # type: ignore

def bar():
    x = 1  # type: ignore
"""
def test_ignores():
    for version in range(MIN_VER, NEXT_VER):
        tree = _ast3._parse(ignores, "<ignores>", "exec", version)
        assert [ti.lineno for ti in tree.type_ignores] == [2, 5]


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


strkind = """\
plain = 'abc'
raw = r'abc'
"""
def test_strkind():
    # Test that Str() objects have a kind argument/attribute.
    node = _ast3.Str("foo", "r")
    assert node.s == "foo"
    assert node.kind == "r"
    for version in range(MIN_VER, NEXT_VER):
        tree = _ast3._parse(strkind, "<strkind>", "exec", version)
        assert tree.body[0].value.kind == ""
        assert tree.body[1].value.kind == "r"
