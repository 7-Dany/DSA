class Canvas {
    /**
     * 
     * @param {string} canvasId specificed canvas id to show sorting visualization.
     * @param {int[]} array specificed array to visualize its sorting process.
     */
    constructor(canvasId, array) {
        this.canvas = document.querySelector(`#${canvasId}`)
        this.context = this.canvas.getContext('2d')
        this.array = array
        this.maxNumber = this.getMaxElement(this.array)
        this.createChart(this.array)
    }

    /**
     * Create rectangle on canvas, with position (x, y), and dimentions (width, height)
     * and specific color for the rectangle.
     * @param {number} x rectangle X position.
     * @param {number} y rectangle Y position.
     * @param {number} width rectangle width.
     * @param {number} height rectangle height.
     * @param {string} color rectangle color.
     */
    createRect = (x, y, width, height, color) => {
        this.context.fillStyle = `${color}`
        this.context.fillRect(x, y, width, height)
    }

    /**
     * Converts an HSL color value to RGB.
     * Assumes h, s, and l are contained in the set [0, 1]
     * and returns r, g, and b in the set [0, 255].
     * @param {number} h hue for the color.
     * @param {number} s saturation for the color.
     * @param {number} l lighting for the color.
    */
    hslToRgb = (h, s, l) => {
        h /= 360;
        s /= 100;
        l /= 100;

        let r, g, b;

        if (s === 0) {
            r = g = b = l; // achromatic
        } else {
            const hue2rgb = (p, q, t) => {
                if (t < 0) t += 1;
                if (t > 1) t -= 1;
                if (t < 1 / 6) return p + (q - p) * 6 * t;
                if (t < 1 / 2) return q;
                if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
                return p;
            };

            const q = l < 0.5 ? l * (1 + s) : l + s - l * s;
            const p = 2 * l - q;

            r = hue2rgb(p, q, h + 1 / 3);
            g = hue2rgb(p, q, h);
            b = hue2rgb(p, q, h - 1 / 3);
        }

        const toHex = x => {
            const hex = Math.round(x * 255).toString(16);
            return hex.length === 1 ? '0' + hex : hex;
        };

        return `#${toHex(r)}${toHex(g)}${toHex(b)}`;
    }


    /**
     * Get the maximum number from the array.
     * @param {int[]} array specified array to get the maximum number from.
     * @returns {int} returns the maximum number.
     */
    getMaxElement = (array) => {
        let maxNumber = Number.MIN_SAFE_INTEGER

        for (let i = 0; i < array.length; i++) {
            if (array[i] > maxNumber) maxNumber = array[i]
        }

        return maxNumber
    }

    /**
     * Sleep specified amount of time before continue.
     * @param {int} ms milliseconds.
     * @returns {Promise<void>}
     */
    sleep = (ms) => {
        return new Promise(resolve => setTimeout(resolve, ms))
    }

    /**
     * Create canvas with rectangles of different shapes and colors to visualize sorting.
     * @param {int[]} array specified array to visualize on canvas.
    */
    createChart = async (array, delay = 20) => {
        // Delete the previous canvas
        let canvasWidth = this.canvas.width
        let canvasHeight = this.canvas.height
        this.context.clearRect(0, 0, canvasWidth, canvasHeight)

        // Create a new canvas to visualize numbers.
        let x = 0;
        let maxElement = this.maxNumber
        for (let i of array) {
            let height = (canvasHeight / maxElement) * i - 5
            let width = canvasWidth / array.length
            let color = this.hslToRgb((i / maxElement) * 360, 100, 50)
            this.createRect(x, canvasHeight - height, width, height, color)
            x += width
        }

        // Sleep few milliseconds to see the content.
        await this.sleep(delay);
    }
}

export default Canvas