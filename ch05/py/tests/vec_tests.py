from ch05.py.vector import Vector


def test_new_vec():
    nv = Vector(5)

    assert nv.n == 0
    assert nv.capacity == 5
    assert str(nv) == '[]'
    assert nv.is_empty() == True


def test_append():
    nv = Vector(5)
    nv.append(0)

    assert nv.n == 1
    assert nv.capacity == 5
    assert nv[0] == 0


def test_resize_up():
    nv = Vector(2)
    nv.append(0)
    nv.append(1)
    nv.append(2)

    assert nv.n == 3
    assert nv.capacity == 4


def test_resize_down():
    nv = Vector(5)
    nv.append(0)
    nv.pop()

    assert nv.n == 0
    assert nv.capacity == 2


def test_pop():
    nv = Vector(5)
    nv.append(0)
    nv.append(1)

    assert nv.pop() == 1


def test_pop_idx():
    nv = Vector(5)
    nv.append(0)
    nv.append(1)

    assert nv.pop(0) == 0
    assert nv[0] == 1
    assert nv.n == 1


def test_set_item():
    nv = Vector(5)
    nv.append(0)
    nv.append(2)
    nv[0] = 5

    assert nv[0] == 5


def test_insert_item():
    nv = Vector(5)
    nv.append(0)
    nv.insert(0, 1)

    assert nv[0] == 1
    assert nv[1] == 0


def test_delete():
    nv = Vector(5)
    nv.append(0)
    nv.append(1)

    nv.delete(1)

    assert nv.n == 1
    assert nv[0] == 0


def test_remove():
    nv = Vector(5)
    nv.append(0)
    nv.append(0)
    nv.append(1)

    nv.remove(0)

    assert nv.n == 1
    assert nv[0] == 1


def test_find():
    nv = Vector(5)
    nv.append(0)
    nv.append(1)
    nv.append(2)

    assert nv.find(1) == 1
