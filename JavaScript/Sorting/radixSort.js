

function getDigit(number, index) {
    return Math.floor((number / Math.pow(10, index)) % 10)
}

function counting(array, index) {
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
    let output = Array(array.length)
    for (let i = array.length - 1; i >= 0; i--) {
        let d = getDigit(array[i], index)
        let j = counts[d] - 1
        counts[d] -= 1
        output[j] = array[i]
    }
    
    return output
}

function radixSort(array) {
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
    for (let i = 0; i < digits; i++) {
        array = counting(array, i)
    }

    if (minNumber < 0) {
        for (let i = 0; i < array.length; i++) {
            array[i] += minNumber
        }
    }

    return array
}


let array = [55, 64, 78, 21, 34, 777, 556, 4459, 74369, 321, 7456, -2]
console.log(radixSort(array)) // Expeceted [21,34,55,64,78]
