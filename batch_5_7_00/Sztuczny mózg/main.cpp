//
//  main.cpp
//  Sztuczny mózg
//
//  Created by Mikołaj Jędrzejewski on 10/16/21.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

//AND gate function
int f(vector<float> a) {
    return a[0] and a[1];
}

class Net {
public:
    vector<float> w;;
    float b;
    vector<float> w_grad;
    float b_grad;
    float lr = 0.001;
    float eps = 0.007;
    
    Net(int size) {
        srand((unsigned int)time(NULL));
        for (int i=0; i<size; ++i) {
            w.push_back(float(rand())/float(RAND_MAX));
            w_grad.push_back(0);
        }
        b = float(rand())/float(RAND_MAX);
        b_grad = 0;
    }
    
    void Params() {
        cout<<"Params: \n";
        cout<<"w = [";
        for (auto ele: w) cout<<ele<<" ";
        cout<<"]\n";
        cout<<"b = "<<b<<"\n";
    }
    
    float ReLU(float y) {
        if (y<0) return 0;
        return y;
    }
    
    float linreg(vector<float> x) {
        assert(x.size() == w.size());
        float y = 0;
        for (int i=0; i<x.size(); ++i) {
            y += x[i] * w[i];
        }
        y += b;
        return ReLU(y);
    }
    
    float loss(float y_hat, float y) {
        return (y_hat - y)*(y_hat - y) / 2;
    }
    
    void update_grad(vector<float> x) {
        for (int i=0; i<w.size(); ++i) {
            w[i] += eps;
            float y_hat = linreg(x);
            float y = f(x);
            w_grad[i] = (y_hat-y) / eps;
            w[i] -= eps;
        }
            
        b += eps;
        float y_hat = linreg(x);
        float y = f(x);
        b_grad = (y_hat-y) / eps;
        b -= eps;
    }
    
    //optimization function
    void sgd() {
        for (int i=0; i<(int)w.size(); ++i)
            w[i] -= lr * w_grad[i];
        b -= lr * b_grad;
    }
    
    float forward(vector<float> x, float y) {
        float l = loss(linreg(x), y);
        update_grad(x);
        sgd();
        return l;
    }
    
    float predict(vector<float> x) {
        return linreg(x) > 0.95;
    }
};

pair<vector<vector<float>>, vector<float>> generateData(int n=256) {
    vector<vector<float>> features;
    vector<float> labels;
    
    for (int i=0; i<n/4; ++i)
        features.push_back({0,0});
    for (int i=0; i<n/4; ++i)
        features.push_back({0,1});
    for (int i=0; i<n/4; ++i)
        features.push_back({1,0});
    for (int i=0; i<n/4; ++i)
        features.push_back({1,1});
    
    srand((unsigned int)time(NULL));
    for (int i=0; i<100000; ++i) {
        float x = (features.size()-1) * float(rand())/float(RAND_MAX);
        swap(features[0], features[(int)x]);
    }
        
    for (auto x: features)
        labels.push_back(f(x));
    
    return make_pair(features, labels);
}

int main() {
    
    Net net(2);
    net.Params();
    
    vector<vector<float>> X;
    vector<float> Y;
    
    pair<vector<vector<float>>, vector<float>> data = generateData(256);
    X = data.first;
    Y = data.second;
    
    int epoch = 256;
    for (int i=0; i<epoch; ++i) {
        for (int j=0; j<X.size(); ++j)
            //cout<<"loss: "<<net.forward(X[j], Y[j])<<"\n";
            net.forward(X[j], Y[j]);
    }
    
    net.Params();
    
    vector<vector<float>> test_X = {{0,0},{0,1},{1,0},{1,1}};

    cout<<"Predictions:\n";
    for (int i=0; i<test_X.size(); ++i) {
        cout<<"("<<test_X[i][0]<<", "<<test_X[i][1]<<") "<<net.predict(test_X[i])<<"\n";
    }
    
    return 0;
}
