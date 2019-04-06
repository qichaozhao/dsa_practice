from ctypes import py_object


class Vector(object):
    """
    A python implementation of a dynamically resizing array
    """

    def __init__(self, capacity=10):
        self.capacity = capacity
        self.n = 0
        self.arr = self.__make_arr(self.capacity)

    def __make_arr(self, capacity):
        """
        Make an array of size = capacity and return it

        :param capacity:
        :return:
        """
        return (capacity * py_object)()

    def __resize(self, new_capacity):
        """
        Resize an array to a new capacity

        :param new_capacity:
        :return:
        """

        # Create the new array
        new_arr = self.__make_arr(new_capacity)

        # Copy the current array's elements over
        for i in range(self.n):
            new_arr[i] = self.arr[i]

        # Set the reference to the new array and update the capacity
        self.arr = new_arr
        self.capacity = new_capacity

    def append(self, item):
        """
        A public method used to append a new item to the array

        :param item:
        :return:
        """

        # Check if we need to resize the array
        if self.n == self.capacity:
            self.__resize(self.capacity * 2)

        # Now perform the append
        self.arr[self.n] = item
        self.n += 1

    def pop(self, idx=None):
        """
        A public method to pop an element off the array

        :param idx:
        :return:
        """

        if idx is None:
            self.n -= 1
            item = self.arr[self.n]

        elif 0 <= idx < self.n:
            self.n -= 1
            item = self.arr[idx]

            # Now we need to shift all elements left by 1
            for i in range(idx, self.n):
                self.arr[i] = self.arr[i + 1]

        else:
            raise IndexError("Index out of bounds")

        # Now check if we should shrink the array
        if self.n < self.capacity // 4:
            self.__resize(self.capacity // 2)

        return item

    def is_empty(self):
        """
        Check if the array is empty or not
        :return:
        """
        return True if self.n == 0 else False

    def __setitem__(self, idx, item):
        """
        Sets an item at a specific index
        :param key:
        :param value:
        :return:
        """

        if 0 <= idx < self.n:
            self.arr[idx] = item
        else:
            raise IndexError("Index out of bounds!")

    def insert(self, idx, item):
        """
        Inserts an item at the given index

        :param idx:
        :param item:
        :return:
        """

        # Check if we need to resize the array
        if self.n == self.capacity:
            self.__resize(self.capacity * 2)

        # Shift all the elements rightward by 1
        for i in reversed(range(idx, self.n)):
            self.arr[idx + 1] = self.arr[i]

        # Insert the element
        self.arr[idx] = item
        self.n += 1

    def prepend(self, item):
        """
        Inserts an item at the head of the list

        :param item:
        :return:
        """
        self.insert(0, item)

    def delete(self, idx):
        """
        Deletes an item from the index

        :param idx:
        :return:
        """

        if 0 <= idx < self.n:
            self.n -= 1

            # We need to shift all elements left by 1
            for i in range(idx, self.n):
                self.arr[i] = self.arr[i + 1]

        else:
            raise IndexError("Index out of bounds")

        # Now check if we should shrink the array
        if self.n < self.capacity // 4:
            self.__resize(self.capacity // 2)

    def remove(self, item):
        """
        Remove all items from the array that match with item

        :param item:
        :return:
        """

        # Find all indexes that match the item
        idxes = []
        for i in range(self.n):
            if self.arr[i] == item:
                idxes.append(i)

        # Delete all found idxes, adjusting for the idx values if there are multiple
        for i, idx in enumerate(idxes):
            self.delete(idx - i)

    def find(self, item):
        """
        Returns the index of the first item that matches the item, else return None if no matches

        :param item:
        :return:
        """

        for i in range(self.n):
            if self.arr[i] == item:
                return i
        return None

    def __len__(self):
        return self.n

    def __getitem__(self, idx):
        if not 0 <= idx < self.capacity:
            raise IndexError("Index out of bounds")
        return self.arr[idx]

    def __str__(self):
        out = "["
        for k in range(self.n):
            out += f"{self.arr[k]}, "

        out = out.rstrip(", ") + "]"
        return out


if __name__ == '__main__':
    # Test our vector class
    # Make a new vector of size 5
    vec = Vector(5)
    print(f"Empty Vector: {vec}")

    # Add a few numbers
    vec.append(0)
    vec.append(1)
    vec.append(2)
    print(f"Vector of 3 elements: {vec}")

    # Make it auto resize
    print(f"Old Capacity: {vec.capacity}")
    vec.append(3)
    vec.append(4)
    vec.append(5)
    vec.append(6)
    print(f"New Vector: {vec}")
    print(f"New Capacity: {vec.capacity}")

    # Now pop 1 elements
    e = vec.pop()
    print(f"Popped last element: {e}")
    print(f"New Vector: {vec}")

    # Now pop all but 1 element
    print("Popping 5 elements more...")
    print(vec.pop())
    print(vec.pop())
    print(vec.pop())
    print(vec.pop())
    print(vec.pop())
    print(f"New Capacity: {vec.capacity}")
    print(f"Num Items: {vec.n}")
    print(f"Vector: {vec}")
