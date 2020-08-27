// gustavo collaco - 111851 - graph theory
#include <iostream>
#include <map>
#include <queue>
#include <string>

// chess board size
#define size 8

using namespace std;

// a struct Cell component represents a cell, with the distance to the initial cell being incremented according the process goes on
// or it could just store coordinates, without having the distance attribute being used
struct Cell {
    int x, y, dist = 0;
};

// checks if the knight's movement is possible
bool insideBoard(int x, int y) {
    return x >= 0 && x < size && y >= 0 && y < size;
}

// finds out the minimum amount of steps to make to reach the destination from the initial spot
int BreadthFirstSearch(Cell init, Cell dest) {
    // possible moves the knight can make
    Cell moves[] = { {2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };

    // matrix to keep the already visited positions
    bool visited[size][size];

    // initializing the visited matrix with false values on all positions
    for (int i = 0; i < size; i++) 
        for (int j = 0; j <= size; j++) 
            visited[i][j] = false;

    // marking the initial spot as visited
    visited[init.x][init.y] = true;

    // creating a queue to keep the cells to be visited
    // pushing the initial cell, which will be the first visited
    queue<Cell> cellQueue;
    cellQueue.push(init);

    // loops while the queue is not empty
    while(!cellQueue.empty()) {
        // gets the first element of the queue and pops it
        Cell current = cellQueue.front();
        cellQueue.pop();

        // check if the destination was reached, clearing the queue and returning the distance to the initial cell
        if(current.x == dest.x && current.y == dest.y) {
            cellQueue = queue<Cell>();
            return current.dist;
        }

        // makes the possible moves according to the start position
        int movesQty = sizeof(moves) / sizeof(moves[0]);
        for (int i = 0; i < movesQty; i++) {
            // gets the new coordinates
            int newX = current.x + moves[i].x;
            int newY = current.y + moves[i].y;

            // checks if the new location is inside the board and hasn't been visited
            if(insideBoard(newX, newY) && !visited[newX][newY]) {
                // marks the location as visited
                visited[newX][newY] = true;
                // enqueue the new found location, so that it will be verified later
                Cell newCell = { newX, newY, current.dist + 1 };
                cellQueue.push(newCell);
            }
        }
    }
}

// initializes the map, linking the letters 'a' to 'h' to the number of its position on the board
map<char, int> initMap() {
    map<char, int> letter_num;

    letter_num.insert(make_pair('a', 0));
    letter_num.insert(make_pair('b', 1));
    letter_num.insert(make_pair('c', 2));
    letter_num.insert(make_pair('d', 3));
    letter_num.insert(make_pair('e', 4));
    letter_num.insert(make_pair('f', 5));
    letter_num.insert(make_pair('g', 6));
    letter_num.insert(make_pair('h', 7));

    return letter_num;
}

// main function
int main() {
    // receiving strings for the initial position and the destination position
    string str_init, str_dest;
    cin >> str_init >> str_dest;

    // map to map letters to numbers
    map<char, int> letter_num = initMap();

    // cells for the initial and destination positions
    // coordinates for x and y based on the inputs
    Cell init = { letter_num.find(str_init[0])->second, (str_init[1] - '0') - 1 };
    Cell dest = { letter_num.find(str_dest[0])->second, (str_dest[1] - '0') - 1 };

    // prints the result found
    cout << BreadthFirstSearch(init, dest) << endl;
    return 0;
}