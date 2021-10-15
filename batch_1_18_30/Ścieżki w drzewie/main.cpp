//
//  main.cpp
//  Ścieżki w drzewie
//
//  Created by Mikołaj Jędrzejewski on 10/15/21.
//

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

struct node {
    int y;   //y - number levelu (1, 2, ...), numberacja od 1
    int w;
    int min = INF;
    int max = 0;
};

int n;
vector<node> G;

int left(int v) {
    return v + G[v].y;
}

int right(int v) {
    return v + G[v].y + 1;
}

void Calc(int v) {
    if (G[v].y != n) {
        G[ left(v) ].min = min( G[ left(v) ].min, G[v].min + G[ left(v) ].w);
        G[ right(v) ].min = min( G[ right(v) ].min, G[v].min + G[ right(v) ].w);
        
        G[ left(v) ].max = max( G[ left(v) ].max, G[v].max + G[ left(v) ].w);
        G[ right(v) ].max = max( G[ right(v) ].max, G[v].max + G[ right(v) ].w);
        
        Calc(left(v));
        Calc(right(v));
    }
}

void printPath(vector<int> V) {
    //print wartosci
    for (int i=(int)V.size()-1; i>=0; --i)
        cout<<G[V[i]].w<<" ";
    //print indeksow
    /*
     for (int i=(int)V.size()-1; i>=0; --i)
         cout<<V[i]<<" ";
     */
    cout<<"\n";
}

void MaxUp(int v, vector<int> &path) {
    int y = G[v].y;
    if (y != 1) {
        if (G[v].w + G[v - y].max == G[v].max) {
            path.push_back(v-y);
            MaxUp(v-y, path);
            path.pop_back();
        }
        if (G[v].w + G[v - y + 1].max == G[v].max) {
            path.push_back(v-y+1);
            MaxUp(v-y+1, path);
            path.pop_back();
        }
    }
    else {
        printPath(path);
    }
}

void MinUp(int v, vector<int> &path) {
    int y = G[v].y;
    if (y != 1) {
        if (G[v].w + G[v - y].min == G[v].min) {
            path.push_back(v-y);
            MinUp(v-y, path);
            path.pop_back();
        }
        if (G[v].w + G[v - y + 1].min == G[v].min) {
            path.push_back(v-y+1);
            MinUp(v-y+1, path);
            path.pop_back();
        }
    }
    else {
        printPath(path);
    }
}

int main() {
    cin>>n;
    
    int m = n * (n+1) / 2;
    G = vector<node> (m);
    
    int curr = 0;
    for (int l=1; l<=n; ++l) {
        for (int i=0; i<l; ++i) {
            cin>>G[curr].w;
            G[curr++].y = l;
        }
    }
    
    G[0].min = G[0].max = G[0].w;
    Calc(0);
    
    int maxVal = 0;
    int minVal = INF;
    for (int i=m-n; i<m; ++i) {
        maxVal = max( maxVal, G[i].max);
        minVal = min( minVal, G[i].min);
    }
    
    cout<<"Ścieżki najkrótsze:\n";
    for (int i=m-n; i<m; ++i)
        if (G[i].min == minVal) {
            vector<int> path = {i};
            MinUp(i, path);
        }
    
    cout<<"Ścieżki najdłuższe:\n";
    for (int i=m-n; i<m; ++i)
        if (G[i].max == maxVal) {
            vector<int> path = {i};
            MaxUp(i, path);
        }
    
    return 0;
}
/*
 IN
 5
 1
 4 4
 9 8 6
 1 5 7 5
 2 3 5 2 1
 OUT
 */
