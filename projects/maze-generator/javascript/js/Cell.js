class Cell {
    constructor(x, y, width, height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.startX = this.x * this.width;
        this.startY = this.y * this.height;
        this.bottom = true;
        this.top = true;
        this.right = true;
        this.left = true;
        this.current = false;
    }

    /**
     * Opens the specified direction by setting the direction to false.
     * @param {string} direction - The direction to open ('top', 'right', 'bottom', 'left').
     */
    openDirection(direction) {
        this[direction] = false;
    }
}

export default Cell