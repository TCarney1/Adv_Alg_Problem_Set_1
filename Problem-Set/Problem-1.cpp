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
void swap(point &p1, point &p2);
int cmp(const void *vp1, const void *vp2);
bool isPointInPolygon(point polygon[], int n, point p);



point p0;

int main(){
    point polygon1[] = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
    point polygon2[] = {{0, 0}, {5, 5}, {5, 0}};
    point p1 = {20, 20}, p2 = {5, 5}, p3 = {3, 3};
    line l1 = {{0, 0}, {2, 2}};

    point polygon3[] = {{0, 0}, {2, 2}, {4, 0}, {6, 2}, {8, 0}, {4, 8}};

    int n = (sizeof(polygon1))/(sizeof(polygon1[0]));

    //std::cout << isPointInPolygon(polygon1, n, p1) << std::endl;
    //std::cout << isPointInPolygon(polygon1, n, p2) << std::endl;


    // PROBLEM 5: What does the intersect fucntion return when called with
    // two copies of the same line
    // ANSWER: False
    // std::cout << intersect(l1, l1);

    // PROBLEM 6: What is the maximum value achievable by count when
    // isPointInPolygon is executed on a polygon with N vertices? Give example.
    // ANSWER: n-1.

    // polygon 3 has 6 vertices, has 5 intersections
    isPointInPolygon(polygon3, 6, (point){1,1});



    return 0;
}

bool isPointInPolygon(point polygon[], int n, point p){
    // create point at same height as p, but INF far on x.
    //point max = {std::numeric_limits<int>::max(), p.y};
    point max = {1000, p.y};

    // iterate through lines and check for intersects
    int i = 0, count = 0;

    do{
        int next = (i+1)%n; // next point (including starting point)

        if(intersect((line) {polygon[i], polygon[next]}, (line) {p, max})){
            count++;
        }
        i=next;
    }while(i != 0);

    std::cout << count << std::endl;

    return !(count%2==0);
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
            //std::cout << "Lines intersect!" << std::endl;
            return true;
        }
    }
    //std::cout << "Lines do NOT intersect!" << std::endl;
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

void swap(point &p1, point &p2){
    point temp = p1;
    p1 = p2;
    p2 = temp;
}