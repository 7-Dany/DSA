import Maze from './Maze.js'


const maze = new Maze(700, 700)
const form = document.querySelector('#maze-generation')
const cellWidth = document.querySelector('#cell-width')
const cellHeight = document.querySelector('#cell-height')
const generate = document.querySelector('#generate')

form.addEventListener('submit', async (event) => {
    event.preventDefault();
    event.stopImmediatePropagation();

    const cellW = parseInt(cellWidth.value);
    const cellH = parseInt(cellHeight.value)

    try {
        generate.disabled = true
        generate.textContent = "Generating"
        await maze.startGenerating(cellW, cellH);
        generate.textContent = "Generate Maze"
        generate.disabled = false
    } catch (error) {
        console.error('Error generating maze:', error);
    }
});