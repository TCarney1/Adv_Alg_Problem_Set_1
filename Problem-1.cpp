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
    point polygon[Nmax] = {{1,2}, {2, 3}, {3, 4}};
    isCounterClockwise(polygon[0], polygon[1], polygon[2]);

}

bool isCounterClockwise(point a, point b, point c){
    std::cout << a.x << std::endl;
    return true;
}