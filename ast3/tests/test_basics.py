def test_dunder_ast3():
    print()
    import _ast3
    print(_ast3.__file__)
    with open(__file__) as f:
        tree = _ast3._parse(f.read(), __file__, 'exec', 7)  # type: ignore
        print(tree)

a = 12  # type: int
