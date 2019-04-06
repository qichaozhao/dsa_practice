class Node(object):
    """
    The nodes of the linked list
    """

    def __init__(self, ptr, item):
        self.ptr = ptr
        self.item = item


class LinkedList(object):
    """
    A singly linked list!
    """

    def __init__(self):
        """
        Set our parameters for the linked list
        """
        self.head = None
        self.tail = None
        self.length = 0

    def __len__(self):
        return self.length

    def __getitem__(self, idx):
        """
        Get an item at index n

        :param idx:
        :return:
        """
        return self.__getnode__(idx).item

    def __getnode__(self, idx):
        """
        Get the node at index n

        :param idx:
        :return:
        """

        if 0 <= idx < self.length:
            # Traverse the list from the start until we hit our index n
            cur_node = self.head
            for i in range(0, idx):
                cur_node = cur_node.ptr

            # Now the cur_node should point at the idx'th node
            return cur_node

        else:
            raise IndexError("Index out of bounds or list is empty!")

    def __reversed__(self):
        """
        Reverse the linked list!

        :return:
        """

        cur_node = None
        next_node = self.head

        while (next_node is not None):
            tmp = next_node.ptr
            next_node.ptr = cur_node

            cur_node = next_node
            next_node = tmp

        # Now swap the tail and head pointers
        self.head, self.tail = self.tail, self.head

    def __str__(self):
        if self.length > 0:
            buf = "["
            cur_node = self.head
            while (cur_node is not None):
                buf += str(cur_node.item)
                buf += ", "

                cur_node = cur_node.ptr

            buf = buf.strip(", ") + "]"
            return buf
        else:
            return "[]"

    def prepend(self, item):
        """
        Insert a new element onto the start of the list. Use the head pointer for speed

        :return:
        """
        self.insert(0, item)

    def insert(self, idx, item):
        """
        Append a new node at the idx'th place in the list

        :param idx:
        :param item:
        :return:
        """
        if 0 < idx <= self.length:
            anchor_node = self.__getnode__(idx - 1)
        elif idx == 0:
            anchor_node = Node(self.head, None)
        else:
            raise IndexError("Index out of bounds!")

        new_node = Node(anchor_node.ptr, item)
        anchor_node.ptr = new_node

        # Update the tail node in case we inserted in the last position
        if idx == self.length:
            self.tail = new_node

        # Update the head node in case we inserted in the first position
        if idx == 0:
            self.head = new_node

        self.length += 1

    def append(self, item):
        """
        Append a new element onto the end of the list. Use the tail pointer for speed.

        :param item:
        :return:
        """
        new_node = Node(None, item)

        if self.length == 0:
            self.head = new_node
            self.tail = new_node

        else:
            end_node = self.tail
            end_node.ptr = new_node
            self.tail = new_node

        self.length += 1

    def pop(self):
        return self.pop_idx(self.length - 1)

    def pop_idx(self, idx):
        """
        Scan along the index and remove the idx'th element and return it

        :param idx:
        :return:
        """
        if 0 < idx < self.length:
            anchor_node = self.__getnode__(idx - 1)
            value_node = anchor_node.ptr

            # Cut the value node out
            anchor_node.ptr = value_node.ptr

        elif idx == 0 and self.length > 0:
            anchor_node = self.head
            value_node = self.head

            # Cut the value node out
            self.head = value_node.ptr

        else:
            raise IndexError("Index out of bounds or list is already empty!")

        # Update the tail pointer if we got rid of the last element
        if idx == self.length - 1:
            self.tail = anchor_node

        self.length -= 1

        # If the list is now empty, reset the head and tail elements
        if self.length == 0:
            self.head = None
            self.tail = None

        # Return
        return value_node.item

    def front(self):
        """
        Return the value of the front of the list

        :return:
        """
        if self.length > 0:
            return self.head.item
        else:
            raise IndexError("List is empty!")

    def back(self):
        """
        Return the value of the tail of the list

        :return:
        """
        if self.length > 0:
            return self.tail.item
        else:
            raise IndexError("List is empty!")

    def delete(self, idx):
        """
        Delete the idx'th element, just relies on pop without returning the value

        :param idx:
        :return:
        """
        self.pop_idx(idx)

    def find(self, item):
        """
        Traverse the list until a value is matched

        :param item:
        :return:
        """
        i = 0
        cur_node = self.head
        while (cur_node.ptr is not None):

            if cur_node.item == item:
                return i

            # Traverse forward along the list
            cur_node = cur_node.ptr
            i += 1

        # We didn't find anything
        return -1

    def remove(self, item):
        """
        Traverse the list until a value is matched and remove this item

        :param item:
        :return:
        """
        i = 0
        cur_node = self.head
        while (cur_node.ptr is not None):

            if cur_node.item == item:
                self.delete(i)
                break

            # Traverse forward along the list
            cur_node = cur_node.ptr
            i += 1

    def is_empty(self):
        return self.length == 0
