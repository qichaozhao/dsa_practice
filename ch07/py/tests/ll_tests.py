from ch07.py.linked_list import LinkedList


def test_new_list():
    ll = LinkedList()

    assert (ll.head == ll.tail == None)
    assert (ll.length == 0)
    assert (len(ll) == 0)
    assert (ll.is_empty())


def test_append():
    ll = LinkedList()
    ll.append(0)

    assert (ll.head.item == 0)
    assert (len(ll) == 1)


def test_get():
    ll = LinkedList()
    ll.append(1)

    assert (ll[0] == 1)


def test_str():
    ll = LinkedList()
    ll.append(2)

    assert (str(ll) == '[2]')


def test_prepend():
    ll = LinkedList()
    ll.append(2)
    ll.prepend(0)

    print(ll)
    assert (ll[0] == 0)
    assert (ll[1] == 2)
    assert (ll.length == 2)


def test_insert():
    ll = LinkedList()
    ll.append(2)
    ll.insert(0, 1)
    ll.insert(1, 2)

    assert (ll[0] == 1)
    assert (ll[1] == 2)
    assert (len(ll) == 3)


def test_pop():
    ll = LinkedList()
    ll.append(2)
    ll.insert(0, 1)
    ll.insert(1, 2)

    assert (ll.pop() == 2)
    assert (ll.pop_idx(0) == 1)
    assert (ll[0] == 2)
    assert (len(ll) == 1)


def test_peek():
    ll = LinkedList()
    ll.append(2)
    ll.insert(0, 1)
    ll.insert(1, 2)

    assert (ll.front() == 1)
    assert (ll.back() == 2)
    assert (len(ll) == 3)


def test_delete():
    ll = LinkedList()
    ll.insert(0, 1)
    ll.insert(0, 2)
    ll.insert(0, 3)

    ll.delete(1)

    assert (len(ll) == 2)
    assert (ll[0] == 3)
    assert (ll[1] == 1)


def test_find():
    ll = LinkedList()
    ll.insert(0, 1)
    ll.insert(0, 2)
    ll.insert(0, 3)

    assert (ll.find(2) == 1)


def test_remove():
    ll = LinkedList()
    ll.insert(0, 1)
    ll.insert(0, 2)
    ll.insert(0, 3)

    ll.remove(2)

    assert (len(ll) == 2)
    assert (ll[0] == 3)
    assert (ll[1] == 1)
