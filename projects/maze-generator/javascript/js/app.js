import Maze from './Maze.js'


const maze = new Maze()
const form = document.querySelector('#maze-generation')
const gridWidth = document.querySelector('#grid-width')
const gridHeight = document.querySelector('#grid-height')
const cellWidth = document.querySelector('#cell-width')
const cellHeight = document.querySelector('#cell-height')

form.addEventListener('submit', async (event) => {
    event.preventDefault();
    event.stopImmediatePropagation();

    const width = parseInt(gridWidth.value);
    const height = parseInt(gridHeight.value);
    const cellW = parseInt(cellWidth.value);
    const cellH = parseInt(cellHeight.value);

    if (isNaN(width) || isNaN(height) || isNaN(cellW) || isNaN(cellH)) {
        console.error('Please enter valid numbers for all dimensions.');
        return;
    }

    try {
        await maze.startGenerating(width, height, cellW, cellH);
    } catch (error) {
        console.error('Error generating maze:', error);
    }
});