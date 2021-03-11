#include <iostream>
#include <limits>
#include <array>
#include <vector>


struct point{
    int x, y;
};


// TASK: 
//  Implement the brute force and divide and conquer algorithms 
//  for the closest pair problem.


//returns the index of the 2 closest points using brute force algorithm
std::array<point, 2> closestPairBruteForce(point strip[], int n);
//returns the index of the 2 closest points using divide and conquer alg.
std::array<point, 2> closestPairDivideAndConq(point strip[], int n);
std::array<point, 2> stripClosest(point strip[], int size, double d);
int compareX(const void *p1, const void *p2);
int compareY(const void *p1, const void *p2);

void display(point p);
double dist(point p1, point p2);



int main(){
    point points[] = {{0, 0}, {2, 2}, {4, 0}, {6, 2}, {8, 0}, {4, 8}, {2, 3}, {7, 7}, {1, 5}};
    std::array<point, 2> answers;

    int n = (sizeof(points))/(sizeof(points[0]));

    // sort pairs.
    qsort(points, n, sizeof(point), compareX);

    answers = closestPairDivideAndConq(points, n);
    std::cout << "Divide and Conq: " << std::endl;
    display(answers[0]);
    display(answers[1]);

    answers = closestPairBruteForce(points, n);
    std::cout << "Brute Force: " << std::endl;
    display(answers[0]);
    display(answers[1]);

   
    return 0;
}


//returns the 2 closest points using brute force algorithm
std::array<point, 2> closestPairBruteForce(point points[], int n){
    int dmin = std::numeric_limits<int>::max();
    std::array<point, 2> closestPair;

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            double d = dist(points[i], points[j]);
            if(d < dmin){
                dmin = d;
                closestPair[0] = points[i];
                closestPair[1] = points[j];
            }
        }
    }
    return closestPair;
}


//returns the index of the 2 closest points using divide and conquer alg.
std::array<point, 2> closestPairDivideAndConq(point points[], int n){

    if(n <= 3){
        return closestPairBruteForce(points, n);
    }

    // take middle index
    int mid = n/2;
    point midPoint = points[mid];

    // recursively call function from each half.
    std::array<point, 2>  lhs = closestPairDivideAndConq(points, mid);
    std::array<point, 2>  rhs = closestPairDivideAndConq(points + mid, n - mid);
    std::array<point, 2>  dPair;

    // take the closer points
    if(dist(lhs[0], lhs[1]) < dist(rhs[0], rhs[1])){
        dPair = lhs;
    } else {
        dPair = rhs;
    }
    double d = dist(dPair[0], dPair[1]);


    // find all the points within d distance from mid point
    point strip[n];

    int stripSize = 0;
    for(int i = 0; i < n; i++){
        // if the point is closer to the mid point than d.
        if(abs(points[i].x - midPoint.x) < d){
            // add it to strip.
            strip[stripSize] = points[i];
            stripSize++;
        }
    }

    //find if the closest point in the strip is closer smaller than d
    std::array<point, 2> smallestStripPair = stripClosest(strip, stripSize, d);
    double stripD = dist(smallestStripPair[0], smallestStripPair[1]);


    if(d < stripD){
        return dPair;
    } else {
        return smallestStripPair;
    }
}

int compareX(const void *a, const void *b){
    point *p1 = (point *)a, *p2 = (point *) b;

    return (p1->x - p2->x);
}

int compareY(const void *a, const void *b){
    point *p1 = (point *)a, *p2 = (point *) b;

    return (p1->y - p2->y);
}

double dist(point p1, point p2){
    return sqrt((p1.x-p2.x) * (p1.x-p2.x) + (p1.y-p2.y) * (p1.y-p2.y));
}

std::array<point, 2> stripClosest(point strip[], int size, double d){
    double min = d;
    std::array<point, 2> closestPair;

    qsort(strip, size, sizeof(point), compareY);

    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; j++){
            double tempD = dist(strip[i], strip[j]);
            if(tempD < min){
                min = tempD;
                closestPair[0] = strip[i];
                closestPair[1] = strip[j];
                
            }
        }
    }

    return closestPair;
}

 void display(point p){
        std::cout << "(" << p.x << ", " << p.y << ") " << std::endl;
    }