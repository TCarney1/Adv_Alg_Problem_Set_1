#include <iostream>

/*
    Task:
        Implement a quick algorithm for deciding if four line segments
        form a square (without using division)
*/

struct point{
    int x, y;

    inline bool operator==(const point&  l2){
        return this->x == l2.x && this->y == l2.y;
    }

    inline bool operator!=(const point& l2){
        return !(*this==l2);
    }
};

struct line{
    point p1, p2;
};

bool isSquare(line lines[]);
double length(line l);

int main(){
    line square[] = {{{0, 0}, {0, 1}},{{0, 1}, {1, 1}}, {{1, 1}, {1, 0}}, {{1, 0}, {0, 0}}};
    line parallelogram[] = {{{0, 0}, {9, 0}},{{9, 0}, {16, 5}}, {{16, 5}, {7, 5}}, {{7, 5}, {0, 0}}};
    line rhombus[] = {{{0, 0}, {5, 0}},{{5, 0}, {8, 4}}, {{8, 4}, {3, 4}}, {{3, 4}, {0, 0}}};
    line lines[] = {{{0, 0}, {0, 2}},{{0, 1}, {1, 1}}, {{1, 1}, {1, 0}}, {{1, 0}, {0, 0}}};
    
    isSquare(square); // true
    isSquare(parallelogram); // false sides not equal
    isSquare(rhombus); // false corners not square
    isSquare(lines); // false not all sides connect
   

    return 0;
}

bool isSquare(line lines[]){
    // check same lengths
    double len = length(lines[0]);
    for(int i = 1; i < 4; i++){
        if(len != length(lines[i])){
            std::cout << "FALSE: Sides not equal" << std::endl;
            return false;
        }
    }

    // check points meet
    point start = lines[0].p1;
    point curr = start;
    int i = 0, count = 0;
    do{
        if(curr == lines[i].p1){
            curr = lines[i].p2;
        } else if (curr == lines[i].p2){
            curr = lines[i].p1;
        }
        i = (i + 1) % 4;
        count++;
        // 4! attempts
        if(count >= 24){
            std::cout << "FALSE: Not all sides connect" << std::endl;
            return false;
        }
    }while(curr != start);

    //check for right angles

    std::cout << "TRUE: Is a square" << std::endl;
    return true;
}

double length(line l){
    return (l.p1.x - l.p2.x) * (l.p1.x - l.p2.x) + (l.p1.y - l.p2.y) * (l.p1.y - l.p2.y);
}
