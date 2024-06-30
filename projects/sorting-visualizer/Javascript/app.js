import Canvas from './canvas.js'
import Sort from './sorts.js'

let test = []
for (let i = 1; i <= 50; i++) {
    test.push(i * 10)
}

const canvas = new Canvas('test', test)
const sort = new Sort(canvas.createChart)

let events = {
    "shuffle": "s",
    "radix": "r",
    "quick": "q",
    "merge": "m",
    "selection": "w",
    "insertion": "i",
    "bubble": "b",
    "reset": " "
}


// Handle buttons clicks
const buttons = document.querySelectorAll('button')

const handleOnClick = async (event) => {
    let id = event.target.id
    let key = events[id]

    await sort.startSorting(key, test)
}

buttons.forEach(button => {
    button.addEventListener('click', handleOnClick)
})

// Handle keyboard press
const onKeyDown = async (event) => {
    let key = event.key
    await sort.startSorting(key, test)
}

document.addEventListener('keydown', onKeyDown)