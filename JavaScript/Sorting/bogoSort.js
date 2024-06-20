/*----------------------------------------------------------------------

    ____                       _____            __
   / __ )____  ____ _____     / ___/____  _____/ /_
  / __  / __ \/ __ `/ __ \    \__ \/ __ \/ ___/ __/
 / /_/ / /_/ / /_/ / /_/ /   ___/ / /_/ / /  / /_
/_____/\____/\__, /\____/   /____/\____/_/   \__/
            /____/

Time complexity : O(N!)
Space complexity: O(1)
----------------------------------------------------------------------*/

function shuffleArray(array) {
    for (let i = array.length - 1; i > 0; i--) {
        let j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
    }
    return array;
}

function isSorted(arr) {
    for (let i = 0; i < arr.length - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false
        }
    }

    return true
}


function bogoSort(arr) {
    let i = 0
    while (! isSorted(arr)) {
        shuffleArray(arr)
        i++
    }

    return i
}

arr = [3, 99, 0, 2, 8, 9, 5, 1, 4]
console.log(bogoSort(arr))
console.log(arr)