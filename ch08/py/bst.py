"""
Implements a binary search tree in python
"""


class BinaryNode(object):
    def __init__(self, left=None, right=None, value=None, parent=None):
        self.left = left
        self.right = right
        self.value = value
        self.parent = parent

    def __eq__(self, other):
        return self.value == other.value

    def __ne__(self, other):
        return self.value != other.value

    def has_sibling(self):
        """
        Returns true if the node has a sibling
        :return:
        """
        return self.get_sibling() is not None

    def get_sibling(self):
        """
        Returns the sibling of the node if it has a sibling

        :return:
        """

        if self.parent.left == self:
            return self.parent.right
        elif self.parent.right == self:
            return self.parent.left
        else:
            return None

    def is_leaf(self):
        """
        Returns true if no children
        :return:
        """
        return self.left is None and self.right is None


class BinarySearchTree(object):
    def __init__(self):
        """
        Init will instantiate an empty tree without even a root node
        """

        self.root = None
        self.num_nodes = 0
        self.height = 0

    def add_root(self, root):
        """
        Adds a root to the tree

        :param root:
        :return:
        """
        if self.root is not None:
            raise AttributeError("Tree already has a root!")

        self.root = root
        self.num_nodes += 1

    def insert(self, item):
        """
        Inserts a value into the correct place in the tree

        :param item:
        :return:
        """

        if self.root is None:
            self.add_root(BinaryNode(value=item))
            return

        def __insert(new_node, node):
            """
            A recursive helper for insertion

            :param item:
            :param node:
            :return:
            """
            # Base case, item already exists (here our tree just stores distinct items)
            if node == new_node:
                raise ValueError("Cannot insert a duplicate item into the tree")

            # Base case, perform the insertion here!
            elif node.is_leaf() or (node.left is None or node.right is None):

                new_node.parent = node

                if item < node.value and node.left is None:
                    node.left = new_node
                elif item > node.value and node.right is None:
                    node.right = new_node
                else:
                    raise Exception("Attempted to insert value at a non-leaf node.")

            # Need to recurse
            else:

                if item < node.value:
                    __insert(new_node, node.left)
                elif item > node.value:
                    __insert(new_node, node.right)
                else:
                    raise Exception("We should never get to this part!")

        node = self.root
        new_node = BinaryNode(value=item)
        __insert(new_node, node)

        # Update our tree metrics
        self.num_nodes += 1
        self.height = self.get_height(self.root)

    def search(self, item, start_node=None, mode="val"):
        """
        Search to see if the item is within the tree
        :param item:
        :return:
        """

        node = self.root if start_node is None else start_node

        # Easiest base case - we found it
        if node.value == item:

            if mode == "val":
                return node.value
            else:
                return node

        # Other base case - we exhausted the search
        elif node.is_leaf() or node is None:
            return None

        # Now the recursive case
        else:

            if item < node.value:
                return self.search(item, node.left, mode=mode)
            elif item > node.value:
                return self.search(item, node.right, mode=mode)

        return self.search(item, node, mode)

    def get_num_nodes(self):
        return self.num_nodes

    def compute_num_nodes(self):
        """
        Count the number of nodes in the tree

        :return:
        """
        counter = 0
        for _ in self:
            counter += 1

        return counter

    def __str__(self):
        """
        Prints values from min to max
        :return:
        """

        out = ""

        def get_gridsize(height, x_pad=4, y_pad=1):
            """
            Helper function which returns width, height of the print grid

            :param x_space:
            :param y_space:
            :param height:
            :return:
            """
            w = (2 ** self.height) * (x_pad + 1)
            h = (height + 1) * (y_pad + 1)

            return w, h

        def get_print_xy(level, node_idx, w, h, y_pad=1):
            """
            Helper function which returns the co-ordinate to print given a level and the node on that level

            :param level:
            :param node:
            :return:
            """
            x = w // ((2 ** level) + 1) * (1 + node_idx)
            y = lvl * (y_pad + 1)

            return int(x), int(y)

        # Size up our grid
        w, h = get_gridsize(self.height)

        # Figure out where we need to plot numbers
        queue = [self.root]
        lvl = 0
        plt = []

        while len(queue) > 0:

            new_queue = []

            for idx, node in enumerate(queue):
                if node is not None:
                    x, y = get_print_xy(lvl, idx, w, h)
                    plt.append(((x, y), node.value))
                    new_queue.extend([node.left, node.right])

            lvl += 1
            queue = new_queue

        # Now print out the tree
        to_plot = plt.pop(0)
        for j in range(h):
            for i in range(w):

                if to_plot[0][0] == i and to_plot[0][1] == j:
                    out += str(to_plot[1])
                    if len(plt) > 0:
                        to_plot = plt.pop(0)

                else:
                    out += " "

            out += "\n"

        return out

    def __iter__(self):
        """
        Returns an inorder iteration through the tree
        :return:
        """

        def inorder(node):
            """
            Recursive helper function for inorder traversal

            :param node:
            :return:
            """

            if node.left is not None:
                yield from inorder(node.left)

            yield node.value

            if node.right is not None:
                yield from inorder(node.right)

        return inorder(self.root) if self.root is not None else iter([])

    def delete_tree(self):
        """
        De-allocates all the nodes and sets the root to None
        :return:
        """

        def __dealloc(node):
            """
            Deallocates a node

            :param node:
            :return:
            """

            if node is None:
                return

            __dealloc(node.left)
            __dealloc(node.right)

            del node

        __dealloc(self.root)

        # Finally reset everything
        self.root = None
        self.num_nodes = 0
        self.height = 0

    def delete_node(self, item, start_node=None):
        """
        Deletes the node corresponding to the value

        :param item:
        :return:
        """

        sn = self.root if start_node is None else start_node
        node = self.search(item, start_node=sn, mode="node")

        if node is None:
            raise Exception("Trying to delete a value that does not exist within the tree.")

        # Now we have 3 possibilities for deletion
        # 1. Node is a leaf, which means we can just delete it
        # 2. Node has one child, in which case we replace the node's value with the child value and delete the child
        # 3. Node has two children, in which case we replace the node's value with the inorder successor
        # and delete the inorder successor node
        if node.is_leaf():
            if node.parent.left == node:
                node.parent.left = None
            elif node.parent.right == node:
                node.parent.right = None

            self.num_nodes -= 1
            self.height = self.get_height(self.root)

        # Node has 1 child with left child being empty
        elif node.left is None:
            node.value = node.right.value
            node.right = None

            self.num_nodes -= 1
            self.height = self.get_height(self.root)

        # Node has 1 child with right child being empty
        elif node.right is None:
            node.value = node.left.value
            node.left = None

            self.num_nodes -= 1
            self.height = self.get_height(self.root)

        # Node is a full node
        # Inorder successor is the min value of the right tree
        else:
            succ_node = self.get_min(node=node.right, mode="node")
            node.value = succ_node.value
            self.delete_node(succ_node.value, start_node=succ_node)

    def get_min(self, node=None, mode="val"):
        """
        Return minimum value, traverse down the left child until we hit the dead end

        :return:
        """
        cur_node = self.root if node is None else node
        while (cur_node.left is not None):
            cur_node = cur_node.left

        if mode == "val":
            return cur_node.value
        elif mode == "node":
            return cur_node
        else:
            raise ValueError("Mode must be one of { val | node }")

    def get_max(self, node=None, mode="val"):
        """
        Return maximum value, traverse down the right child until we hit the dead end

        :return:
        """
        cur_node = self.root if node is None else node
        while (cur_node.right is not None):
            cur_node = cur_node.right

        if mode == "val":
            return cur_node.value
        elif mode == "node":
            return cur_node
        else:
            raise ValueError("Mode must be one of { val | node }")

    def verify_bst(self):
        """
        Check if our binary tree is a valid binary search tree
        i.e.
        1. left subtree is < node & is valid bst
        2. right subtree is > node & is valid bst

        :return:
        """

        def verify_bst_helper(node):
            """
            Recursive helper for verifying the bst

            :param node:
            :return:
            """

            if node.is_leaf():
                return True

            elif node.right is None:
                return node.left.value < node.value and verify_bst_helper(node.left)

            elif node.left is None:
                return node.right.value > node.value and verify_bst_helper(node.right)

            else:
                return node.left.value < node.value and verify_bst_helper(node.left) \
                       and node.right.value > node.value and verify_bst_helper(node.right)

        return verify_bst_helper(self.root) if self.root is not None else False

    def get_before(self, item, mode="val"):
        """
        Returns next highest value in tree before given value, None if None
        :return:
        """

        # The next highest value should be the max of the left branch of the node
        node = self.search(item, start_node=self.root, mode="node")

        if node is None or node.left is None:
            return None

        return self.get_max(node=node.left, mode=mode)

    def get_after(self, item, mode="val"):
        """
        Returns next lowest value in tree after given value. None if None
        :param item:
        :return:
        """
        # The next lowest value in the tree is the min of the right branch
        node = self.search(item, start_node=self.root, mode="node")

        if node is None or node.right is None:
            return None

        return self.get_min(node=node.right, mode=mode)

    def iter_preorder(self):
        """
        Returns a preorder iteration through the tree
        :return:
        """

        def preorder(node):
            """
            Recursive helper for pre-order

            :param node:
            :return:
            """

            yield node.value

            for child in (node.left, node.right):
                if child is not None:
                    yield from preorder(child)

        return preorder(self.root) if self.root is not None else iter([])

    def iter_postorder(self):
        """
        Returns a postorder iteration through the tree
        :return:
        """

        def postorder(node):
            """
            Recursive helper for post-order

            :param node:
            :return:
            """

            for child in (node.left, node.right):
                if child is not None:
                    yield from postorder(child)

            yield node.value

        return postorder(self.root) if self.root is not None else iter([])

    def iter_bfs(self):
        """
        Return the breadth first traversal of the tree
        :return:
        """
        if self.root is None:
            return iter([])

        queue = [self.root]  # This is not an efficient queue structure but it'll do
        while len(queue) > 0:
            node = queue.pop(0)

            if node is not None:
                yield node.value
                queue.extend((node.left, node.right))

    def get_height(self, node=None):
        """
        Returns the height of tree if node = None, else return the height of the tree from that Node

        :param node:
        :return:
        """

        def __get_height(node):
            if node is None or node.is_leaf():
                return 0
            else:
                return 1 + max(__get_height(node.left), __get_height(node.right))

        if node is None:
            return self.height
        else:
            return __get_height(node)

    def balance(self):
        """
        Balances the tree
        :return:
        """

        # To balance the tree we first perform an inorder traversal which should leave us with a sorted array
        arr = list(self.__iter__())
        self.delete_tree()
        self.from_array(arr)

    def from_array(self, arr):
        """
        Build a balanced binary search tree from an array

        :param arr:
        :return:
        """

        def __from_array(arr, parent, child):
            """
            Recursive helper

            :param arr:
            :param parent:
            :return:
            """

            # Check the length of the array to see if we need to do anything as the base case
            if len(arr) < 1:
                return

            else:
                m = len(arr) // 2
                v = arr[m]

                # Assign the correct reference at the parent node
                new_node = BinaryNode(value=v, parent=parent)
                if child == 'left':
                    parent.left = new_node
                elif child == 'right':
                    parent.right = new_node

                # Now recurse
                __from_array(arr[:m], new_node, 'left')
                __from_array(arr[m + 1:], new_node, 'right')

        if self.root is not None:
            raise ValueError("Cannot build a tree as one already exists")

        if len(arr) < 1:
            raise ValueError("Must take an array of at least 1 element")

        # Sort the array
        s_arr = sorted(arr)

        # Extract the middle value of the array
        m = len(s_arr) // 2
        v = s_arr[m]
        self.root = BinaryNode(value=v)

        # Now recurse
        __from_array(s_arr[:m], self.root, 'left')
        __from_array(s_arr[m + 1:], self.root, 'right')

        # Now set the other parameters
        self.num_nodes = len(arr)
        self.height = self.get_height(self.root)
