class Graph {
    constructor(array) {
        this.array = array
    }

    adjList() {
        let list = {}
        for (let i = 0; i < this.array.length; i++) {
            let [a, b] = this.array[i]
            if (!list[a]) list[a] = []
            if (!list[b]) list[b] = []
            list[a].push(b)
            list[b].push(a)
        }
        return list
    }

    dfs(src) {
        let list = this.adjList()
        let stack = [src]
        let visited = new Set([src])

        while (stack.length > 0) {
            let current = stack.pop()
            console.log(current)

            for (let key of list[current]) {
                if (!visited.has(key)) {
                    stack.push(key)
                    visited.add(key)
                }
            }
        }
    }

    bfs(src) {
        let list = this.adjList()
        let queue = [src]
        let visited = new Set([src])

        while (queue.length > 0) {
            let current = queue.shift()
            console.log(current)

            for (let key of list[current]) {
                if (!visited.has(key)) {
                    queue.unshift(key)
                    visited.add(key)
                }
            }
        }
    }
}

const graph = new Graph([['a', 'b'], ['c', 'd'], ['a', 'c'], ['c', 'b'], ['d', 'a']])
console.log(graph.adjList())
graph.dfs('a')
graph.bfs('d')
export default Graph