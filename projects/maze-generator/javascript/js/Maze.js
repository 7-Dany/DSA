import Renderer from './Renderer.js'
import Canvas from './Canvas.js'
import Cell from './Cell.js';

class Maze {
    constructor(width = 500, height = 500, cellWidth = 100, cellHeight = 100) {
        this.canvas = new Canvas('canvas', width, height);
        this.width = width;
        this.height = height;
        this.cellWidth = cellWidth;
        this.cellHeight = cellHeight;
        this.cells = [];
        this.cellRenderer = new Renderer(this.canvas);
    }

    startGenerating = async (width, height, cellWidth, cellHeight) => {
        this.cells = [];
        this.width = width;
        this.height = height;
        this.cellWidth = cellWidth;
        this.cellHeight = cellHeight;
        this.canvas.setDimentions(width, height);
        this.createCells();
        await this.reloadCells();
        await this.createMaze();
    }

    createCells() {
        for (let y = 0; y < this.height / this.cellHeight; y++) {
            let row = [];
            for (let x = 0; x < this.width / this.cellWidth; x++) {
                const cell = new Cell(x, y, this.cellWidth, this.cellHeight);
                row.push(cell);
            }
            this.cells.push(row);
        }
    }

    async reloadCells() {
        this.canvas.reset();

        for (let row of this.cells) {
            for (let cell of row) {
                this.cellRenderer.draw(cell);
            }
        }

        await this.sleep(50);
    }

    getUnvisitedNeighbors(currentCell, visited) {
        let { x: posX, y: posY } = currentCell;
        let neighbors = [];

        // Left
        if (posX > 0) {
            let left = this.cells[posY][posX - 1];
            if (!visited.has(left)) neighbors.push(left);
        }

        // Right
        if (posX < this.cells[0].length - 1) {
            let right = this.cells[posY][posX + 1];
            if (!visited.has(right)) neighbors.push(right);
        }

        // Top
        if (posY > 0) {
            let top = this.cells[posY - 1][posX];
            if (!visited.has(top)) neighbors.push(top);
        }

        // Bottom
        if (posY < this.cells.length - 1) {
            let bottom = this.cells[posY + 1][posX];
            if (!visited.has(bottom)) neighbors.push(bottom);
        }

        return neighbors;
    }

    getNeighborDirection(neighborDirection) {
        const directions = {
            "right": "left",
            "left": "right",
            "top": "bottom",
            "bottom": "top"
        };

        return directions[neighborDirection];
    }

    async openWall(currentCell, neighbor) {
        let { x: currentX, y: currentY } = currentCell;
        let { x: neighborX, y: neighborY } = neighbor;

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
                let randomNeighbor = neighbors[Math.floor(Math.random() * neighbors.length)];

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

    sleep(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
}

export default Maze;
