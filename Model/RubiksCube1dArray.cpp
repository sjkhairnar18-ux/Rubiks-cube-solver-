#include "RubiksCube.h"

// 1D Array Representation of Rubik's Cube
// Maps the 3D cube[face][row][col] to a flat array cube[face*9 + row*3 + col]
// Each face has 9 cells (3x3), total 54 cells for 6 faces.

class RubiksCube1dArray : public RubiksCube {
private:

    // Helper to rotate a face 90 degrees clockwise (in-place)
    void rotateFace(int ind) {
        char temp_arr[9] = {};
        for (int i = 0; i < 9; i++) temp_arr[i] = cube[ind * 9 + i];
        // Mapping for 90° clockwise rotation of a 3x3 grid:
        // old(r,c) -> new(c, 2-r)
        // (0,0)->6, (0,1)->3, (0,2)->0
        // (1,0)->7, (1,1)->4, (1,2)->1
        // (2,0)->8, (2,1)->5, (2,2)->2
        cube[ind * 9 + 0] = temp_arr[6];
        cube[ind * 9 + 1] = temp_arr[3];
        cube[ind * 9 + 2] = temp_arr[0];
        cube[ind * 9 + 3] = temp_arr[7];
        cube[ind * 9 + 4] = temp_arr[4];
        cube[ind * 9 + 5] = temp_arr[1];
        cube[ind * 9 + 6] = temp_arr[8];
        cube[ind * 9 + 7] = temp_arr[5];
        cube[ind * 9 + 8] = temp_arr[2];
    }

public:
    char cube[54]{};

    RubiksCube1dArray() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 9; j++) {
                cube[i * 9 + j] = getColorLetter(COLOR(i));
            }
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char color = cube[int(face) * 9 + row * 3 + col];
        switch (color) {
            case 'B':
                return COLOR::BLUE;
            case 'R':
                return COLOR::RED;
            case 'G':
                return COLOR::GREEN;
            case 'O':
                return COLOR::ORANGE;
            case 'Y':
                return COLOR::YELLOW;
            default:
                return COLOR::WHITE;
        }
    }

    bool isSolved() const override {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 9; j++) {
                if (cube[i * 9 + j] != getColorLetter(COLOR(i))) return false;
            }
        }
        return true;
    }

    // face indices: UP=0, LEFT=1, FRONT=2, RIGHT=3, BACK=4, DOWN=5

    RubiksCube &u() override {
        this->rotateFace(0);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[4 * 9 + 0 * 3 + (2 - i)];
        for (int i = 0; i < 3; i++) cube[4 * 9 + 0 * 3 + (2 - i)] = cube[1 * 9 + 0 * 3 + (2 - i)];
        for (int i = 0; i < 3; i++) cube[1 * 9 + 0 * 3 + (2 - i)] = cube[2 * 9 + 0 * 3 + (2 - i)];
        for (int i = 0; i < 3; i++) cube[2 * 9 + 0 * 3 + (2 - i)] = cube[3 * 9 + 0 * 3 + (2 - i)];
        for (int i = 0; i < 3; i++) cube[3 * 9 + 0 * 3 + (2 - i)] = temp_arr[i];

        return *this;
    }

    RubiksCube &uPrime() override {
        this->u();
        this->u();
        this->u();
        return *this;
    }

    RubiksCube &u2() override {
        this->u();
        this->u();
        return *this;
    }

    RubiksCube &l() override {
        this->rotateFace(1);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0 * 9 + i * 3 + 0];
        for (int i = 0; i < 3; i++) cube[0 * 9 + i * 3 + 0] = cube[4 * 9 + (2 - i) * 3 + 2];
        for (int i = 0; i < 3; i++) cube[4 * 9 + (2 - i) * 3 + 2] = cube[5 * 9 + i * 3 + 0];
        for (int i = 0; i < 3; i++) cube[5 * 9 + i * 3 + 0] = cube[2 * 9 + i * 3 + 0];
        for (int i = 0; i < 3; i++) cube[2 * 9 + i * 3 + 0] = temp_arr[i];

        return *this;
    }

    RubiksCube &lPrime() override {
        this->l();
        this->l();
        this->l();
        return *this;
    }

    RubiksCube &l2() override {
        this->l();
        this->l();
        return *this;
    }

    RubiksCube &f() override {
        this->rotateFace(2);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0 * 9 + 2 * 3 + i];
        for (int i = 0; i < 3; i++) cube[0 * 9 + 2 * 3 + i] = cube[1 * 9 + (2 - i) * 3 + 2];
        for (int i = 0; i < 3; i++) cube[1 * 9 + (2 - i) * 3 + 2] = cube[5 * 9 + 0 * 3 + (2 - i)];
        for (int i = 0; i < 3; i++) cube[5 * 9 + 0 * 3 + (2 - i)] = cube[3 * 9 + i * 3 + 0];
        for (int i = 0; i < 3; i++) cube[3 * 9 + i * 3 + 0] = temp_arr[i];

        return *this;
    }

    RubiksCube &fPrime() override {
        this->f();
        this->f();
        this->f();
        return *this;
    }

    RubiksCube &f2() override {
        this->f();
        this->f();
        return *this;
    }

    RubiksCube &r() override {
        this->rotateFace(3);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0 * 9 + (2 - i) * 3 + 2];
        for (int i = 0; i < 3; i++) cube[0 * 9 + (2 - i) * 3 + 2] = cube[2 * 9 + (2 - i) * 3 + 2];
        for (int i = 0; i < 3; i++) cube[2 * 9 + (2 - i) * 3 + 2] = cube[5 * 9 + (2 - i) * 3 + 2];
        for (int i = 0; i < 3; i++) cube[5 * 9 + (2 - i) * 3 + 2] = cube[4 * 9 + i * 3 + 0];
        for (int i = 0; i < 3; i++) cube[4 * 9 + i * 3 + 0] = temp_arr[i];

        return *this;
    }

    RubiksCube &rPrime() override {
        this->r();
        this->r();
        this->r();
        return *this;
    }

    RubiksCube &r2() override {
        this->r();
        this->r();
        return *this;
    }

    RubiksCube &b() override {
        this->rotateFace(4);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0 * 9 + 0 * 3 + (2 - i)];
        for (int i = 0; i < 3; i++) cube[0 * 9 + 0 * 3 + (2 - i)] = cube[3 * 9 + (2 - i) * 3 + 2];
        for (int i = 0; i < 3; i++) cube[3 * 9 + (2 - i) * 3 + 2] = cube[5 * 9 + 2 * 3 + i];
        for (int i = 0; i < 3; i++) cube[5 * 9 + 2 * 3 + i] = cube[1 * 9 + i * 3 + 0];
        for (int i = 0; i < 3; i++) cube[1 * 9 + i * 3 + 0] = temp_arr[i];

        return *this;
    }

    RubiksCube &bPrime() override {
        this->b();
        this->b();
        this->b();
        return *this;
    }

    RubiksCube &b2() override {
        this->b();
        this->b();
        return *this;
    }

    RubiksCube &d() override {
        this->rotateFace(5);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[2 * 9 + 2 * 3 + i];
        for (int i = 0; i < 3; i++) cube[2 * 9 + 2 * 3 + i] = cube[1 * 9 + 2 * 3 + i];
        for (int i = 0; i < 3; i++) cube[1 * 9 + 2 * 3 + i] = cube[4 * 9 + 2 * 3 + i];
        for (int i = 0; i < 3; i++) cube[4 * 9 + 2 * 3 + i] = cube[3 * 9 + 2 * 3 + i];
        for (int i = 0; i < 3; i++) cube[3 * 9 + 2 * 3 + i] = temp_arr[i];

        return *this;
    }

    RubiksCube &dPrime() override {
        this->d();
        this->d();
        this->d();
        return *this;
    }

    RubiksCube &d2() override {
        this->d();
        this->d();
        return *this;
    }

    bool operator==(const RubiksCube1dArray &r1) const {
        for (int i = 0; i < 54; i++) {
            if (cube[i] != r1.cube[i]) return false;
        }
        return true;
    }

    RubiksCube1dArray &operator=(const RubiksCube1dArray &r1) {
        for (int i = 0; i < 54; i++) {
            cube[i] = r1.cube[i];
        }
        return *this;
    }
};

struct Hash1d {
    size_t operator()(const RubiksCube1dArray &r1) const {
        string str = "";
        for (int i = 0; i < 54; i++) {
            str += r1.cube[i];
        }
        return hash<string>()(str);
    }
};
