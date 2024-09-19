import Node from "./Node.js";

class AVL<T> {
  root: Node<T> | null

  constructor() {
    this.root = null
  }

  private rotateLeft = (root: Node<T>) => {
    let rightChild = root.right
    let rightChildLeftTree = rightChild.left

    rightChild.left = root
    root.right = rightChildLeftTree

    root.height = 1 + Math.max(this.getHeight(root.right), this.getHeight(root.left))
    rightChild.height = 1 + Math.max(this.getHeight(rightChild.left), this.getHeight(rightChild.right))

    return rightChild
  }

  private rotateRight = (root: Node<T>) => {
    let leftChild = root.left
    let leftChildRightTree = leftChild.right

    leftChild.right = root
    root.left = leftChildRightTree

    leftChild.height = 1 + Math.max(this.getHeight(leftChild.right), this.getHeight(leftChild.left))
    root.height = 1 + Math.max(this.getHeight(root.right), this.getHeight(root.left))

    return leftChild
  }

  private getHeight = (node: Node<T>) => {
    return node ? node.height : 0
  }

  private getBalanceFactor = (root: Node<T>) => {
    return root ? (this.getHeight(root.left) - this.getHeight(root.right)) : 0
  }

  private balance = (root: Node<T>, value: T) => {
    const balanceFactor = this.getBalanceFactor(root)

    if (balanceFactor > 1 && value < root.left.value) {
      return this.rotateRight(root)
    }

    if (balanceFactor > 1 && value > root.left.value) {
      root.left = this.rotateLeft(root.left)
      return this.rotateRight(root)
    }

    if (balanceFactor < -1 && value > root.right.value) {
      return this.rotateLeft(root)
    }

    if (balanceFactor < -1 && value < root.right.value) {
      root.right = this.rotateRight(root.right)
      return this.rotateLeft(root)
    }
  }

  private insertHelper = (root: Node<T>, element: T) => {
    if (root === null) {
      return new Node<T>(element)
    } else if (root.value < element) {
      root.right = this.insertHelper(root.right, element)
    } else {
      root.left = this.insertHelper(root.left, element)
    }

    root.height = 1 + Math.max(this.getHeight(root.left), this.getHeight(root.right))

    const factor = this.getBalanceFactor(root)

    if (factor > 1 || factor < -1) {
      return this.balance(root, element)
    } else {
      return root
    }
  }

  insert = (element: T) => {
    this.root = this.insertHelper(this.root, element)
  }

  private getMaxHelper = (root: Node<T>) => {
    if (root.right === null) return root.value
    else return this.getMaxHelper(root.right)
  }

  private removeHelper = (root: Node<T>, element: T) => {
    if (root === null) return root
    else if (root.value < element) root.right = this.removeHelper(root.right, element)
    else if (root.value > element) root.left = this.removeHelper(root.left, element)
    else {
      if (root.right === null) return root.left
      else if (root.left === null) return root.right
      else {
        const max = this.getMaxHelper(root.left)
        root.value = max
        root.left = this.removeHelper(root.left, max)
      }
    }

    if (!root) return root

    root.height = 1 + Math.max(this.getHeight(root.left), this.getHeight(root.right))

    const factor = this.getBalanceFactor(root)

    if (factor > 1) {
      const leftFactor = this.getBalanceFactor(root.left)
      if (leftFactor >= 0) {
        return this.rotateRight(root)
      } else {
        root.left = this.rotateLeft(root.left)
        return this.rotateRight(root)
      }
    } else if (factor < -1) {
      const rightFactor = this.getBalanceFactor(root.right)
      if (rightFactor <= 0) {
        return this.rotateLeft(root)
      } else {
        root.right = this.rotateRight(root.right)
        return this.rotateLeft(root)
      }
    } else {
      return root
    }
  }

  remove = (element: T) => {
    this.root = this.removeHelper(this.root, element)
  }

  private printHelper = (currPtr, indent, last) => {
    if (currPtr != null) {
      process.stdout.write(indent);
      if (last) {
        process.stdout.write("R----");
        indent += "     ";
      } else {
        process.stdout.write("L----");
        indent += "|    ";
      }
      console.log(currPtr.value);
      this.printHelper(currPtr.left, indent, false);
      this.printHelper(currPtr.right, indent, true);
    }
  }

  print = () => {
    this.printHelper(this.root, "", true)
  }
}

export default AVL