function insertionSort(array) {
    for (let i = 1; i < array.length; i++) {
        let temp = array[i]
        let j = i - 1

        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j]
            j--
        }

        array[j + 1] = temp
    }
    
    return array
}

console.log(insertionSort([4, 5, 3, 1, 2, 6, 7]))