from ch09.py.heap_arr import Item, MinHeap


def test_init():
    hp = MinHeap()
    assert (len(hp.data) == 0)


def test_insert():
    hp = MinHeap()
    hp.insert(5, "A")

    assert (hp.min() == (5, "A"))

    hp.insert(3, "B")

    assert (hp.min() == (3, "B"))

    hp.insert(9, "C")

    assert (hp.min() == (3, "B"))
    assert (hp.data == [Item(3, "B"), Item(5, "A"), Item(9, "C")])


def test_min():
    hp = MinHeap()
    hp.insert(5, "A")
    assert (hp.min() == (5, "A"))
    assert (hp.data[0] == Item(5, "A"))
    assert (len(hp.data) == 1)

    print("hello")
    print(hp)


def test_pop():
    hp = MinHeap()
    hp.insert(5, "A")
    hp.insert(9, "C")
    hp.insert(3, "B")
    hp.insert(7, "D")

    key, val = hp.pop()

    assert (len(hp.data) == 3)
    assert (hp.min() == (5, "A"))
    assert ((key, val) == (3, "B"))

    key, val = hp.pop()

    assert ((key, val) == (5, "A"))

    key, val = hp.pop()

    assert ((key, val) == (7, "D"))

    key, val = hp.pop()

    assert ((key, val) == (9, "C"))
