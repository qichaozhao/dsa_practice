import math


class Item(object):
    """
    An item which encapsulates our key, value pair and also makes up the nodes of our tree
    """

    def __init__(self, key, value, parent=None, left=None, right=None):
        self.key = key
        self.value = value
        self.parent = parent
        self.left = left
        self.right = right

    def __lt__(self, other):
        return self.key < other.key

    def __le__(self, other):
        return self.key <= other.key

    def __eq__(self, other):
        return self.key == other.key and self.value == other.value

    def __str__(self):
        return "({}, {})".format(self.key, self.value)

    def has_left(self):
        return self.left is not None

    def has_right(self):
        return self.right is not None


class MinHeapTree(object):
    """
    A heap based priority queue written on top of a python list
    """

    def __init__(self, root=None):
        self.root = root
        self.length = 1 if root is not None else 0

    #
    # Private methods for treating the list like a tree
    #
    def _get_node_at(self, idx):
        """
        Use the current number of nodes to get the next node that should be inserted

        Note that if we change the number into a binary representation, it allows us to traverse the tree
        to the insertion node

        :return:
        """

        msb_pos = int(math.log(idx, 2))

        # Now iterate through all the bit positions in reversed order (not including the msb)
        # If the bit position = 0, then we need to branch left
        # If the bit position = 1, then we need to branch right
        cur_node = self.root
        child = 'root'
        for msb in reversed(range(0, msb_pos)):

            if 1 << msb & idx == 0:
                cur_node = cur_node.left if cur_node.has_left() else cur_node
                child = 'left'

            elif 1 << msb & idx != 0:
                cur_node = cur_node.right if cur_node.has_right() else cur_node
                child = 'right'

            else:
                raise Exception("Something went wrong!")

        return cur_node, child

    def __str__(self):
        pass

    def _swap(self, node_i, node_j):
        """
        Swap the two nodes
        """

        # We can achieve an easier swap if we just swap the key and value of the node and leave the rest the same
        node_i.key, node_j.key = node_j.key, node_i.key
        node_i.value, node_j.value = node_j.value, node_i.value

    def _sift_up(self, node):

        # Base case, the heap property is satisfied
        # Or idx is zero
        if node == self.root or node.parent < node:
            return

        else:
            # Swap the parent and the element
            self._swap(node, node.parent)

            # Sift on the parent
            self._sift_up(node.parent)

    def _sift_down(self, node):
        """
        :param node:
        :return:
        """
        # Check we are not trying to downsift the root
        if node is None:
            return

        # Get the child with which to compare
        c = None

        # First case, we are the root...
        if node.has_left() is False and node.has_right() is False:
            return

        # Second case, left child only
        elif node.has_left() is True and node.has_right() is False:
            c = node.left

        # Third case, left and right children
        elif node.has_left() is True and node.has_right() is True:

            if node.left < node.right:
                c = node.left
            else:
                c = node.right

        else:
            raise Exception("We should not be here!")

        # Base case, the heap property is satisfied
        if node <= c:
            return

        else:
            # Swap the node and the child
            self._swap(node, c)

            # Sift down on the child
            self._sift_down(c)

    def _remove_node(self, node):
        """
        To remove a node we remove its association in the parent, then delete the node itself

        :param node:
        :return:
        """

        if node == self.root:
            self.root = None
        elif node == node.parent.left:
            node.parent.left = None
        elif node == node.parent.right:
            node.parent.right = None
        else:
            raise Exception("Node doesn't belong to this parent? Uh oh...")

        self.length -= 1

    #
    # Public methods
    #
    def __len__(self):
        return self.length

    def insert(self, key, value):

        parent, child = self._get_node_at(self.length + 1)
        new_node = Item(key, value, parent=parent)

        if child == 'left':
            parent.left = new_node
        elif child == 'right':
            parent.right = new_node
        elif child == 'root':
            self.root = new_node
        else:
            raise Exception("Traversal failed!")

        self._sift_up(new_node)
        self.length += 1

    def min(self):
        """
        Get the minimum value

        :return:
        """

        if self.length == 0:
            raise Exception("Priority queue is empty...")

        return self.root

    def pop(self):
        """
        Remove and return the head of the queue

        :return:
        """

        if self.length == 0:
            raise Exception("Priority queue is empty...")

        # Swap the head to the end of the list
        # Then pop
        last_node, _ = self._get_node_at(self.length)
        self._swap(self.root, last_node)
        self._remove_node(last_node)

        # Now fix the root by down-sifting
        self._sift_down(self.root)
        return last_node
