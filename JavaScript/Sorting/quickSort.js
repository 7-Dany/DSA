/*--------------------------------------------------

   ____        _      __      _____            __
  / __ \__  __(_)____/ /__   / ___/____  _____/ /_
 / / / / / / / / ___/ //_/   \__ \/ __ \/ ___/ __/
/ /_/ / /_/ / / /__/ ,<     ___/ / /_/ / /  / /_
\___\_\__,_/_/\___/_/|_|   /____/\____/_/   \__/

- Time Complexity : O(n log n)
- Space Complexity: O(log n)

--------------------------------------------------*/
function partition(array, start, end) {
    let i = start - 1

    for (let j = start; j < end; j++) {
        if (array[j] < array[end]) {
            i++
            let temp = array[j]
            array[j] = array[i]
            array[i] = temp
        }
    }

    i++
    let temp = array[i]
    array[i] = array[end]
    array[end] = temp

    return i
}

function quickSort(array, start = 0, end = array.length - 1) {
    if (start > end) return
    let pivot = partition(array, start, end);
    quickSort(array, start, pivot - 1)
    quickSort(array, pivot + 1, end)
}

let array = [1, 2, 3, 4, 5]
quickSort(array)

console.log(array)