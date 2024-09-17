class Node {
    constructor(data) {
        this.data = data
        this.right = null
        this.left = null
    }
}

class BST {
    constructor() {
        this.root = null
    }

    insertionHelper(root, data) {
        if (root.data < data) {
            if (root.right === null) {
                root.right = new Node(data)
                return root.right
            }
            else {
                return this.getLeaf(root.right, data)
            }
        }
        else {
            if (root.left === null) {
                root.left = new Node(data)
                return root.left
            }
            else {
                return this.getLeaf(root.left, data)
            }
        }
    }

    insert(data) {
        if (!this.root) {
            this.root = Node(data)
            return
        }

        this.insertionHelper(this.root, data)
    }

    successor(root) {
        let node = root.left

        while (node != null) {
            node = node.left
        }

        return node.data
    }

    predecessor(root) {
        let node = root.right

        while (node != null) {
            node = node.right
        }

        return node.data
    }

    deleteHelper(root, data) {
        if (root === null) return root
        else if (root.data < data) root.right = this.deleteHelper(root.right, data)
        else if (root.data > data) root.left = this.deleteHelper(root.left, data)
        else {
            if (root.right === null && root.left === null) {
                root = null
            }
            else if (root.right !== null) {
                root.data = this.successor(root)
                root.right = this.deleteHelper(root.right, root.data)
            }
            else {
                root.data = this.predecessor(root)
                root.left = this.deleteHelper(root.left, root.data)
            }
        }

        return root
    }

    delete(data) {
        let root = search(data)

        return this.deleteHelper(root, data)
    }

    search(data) {
        if (root.data === data) return root
        else if (root.data > data) return this.search(root.left, data)
        else if (root.data < data) return this.search(root.right, data)
    }
}