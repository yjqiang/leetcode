# Definition for a binary tree node.
from queue import Queue


class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


from queue import Queue

class Codec:
    def serialize(self, root: TreeNode):
        """Encodes a tree to a single string.

        :type root: TreeNode
        :rtype: str
        """
        if root is None:
            return 'X'
        left = self.serialize(root.left)
        right = self.serialize(root.right)
        return f'{root.val},{left},{right}'

    def deserialize(self, data: str):
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """

        result = data.split(',')
        self.index = 0
        return self.create(result)

    def create(self, data):
        """

        :param data: list[str]
        :return:
        """
        if data[self.index] == 'X':
            self.index += 1
            return None
        node = TreeNode(data[self.index])
        self.index += 1
        node.left = self.create(data)
        node.right = self.create(data)
        return node


# Your Codec object will be instantiated and called as such:
ser = Codec()
deser = Codec()
root = None
ans = deser.deserialize(ser.serialize(root))