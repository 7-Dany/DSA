class Cell {
    constructor(context, x, y, width) {
        this.context = context
        this.x = x
        this.y = y
        this.width = width
        this.bottom = true
        this.top = true
        this.right = true
        this.left = true
        this.draw()
    }

    drawLine(start, end){
        let [xStart, yStart] = start
        let [xEnd, yEnd] = end

        this.context.beginPath()
        this.context.moveTo(xStart, yStart)
        this.context.lineTo(xEnd, yEnd)
        this.context.closePath()

        this.context.stroke()
    }

    draw() {
        if (this.left) this.drawLine([this.x, this.y], [this.x, this.y + this.width])
        if (this.top) this.drawLine([this.x, this.y + this.width], [this.x + this.width, this.y + this.width])
        if (this.right) this.drawLine([this.x + this.width, this.y + this.width], [this.x + this.width, this.y])
        if (this.bottom) this.drawLine([this.x, this.y], [this.x + this.width, this.y])
    }
}

export default Cell