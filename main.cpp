#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <windows.h>

#include "MATRIX.h"
#include "gale-shapley.h"
#include "GRAPHS.h"


using namespace std;

void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

ofstream output("adm_leaked_test.tex");
ofstream odpovede("odpovede.txt");

int priklad=1 ;

vector<int> rand_vektor(int size) {
    vector<int> x;
    for (int i =0 ; i < size; i++)
        x.push_back(rand() % (UPPER_RAND-LOWER_RAND) + LOWER_RAND);
    return x;
}

void GAUSOVKA(int size , int seed) {
    srand(seed);

    setTextColor(2);
    odpovede<<priklad<<". Riesenie pomocou Gausovej-Eliminacie { ";
    MATRIX<int> A(size, size,"rand-det_not_null");
    vector<int> b=rand_vektor(size);
    for (auto i : b) {
        odpovede<<i<<", ";
    }
    odpovede<<"}\n";
    setTextColor(7);

    A.assign_vector(b);
    output<<"\n\n" <<priklad++<<"\\textbf{.Pomocou gausovej eliminacie upravte nasledovnu maticu na jednotkovu a najdite riesenie danej sustavy:}\n";
    A.latex_display(output,b);
    output<<"\n\\newpage\n";
}

void INVERZNA(int size, int seed) {
    srand(seed);

    setTextColor(2);
    odpovede<<priklad<<". Riesenie pomocou Inverznej-Matice { ";
    MATRIX<int> A(size, size,"rand-det_not_null");
    vector<int> b=rand_vektor(size);
    for (auto i : b) {
        odpovede<<i<<", ";
    }
    odpovede<<"}\n";
    setTextColor(7);

    A.assign_vector(b);
    output<<"\n\n" <<priklad++<<"\\textbf{.Pomocou inverznej matice nájdite riešenie sústavy rovníc. Všetky realizované úpravy pri výpočte inverznej matice riadne zapisujte, inak bude príklad hodnotený automaticky za 0 b. Nezabudnitepríklad dopočítať dokonca a nájsť aj riešenie sústavy:}\n";
    A.latex_display(output,b);
    output<<"\n\\newpage\n";
}

void KRAMEROVO(int size, int seed) {
    srand(seed);

    setTextColor(2);
    odpovede<<priklad<<". Riesenie pomocou Kramerovho Pravidla { ";
    MATRIX<int> A(size, size,"rand-det_not_null");
    vector<int> b=rand_vektor(size);
    for (auto i : b) {
        odpovede<<i<<", ";
    }
    odpovede<<"}\n";
    setTextColor(7);

    A.assign_vector(b);
    output<<"\n\n" <<priklad++<<"\\textbf{.Metódou determinantov nájdite riešenie sústavy rovníc. Všetky realizované úpravy pri výpočte determinantov riadne zapisujte, Inak bude príklad hodnotený automaticky za 0 b. Nezabudnite príklad vypočítať dokonca a nájsť aj riešenie sústavy –nestačia len determinanty:}\n";
    A.latex_display(output,b);
    output<<"\n\\newpage\n";
}

void EIGEN_VALUES(int size, int seed) {
    srand(seed);
    setTextColor(2);
    odpovede<<priklad<<". Vlastne cisla { ";
    MATRIX<int> A(size,size, "rand-nice_inverse");
    MATRIX<int> eigen(size,size);
    for (int i = 0; i < size; i++) {
        eigen.matrix[i][i] = rand()%11-5;
        odpovede<<eigen.matrix[i][i]<<", ";
    }
    odpovede<<"}\n";
    setTextColor(7);
    output<<"\n\n" <<priklad++<<"\\textbf{.Pre maticu A nájdite charakteristický polynóm, vlastné čísla a bázu tvorenú vlastnými vektormi:}\n";
    (A*eigen*A.int_inverse() ).latex_display(output);
    output<<"\n\\newpage\n";
}

void LU_DECOMPOSITION(int size, int seed) {
    srand(seed);

    setTextColor(2);
    odpovede <<priklad<<". LU rozklad: ";
    vector<int> b=rand_vektor(size);for (auto i : b) {
        odpovede<<i<<", ";
    }
    odpovede<<"}\n";

    MATRIX<int> S(size, size);
    do {
        MATRIX<int> L(size, size, "rand-L");
        MATRIX<int> U(size, size, "rand-U");
        S=L*U;
        if (S.det()!=0) {
            odpovede<<"\n L - matica: \n";
            L.display();
            odpovede<<"\n U - matica: \n";
            U.display();
        }
    }while (S.det() == 0);
    setTextColor(7);

    S.assign_vector(b);
    output<<"\n\n" <<priklad++<<"\\textbf{.Metodou LU rozkladu najdite riesenie nasledovnej sustavy a determinant matice:}\n";
    S.latex_display(output,b);
    output<<"\n\\newpage\n";
}

void TRANSFORMACIE(int pocet_transformacii, int seed) {
    srand(seed);

    odpovede<<"\n\n" <<priklad<<".Domcek postaveny: \n";
    MATRIX<int> DOM(5,2);
    DOM.matrix={
        {0 , 0},
        {0 , 2},
        {2 , 0},
        {2 , 2},
        {1 , 3},
    };


    vector<string> transformacie=
        { "Otocime o 60 stupnov VPROTI smere hodinovych ruciciek. ",
          "Otocime o 30 stupnov V smere hodinovych ruciciek. ",
          "Posunieme v smere x-ovej osy o 3 j .",
          "Pusnieme v smere y-ovej osy o -2 j.",
          "Roztiahneme do sirky 2-nasobne",
          "Roztiahneme do vysky 3-nasobne",
          "Domcek zvacsime 5 nasobne"
             "Obraz podla osy x",
             "Obraz podla osy y",
        };
    mt19937 g(seed);
    shuffle(transformacie.begin(), transformacie.end(),g);

    output<<"\n\n" <<priklad++<<"\\textbf{.Mame definovovany domcek: }\n";
    DOM.latex_display(output);
    output<<"\n\\textbf{Postupne na nom vykoname postupne nasledovne transformacie:}\n";
    for (int i = 0; i< pocet_transformacii; i++) {
        output<<"\nT"<<i+1<<" "<<transformacie[i]<<"\n ";
    }
    output<<"\n\\newpage\n";

}

void GALE_SHAPLEY(int size , int seed) {
    srand(seed);

    if (size>7)
        size=7;
    if (size<3)
        size=3;

    odpovede <<priklad<<". Parovanie: https://www.youtube.com/watch?v=uigz45tk2-s&t=475s\n";
    matching(size);
    odpovede<<"\nIf women chose first:";
    find_pairing(women, men,size);
    odpovede<<"\nIf men chose first:";
    find_pairing(men, women,size);

    output<<"\n\n" <<priklad++<<"\\textbf{.Použite Gale-Shapley algoritmus pre určenie najlepšieho možného párovania v prípade preferencií zadaných tabuľkou}\n\na) V prípade, že muž si vyberá ako prvý.\n\nb) V prípade, že žena si vyberá ako prvá.\n\nPorovnajte oba výsledky\n";
    matching(output,size);
    output<<"\n\\newpage\n";
    clear_preferences();
}
void KRITICKA_CESTA(int pocet_vrcholov, int seed) {
    srand(seed);
}

void FORD_FULKERSON(vector<int> layers, int seed) {
    srand(seed);
    GRAPH graph;
    MATRIX A=graph.layer_distribution(layers, "");
    graph.flow_edges(A);
    graph.latex_display(output,"scale=1");
    output<<"\n\\newpage\n";
}

void DJIKSTRA(int number_of_vertices, int seed) {
    srand(seed);
    GRAPH graph;
    graph.layer_distribution({5,4,3,4,5},"color=violet");
    graph.proximity_edges(4.0, "");
    graph.latex_display(output,"scale=0.8");
    graph.latex_display(output,"scale=0.8");
    output<<"\n\\newpage\n";
}

void SPANNING_TREE(int number_of_vertices, int seed) {
    srand(seed);
    GRAPH graph;
    graph.rand_distribution(20, 2, "color=orange");
    graph.proximity_edges(4.0, "");
    graph.latex_display(output,"scale=0.8");
    graph.latex_display(output,"scale=0.8");
    output<<"\n\\newpage\n";
}

int main() {
    // NEMENIT, nic okrem seedu !!!!!
    output<<"\n\\documentclass{letter}\n\\pagestyle{empty}\n\\usepackage{tikz-network}\n\\usepackage{amsmath}\n\\usepackage[a4paper, left=1in, right=1in, top=1in, bottom=1in]{geometry}\n\\begin{document}\n\\large\n";
    random_device rd;
    int seed = rd();
    seed=abs(seed)%10000000;

    odpovede<<"SEED: "<<seed<<"\n";
    output<<"SEED: "<<seed<<"\n";

    //uprav si podla seba

        GAUSOVKA(4,seed++);
        INVERZNA(4,seed);
        KRAMEROVO(4,seed++);
        EIGEN_VALUES(3,seed++);
        LU_DECOMPOSITION(3,seed++);
        TRANSFORMACIE(3,seed++);
        GALE_SHAPLEY(7,seed++);
        KRITICKA_CESTA(14, seed++);
        FORD_FULKERSON({1,3,3,3,1},seed++);
        SPANNING_TREE(20,seed++);
        DJIKSTRA(20, seed++);

    //taktiez nemenit
    output<<"\\end{document}\n";
    output.close();
    odpovede.close();
    return 0;
}
