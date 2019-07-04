from random import randrange


class ProbeHashMap(object):
    _AVAIL = object()

    class _Item(object):
        __slots__ = 'key', 'value'

        def __init__(self, k, v):
            self.key = k
            self.value = v

    def __init__(self, cap=11, p=109345121):
        """
        Initiate a hashmap using linear probing where the hash function is MAD (multiply add divide)

        :param cap:
        :param p:
        """

        self._table = [None] * cap
        self._n = 0
        self._p = p
        self._a = 1 + randrange(p - 1)
        self._b = randrange(p - 1)

    def _hash(self, o):
        return ((self._a * hash(o) + self._b) % self._p) % len(self._table)

    def __len__(self):
        return self._n

    def _find_slot(self, key):
        k = self._hash(key)

        tbl_entry = self._table[k]
        while tbl_entry is not None and tbl_entry != ProbeHashMap._AVAIL:

            if key == tbl_entry.key:
                return (True, k)

            k = (k + 1) % len(self._table)
            tbl_entry = self._table[k]

        return (False, k)

    def __getitem__(self, key):
        found, k = self._find_slot(key)

        if found is True:
            return self._table[k].value

        raise KeyError("Key not found!")

    def __setitem__(self, key, value):
        found, k = self._find_slot(key)

        if found is True:
            self._table[k].value = value

        else:
            self._table[k] = self._Item(key, value)
            self._n += 1

        if self._n > len(self._table) // 2:
            self._resize(len(self._table) * 2 - 1)

    def __delitem__(self, key):
        found, k = self._find_slot(key)

        if found is True:
            self._table[k] = ProbeHashMap._AVAIL
            self._n -= 1
        else:
            raise KeyError("Key not found!")

    def _resize(self, c):

        old = list(self)
        self._table = [None] * c
        self._n = 0

        for k, v in enumerate(old):
            self[k] = v

    def __iter__(self):
        for b in self._table:
            if b is not None and b != ProbeHashMap._AVAIL:
                yield b
