#include "BenchmarkUtils.hpp"


int main() {
    std::srand(42);

    std::ofstream log_file;
    log_file.open("ninther_results.txt");

    testAllSizes<nintherPerformanceTest>(log_file);
    log_file.close();
}