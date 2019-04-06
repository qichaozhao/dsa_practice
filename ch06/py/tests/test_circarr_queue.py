from ch06.py.circarr_queue import Queue


def test_create_queue():
    q = Queue()

    assert (q.capacity == 16)
    assert (q.n == 0)


def test_enqueue():
    q = Queue()
    q.enqueue(10)

    assert (q.first() == 10)
    assert (len(q) == 1)


def test_increase_size():
    q = Queue()
    for i in range(0, 16):
        q.enqueue(i)
        assert (q.capacity == 16)

    q.enqueue(17)
    assert (q.capacity == 32)


def test_dequeue():
    q = Queue()
    q.enqueue(10)
    q.enqueue(20)

    deq = q.dequeue()
    assert (deq == 10)
    assert (len(q) == 1)

    deq = q.dequeue()
    assert (deq == 20)
    assert (len(q) == 0)


def test_decrease_size():
    q = Queue()
    q.enqueue(10)
    q.enqueue(20)

    assert (q.n == 2)
    assert (q.capacity == 16)

    q.dequeue()
    assert (q.n == 1)
    assert (q.capacity == 8)


def test_empty():
    q = Queue()

    assert (q.is_empty())
