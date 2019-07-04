class Item(object):
    """
    An item which encapsulates our key, value pair
    """
    __slots__ = 'key', 'value'

    def __init__(self, key, value):
        self.key = key
        self.value = value

    def __lt__(self, other):
        return self.key < other.key

    def __le__(self, other):
        return self.key <= other.key

    def __eq__(self, other):
        return self.key == other.key and self.value == other.value

    def __str__(self):
        return "({}, {})".format(self.key, self.value)


class MinHeap(object):
    """
    A heap based priority queue written on top of a python list
    """

    def __init__(self):
        self.data = []

    #
    # Private methods for treating the list like a tree
    #
    def __str__(self):
        return str(self.data)

    def __parent(self, idx):
        return (idx - 1) // 2

    def __left(self, idx):
        return (2 * idx) + 1

    def __right(self, idx):
        return (2 * idx) + 2

    def __has_left(self, idx):
        return self.__left(idx) < len(self.data)

    def __has_right(self, idx):
        return self.__right(idx) < len(self.data)

    def __swap(self, i, j):
        """
        Swap the elements at indices i and j of the array

        :param i:
        :param j:
        :return:
        """
        self.data[i], self.data[j] = self.data[j], self.data[i]

    def __sift_up(self, idx):

        # Base case, the heap property is satisfied
        # Or idx is zero
        if self.data[self.__parent(idx)] < self.data[idx] or idx == 0:
            return

        else:
            # Swap the parent and the element
            self.__swap(idx, self.__parent(idx))

            # Sift on the parent
            self.__sift_up(self.__parent(idx))

    def __sift_down(self, idx):

        # Get the child with which to compare
        c = None

        # First case, we are the root...
        if self.__has_left(idx) is False and self.__has_right(idx) is False:
            return

        # Second case, left child only
        elif self.__has_left(idx) is True and self.__has_right(idx) is False:
            c = self.__left(idx)

        # Third case, left and right children
        elif self.__has_left(idx) is True and self.__has_right(idx) is True:

            if self.data[self.__left(idx)] < self.data[self.__right(idx)]:
                c = self.__left(idx)
            else:
                c = self.__right(idx)

        else:
            raise Exception("We should not be here!")

        # Base case, the heap property is satisfied
        if self.data[idx] <= self.data[c]:
            return

        else:
            # Swap the node and the child
            self.__swap(idx, c)

            # Sift down on the child
            self.__sift_down(c)

    #
    # Public methods
    #
    def __len__(self):
        return len(self.data)

    def insert(self, key, value):

        self.data.append(Item(key, value))
        self.__sift_up(len(self.data) - 1)

    def min(self):
        """
        Get the minimum value

        :return:
        """

        if len(self.data) == 0:
            raise Exception("Queue is empty...")

        return self.data[0].key, self.data[0].value

    def pop(self):
        """
        Remove and return the head of the queue

        :return:
        """

        if len(self.data) == 0:
            raise Exception("Queue is empty...")

        # Swap the head to the end of the list
        # Then pop
        self.__swap(0, len(self.data) - 1)
        item = self.data.pop()

        # Now fix the root by down-sifting
        self.__sift_down(0)
        return item.key, item.value

    def heapify(self, arr, j=None, k=None):
        """
        Takes an array of elements and turns it into a heap, j and k define boundaries so we can heapify just part of an array

        :param arr:
        :j:
        :k:
        :return:
        """

        self.data = arr

        j = 0 if j is None else j
        k = len(self.data) - 1 if k is None else k

        start = self.__parent(k)
        for i in range(start, j - 1, -1):
            self.__sift_down(i)

    def heap_sort(self):
        """
        Returns a sorted array from our heap

        Since we have a min heap we make use of an extra array to store results

        If we had a max heap we could do this in place
        :return:
        """

        out = []
        while len(self.data) > 0:
            out.append(self.pop())

        return out
