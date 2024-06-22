const canvas = document.querySelector("#test")
const context = canvas.getContext("2d")

let test = []
for (let i = 1; i <= 50; i++) {
    test.push(i * 10)
}

function hsl(h, s, l) {
    return `hsl(${h}, ${s}, ${l})`
}

function createRect(x, y, width, height, color) {
    context.fillStyle = `${color}`
    context.fillRect(x, y, width, height)
}

function getMaxElement(array) {
    let maxNumber = Number.MIN_SAFE_INTEGER

    for (let i = 0; i < array.length; i++) {
        if (array[i] > maxNumber) maxNumber = array[i]
    }

    return maxNumber
}

async function createChart(array) {
    context.clearRect(0, 0, canvas.width, canvas.height)
    let x = 0;
    let maxElement = getMaxElement(array)
    for (let i of array) {
        let height = (canvas.height / maxElement) * i - 5
        let width = canvas.width / array.length
        let color = hslToRgb((i / maxElement) * 360, 100, 50)
        createRect(x, canvas.height - height, width, height, color)
        x += width
    }
    await sleep(50);
}

/**
 * Converts an HSL color value to RGB.
 * Assumes h, s, and l are contained in the set [0, 1]
 * and returns r, g, and b in the set [0, 255].
 */
function hslToRgb(h, s, l) {
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

async function insertionSort(array) {
    for (let i = 1; i < array.length; i++) {
        let temp = array[i]
        let j = i - 1

        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j]
            j--
            await createChart(array)
        }

        await createChart(array)
        array[j + 1] = temp
    }
    await createChart(array)
    return array
}

async function shuffleArray(array) {
    for (let i = array.length - 1; i > 0; i--) {
        let j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
        await createChart(array)
    }
    return array;
}

function getDigit(number, index) {
    return Math.floor((number / Math.pow(10, index)) % 10)
}

async function counting(array, index) {
    // Count
    let counts = Array(10).fill(0)
    for (let i = 0; i < array.length; i++) {
        let d = getDigit(array[i], index)
        counts[d] += 1
    }

    // Prefix sum
    for (let i = 1; i < counts.length; i++) {
        counts[i] += counts[i - 1]
    }

    // Create output array 
    let output = [...array]
    for (let i = array.length - 1; i >= 0; i--) {
        let d = getDigit(output[i], index)
        let j = counts[d] - 1
        counts[d] -= 1
        array[j] = output[i]
        await createChart(array)
    }

    return array
}

async function radixSort(array) {
    // Get the number with maxdigits
    let maxNumber = Number.MIN_SAFE_INTEGER
    let minNumber = Number.MAX_SAFE_INTEGER
    for (let i = 0; i < array.length; i++) {
        if (array[i] > maxNumber) maxNumber = array[i]
        if (array[i] < minNumber) minNumber = array[i]
    }

    // Shift if their is negative number
    if (minNumber < 0) {
        for (let i = 0; i < array.length; i++) {
            array[i] += minNumber * -1
        }
    }

    // Sort for each digit
    let digits = Math.floor(Math.log10(maxNumber)) + 1
    for (let i = 1; i < digits; i++) {
        array = await counting(array, i)
    }

    if (minNumber < 0) {
        for (let i = 0; i < array.length; i++) {
            array[i] += minNumber
        }
    }

    await createChart(array)
    return array
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms))
}


document.addEventListener('keydown', async (event) => {
    if (event.key === 's') {
        await runSort(shuffleArray, test)
    }
    if (event.key === 'r') {
        console.log('r clicked')
        await runSort(radixSort, test)
    }
    if (event.key === 'i') {
        console.log('i clicked')
        await runSort(insertionSort, test)
    }
})

let locked = false
async function runSort(sort, ...args) {
    if (locked) return
    locked = true
    await sort(...args)
    locked = false
}


createChart(test)