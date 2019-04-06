"""
Implement a queue using a fixed size array
"""


class Queue():
    def __init__(self, capacity):
        self.__queue = [None] * capacity
        self.capacity = capacity
        self.n = 0

    def enqueue(self, item):

        if self.n == self.capacity:
            raise IndexError("Queue is full!")

        self.__queue[self.n] = item
        self.n += 1

    def dequeue(self):
        item = self.__queue[0]

        # Now we have to shuffle all the items forward by 1
        for i in range(self.n - 1):
            self.__queue[i] = self.__queue[i + 1]

        # Make sure to set the last element back to None
        self.__queue[self.n - 1] = None
        self.n -= 1

        return item

    def first(self):
        return self.__queue[0]

    def is_empty(self):
        return self.n == 0

    def is_full(self):
        return self.n == self.capacity

    def __len__(self):
        return self.n
