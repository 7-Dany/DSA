import Canvas from './Canvas.js'
import Cell from './Cell.js'

let width = 500
let height = 500
let grid = 5
let cellWidth = width / grid
let cells = []

const canvas = new Canvas('canvas', width, height)

for(let y = 0; y < width; y += cellWidth){
    for(let x = 0; x < height; x += cellWidth){
        const cell = new Cell(canvas.context, x, y, cellWidth)
        cells.push(cell)
    }
}