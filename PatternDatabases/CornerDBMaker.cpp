#include "CornerDBMaker.h"
#include <bits/stdc++.h>

using namespace std;

CornerDBMaker::CornerDBMaker(string _fileName) {
    fileName = _fileName;
}

CornerDBMaker::CornerDBMaker(string _fileName, uint8_t init_val) : cornerDB(init_val) {
    fileName = _fileName;
}

bool CornerDBMaker::bfsAndStore() {
    RubiksCubeBitboard cube;
    queue<RubiksCubeBitboard> q;
    q.push(cube);
    cornerDB.setNumMoves(cube, 0);
    int cnt = 1;

    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            RubiksCubeBitboard node = q.front();
            q.pop();
            for (int j = 0; j < 18; j++) {
                auto curr_move = RubiksCube::MOVE(j);
                node.move(curr_move);
                if ((int) cornerDB.getNumMoves(node) > (int) cornerDB.getNumMoves(cube)) {
                    cornerDB.setNumMoves(node, cornerDB.getNumMoves(cube) + 1);
                    cnt++;
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
        cube.move(RubiksCube::MOVE(0));
        cube.invert(RubiksCube::MOVE(0));
    }

    cornerDB.toFile(fileName);
    return true;
}
