#include "BenchmarkUtils.hpp"


int main() {
    std::srand(42);

    std::ofstream log_file;
    log_file.open("std_results.txt");

    testAllSizes<stdPerformanceTest>(log_file);
    log_file.close();
}