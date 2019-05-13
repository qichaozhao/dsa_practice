"""
Contains all the tests for my BST implementation
"""

from ch08.py.bst import BinarySearchTree, BinaryNode


def generate_bst(range_start=0, num_nodes=3):
    """
    Generates a bst for use in testing

    :param range_start:
    :param num_nodes:
    :return:
    """

    arr = [i for i in range(range_start, range_start + num_nodes)]
    bst = BinarySearchTree()
    bst.from_array(arr)

    return bst


def test_bst_create():
    bst = BinarySearchTree()

    assert (bst.root is None)
    assert (bst.num_nodes == 0)
    assert (bst.height == 0)


def test_bst_add_root():
    bst = BinarySearchTree()
    root = BinaryNode(value=123)

    bst.add_root(root)

    assert (bst.root is not None)
    assert (bst.root.value == 123)
    assert (bst.height == 0)
    assert (bst.num_nodes == 1)


def test_bst_insert_empty():
    bst = BinarySearchTree()
    bst.insert(123)

    assert (bst.root is not None)
    assert (bst.root.value == 123)
    assert (bst.height == 0)
    assert (bst.num_nodes == 1)


def test_bst_insert_non_empty():
    bst = generate_bst(num_nodes=3)
    bst.insert(123)

    assert (bst.num_nodes == 4)
    assert (bst.root.value == 1)
    assert (bst.root.left.value == 0)
    assert (bst.root.right.value == 2)
    assert (bst.root.right.right.value == 123)
    assert (bst.height == 2)


def test_bst_search_exists():
    bst = generate_bst(num_nodes=7)
    val = bst.search(6)

    assert (val == 6)


def test_bst_search_notexists():
    bst = generate_bst(num_nodes=7)
    val = bst.search(60)

    assert (val is None)


def test_bst_compute_nodes():
    bst = generate_bst(num_nodes=7)
    nodes = bst.compute_num_nodes()

    assert (nodes == 7)


def test_bst_iter():
    bst = generate_bst(num_nodes=6)

    assert (list([n for n in bst]) == [0, 1, 2, 3, 4, 5])


def test_delete_tree():
    bst = generate_bst(num_nodes=4)
    bst.delete_tree()

    assert (bst.root is None)
    assert (bst.num_nodes == 0)
    assert (bst.height == 0)


def test_delete_node():
    # 3 scenarios to test

    # 1. Where node is leaf
    bst = generate_bst(num_nodes=4)
    bst.delete_node(3)

    assert (bst.root.right is None)
    assert (bst.num_nodes == 3)
    assert (bst.height == 2)

    # 2. Where node has 1 child
    bst = generate_bst(num_nodes=4)
    bst.delete_node(1)

    assert (bst.root.left.value == 0)
    assert (bst.root.left.left is None)
    assert (bst.num_nodes == 3)
    assert (bst.height == 1)

    # 3. Where node has 2 child
    bst = generate_bst(num_nodes=4)
    bst.delete_node(2)

    assert (bst.root.value == 3)
    assert (bst.root.right is None)
    assert (bst.root.left.value == 1)
    assert (bst.root.left.left.value == 0)
    assert (bst.num_nodes == 3)
    assert (bst.height == 2)


def test_get_min():
    # Test get min of tree and also get min of sub branch
    bst = generate_bst(num_nodes=6)
    bst_min = bst.get_min()
    assert (bst_min == 0)

    bst_min = bst.get_min(node=bst.root.right)
    assert (bst_min == 4)


def test_get_max():
    # Test get min of tree and also get min of sub branch
    bst = generate_bst(num_nodes=6)
    bst_max = bst.get_max()
    assert (bst_max == 5)

    bst_max = bst.get_max(node=bst.root.left)
    assert (bst_max == 2)


def test_verify_bst():
    bst = generate_bst(num_nodes=3)

    assert (bst.verify_bst())

    bst.root.left.value = 5

    assert (bst.verify_bst() is False)


def test_get_before():
    bst = generate_bst(num_nodes=6)
    bf = bst.get_before(3)

    assert (bf == 2)


def test_get_after():
    bst = generate_bst(num_nodes=6)
    af = bst.get_after(3)

    assert (af == 4)


def test_iter_preorder():
    bst = generate_bst(num_nodes=6)

    assert (list(bst.iter_preorder()) == [3, 1, 0, 2, 5, 4])


def test_iter_postorder():
    bst = generate_bst(num_nodes=6)

    assert (list(bst.iter_postorder()) == [0, 2, 1, 4, 5, 3])


def test_iter_bfs():
    bst = generate_bst(num_nodes=6)

    assert (list(bst.iter_bfs()) == [3, 1, 5, 0, 2, 4])


def test_get_height():
    bst = generate_bst(num_nodes=6)

    assert (bst.get_height() == 2)


def test_balance():
    bst = BinarySearchTree()
    bst.root = BinaryNode(value=0)
    bst.root.left = BinaryNode(value=1)
    bst.root.left.left = BinaryNode(value=2)

    assert (bst.verify_bst() is False)

    bst.balance()

    assert (bst.root.value == 1)
    assert (bst.root.left.value == 0)
    assert (bst.root.right.value == 2)


def test_from_array():
    bst = BinarySearchTree()
    bst.from_array([0, 1, 2])

    assert (bst.root.value == 1)
    assert (bst.root.left.value == 0)
    assert (bst.root.right.value == 2)
