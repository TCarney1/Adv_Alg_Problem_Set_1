#include <iostream>



const int Nmax = 30;

struct point{
    int x, y;
};

struct line{
    point p1, p2;
};

bool isCounterClockwise(point a, point b, point c);

int main(){
    point polygon[Nmax] = {{0,0}, {0, 1}, {-1, 0}};
    isCounterClockwise(polygon[0], polygon[1], polygon[2]);

    return 0;
}

// returns true if 3 points form a counter clockwise angle.
bool isCounterClockwise(point a, point b, point c){
    if(a.x*b.y - a.y*b.x + a.y*c.x - a.x*c.y + b.x*c.y - c.x*b.y > 0){
        std::cout << "Counter Clockwise." << std::endl;
        return true;
    } else {
        std::cout << "Clockwise." << std::endl;
        return false;
    }
}