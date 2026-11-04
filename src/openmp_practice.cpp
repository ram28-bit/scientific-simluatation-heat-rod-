#include <iostream>
#include <omp.h>

int main() {

    #pragma omp parallel for
    for (int i = 0; i < 8; ++i) {

        int thread_id = omp_get_thread_num();

        #pragma omp critical
        {
            std::cout << "Grid point: " << i
                      << " | Thread: " << thread_id
                      << '\n';
        }
    }

    return 0;
}