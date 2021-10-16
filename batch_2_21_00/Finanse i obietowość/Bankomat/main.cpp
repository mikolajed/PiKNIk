//
//  main.cpp
//  Bankomat
//
//  Created by Mikołaj Jędrzejewski on 10/15/21.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const int INF = 1e9;
int k = 1e6; //maksymalna kwota

int n;

int main() {
    cin>>n;
    
    vector<int> dp(k+1, INF);
    dp[0] = 0;
    
    vector<int> b;
    
    for (int i=0; i<n; ++i) {
        int a;
        cin>>a;
        b.push_back(a);
        for (int j=0; j<=k-a; ++j)
            if (dp[j] < INF)
                dp[j+a] = min( dp[j]+1, dp[j+a]);
    }
    
    //odzyskanie ilosci uzytych banknotow
    int q;
    cin>>q;
    
    unordered_map<int, int> ile;
    while (q--) {
        cout<<"\n";
        int x;
        cin>>x;
        if (dp[x] == INF) {
            cout<<"NIE\n";
            continue;
        }
        while (x > 0) {
            for (int jump: b)
                if (x-jump >= 0 and dp[x]-1 == dp[x-jump]) {
                    ile[jump]++;
                    x -= jump;
                    break;
                }
        }
        for (int nom: b)
            if (ile[nom] > 0) {
                cout<<nom<<"x"<<ile[nom]<<"\n";
                ile[nom] = 0;
            }
    }
    
    return 0;
}
/*
 IN
 5
 1 5 10 20 50
 2
 68
 21
 OUT
 
 
 IN
 4
 2 5 10 20
 10
 
 */
