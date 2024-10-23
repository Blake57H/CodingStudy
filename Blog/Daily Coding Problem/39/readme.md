# Daily Coding Problem: Problem #39 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Dropbox.

Conway's Game of Life takes place on an infinite two-dimensional board of square cells. Each cell is either dead or alive, and at each tick, the following rules apply:

- Any live cell with less than two live neighbours dies.
- Any live cell with two or three live neighbours remains living.
- Any live cell with more than three live neighbours dies.
- Any dead cell with exactly three live neighbours becomes a live cell.

A cell neighbours another cell if it is horizontally, vertically, or diagonally adjacent.

Implement Conway's Game of Life. It should be able to be initialized with a starting list of live cell coordinates and the number of steps it should run for. Once initialized, it should print out the board state at each step. Since it's an infinite board, print out only the relevant coordinates, i.e. from the top-leftmost live cell to bottom-rightmost live cell.

You can represent a live cell with an asterisk (`*`) and a dead cell with a dot (`.`).

## My solution

1. Read living cells from the given list.
2. Find the neightbour cells and count how many time have they been mentioned (number of living cells in its neightbour).
3. For neightbour cell mentioned 3 times, it becomes alive, less than 2 or more than 3 becomes dead, do nothing if 2.

Couldn't print asterisk and dot. I printed its row and column instead.

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)
