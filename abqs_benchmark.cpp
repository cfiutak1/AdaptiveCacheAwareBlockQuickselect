#include "BenchmarkUtils.hpp"


int main() {
    std::srand(42);

    std::ofstream log_file;
    log_file.open("abqs_results.txt");

    testAllSizes<adaptiveBlockPerformanceTest>(log_file);
    log_file.close();
}