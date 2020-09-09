#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <vector>
#include <cassert>
#include <random>

#include "adaptive_blockquickselect.hpp"
//#include "BlockQuicksort/quickselect.hpp"
//#include "MedianOfNinthers/src/median_of_ninthers.h"

int* generateRandomArray(long n) {

    int* a = new int[n];

    std::generate(a, a + n, std::rand);

    return a;
}

std::vector<int> generateRandomVector(long n) {
    std::vector<int> v;
    v.resize(n);

    std::generate(v.begin(), v.end(), std::rand);

    return v;
}





void performanceTest(long num_elements, int num_trials) {
    double bqs_diff = 0.0;

    for (int i = 0; i < num_trials; ++i) {
//        int* a = generateRandomArray(num_elements);
        std::vector<int> a = generateRandomVector(num_elements);
        std::vector<int> b(a);
//        printf("%s:%d %lu\n", __FILE__, __LINE__);

        auto sort_start = std::chrono::steady_clock::now();
        nth_element(a.begin(), a.end(), std::less<>(), num_elements / 2);
//        original_block::nth_element(a, a + num_elements, std::less<>(), num_elements / 2);
//        adaptiveQuickselect(a, num_elements / 2, num_elements);

//        printf("%s:%d\n", __FILE__, __LINE__);


        auto sort_end = std::chrono::steady_clock::now();
        std::chrono::duration<double> sort_diff = (sort_end - sort_start);

        std::nth_element(b.begin(), b.begin() + (num_elements / 2), b.end());
        assert(a[num_elements / 2] == b[num_elements / 2]);
        bqs_diff += sort_diff.count();
//        delete[] a;
//        printf("passed trial %ld\n", i);
    }

    printf("%.10f\n", bqs_diff / num_trials);
//    printf("std::nth_element on median of %lu elements took %.10f seconds\n", num_elements, std_diff / num_trials);
}


int main() {
    std::srand(42);

    printf("Small array test\n");

    for (int i = 1; i < 10; ++i) {
        performanceTest(1lu << i, 100000);
    }

    printf("Medium array test\n");

    for (int i = 10; i < 20; ++i) {
        performanceTest(1lu << i, 1000);
    }


    printf("Large array test\n");
    for (int i = 20; i <= 32; ++i) {
        performanceTest(1lu << i, 50);
    }


//    performanceTest(1lu << 32, 20);
}
