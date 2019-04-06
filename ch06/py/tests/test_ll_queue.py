from ch06.py.ll_queue import Queue


def test_enqueue():
    q = Queue()
    q.enqueue(10)

    assert (q.first() == 10)
    assert (len(q) == 1)


def test_dequeue():
    q = Queue()
    q.enqueue(10)
    deq = q.dequeue()

    assert (deq == 10)
    assert (len(q) == 0)


def test_empty():
    q = Queue()

    assert (q.is_empty())
