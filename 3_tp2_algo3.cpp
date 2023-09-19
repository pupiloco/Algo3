#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>

using namespace std;
constexpr int INF = 10e6;
constexpr int BOTTOM = -1;

pair<int,int> extract_min(priority_queue<pair<int,int>> &Q){
    pair<int,int> res = Q.top();
    Q.pop();
    return res;
}

vector<int> DIJKSTRA(int x, vector<list<int>> &adj, map<pair<int,int>,int> &w,int s){
    vector<int> dist(x);
    vector<int> pred(x);
    for(int i=0;i<x;i++){
        dist[i]=INF;
        pred[i]=BOTTOM;
    }
    dist[s]=0;

    priority_queue<pair<int,int>> Q;

    for(int i=0;i<x;i++){
        Q.push({dist[i],i});
    }

    pair<int,int> u;
    while(!Q.empty()){
        u = extract_min(Q);
        for(int v : adj[u.second]){
            if(dist[v]>dist[u.second]+w[{u.second,v}]){
                dist[v] = dist[u.second] + w[{u.second,v}];
                pred[v] = u.second;
                Q.push({dist[v],v});
            }
        }
    }
    return dist;
};

int main() {
    int t;
    cin >> t;
    for(int i=0;i<t;i++) {
        int c,p;
        cin >> c >> p;
        int q;
        cin >> q;
        vector<int> Q(q);
        vector<list<int>> adj(p+2);
        map<pair<int,int>,int> w;
        for(int j=0;j<q;j++){
            int aux;
            cin >> aux;
            adj[p+1].push_back(aux);
        }
        for(int k=1;k<=p;k++){
            int r;
            cin >> r;
            int a,b;
            for(int l=0;l<r;l++){
                cin >> a >> b;
                if(w[{k,b}]==0){
                    adj[k].push_back(b);
                }
                if(w[{k,b}]==0 || w[{k,b}]>a){
                    w[{k,b}]=a;
                }
            }
        }

        int minima_recaudacion = DIJKSTRA(p+2, adj, w, p+1)[0];
        int robado = 0;
        int caja = 0;
        while(caja<c){
            caja+=minima_recaudacion;
            if(caja<c){
                robado++;
                caja--;
            }
        }
        cout << robado << "\n";
    }

    int cero;
    cin >> cero;

    return 0;
}