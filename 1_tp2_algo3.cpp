#include<iostream>
#include<vector>

using namespace std;

void asignar_componentes(vector<int> &padres, vector<pair<bool,int>> &componentes, vector<bool> &arista_puente, int i){
    if(padres[i]==i){ //sos raiz?
        componentes[i].second=i; //sos raiz de componente
    }else if(arista_puente[i]==0){ //arista con parent no puente?
        componentes[i].second=i; //sos de otra componente que tu padre
    }else if(componentes[padres[i]].first==true) { //le asign aron componente a tu padre?
        componentes[i].second=componentes[padres[i]].second; //misma componente que padre
    } else{//no sos raiz, tenes puente con parent y a tu padre no le asignaron
        asignar_componentes(padres, componentes,arista_puente, padres[i]);
        componentes[i].second=componentes[padres[i]].second;
    }
    componentes[i].first=true;
}


//RECURSIVO CON TIMER Y COLORES
void dfs_timer(const vector<vector<int>>& ady,const int source, int & current_time, vector<int>& time_in, vector<int>& color) {
    color[source] = 1;
    time_in[source] = current_time++;
    for (int u : ady[source]) {
        if (color[u]==0) {
            dfs_timer(ady, u, current_time, time_in, color);
        }
    }
    color[source]=2;
}

//RECURSIVO CON PARENT
void dfs_parent(vector<vector<int>>& ady, int source, vector<int>& parents) {
    for (int u : ady[source]) {
        if (parents[u]==-1) {
            parents[u]=source;
            dfs_parent(ady, u, parents);
        }
    }
}

//DETECCIÓN DE PUENTES
int dp(const vector<vector<int>>& ady, int source, const vector<int>& time_in, const vector<int>& parents, vector<bool>& puente_con_parent) {
    int cantidad = 0;
    for (int u : ady[source]) {
        if (parents[u]==source) {
            cantidad +=dp(ady, u, time_in, parents, puente_con_parent);
        } else {
            if (time_in[source]>time_in[u] and parents[source]!=u) { //(source,u) es backedge que sube
                cantidad++;
            }
            if (time_in[source]<time_in[u]) { //(source,u) es backedge que viene de abajo
                cantidad--;
            }
        }
    }
    if (cantidad==0 and parents[source]!=source) {
        puente_con_parent[source] = true;
    }
    return cantidad;
}

int main() {
    int n,m,q;
    n=-1;
    m=-1;
    q=-1;
    while(n!=0 && m!=0 && q!=0){
        cin >> n >> m >> q;
        if(n!=0 && m!=0 && q!=0){
            //Creo un vector de dimensión n+1 sólo para poder usar el índice 1 en el primer vértice, se ignora
            //                                                                  la posición 0 en los resultados
            vector<vector<int>> grafo(n+1,vector<int>());
            for (int i=0;i<m;i++) {
                int v,w;cin>>v>>w;
                grafo[v].push_back(w);
                grafo[w].push_back(v);
            }

            //Versión con vector de padres
            vector<int> padres(n+1,-1);

            //Genero vector de tiempos
            int tiempo = 0;
            vector<int> tiempos(n+1,0);
            vector<int> colores(n+1,0);

            //Para detectar puentes
            vector<bool> arista_puente(n+1,false);

            //Si busco encontrar los puentes en todas las componentes conexas
            for (int i = 0;i<n+1;i++) {
                if(padres[i]==-1) {
                    padres[i]=i;
                    dfs_parent(grafo, i, padres);
                    dfs_timer(grafo, i, tiempo, tiempos, colores);
                    dp(grafo, i, tiempos, padres, arista_puente);
                }
            }

            // Hasta aca solo usamos el codigo generico de DFS. Ahora hacemos lo especifico para este ejercicio

            vector<pair<bool,int>> componentes(n+1);    // Guardo en este vector a que componente sin ciclos pertenece cada nodo.
                                                           // En el primer elemento guardo si ya le fue asignada una componente al nodo. En el segundo cual le asignaron

            for(int i=0;i<n+1;i++){
                asignar_componentes(padres,componentes,arista_puente, i);
            }

            int s,t;
            for(int i=0;i<q;i++){
                cin >> s >> t;
                if(componentes[s].second==componentes[t].second){
                    cout << 'Y' << '\n';
                }else{
                    cout << 'N' << '\n';
                }
            }
            cout << '-' << '\n';
        }
    }

    return 0;
}