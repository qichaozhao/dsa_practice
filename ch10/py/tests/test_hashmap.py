from ch10.py.hashmap import ProbeHashMap
import pytest


def test_new():
    hm = ProbeHashMap()

    assert (len(hm._table) == 11)


def test_add():
    hm = ProbeHashMap(cap=5)
    hm[1] = 3

    assert (len(hm._table) == 5)
    assert (len(hm) == 1)
    assert (hm[1] == 3)


def test_delete():
    hm = ProbeHashMap(cap=5)
    hm[1] = 3
    hm[2] = 3

    assert (len(hm._table) == 5)
    assert (len(hm) == 2)
    assert (hm[1] == 3)
    assert (hm[2] == 3)

    del hm[2]

    with pytest.raises(KeyError):
        assert (hm[2])


def test_get_error():
    hm = ProbeHashMap(cap=5)

    with pytest.raises(KeyError):
        assert (hm[3])


def test_resize():
    hm = ProbeHashMap(cap=2)
    assert (len(hm._table) == 2)

    hm[1] = 3
    assert (len(hm._table) == 2)

    hm[2] = 3
    assert (len(hm._table) == 5)
