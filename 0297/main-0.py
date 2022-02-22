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
            return ''

        my_queue = Queue()
        my_queue.put(root)

        result = []
        while not my_queue.empty():
            cur = my_queue.get()

            if cur is None:
                result.append('X')
            else:
                result.append(str(cur.val))
                my_queue.put(cur.left)
                my_queue.put(cur.right)

        return ','.join(result)


    def deserialize(self, data: str):
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """
        if not data:
            return None
        result = data.split(',')


        my_queue = Queue()
        root = TreeNode(result[0])
        my_queue.put(root)

        i = 0
        while not my_queue.empty():
            cur = my_queue.get()

            i += 1
            if result[i] != 'X':
                cur.left = TreeNode(int(result[i]))
                my_queue.put(cur.left)

            i += 1
            if result[i] != 'X':
                cur.right = TreeNode(int(result[i]))
                my_queue.put(cur.right)
        return root



# Your Codec object will be instantiated and called as such:
ser = Codec()
deser = Codec()
root = None
ans = deser.deserialize(ser.serialize(root))