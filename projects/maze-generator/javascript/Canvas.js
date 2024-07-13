class Canvas {
    constructor(id, width, height) {
        this.canvas = document.querySelector(`#${id}`)
        this.context = this.canvas.getContext('2d')
        this.canvas.width = width
        this.canvas.height = height
        this.context.strokeStyle = '#fff'
    }
}


export default Canvas