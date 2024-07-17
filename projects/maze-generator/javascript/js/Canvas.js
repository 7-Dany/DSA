class Canvas {
    constructor(id, width, height) {
        this.canvas = document.querySelector(`#${id}`);
        this.context = this.canvas.getContext('2d');
        this.canvas.width = width;
        this.canvas.height = height;
        this.context.fillStyle = '#0ff';
        this.context.strokeStyle = '#fff';
    }

    /**
     * Draws a line on the canvas.
     * @param {Array} start - The starting point [x, y].
     * @param {Array} end - The ending point [x, y].
     */
    drawLine(start, end) {
        let [xStart, yStart] = start;
        let [xEnd, yEnd] = end;

        this.context.beginPath();
        this.context.moveTo(xStart, yStart);
        this.context.lineTo(xEnd, yEnd);
        this.context.closePath();

        this.context.stroke();
    }

    /**
     * Draws a rectangle on the canvas.
     * @param {number} x - The x-coordinate of the rectangle.
     * @param {number} y - The y-coordinate of the rectangle.
     * @param {number} width - The width of the rectangle.
     * @param {number} height - The height of the rectangle.
     */
    drawRect(x, y, width, height) {
        this.context.fillRect(x, y, width, height);
    }

    /**
     * Resets the canvas by clearing all drawings.
     */
    reset() {
        this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }
}

export default Canvas