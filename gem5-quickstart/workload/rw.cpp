#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <omp.h>
#include <cstdint>

#ifdef GEM5
#include <gem5/m5ops.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{

    if (argc != 2) {
        cout << "Usage: random write size" << endl;
        return 1;
    }

    int size = atoi(argv[1]);

    if (size <= 0) {
        cout << "Invalid size" << endl;
        cout << "Usage: random write size" << endl;
    }

    cout << "Initializing ..." << endl;
    
    std::default_random_engine e;

    // generate random address
    // uniform distribution
    uniform_int_distribution<int> u(0, size);
    normal_distribution<double> n(0, 1);

    int *A = new int[size];
    double *B = new double[size];
    double *C = new double[size];


    int addr;
    double data;
    
    for (int i = 0; i < size; i++)    {
        addr = u(e);
        data = n(e);
        A[i] = addr;
        B[i] = data;
    }
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < size; i++) {
            C[i] = C[size-i] + B[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    
    cout << "Done." << endl;

    cout << "Time " << (double)(end-start).count()/1e6 << " ms" << endl;
    // For debug    
    // for (int i = 0; i < size; i++)
    // {
    //     cout << A[i] << endl;
    // }
    
    
    delete [] A;
    delete [] B;
    delete [] C;

}
