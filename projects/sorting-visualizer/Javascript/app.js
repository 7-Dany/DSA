import Sort from "./sorts.js"
import Canvas from './canvas.js'

let test = []
for (let i = 1; i <= 50; i++) {
    test.push(i * 10)
}

const canvas = new Canvas('test', test)
const sort = new Sort(canvas.createChart)
const events = sort.events

let locked = false
const onKeyDown = async (event) => {
    if (locked) return
    let key = event.key
    let sortingFunc = events[key]
    locked = true
    await sortingFunc(test)
    locked = false
}

document.addEventListener('keydown', onKeyDown)