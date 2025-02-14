
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "MATRIX.h"

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::to_string;

#ifndef GRAPHS_H
#define GRAPHS_H




struct EDGE {
    string label;
    string parameters;
    char end_points[2];
};

struct VERTEX {
    char name;
    string label;
    string parameters;
    float x;
    float y;
};

class GRAPH {
private:
    vector<EDGE> edges;
    vector<VERTEX> vertices;

public:

    void add_edge(EDGE x) {
        edges.push_back(x);
    }
    void add_vertex(VERTEX x) {
        vertices.push_back(x);
    }
    void clear() {
        edges.clear();
        vertices.clear();
    }
    //zobrazenie do suboru
    void latex_display(ofstream &output , string parameters) {
        output<<"\n\\begin{center}";
        output<<"\n\\begin{tikzpicture}"<<"["<< parameters <<"]\n";
        for (auto it: vertices)
            output<<"\\Vertex[label="<<it.label<<", x="<<it.x<<",y="<<it.y<<","<<it.parameters<<"] {"<<it.name<<"} \n";
        for (auto it : edges)
            output<<"\\Edge[label="<<it.label<<","<<it.parameters<<"]("<<it.end_points[0]<<")("<<it.end_points[1]<<") \n";
        output<<"\n\\end{tikzpicture}";
        output<<"\n\\begin{center}\n";
    }

    //GENEROVANIE VRCHOLOV
    MATRIX<int> layer_distribution(vector<int> layers, string parameters) {
        vector<vector<VERTEX>> V_layers ;
        int count = 0;
        int numb_of_vertices=0;
        for (auto it: layers) {
            numb_of_vertices +=it;
        }

        MATRIX<int> A(numb_of_vertices, numb_of_vertices);

        for (int i = 0; i < layers.size(); i++) {
            int n = layers[i];
            vector<float> y_positions;
            if (n == 1) {
                y_positions.push_back(0);
            } else {
                for (int j = 0; j < n; j++) {
                    float offset = 2*((j + 1)/2);
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
                temp[j].parameters = parameters;
                temp[j].x = i * 3;
                temp[j].y = y_positions[j];
                if (i>0)
                for (int k = 0; k< layers[i-1]; k++) {
                    A.matrix[temp[j].name-'A'][V_layers[i-1][k].name-'A'] =rand()%5+1;
                }
            }
            V_layers.push_back(temp);
        }
        for (const auto it: V_layers) {
            for (const auto it2: it) {
                vertices.push_back(it2);
            }
        }
        return A;
    }
    void rand_distribution(int numb_of_vertices, float min_distance, string parameters) {
        vector<VERTEX> V(numb_of_vertices);
        set<pair<char, char>> existing_edges;
        int count = 0;
        for (auto& it : V) {
            bool valid_position;
            do {
                valid_position = true;
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
            it.parameters = parameters;
        }
        vertices = V;
    }
    void bibartite_graph(){}


    //GENEROVANIE HRAN
    // pre toky, vstupna matica, je matica susedností, ktorá zároveň má aj random váhu
    void flow_edges(MATRIX<int> A) {
        int numb_of_vertices= vertices.size();
        bool approved;
        bool change;
        do{
            do {
                approved=true;
                change = false;
                for (int i = 0; i < numb_of_vertices; i++) {
                    int sum_row = 0;
                    int sum_col = 0;
                    vector<int> row_coord;

                    do {
                        sum_row = 0;
                        sum_col = 0;
                        row_coord.clear();

                        for (int j = 0; j < numb_of_vertices; j++) {
                            sum_row += A.matrix[i][j];
                            if (A.matrix[i][j] != 0)
                                row_coord.push_back(j);

                            if (numb_of_vertices > 0)
                                sum_col += A.matrix[j][i];
                        }

                        if (sum_row ==0 || sum_col==0) {break;}
                        if (sum_row != sum_col) {
                            A.matrix[i][row_coord[rand() % row_coord.size()]] += (sum_row < sum_col) ? 1 : -1;
                            change = true;
                        }

                    } while (sum_row != sum_col);
                }
                for (int i =0; i<numb_of_vertices-1; i++) {
                    int sum =0;
                    for (int j = 0; j < numb_of_vertices; j++) {
                        sum += A.matrix[j][i];
                    }
                    if (sum==0) approved=false;
                }
            } while (change);
        }while (0);
        for (auto i = 0; i< numb_of_vertices; i++ ) {
            for (auto j=0 ;j < numb_of_vertices; j++) {
                if (A.matrix[i][j]!=0) {
                    EDGE e;
                    e.parameters="Direct,distance=0.2";
                    e.label="("+ to_string(A.matrix[i][j]) +"."+ to_string(A.matrix[i][j]+rand()%3+1) +")";
                    e.end_points[0]= j+'A';
                    e.end_points[1]= i+'A';
                    edges.push_back(e);
                }
            }
        }
    }
    // pre grafy, proximity treshold aspon 3
    void proximity_edges(int proximity_threshold, string parameters) {
        set<pair<char, char>> existing_edges;


        for (auto& it : vertices) {
        vector<pair<int, float>> close_vertices;
        for (int i = 0; i < vertices.size(); i++) {
            if (&vertices[i] == &it)
                continue;
            float distance = sqrt(pow(it.x - vertices[i].x, 2) + pow(it.y - vertices[i].y, 2));
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
            for (int i = 0; i < vertices.size(); i++) {
                if (i != &it - &vertices[0] && find(selected_vertices.begin(), selected_vertices.end(), i) == selected_vertices.end()) {
                    selected_vertices.push_back(i);
                    if (selected_vertices.size() == 3) break;
                }
            }
        }

        for (int idx : selected_vertices) {
            char start = it.name;
            char end = vertices[idx].name;

            bool intersects = false;
            for (const auto& v : vertices) {
                if (v.name == start || v.name == end) continue;

                float crossproduct = (v.y - it.y) * (vertices[idx].x - it.x) - (v.x - it.x) * (vertices[idx].y - it.y);
                if (fabs(crossproduct) > 1e-6) continue;

                float dotproduct = (v.x - it.x) * (vertices[idx].x - it.x) + (v.y - it.y) * (vertices[idx].y - it.y);
                if (dotproduct < 0) continue;

                float squaredlength = pow(vertices[idx].x - it.x, 2) + pow(vertices[idx].y - it.y, 2);
                if (dotproduct > squaredlength) continue;

                intersects = true;
                break;
            }

            if (!intersects && start != end &&
                existing_edges.count({start, end}) == 0 &&
                existing_edges.count({end, start}) == 0) {
                EDGE edge;
                edge.label = std::to_string(1 + rand() % 12);
                edge.parameters = parameters;
                edge.end_points[0] = start;
                edge.end_points[1] = end;

                edges.push_back(edge);
                existing_edges.insert({start, end});
            }
        }
    }
    }
};

#endif //GRAPHS_H
