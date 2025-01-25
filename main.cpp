#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <windows.h>
#include "MATRIX.h"
#include "gale-shapley.h"


using namespace std;

void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

ofstream output("adm_leaked_test.tex");
static int priklad=1 ;

void GAUSOVKA(int size , int seed) {
    srand(seed);
    setTextColor(2);
    cout<<"\n\n" <<priklad<<".Pomocou gausovej eliminacie upravte nasledovnu maticu na jednotkovu a najdite riesenie danej sustavy\n";
    setTextColor(7);
    MATRIX<int> A(size, size,"rand-det_not_null");
    vector<int> b;
    A.assign_vector(b);
    A.display(b);

    output<<"\n\n" <<priklad++<<"\\textbf{.Pomocou gausovej eliminacie upravte nasledovnu maticu na jednotkovu a najdite riesenie danej sustavy:}\n";
    A.latex_display(output,b);
    output<<"\n\\newpage\n";
}

void INVERZNA(int size, int seed) {
    srand(seed);
    setTextColor(2);
    cout<<"\n\n" <<priklad<<".Metodou inverznej matice najdite riesenie nasledujucej sustavy:\n";
    setTextColor(7);
    MATRIX<int> A(size, size,"rand-det_not_null");
    vector<int> b;
    A.assign_vector(b);
    A.display(b);

    output<<"\n\n" <<priklad++<<"\\textbf{.Metodou inverznej matice najdite riesenie nasledujucej sustavy:}\n";
    A.latex_display(output,b);
    output<<"\n\\newpage\n";
}

void KRAMEROVO(int size, int seed) {
    srand(seed);
    setTextColor(2);
    cout<<"\n\n" <<priklad<<".Pomocou determinantov najdite riesenie nasledujucej sustavy: (kramerovo pravidlo)\n";
    setTextColor(7);
    MATRIX<int> A(size, size,"rand-det_not_null");
    vector<int> b;
    A.assign_vector(b);
    A.display(b);

    output<<"\n\n" <<priklad++<<"\\textbf{.Pomocou determinantov najdite riesenie nasledujucej sustavy: (kramerovo pravidlo)}\n";
    A.latex_display(output,b);
    output<<"\n\\newpage\n";
}

void EIGEN_VALUES(int size, int seed) {
    srand(seed);
    setTextColor(2);
    cout<<"\n\n" <<priklad<<".Najdite vlastne hodnoty a vlastne vektory nasledujucej matice: (nezabudni na t patri R)\n";
    setTextColor(7);
    MATRIX<int> A(size,size, "rand-nice_inverse");
    MATRIX<int> eigen(size,size);
    for (int i = 0; i < size; i++) {
        eigen.matrix[i][i] = rand()%11-5;
    }
    (A*eigen*A.int_inverse() ).display();

    output<<"\n\n" <<priklad++<<"\\textbf{.Najdite vlastne hodnoty a vlastne vektory nasledujucej matice: (nezabudni na t patri R)}\n";
    A.latex_display(output);
    output<<"\n\\newpage\n";
}

void LU_DECOMPOSITION(int size, int seed) {
    srand(seed);
    setTextColor(2);
    cout<<"\n\n" <<priklad<<".Metodou LU rozkladu najdite riesenie nasledovnej sustavy a determinant matice:\n";
    setTextColor(7);
    MATRIX<int> S(size, size);
    do {
        MATRIX<int> L(size, size, "rand-L");
        MATRIX<int> U(size, size, "rand-U");
        S=L*U;
    }while (S.det() == 0);

    vector<int> b;
    S.assign_vector(b);
    S.display(b);

    output<<"\n\n" <<priklad++<<"\\textbf{.Metodou LU rozkladu najdite riesenie nasledovnej sustavy a determinant matice:}\n";
    S.latex_display(output,b);
    output<<"\n\\newpage\n";
}

void TRANSFORMACIE(int pocet_transformacii, int seed) {
    srand(seed);
    setTextColor(2);
    cout<<"\n\n" <<priklad++<<".Mame definovovany domcek: \n";
    setTextColor(7);
    MATRIX<int> DOM(5,2);
    DOM.matrix={
        {0 , 0},
        {0 , 2},
        {2 , 0},
        {2 , 2},
        {1 , 3},
    };
    DOM.display();
    cout<<"Postupne na nom vykoname postupne nasledovne transformacie: \n";

    vector<string> transformacie=
        { "Otocime o 60 stupnov VPROTI smere hodinovych ruciciek. ",
          "Otocime o 30 stupnov V smere hodinovych ruciciek. ",
          "Posunieme v smere x-ovej osy o 3 j .",
          "Pusnieme v smere y-ovej osy o -2 j.",
          "Roztiahneme do sirky 2-nasobne",
          "Roztiahneme do vysky 3-nasobne",
          "Domcek zvacsime 5 nasobne"
        };
    mt19937 g(seed);
    shuffle(transformacie.begin(), transformacie.end(),g);
    for (int i = 0; i< pocet_transformacii; i++) {
        cout<<"\nT"<<i+1<<" "<<transformacie[i]<<"\n ";
    }

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
    setTextColor(2);
    cout<<"\n\n" <<priklad++<<".Pomocou gale-shapley algoritmu najdite co najlepsie pary, pre kazde pohlavie osobitne:\n";
    setTextColor(7);
    matching(size);

    output<<"\n\n" <<priklad++<<"\\textbf{.Pomocou gale-shapley algoritmu najdite co najlepsie pary, pre kazde pohlavie osobitne:}\n";
    matching(output,size);
    output<<"\n\\newpage\n";
}

int main() {
    // NEMENIT, nic okrem seedu !!!!!
    output<<"\n\\documentclass{letter}\n\\pagestyle{empty}\n\\usepackage{amsmath}\n\\usepackage[a4paper, left=1in, right=1in, top=1in, bottom=1in]{geometry}\n\\begin{document}\n\\large\n";
    random_device rd;
    int seed = rd();
    seed=abs(seed)%10000000;

    cout<<"SEED: "<<seed<<"\n";
    output<<"SEED: "<<seed<<"\n";

    //uprav si podla seba

    GAUSOVKA(4,seed++);
    INVERZNA(4,seed++);
    KRAMEROVO(4,seed++);
    EIGEN_VALUES(3,seed++);
    LU_DECOMPOSITION(3,seed++);
    TRANSFORMACIE(3,seed++);
    GALE_SHAPLEY(7,seed++);

    //taktiez nemenit
    output<<"\\end{document}\n";
    output.close();
    return 0;
}
