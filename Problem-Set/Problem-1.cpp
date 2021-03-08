#include <iostream>
#include <map>
#include <cmath>
#include <limits>



struct point{
    int x, y;
};

struct line{
    point p1, p2;
};

int isClockwise(point a, point b, point c);
bool intersect(line l1, line l2);
void printClosedPath(point polygon[], int n);
void swapPoints(point &a, point &b);
double dist(point a, point b);
int swap(point &p1, point &p2);
int cmp(const void *vp1, const void *vp2);



point p0;

int main(){
    point polygon[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = (sizeof(polygon))/(sizeof(polygon[0]));

    printClosedPath(polygon, n);  

    return 0;
}

// returns true if 3 points form a clockwise angle.
int isClockwise(point a, point b, point c){
    int x = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);     
    // straight line
    if(x == 0){
        return 0;
    }else if(x  < 0){
        // clockwise
        return 1;
    } else {
        // counter clockwise
        return 2;
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

// takes a list of points, returns points in order to make a path without intersects
void printClosedPath(point polygon[], int n){
    //find bottom point (left most if tie)
    int lowest = polygon[0].y;
    int min = 0;

    for(int i = 1; i < n; i++){
        // get current y
        int y = polygon[i].y;

        // if there is a point lower, or a point just as low but further left
        if((y < lowest) || (y == lowest) && polygon[i].x < polygon[min].x){
            lowest = y;
            min = i;
        }
    }

    swap(polygon[0], polygon[min]);
    p0 = polygon[0]; 
    qsort(&polygon[1], n-1, sizeof(point), cmp);

    for(int i = 0; i < n; i++){
        std::cout << polygon[i].x << " " << polygon[i].y << std::endl;
    }
}

// for qsort
int cmp(const void *vp1, const void *vp2){
    point *p1 = (point *)vp1;
    point *p2 = (point *)vp2;

    int o = isClockwise(p0, *p1, *p2);

    if(o == 0){
        return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1;
    }
    
    return (o == 2) ? -1 : 1;
}

double dist(point a, point b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int swap(point &p1, point &p2){
    point temp = p1;
    p1 = p2;
    p2 = temp;
}