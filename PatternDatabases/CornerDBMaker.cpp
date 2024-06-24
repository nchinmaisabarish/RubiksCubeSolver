#include "CornerDBMaker.h"
#include <iostream>
using namespace std;

CornerDBMaker::CornerDBMaker(string _fileName) {
    fileName = _fileName;
}

CornerDBMaker::CornerDBMaker(string _fileName, uint8_t init_val) {
    fileName = _fileName;
    cornerDB = CornerPatternDatabase(init_val);
}

bool CornerDBMaker::bfsAndStore() {
    RubiksCubeBitboard cube;
    queue<RubiksCubeBitboard> q;
    q.push(cube);
    cornerDB.setNumMoves(cube, 0);
    int curr_depth = 0;

    while (!q.empty()) {
        int n = q.size();
        curr_depth++;
        cout << "Processing depth " << curr_depth << endl; // Print current depth

        if (curr_depth == 9) break;

        for (int counter = 0; counter < n; counter++) {
            RubiksCubeBitboard node = q.front();
            q.pop();

            for (int i = 0; i < 18; i++) {
                auto curr_move = RubiksCube::MOVE(i);
                node.move(curr_move);

                // Check if this move leads to a shorter path to the node
                if ((int) cornerDB.getNumMoves(node) > curr_depth) {
                    cornerDB.setNumMoves(node, curr_depth);
                    q.push(node);
                }

                node.invert(curr_move);
            }
        }

        cout << "Completed processing depth " << curr_depth << endl; // Print completion of depth
    }

    cornerDB.toFile(fileName);
    cout << "BFS completed. Results stored in " << fileName << endl; // Print completion of BFS

    return true;
}
