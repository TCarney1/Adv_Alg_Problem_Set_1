#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <stack>


struct point{
    int x, y;
};

struct cmp{
    cmp(point p){this->p = p;}
    bool operator () (point p1, point p2){ 
        return (angle(this->p, p1) < angle(this->p, p2));
    }

    double angle(point p1, point p2){
        double angle = 0;
        point horizontal = {p2.x , p1.y};
        double adjacent = dist(p1, horizontal);
        double hypotenuse = dist(p1, p2);
        
        angle = cos(adjacent/hypotenuse);

        // obtuse angle.
        if(p2.x < p1.x){
            angle = 180 - angle;
        }

        return angle;
    }

    double dist(point p1, point p2){
        return sqrt((p1.x-p2.x) * (p1.x-p2.x) + (p1.y-p2.y) * (p1.y-p2.y));
    }

    point p;
};


// Task: 
// Implement the Graham Scan algorithm for 
// finding the convex hull of a set of points.

// finds convex hull using Graham Scan algorithm
void GrahamScan(std::array<point, 8> &points);
// returns lowest y value point
int getAnchor(std::array<point, 8> &points);
// returns 0 for straight line, 1 for CW, 2 for CCW 
int orientation(point a, point b, point c);
// pop() top() push()
point underTop(std::stack<point> &s);

int main(){
    std::array<point, 8> points = {{{0, 0}, {4, 0}, {6, 2}, {8, 0}, {4, 8}, {2, 3}, {7, 7}, {1, 5}}};
    std::array<point, 8> points2 = {{{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}}};

    GrahamScan(points);
    std::cout << "---------" << std::endl;
    GrahamScan(points2);

    return 0;
}

void GrahamScan(std::array<point, 8> &points){
    // find point with lowest y value.
    int anchor = getAnchor(points);
    
    point temp = points[0];
    points[0] = points[anchor];
    points[anchor] = temp;

    anchor = 0; // anchor is now at 0 index;

    // sort by angle from anchor (CCW)
    std::sort(points.begin() + 1, points.end(), cmp(points[anchor]));

    int m = 1;

    for(int i = 1; i < points.size(); i++){
        while(i < points.size()-1 && orientation(points[0], points[i], points[i+1]) == 0){
            i++;
        }
        points[m] = points[i];
        m++;
    }

    if(m<3) return;


    std::stack<point> s;
    s.push(points[0]);
    s.push(points[1]);
    s.push(points[2]);

    // iterate through sorted points
    for(size_t i = 3; i < m; i++){
        while(s.size()>1 && orientation(underTop(s), s.top(), points[i]) != 2){
            s.pop();
        }
        s.push(points[i]);
    }
    // while the last turn is right (CW) remove second to last point

    while(!s.empty()){
        point p = s.top();
        std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
        s.pop();
    }
}

// returns the index of the point with the lowest y value
int getAnchor(std::array<point, 8> &points){
    int min = points[0].y;
    int minPoint = 0;

    for(size_t i = 1; i < points.size(); i++){
        if(points[i].y < min){
            min = points[i].y;
            minPoint = i;
        }
    }

    return minPoint;
}

// returns 0 for straight line, 1 for CW, 2 for CCW
int orientation(point a, point b, point c){
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

point underTop(std::stack<point> &s){
    point p = s.top();
    s.pop();
    point result = s.top();
    s.push(p);
    return result;
}
