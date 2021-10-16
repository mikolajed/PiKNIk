//
//  main.cpp
//  PKS
//
//  Created by Mikołaj Jędrzejewski on 10/16/21.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF=1e9;

struct node {
    vector<int> adj;
    int dist = INF;
};

void bfs(vector<node> &G, int v) {
    queue<int> Q;
    Q.push(v);
    G[v].dist = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto x: G[u].adj) if (G[x].dist == INF) {
            G[x].dist = G[u].dist+1;
            Q.push(x);
        }
    }
}

int main() {
    int m;          //liczba miast
    cin>>m;
    
    int a, b;       //poczatek podrozy, miasto docelowe
    cin>>a>>b;
    a--; b--;
    
    int n;          //liczba poloczen miedzy miastami
    cin>>n;
    
    vector<node> G(m);
    for (int i=0; i<n; ++i) {
        int v, u;
        cin>>v>>u;
        v--; u--;
        G[v].adj.push_back(u);
    }
    
    bfs(G, a);
    
    G[b].dist == INF ? cout<<"NIE" : cout<<G[b].dist;

    return 0;
}
/*
 IN
 4
 4
 3
 4
 1 2
 2 3
 1 3
 4 1
 */
