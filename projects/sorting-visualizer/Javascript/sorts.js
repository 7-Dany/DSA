class Sort {
    #_locked;
    /**
     * Contains all sorting algorithms
     * @param {Function} chart function to create chart for the array that being sorted.
    */
    constructor(chart) {
        this.chart = chart
    }

    getSort = (key) => {
        switch (key) {
            case "s": return this.shuffleArray;
            case "r": return this.radixSort;
            case "i": return this.insertionSort;
            case "b": return this.bubbleSort;
            case "w": return this.selectionSort;
            case "q": return this.quickSort;
            case "m": return this.mergeSort;
            case " ": return this.reset;
            default: return null;
        }
    }

    /**
     * Shuffle the array
     * @param {int[]} array array of numbers. 
     * @returns {int[]} shuffled array.
    */
    shuffleArray = async (array) => {
        for (let i = array.length - 1; i > 0; i--) {
            let j = Math.floor(Math.random() * (i + 1));

            [array[i], array[j]] = [array[j], array[i]];

            await this.chart(array)
        }

        await this.chart(array)
    }

    getDigit = (number, index) => {
        return Math.floor((number / Math.pow(10, index)) % 10)
    }

    counting = async (array, index) => {
        // Count
        let counts = Array(10).fill(0)
        for (let i = 0; i < array.length; i++) {
            let d = this.getDigit(array[i], index)
            counts[d] += 1
        }

        // Prefix sum
        for (let i = 1; i < counts.length; i++) {
            counts[i] += counts[i - 1]
        }

        // Create output array 
        let output = [...array]
        for (let i = array.length - 1; i >= 0; i--) {
            let d = this.getDigit(output[i], index)
            let j = counts[d] - 1
            counts[d] -= 1
            array[j] = output[i]
            await this.chart(array)
        }

        return array
    }

    /**
     * Radix sort algorithm.
     * @param {int[]} array 
     * @returns  {int[]} sorted array
    */
    radixSort = async (array) => {
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
            array = await this.counting(array, i)
        }

        if (minNumber < 0) {
            for (let i = 0; i < array.length; i++) {
                array[i] += minNumber
            }
        }

        await this.chart(array)
    }

    partition = async (array, start, end) => {
        let i = start - 1

        for (let j = start; j < end; j++) {
            if (array[j] < array[end]) {
                i++
                let temp = array[j]
                array[j] = array[i]
                array[i] = temp

                await this.chart(array)
            }
        }

        i++
        let temp = array[i]
        array[i] = array[end]
        array[end] = temp

        await this.chart(array)
        return i
    }

    /**
     * Quick sort algorithm.
     * @param {int[]} array array to be sorted
     * @param {int} start start of the array (default = 0)
     * @param {int} end end of the array (default = array.length - 1)
     * @returns {Promise<void>} sorted array
     */
    quickSort = async (array, start = 0, end = array.length - 1) => {
        if (start > end) return
        let pivot = await this.partition(array, start, end);
        await this.quickSort(array, start, pivot - 1)
        await this.quickSort(array, pivot + 1, end)
    }

    merge = async (array, l1, r1, l2, r2) => {
        let i = l1
        let j = l2
        let results = []

        while (i < r1 + 1 && j < r2 + 1) {
            if (array[i] < array[j]) {
                results.push(array[i])
                i++
            }
            else {
                results.push(array[j])
                j++
            }
        }

        while (i < r1 + 1) {
            results.push(array[i])
            i++
        }

        while (j < r2 + 1) {
            results.push(array[j])
            j++
        }

        let k = 0

        for (let x = l1; x < r2 + 1; x++) {
            array[x] = results[k]
            k++
            await this.chart(array, 1)
        }
    }

    /**
     * Merge sort algorithm
     * @param {int[]} array array to be sorted
    */
    mergeSort = async (array, l = 0, r = array.length - 1) => {
        if (r - l == 0) return

        let mid = Math.floor((l + r) / 2)
        let left1 = l
        let right1 = mid
        let left2 = mid + 1
        let right2 = r

        await this.mergeSort(array, left1, right1)
        await this.mergeSort(array, left2, right2)

        await this.merge(array, left1, right1, left2, right2)
    }

    /**
     * Insertion sort algorithm.
     * @param {int[]} array array to be sorted.
     * @returns {int[]} sorted array
    */
    insertionSort = async (array) => {
        for (let i = 1; i < array.length; i++) {
            let temp = array[i]
            let j = i - 1

            while (j >= 0 && array[j] > temp) {
                array[j + 1] = array[j]
                j--

                await this.chart(array)
            }

            await this.chart(array)
            array[j + 1] = temp
        }

        await this.chart(array)
        return array
    }

    /**
     * Bubble sort algorithm.
     * @param {int[]} array array to be sorted
     * @returns {int[]} sorted array
    */
    bubbleSort = async (array) => {
        for (let i = 0; i < array.length - 1; i++) {
            for (let j = 0; j < array.length - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    let temp = array[j]
                    array[j] = array[j + 1]
                    array[j + 1] = temp
                    await this.chart(array)
                }
            }
        }

        await this.chart(array)
        return array
    }

    /**
     * Selection sort algorithm.
     * @param {int[]} array array to be sorted
     * @returns {int[]} sorted array
    */
    selectionSort = async (array) => {
        for (let i = 0; i < array.length; i++) {
            let min = i
            for (let j = i; j < array.length; j++) {
                if (array[j] < array[min]) {
                    min = j
                }
            }

            let temp = array[min]
            array[min] = array[i]
            array[i] = temp
            await this.chart(array)
        }

        await this.chart(array)
        return array
    }

    reset = async (array) => {
        for (let i = 1; i <= 50; i++) {
            array[i - 1] = i * 10
            await this.chart(array)
        }
    }

    startSorting = async (key, array) => {
        if (this._locked) return
        let sortFunc = this.getSort(key)
        if (!sortFunc) return

        this._locked = true
        await sortFunc(array);
        this._locked = false
    }
}

export default Sort