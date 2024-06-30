import Sort from "./sorts.js"
import Canvas from './canvas.js'

let test = []
for (let i = 1; i <= 50; i++) {
    test.push(i * 10)
}

const canvas = new Canvas('test', test)
const sort = new Sort(canvas.createChart)

let locked = false
const onKeyDown = async (event) => {
    if (locked) return
    let key = event.key

    let sortingFunc = sort.getSort(key);
    if (!sortingFunc) return

    locked = true
    await sortingFunc(test)
    locked = false

}

document.addEventListener('keydown', onKeyDown)

let events = {
    "shuffle": "s",
    "radix": "r",
    "quick": "q",
    "merge": "m",
    "selection": "w",
    "insertion": "i",
    "bubble": "b",
}

const buttons = document.querySelectorAll('button')

const handleOnClick = async (event) => {
    let id = event.target.id
    let key = events[id]
    
    let sortingFunc = sort.getSort(key)
    if (!sortingFunc) return

    locked = true
    await sortingFunc(test)
    locked = false
}

buttons.forEach(button => {
    button.addEventListener('click', handleOnClick)
})