"""
A queue implementation backed by a linked list with a tail pointer. An adapter pattern!
"""

from ch06.py.linked_list import LinkedList


class Queue(object):
    def __init__(self):
        self.__queue = LinkedList()

    def enqueue(self, item):
        """
        Method for adding a new item at the back of the queue

        :param item:
        :return:
        """
        self.__queue.append(item)

    def dequeue(self):
        """
        Method for returning an item from the front of the queue

        :return:
        """
        return self.__queue.pop_idx(0)

    def first(self):
        """
        Peek at the front of the queue without dequeueing it

        :return:
        """
        return self.__queue.front()

    def is_empty(self):
        """
        Boolean value on whether the queue is empty

        :return:
        """
        return self.__queue.is_empty()

    def __len__(self):
        """
        Return the length of the queue

        :return:
        """
        return len(self.__queue)
