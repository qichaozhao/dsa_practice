from ch09.py.heap_tree import Item, MinHeapTree


def test_init():
    hp = MinHeapTree()
    assert (hp.length == 0)


def test_min():
    hp = MinHeapTree()
    hp.insert(5, "A")
    res = hp.min()

    assert ((res.key, res.value) == (5, "A"))
    assert (hp.length == 1)


def test_insert():
    hp = MinHeapTree()

    hp.insert(5, "A")
    res = hp.min()
    assert ((res.key, res.value) == (5, "A"))

    hp.insert(3, "B")
    res = hp.min()
    assert ((res.key, res.value) == (3, "B"))

    hp.insert(9, "C")
    res = hp.min()
    assert ((res.key, res.value) == (3, "B"))


def test_pop():
    hp = MinHeapTree()
    hp.insert(5, "A")
    hp.insert(9, "C")
    hp.insert(3, "B")
    hp.insert(7, "D")

    itam = hp.pop()

    assert (hp.length == 3)
    assert (hp.min() == Item(5, "A"))
    assert ((itam.key, itam.value) == (3, "B"))

    itam = hp.pop()

    assert ((itam.key, itam.value) == (5, "A"))

    itam = hp.pop()

    assert ((itam.key, itam.value) == (7, "D"))

    itam = hp.pop()

    assert ((itam.key, itam.value) == (9, "C"))
