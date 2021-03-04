#include <iostream>



const int Nmax = 30;

struct point{
    int x, y;
};

struct line{
    point p1, p2;
};

bool isClockwise(point a, point b, point c);
bool intersect(line l1, line l2);

int main(){
    point polygon[Nmax] = {{0,0}, {0, 1}, {-1, 0}};

    line 
        l1 = {{0, 0}, {2, 2}}, 
        l2 = {{0, 2}, {2, 0}}, 
        l3 = {{5, 5}, {6, 6}};

    intersect(l1, l2); // should be true
    intersect(l1,l3); // should be false


    return 0;
}

// returns true if 3 points form a clockwise angle.
bool isClockwise(point a, point b, point c){
    if(a.x*b.y - a.y*b.x + a.y*c.x - a.x*c.y + b.x*c.y - c.x*b.y > 0){
        std::cout << "Counter Clockwise." << std::endl;
        return false;
    } else {
        std::cout << "Clockwise." << std::endl;
        return true;
    }
}


// returns true 2 lines intersect 
bool intersect(line l1, line l2){
    // checks that the ends of l2 are NOT on the same sides of l1
    if(isClockwise(l1.p1, l1.p2, l2.p1) != isClockwise(l1.p1, l1.p2, l2.p2)){
        // checks that the ends of l1 are NOT on the same sides of l2
        if(isClockwise(l2.p1, l2.p2, l1.p1) != isClockwise(l2.p1, l2.p2, l1.p2)){
            std::cout << "Lines intersect!" << std::endl;
            return true;
        }
    }
    
    std::cout << "Lines do NOT intersect!" << std::endl;
    return false;
}