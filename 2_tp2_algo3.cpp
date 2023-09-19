#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int INF = 10e6;
using Costo = unsigned long int;
using Arista = pair<size_t,size_t>;

struct UF {     // Union-Find
    vector<int> p, s, minE;
    //  p: Vector con los parents
    //  s: Vector con tamaños
    //  minE (min edge): vector con la minima arista de cada componente
    //  sumaTamanos: la suma que buscamos devolver en el ejercicio
    //  incidencias: la matriz de incidencias entre componentes
    int sumaTamanos;
    vector<vector<pair<int,int>>> incidencias;

    UF(int n, vector<vector<pair<int,int>>> matriz): p(n, -1), s(n, 1), minE(n, INF), sumaTamanos(n-1), incidencias(matriz){}
    // la componente formada por todos los nodos siempre será candidata por eso sumaTamanos se inicializa con el valor la cantidad de nodos

    int unite(int v, int w, int c) {
        v = find(v);
        w = find(w);
        if (minE[v] != INF && minE[v] > c) sumaTamanos += s[v];    // En este paso chequeo si cada una de las dos componentes
        if (minE[w] != INF && minE[w] > c) sumaTamanos += s[w];    //  que estoy uniendo eran candidatas
        if (v == w) return s[v];
        if (s[v] < s[w]) swap(v, w);
        p[w] = v;           // v pasa a ser el padre de la nueva componente

        minE[v] = min(min(minE[v], minE[w]),c);    //Actualizo el minimo de la nueva componente comparando los minimos de las dos anteriores y la arista que las une

        if (incidencias[w][v].first == 1) {
            if (incidencias[w][v].second < minE[v]) {
                minE[v] = incidencias[w][v].second;     // si la componente w incidia en v con una arista de menor peso, actualizo la minima arista de la nueva componente
            }
        }

        // Paso toda la informacion de las incidencias de w a v, pues v es el padre de la nueva componente
        // Descarto la informacion sobre las incidencias en w

        for(int j=0;j<incidencias.size();j++){      // v pasa a incidir sobre las componentes sobre las que w incidia
            if(incidencias[w][j].first==1){         // si ya habia una incidencia, me quedo con la de menor peso. Pues esa es la que eventualmente puede modificar el minimo de las componentes
                incidencias[w][j].first=0;
                if(incidencias[v][j].first==0){
                    incidencias[v][j].first=1;
                    incidencias[v][j].second=incidencias[w][j].second;
                }else if(incidencias[w][j].second<incidencias[v][j].second){
                    incidencias[v][j].second=incidencias[w][j].second;
                }
            }
        }

        for(int i=0;i<incidencias.size();i++){      // las componentes que incidian en w pasan a incidir en w
            if(incidencias[i][w].first==1){         // si ya habia una incidencia, me quedo con la de menor peso. Pues esa es la que eventualmente puede modificar el minimo de las componentes
                incidencias[i][w].first=0;
                if(incidencias[i][v].first==0){
                    incidencias[i][v].first=1;
                    incidencias[i][v].second=incidencias[i][w].second;
                }else if(incidencias[i][w].second<incidencias[i][v].second){
                    incidencias[i][v].second=incidencias[i][w].second;
                }
            }
        }

            return s[v] += s[w];
        }

    int find(int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]);
    }
};

int main() {
    int t;
    cin >> t;
    for(int k=0;k<t;k++){
        size_t n,m;
        cin >> n >> m;

        vector<pair<Costo, Arista>> valores(m);     //Para indexar desde 1

        vector<vector<pair<int,int>>> incidencias (n+1, vector<pair<int,int>> (n+1,{0,0}));    //Matriz de incidencias
        // En esta matriz llevamos cuenta de si la componente i incide sobre la componente j (y con que peso como minimo)
        // En un principio las incidencias seran las mismas que entre los nodos
        // Pero a medida que actualizemos, iremos pasando la informacion de las incidencias solo al padre de cada componente y descartando la informacion de los nodos que no son padres


        for (auto& [c, e] : valores){
            cin >> e.first >> e.second >> c;
            incidencias[e.first][e.second].first=1;
            incidencias[e.second][e.first].first=1;
            incidencias[e.first][e.second].second=c;
            incidencias[e.second][e.first].second=c;
        }

        UF componentes(n+1, incidencias);

        sort(valores.rbegin(), valores.rend());     //Ordeno las aristas decrecientemente por su peso

        for (auto [c, e] : valores) {
            auto [i,j] = e;
            if (componentes.find(i) != componentes.find(j)) {
                componentes.unite(i,j,c);
            }
        }

        cout << componentes.sumaTamanos << "\n";
    }

    return 0;
}