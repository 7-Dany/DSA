/*--------------------------------------------------------

    __  ___                        _____            __
   /  |/  /__  _________ ____     / ___/____  _____/ /_
  / /|_/ / _ \/ ___/ __ `/ _ \    \__ \/ __ \/ ___/ __/
 / /  / /  __/ /  / /_/ /  __/   ___/ / /_/ / /  / /_
/_/  /_/\___/_/   \__, /\___/   /____/\____/_/   \__/
                 /____/

 * It works by:
 *  1. Dividing the array into two halves recursively until we get subarrays of size 1.
 *  2. Merging the subarrays back together in a sorted order.

 - Time Complexity : O(n log n)
 - Space Complexity: O(n) 
--------------------------------------------------------*/

function split(array) {
    let right = []
    let left = []
    let middle = Math.floor(array.length / 2)

    for (let i = 0; i < array.length; i++) {
        if (i < middle) {
            left.push(array[i])
        } else {
            right.push(array[i])
        }
    }

    return [left, right]
}
function merge(left, right) {
    let i = 0;
    let j = 0;
    let results = []

    while (i < left.length && j < right.length) {
        if (left[i] < right[j]) {
            results.push(left[i])
            i++
        } else {
            results.push(right[j])
            j++
        }
    }

    while (i < left.length) {
        results.push(left[i])
        i++
    }

    while (j < right.length) {
        results.push(right[j])
        j++
    }

    return results
}

function mergeSort(array) {
    if (array.length === 1) return array

    let [left, right] = split(array)

    left = mergeSort(left)
    right = mergeSort(right)

    return merge(left, right)
}

let arr = [3, 0, 9, 10, 1, 342, 2]

console.log(mergeSort(arr))