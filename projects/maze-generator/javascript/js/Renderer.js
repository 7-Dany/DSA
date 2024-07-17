class Renderer {
    constructor(canvas) {
        this.canvas = canvas;
    }

    /**
     * Draws the cell on the canvas based on its properties.
     * @param {Cell} cell - The cell to draw.
     */
    draw(cell) {
        if (cell.current) {
            return this.canvas.drawRect(cell.startX, cell.startY, cell.width, cell.height);
        }
        
        if (cell.left) this.canvas.drawLine([cell.startX, cell.startY], [cell.startX, cell.startY + cell.height]);
        if (cell.right) this.canvas.drawLine([cell.startX + cell.width, cell.startY], [cell.startX + cell.width, cell.startY + cell.height]);
        if (cell.bottom) this.canvas.drawLine([cell.startX, cell.startY + cell.height], [cell.startX + cell.width, cell.startY + cell.height]);
        if (cell.top) this.canvas.drawLine([cell.startX, cell.startY], [cell.startX + cell.width, cell.startY]);
    }
}

export default Renderer