#include "BenchmarkUtils.hpp"


int main() {
    std::srand(42);

    std::ofstream log_file;
    log_file.open("original_bqs_results.txt");

    testAllSizes<blockPerformanceTest>(log_file);
    log_file.close();
}