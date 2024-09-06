class Heap {
    constructor(type, array) {
        this.type = type

        if (array) {
            this.array = array
            this.build()
        } else {
            this.array = []
        }
    }

    swap(parent, child) {
        [this.array[parent], this.array[child]] = [this.array[child], this.array[parent]]
    }

    inBounds(index) {
        return index >= 0 && index < this.array.length
    }

    getLeftChild(index) {
        let left = index * 2 + 1
        return this.inBounds(left) ? left : -1
    }

    getRightChild(index) {
        let right = index * 2 + 2
        return this.inBounds(right) ? right : -1
    }

    getParent(index) {
        let parent = Math.floor((index - 1) / 2)
        return this.inBounds(parent) ? parent : -1
    }

    getBiggestChild(index) {
        let biggest = index
        let right = this.getRightChild(index);
        let left = this.getLeftChild(index)

        if (right !== -1 && this.array[right] > this.array[biggest]) {
            biggest = right
        }

        if (left !== -1 && this.array[left] > this.array[biggest]) {
            biggest = left
        }

        return biggest
    }

    getSmallestChild(index) {
        let smallest = index
        let right = this.getRightChild(index);
        let left = this.getLeftChild(index)

        if (right !== -1 && this.array[right] < this.array[smallest]) {
            smallest = right
        }

        if (left !== -1 && this.array[left] < this.array[smallest]) {
            smallest = left
        }

        return smallest
    }

    heapify(index) {
        while (index < this.array.length) {
            let child

            switch (this.type) {
                case 'min':
                    child = this.getSmallestChild(index)
                    break
                case 'max':
                    child = this.getBiggestChild(index)
                    break
            }

            if (child === index) return
            this.swap(index, child);
            index = child
        }
    }

    build() {
        let middle = Math.floor((this.array.length - 1) / 2)
        for (let i = middle; i >= 0; i--) {
            this.heapify(i)
        }
    }

    insert(element){
        this.array.push(element)
        let parent = this.getParent(this.array.length - 1)
        let child
        
        while (parent >= 0) {
            switch (this.type) {
                case 'min':
                    child = this.getSmallestChild(parent)
                    break
                case 'max':
                    child = this.getBiggestChild(parent)
                    break
            }
            if (child === parent) return
            this.swap(parent, child)
            parent = this.getParent(parent)
        }
    }

    delete() {
        if (this.array.length <= 1) {
            return this.array.pop()
        }

        let root = this.array[0]
        this.array[0] = this.array.pop()
        this.heapify(0)

        return root
    }

    sort() {
        let result = []
        let length = this.array.length

        for (let i = 0; i < length; i++) {
            result.push(this.delete())
        }
        
        this.array = result
        return this.array
    }
}


const heap = new Heap('min', [7, 5, 3, 8, 9, 1, 4, 2, 6])
console.log(heap.array)
heap.delete()
console.log(heap.array)
console.log(heap.sort())
heap.insert(0)
heap.insert(-1)
console.log(heap.array)

export default Heap