/*
   _____      __          __  _                _____            __
  / ___/___  / /__  _____/ /_(_)___  ____     / ___/____  _____/ /_
  \__ \/ _ \/ / _ \/ ___/ __/ / __ \/ __ \    \__ \/ __ \/ ___/ __/
 ___/ /  __/ /  __/ /__/ /_/ / /_/ / / / /   ___/ / /_/ / /  / /_
/____/\___/_/\___/\___/\__/_/\____/_/ /_/   /____/\____/_/   \__/

 * 
 * It works by:
 *  1. Selecting the smallest (or largest, depending on sorting order) element from the unsorted part of the array.
 *  2. Swapping it with the leftmost unsorted element.

 * Time Complexity: O(n ^ 2)
 * Space Complexity: O(1)
*/

function selectionSort(array) {
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
    }
    return array
}

console.log(selectionSort([4, 5, 3, 1, 2, 6, 7]))