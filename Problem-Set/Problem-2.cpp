#include <iostream>

/*
    Task:
    Implement a quick algorithm for deciding if two line segments are parallel
    (without using and division)
*/

struct point{
    int x, y;
};

struct line{
    point p1, p2;
};

bool isParallel(line l1, line l2);

int main(){
    // l1 and l2 are parallel, l3 is not parallel with either.
    line l1 = {{0, 0}, {0, 4}}, l2 = {{2, 0}, {2, 5}}, l3 = {{1, 1}, {2, 3}};
    line l4 = {{1, 1}, {2, 3}}, l5 = {{1, 3}, {2, 5}};

    line l6 = {{0,0}, {4, 0}};

    
    std::cout << isParallel(l1, l2) << std::endl; // true
    std::cout << isParallel(l1, l3) << std::endl; // false
    std::cout << isParallel(l4, l5) << std::endl; // true
    std::cout << isParallel(l1, l6) << std::endl; // false

    return 0;
}


bool isParallel(line l1, line l2){

    if(l1.p1.x == l1.p2.x){
        // line 1 is horizontal
        // check if line 2 is horizontal
        return l2.p1.x == l2.p2.x;
    }

    if(l1.p1.y == l1.p2.y){
        // line 1 is vertical
        // check if line 2 is vertical
        return l2.p1.y == l2.p2.y;
    }

    // line 1 has gradient, find if they are equal.

    int d1 = abs(l1.p1.x - l1.p2.x);
    int d2 = abs(l1.p1.y - l1.p2.y);
    int d3 = abs(l2.p1.x - l2.p2.x);
    int d4 = abs(l2.p1.y - l2.p2.y);

    if(abs(d1-d3) == abs(d2-d4)){
        return true;
    } else {
        return false;
    }
}
