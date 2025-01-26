//
// Created by nikolas on 1/25/2025.
//
#include "MATRIX.h"
#include <set>

#ifndef GRAPHS_H
#define GRAPHS_H

extern int priklad;
extern ofstream output;

struct element_of_CP {
    char name;
    int value;
    vector<char> prepositions;
};

//WOHOOO TOKY A GRAPH GENERATOR

struct EDGE {
    string label;
    string parameters;
    char end_points[2];
};

struct VERTEX {
    char name;
    char label;
    string parameters;
    float x;
    float y;
};

//\Vertex[label=d, x=6, y=2]{D}

//\Edge[label=(0.6), position=above, Direct](C)(D)

void GRAPH_TO_LATEX(ofstream &output,vector<VERTEX>V, vector<EDGE> E) {
    output<<"\n\\begin{tikzpicture}\n";
    for (auto it: V)
        output<<"\\Vertex[label="<<it.label<<", x="<<it.x<<",y="<<it.y<<","<<it.parameters<<"] {"<<it.name<<"} \n";
    for (auto it : E)
        output<<"\\Edge[label="<<it.label<<","<<it.parameters<<"]("<<it.end_points[0]<<")("<<it.end_points[1]<<") \n";
    output<<"\n\\end{tikzpicture}\n";
}

void KRITICKA_CESTA(int pocet_vrcholov, int seed) {
    srand(seed);
    cout<<"\n\n"<<priklad<<". Najdite kriticku cestu:  \n";
    vector<vector<element_of_CP>> elements;
    int per_layer = pocet_vrcholov/3;
    int tempe = pocet_vrcholov-2;
    vector<int> layers;

    layers.push_back(1);
    while (tempe > 0) {
        int x = (tempe > per_layer) ? per_layer : tempe;
        if (tempe - x == 1) x--;


        layers.push_back(x);
        tempe -= x;
    }
    if (layers.back() != 1) {
        layers.push_back(1);
    }

    elements.push_back({{'a', 0, {}}});
    int count=1;
    for (int i =1 ; i<layers.size(); i++) {
        vector<element_of_CP> temp(layers[i]);
        for (int j = 0 ; j < layers[i]; j++) {
            temp[j].name='a'+(count++);
            temp[j].value = rand()%8+1;
            for (auto it: elements[i-1])
                if (rand()%2)temp[j].prepositions.push_back(it.name);
            if (temp[j].prepositions.size()==0)
                temp[j].prepositions.push_back(elements[i-1][0].name );
        }
        elements.push_back(temp);
    }
    elements[layers.size()-1][0].value=0;
    for (auto it: elements) {
        for (auto it2: it) {
            cout<<" | "<<it2.name<<"  | "<<it2.value<<" | ";
            for (auto preposition: it2.prepositions)
                cout<<preposition<<" ";
            cout<<" | \n";
        }

    }

    output<<"\n\n" <<priklad++<<"\\textbf{.Najdite kriticku cestu:}\n";
    output<<"\n\\[\n\\begin{tabular}{ccc}\n";
    output<<"\\hline\n";
    output<<" Task & Time & Precedence \\\\ \n";
    output<<"\\hline\n";
    for (auto it: elements) {
        for (auto it2: it) {
            output<<it2.name<<"  & "<<it2.value<<" & ";
            for (auto preposition: it2.prepositions)
                output<<preposition<<" ";
            output<<"\\\\ \n";
        }
    }
    output<<"\\hline\n";
    output<<"\n\\]\n\\end{tabular}\n";
    count = 0;
    int numb_of_vertices=0;
    for (auto it: layers) {
        numb_of_vertices +=it;
    }
    vector<VERTEX> V;
    vector<vector<VERTEX>> V_layers ;
    vector<EDGE> E;

    for (int i = 0; i < layers.size(); i++) {
        int n = layers[i];
        vector<float> y_positions;
        if (n == 1) {
            y_positions.push_back(0);
        } else {
            for (int j = 0; j < n; j++) {
                float offset = 2*((j + 1)/2); //<----spacing
                if (j % 2 == 0)
                    y_positions.push_back(offset);
                else
                    y_positions.push_back(-offset);
            }
        }
        sort(y_positions.begin(), y_positions.end());
        reverse(y_positions.begin(), y_positions.end());
        vector<VERTEX> temp(layers[i]);
        for (int j = 0; j < n; j++) {
            temp[j].name = (char)('A' + (count));
            temp[j].label = (char)('a' + (count++));
            temp[j].parameters = "";
            temp[j].x = i * 3;
            temp[j].y = y_positions[j];
        }
        V_layers.push_back(temp);
    }

    for (const auto it: V_layers) {
        for (const auto it2: it) {
            V.push_back(it2);
        }
    }
    GRAPH_TO_LATEX(output,V,E);
    output<<"\n\\newpage\n";
}

void FORD_FULKERSON(vector<int> layers, int seed) {
    srand(seed);
    output<<"\\textbf{"<<priklad++<<".Nájdite maximálnu realizáciu tokov prípustnosti vo vodovodnej siete metódou FordFulkersonovho algoritmu ak:}\n";
    int count = 0;
    int numb_of_vertices=0;
    for (auto it: layers) {
        numb_of_vertices +=it;
    }
    vector<VERTEX> V;
    vector<vector<VERTEX>> V_layers ;
    vector<EDGE> E;
    cout<<"FORD_FULKERSON\n";
    for (int i = 0; i < layers.size(); i++) {
        int n = layers[i];
        vector<float> y_positions;
        if (n == 1) {
            y_positions.push_back(0);
        } else {
            for (int j = 0; j < n; j++) {
                float offset = 2*((j + 1)/2); //<----spacing
                if (j % 2 == 0)
                    y_positions.push_back(offset);
                else
                    y_positions.push_back(-offset);
            }
        }
        sort(y_positions.begin(), y_positions.end());
        reverse(y_positions.begin(), y_positions.end());
        vector<VERTEX> temp(layers[i]);
        for (int j = 0; j < n; j++) {
            temp[j].name = (char)('A' + (count));
            temp[j].label = (char)('a' + (count++)-1);
            temp[j].parameters = "";
            temp[j].x = i * 3;
            temp[j].y = y_positions[j];
            for (int k = 0; k< layers[i-1]; k++) {
                E.push_back(
                    {"(0.0)", "Direct, position=above",{V_layers[i-1][k].name,temp[j].name }}
                    );
            }
        }
        V_layers.push_back(temp);
    }
    for (const auto it: V_layers) {
        for (const auto it2: it) {
            V.push_back(it2);
        }
    }
    V[0].label = 'S';
    V[layers.size()-1].label = 'E';
    GRAPH_TO_LATEX(output,V,E);
    output<<"\n\\newpage\n";
}

void SPANNING_TREE(int number_of_vertices, int seed) {
    srand(seed);
    output<<"\\textbf{"<<priklad++<<".Nájdite kostru (spanning tree) v grafe pomocou Kruskalovho a pomocou Primovho algoritmu:}\n";
    vector<VERTEX> V(number_of_vertices);
    vector<EDGE> E;
    set<pair<char, char>> existing_edges;
    float proximity_threshold = 3.0;
    int count = 0;
    float min_distance = 1.8;

    for (auto& it : V) {
        bool valid_position;
        do {
            valid_position = true;
            // Generate random position
            it.x = ((rand() / (float)RAND_MAX)) * 10.0;
            it.y = ((rand() / (float)RAND_MAX)) * 10.0;

            for (const auto& v : V) {
                if (&v == &it) continue;
                float distance = sqrt(pow(it.x - v.x, 2) + pow(it.y - v.y, 2));
                if (distance < min_distance) {
                    valid_position = false;
                    break;
                }
            }
        } while (!valid_position);

        it.label = (char)('A' + count);
        it.name = (char)('A' + count++);
        it.parameters = "color=orange";
    }

    for (auto& it : V) {
        vector<std::pair<int, float>> close_vertices;


        for (int i = 0; i < V.size(); i++) {
            if (&V[i] == &it) continue;
            float distance = sqrt(pow(it.x - V[i].x, 2) + pow(it.y - V[i].y, 2));
            if (distance <= proximity_threshold) {
                close_vertices.push_back({i, distance});
            }
        }

        sort(close_vertices.begin(), close_vertices.end(),
             [](const pair<int, float>& a, const pair<int, float>& b) {
                 return a.second < b.second;
             });

        vector<int> selected_vertices;

        for (int i = 0; i < close_vertices.size(); i++) {
            if (selected_vertices.size() < 3) {
                selected_vertices.push_back(close_vertices[i].first);
            }
        }
        if (selected_vertices.size() < 2) {
            for (int i = 0; i < V.size(); i++) {
                if (i != &it - &V[0] && find(selected_vertices.begin(), selected_vertices.end(), i) == selected_vertices.end()) {
                    selected_vertices.push_back(i);
                    if (selected_vertices.size() == 3) break;
                }
            }
        }

        for (int idx : selected_vertices) {
            char start = it.name;
            char end = V[idx].name;
            if (start != end && existing_edges.count({start, end}) == 0 &&
                existing_edges.count({end, start}) == 0) {
                EDGE edge;
                edge.label = std::to_string(1 + rand() % 12);
                edge.parameters = "";
                edge.end_points[0] = start;
                edge.end_points[1] = end;

                E.push_back(edge);
                existing_edges.insert({start, end});
            }
        }
    }

    GRAPH_TO_LATEX(output, V, E);
    GRAPH_TO_LATEX(output, V, E);
}

void AUGMENTING_PATH(int size , int seed) {
    srand(seed);
    output<<"Augmeniting path\n";
    vector<VERTEX> V;
    vector<VERTEX> A(size+1),B(size);
    vector<EDGE> E( size/2+1);
    int count = 0;
    for (int i =0; i < size+1; i++) {
        A[i].name = (char)('A' + count++);
        A[i].parameters = "";
        A[i].x =3*i -1.5 ;
        A[i].y =0 ;
    }
    for (int i =0; i < size; i++) {
        B[i].name = (char)('A' + count++);
        B[i].parameters = "";
        B[i].x =3*i ;
        B[i].y =-3 ;
    }
    for (auto it : A)
        V.push_back(it);
    for (auto it : B)
        V.push_back(it);
    shuffle(A.begin(), A.end(), default_random_engine(seed));
    shuffle(B.begin(), B.end(), default_random_engine(seed));
    for (int i =0 ; i < size/2+1 ; i++) {
        E[i].end_points[0]= A[i].name ;
        E[i].end_points[1] = B[i].name ;
    }
    GRAPH_TO_LATEX(output, V, E);

}

void PAIRING(int size ,int seed) {

}

#endif
