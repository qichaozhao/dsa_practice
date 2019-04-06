from ch06.py.arr_queue import Queue


def test_create_queue():
    q = Queue(10)

    assert (q.capacity == 10)
    assert (q.n == 0)


def test_enqueue():
    q = Queue(10)
    q.enqueue(10)

    assert (q.first() == 10)
    assert (len(q) == 1)


def test_dequeue():
    q = Queue(10)
    q.enqueue(10)
    q.enqueue(20)

    deq = q.dequeue()
    assert (deq == 10)
    assert (len(q) == 1)

    deq = q.dequeue()
    assert (deq == 20)
    assert (len(q) == 0)

def test_empty():
    q = Queue(10)

    assert (q.is_empty())


def test_full():
    q = Queue(2)

    assert (q.is_full() is False)
    q.enqueue(1)
    q.enqueue(2)
    assert (q.is_full())
