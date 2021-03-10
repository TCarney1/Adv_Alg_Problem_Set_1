#include <iostream>
#include <algorithm>

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

bool isASquare(line lines[]);
double distance(line l);

int main(){
    line square[] = {{{0, 0}, {0, 1}},{{0, 1}, {1, 1}}, {{1, 1}, {1, 0}}, {{1, 0}, {0, 0}}};
    line parallelogram[] = {{{0, 0}, {9, 0}},{{9, 0}, {16, 5}}, {{16, 5}, {7, 5}}, {{7, 5}, {0, 0}}};
    line rhombus[] = {{{0, 0}, {5, 0}},{{5, 0}, {8, 4}}, {{8, 4}, {3, 4}}, {{3, 4}, {0, 0}}};
    line lines[] = {{{0, 0}, {0, 2}},{{0, 1}, {1, 1}}, {{1, 1}, {1, 0}}, {{1, 0}, {0, 0}}};
    
    isASquare(square); // true
    isASquare(parallelogram); // false sides not equal
    isASquare(rhombus); // false corners not square
    isASquare(lines); // false not all sides connect
   

    return 0;
}

bool isASquare(line lines[]){
    // check same lengths
    double len = distance(lines[0]);
    for(int i = 1; i < 4; i++){
        if(len != distance(lines[i])){
            std::cout << "FALSE: Sides not equal" << std::endl;
            return false;
        }
    }

    // check points meet
    const point start = lines[0].p1;
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

        // ensure we loop through enough to return to the start
        if(count >= 24){
            std::cout << "FALSE: Not all sides connect" << std::endl;
            return false;
        }
    }while(curr != start);

    //check for right angles
    
    double maxD = 0, maxD2 = 0;
    point second;
    for(int i = 1; i < 4; i++){
        double d1 = distance((line){start, lines[i].p1});
        double d2 = distance((line){start, lines[i].p2});
        //find other diagonal
        if(d1 < maxD && d2 < maxD){
            second = lines[i].p1;
        }
        maxD = std::max(maxD, d1);
        maxD = std::max(maxD, d2); 
    }

    for(int i = 1; i < 4; i++){
        double d1 = distance((line){second, lines[i].p1});
        double d2 = distance((line){second, lines[i].p2});
        maxD2 = std::max(maxD2, d1);
        maxD2 = std::max(maxD2, d2); 
    }
    
    if(maxD == maxD2){
        std::cout << "TRUE: Is a square" << std::endl;
        return true;
    } else {
        std::cout  << "FALSE: Corners not square" << std::endl;
        return false;
    }
}

double distance(line l){
    return (l.p1.x - l.p2.x) * (l.p1.x - l.p2.x) + (l.p1.y - l.p2.y) * (l.p1.y - l.p2.y);
}
