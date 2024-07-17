import Renderer from './Rendrer.js'
import Canvas from './Canvas.js'
import Cell from './Cell.js';

class Maze {
    constructor(width, height, nums) {
        this.canvas = new Canvas('canvas', width, height);
        this.width = width;
        this.height = height;
        this.gridCells = nums;
        this.cellWidth = this.width / nums;
        this.cellHeight = this.height / nums;
        this.cells = [];
        this.cellRenderer = new Renderer(this.canvas);
        this.createCells();
        this.createMaze();
    }

    /**
     * Creates the cells for the maze.
     */
    createCells() {
        for (let y = 0; y < this.gridCells; y++) {
            let row = [];
            for (let x = 0; x < this.gridCells; x++) {
                const cell = new Cell(x, y, this.cellWidth, this.cellHeight);
                row.push(cell);
            }
            this.cells.push(row);
        }
    }

    /**
     * Reloads and redraws all cells in the maze.
     */
    async reloadCells() {
        this.canvas.reset();

        for (let row of this.cells) {
            for (let cell of row) {
                this.cellRenderer.draw(cell);
            }
        }

        await this.sleep(50);
    }

    /**
     * Gets the unvisited neighbors of a given cell.
     * @param {Cell} currentCell - The current cell.
     * @param {Set} visited - The set of visited cells.
     * @returns {Array} - The array of unvisited neighbors.
     */
    getUnvisitedNeighbors(currentCell, visited) {
        let positionX = currentCell.x;
        let positionY = currentCell.y;

        let neighbors = [];

        // Left
        if (positionX > 0 && positionX <= this.cells[0].length - 1) {
            let left = this.cells[positionY][positionX - 1];
            if (!visited.has(left)) neighbors.push(left);
        }

        // Right
        if (positionX >= 0 && positionX < this.cells[0].length - 1) {
            let right = this.cells[positionY][positionX + 1];
            if (!visited.has(right)) neighbors.push(right);
        }

        // Top
        if (positionY > 0 && positionY <= this.cells.length - 1) {
            let bottom = this.cells[positionY - 1][positionX];
            if (!visited.has(bottom)) neighbors.push(bottom);
        }

        // Bottom
        if (positionY >= 0 && positionY < this.cells.length - 1) {
            let top = this.cells[positionY + 1][positionX];
            if (!visited.has(top)) neighbors.push(top);
        }

        return neighbors;
    }

    /**
     * Gets the opposite direction of a given direction.
     * @param {string} neighborDirection - The given direction.
     * @returns {string} - The opposite direction.
     */
    getNeighborDirection(neighborDirection) {
        let directions = {
            "right": "left",
            "left": "right",
            "top": "bottom",
            "bottom": "top"
        };

        return directions[neighborDirection];
    }

    /**
     * Opens the wall between the current cell and its neighbor.
     * @param {Cell} currentCell - The current cell.
     * @param {Cell} neighbor - The neighboring cell.
     */
    async openWall(currentCell, neighbor) {
        let currentX = currentCell.x;
        let currentY = currentCell.y;

        let neighborX = neighbor.x;
        let neighborY = neighbor.y;

        let direction = "";
        if (neighborX < currentX) direction = "left";
        if (neighborX > currentX) direction = "right";
        if (neighborY < currentY) direction = "top";
        if (neighborY > currentY) direction = "bottom";

        currentCell.openDirection(direction);

        let neighborDirection = this.getNeighborDirection(direction);
        neighbor.openDirection(neighborDirection);

        await this.reloadCells();
    }

    /**
     * Creates the maze using a randomized depth-first search algorithm.
    */
    async createMaze() {
        let randomStart = Math.floor(Math.random() * this.cells.length);
        let current = this.cells[randomStart][0];
        current.left = false;

        let visited = new Set([current]);
        let stack = [current];

        while (stack.length) {
            let currentCell = stack[stack.length - 1];
            currentCell.current = true;

            let neighbors = this.getUnvisitedNeighbors(currentCell, visited);

            if (neighbors.length) {
                let randomNum = Math.floor(Math.random() * neighbors.length);
                let randomNeighbor = neighbors[randomNum];

                await this.openWall(currentCell, randomNeighbor);

                visited.add(randomNeighbor);
                stack.push(randomNeighbor);

                currentCell.current = false;
            } else {
                currentCell.current = false;
                stack.pop();
            }
        }

        let randomEnd = Math.floor(Math.random() * this.cells.length);
        let end = this.cells[randomEnd][this.cells[0].length - 1];
        end.right = false;

        await this.reloadCells();
    }

    /**
     * Pauses execution for a specified number of milliseconds.
     * @param {number} ms - The number of milliseconds to sleep.
     * @returns {Promise} - A promise that resolves after the specified time.
     */
    sleep(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
}

export default Maze