//
//  main.cpp
//  Nowa działka Jasia
//
//  Created by Mikołaj Jędrzejewski on 10/16/21.
//

#include <iostream>
#include <vector>

using namespace std;

int n;

struct vertex {
    int x, y;
};

vector<vertex> p;

int sgn(int x){
    if(x>0)         return 1;
    else if(x<0)    return -1;
    return 0;
}

int det(int x1, int y1, int x2, int y2, int x3, int y3){
    return sgn(x1*y2+x2*y3+x3*y1-y2*x3-y3*x1-y1*x2);
}

bool intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    return(
       (det(x1, y1, x2, y2, x3, y3)!=det(x1, y1, x2, y2, x4, y4) &&
        det(x3, y3, x4, y4, x1, y1)!=det(x3, y3, x4, y4, x2, y2)) ||
       (det(x1, y1, x2, y2, x3, y3)==0 && det(x1, y1, x2, y2, x4, y4)==0 &&
        ((x3>=min(x1, x2) && x3<=max(x1, x2) && y3>=min(y1, y2) && y3<=max(y1, y2)) ||
         (x4>=min(x1, x2) && x4<=max(x1, x2) && y4>=min(y1, y2) && y4<=max(y1, y2)))) ||
       (det(x3, y3, x4, y4, x1, y1)==0 && det(x3, y3, x4, y4, x2, y2)==0 &&
        ((x1>=min(x3, x4) && x1<=max(x3, x4) && y1>=min(y3, y4) && y1<=max(y3, y4)) ||
         (x2>=min(x3, x4) && x2<=max(x3, x4) && y1>=min(y3, y4) && y2<=max(y3, y4))))
       );
}

//checks if any pair of lines intersect
//checks every possible pair O(n^2)
bool linesIntersect() {
    for (int i=0; i<n; ++i) {
        vertex p1=p[i];
        vertex p2=p[i+1];
        for (int j=i+2; j+1<n; ++j) {
            vertex q1=p[j];
            vertex q2=p[j+1];
            if (intersect(p1.x, p1.y, p2.x, p2.y, q1.x, q2.y, q2.x, q2.y)) return 1;
        }
    }
    //checking if the last remaning line doesn't intersect with any other
    vertex p1=p[n-1];
    vertex p2=p[0];
    for (int j=2; j+1<n-1; ++j) {
        vertex q1=p[j];
        vertex q2=p[j+1];
        if (intersect(p1.x, p1.y, p2.x, p2.y, q1.x, q2.y, q2.x, q2.y)) return 1;
    }
    return 0;
}

int shoelace_algorithm() {
    int area = 0;
    for (int i=0; i<=n; ++i)
        area += p[i].x * p[(i+1)%n].y;
    for (int i=0; i<=n; ++i)
        area -= p[(i+1)%n].x * p[i].y;
    area /= 2;
    return sgn(area)*area;
}

int main() {
    cin>>n;
    
    p = vector<vertex> (n);
    
    for (int i=0; i<n; ++i)
        cin>>p[i].x>>p[i].y;
    
    if (linesIntersect()) cout<<"BLAD";
    else {
        cout<<shoelace_algorithm();
    }
    
    return 0;
}
/*
 IN
 4
 1 1
 1 2
 2 2
 2 1
 OUT
 1
 */
