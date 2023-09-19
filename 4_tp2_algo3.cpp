#include <iostream>
#include <vector>

using namespace std;
constexpr int BOTTOM = -1;

int maxDmenor(vector<int> &D, int x){
    int d = BOTTOM;
    for(int i=0;i<D.size();i++){
        if(D[i]<=x){
            d = i;
        }
    }
    return d;
}

void fishburn(vector<vector<int>> &E, int n, vector<int> &D){
    vector<int> X(n);
    for(int i=0;i<n;i++){
        X[i]=D.size()-1;
    }
    bool huboCambio = true;
    while(huboCambio){
        huboCambio=false;
        for(int i=0;i<E.size();i++){
            int a = D[X[E[i][0]]];
            int b = D[X[E[i][1]]];
            int c = E[i][2];
            int nuevoX = maxDmenor(D, c+b);
            if(a>b+c && nuevoX!=BOTTOM){
                X[E[i][0]]=nuevoX;
                huboCambio=true;
            }
        }
    }
    bool res = true;
    for(int i=0;i<E.size();i++){
        int a = D[X[E[i][0]]];
        int b = D[X[E[i][1]]];
        int c = E[i][2];
        if(a-b>c){
            res = false;
        }
    }
    if(res==false){
        cout << "insatisfactible";
    }else{
        for(int i=0;i<n;i++){
            cout << X[i]+1 << " ";
        }
        cout << "\n";
    }
}


int main() {
    int t,k,n,m;
    cin >> t;
    for(int i=0;i<t;i++) {
        cin >> k >> n >> m;
        vector<vector<int>> E(k, vector<int>(3));   /// E = Ecuaciones: a-b<=c <=> a<=c+b
        for (int j = 0; j < k; j++) {
            cin >> E[j][0] >> E[j][1] >> E[j][2];    /// E[x][0]=a, E[x][1]=b. E[x][2]=c
            E[j][0]--;
            E[j][1]--;
        }
        vector<int> D(m);
        for (int l = 0; l < m; l++) {
            cin >> D[l];
        }

        fishburn(E,n,D);
    }
    return 0;
}