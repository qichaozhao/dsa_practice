"""
Implement a queue using a resizeable circular array
"""


class Queue():
    def __init__(self):
        # Specify an initial capacity of 16
        self.capacity = 16
        self.__queue = [None] * self.capacity
        self.n = 0
        self.f = 0

    def __resize(self, new_capacity):

        new = [None] * new_capacity

        # Loop through all elements and copy them from the old list to the new list
        for i in range(self.n):
            new[i] = self.__queue[(self.f + i) % self.capacity]

        # Set the new capacity and queue variable
        self.capacity = new_capacity
        self.__queue = new
        self.f = 0

    def enqueue(self, item):

        if self.n == self.capacity:
            self.__resize(self.capacity * 2)

        idx = (self.f + self.n) % self.capacity
        self.__queue[idx] = item
        self.n += 1

    def dequeue(self):
        item = self.__queue[self.f]
        self.f = (self.f + 1) % self.capacity
        self.n -= 1

        # Resize the queue if needed
        if self.n < self.capacity // 4:
            self.__resize(self.capacity // 2)

        return item

    def first(self):
        return self.__queue[self.f]

    def is_empty(self):
        return self.n == 0

    def __len__(self):
        return self.n
