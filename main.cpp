#include <iostream>
#include <random>
#include "MATRIX.h"

using namespace std;

void INVERZNA(int size, int seed) {
    srand(seed);
    cout<<"\n\nMetodou inverznej matice najdite riesenie nasledujucej sustavy:\n";
    MATRIX<int> A(size, size,"rand-det_not_null");
    vector<int> b;
    A.assign_vector(b);
    A.display(b);
}

void KRAMEROVO(int size, int seed) {
    srand(seed);
    cout<<"\n\nPomocou determinantov najdite riesenie nasledujucej sustavy: (kramerovo pravidlo)\n";
    MATRIX<int> A(size, size,"rand-det_not_null");
    vector<int> b;
    A.assign_vector(b);
    A.display(b);
}

void EIGEN_VALUES(int size, int seed) {
    srand(seed);
    cout<<"\n\n Najdite vlastne hodnoty a vlastne vektory nasledujucej matice: \n";
    MATRIX<int> A(size,size, "rand-nice_inverse");
    MATRIX<int> eigen(size,size);
    for (int i = 0; i < size; i++) {
        eigen.matrix[i][i] = rand()%11-5;
    }
    (A*eigen*A.int_inverse() ).display();
}

int main() {
    random_device rd;
    int seed = rd();
    seed=abs(seed)%10000000;

    cout<<"SEED: "<<seed<<"\n";
    INVERZNA(4,seed++);
    KRAMEROVO(4,seed++);
    EIGEN_VALUES(3,seed++);

    return 0;
}
