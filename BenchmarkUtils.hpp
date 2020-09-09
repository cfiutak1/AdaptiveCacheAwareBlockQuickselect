#include <random>
#include <algorithm>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <iomanip>

#include "adaptive_blockquickselect.hpp"
#include "BlockQuicksort/quickselect.hpp"
#include "MedianOfNinthers/src/median_of_ninthers.h"

#pragma once

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


void adaptiveBlockPerformanceTest(std::size_t num_elements, int num_trials, std::ofstream& log_file) {
    double total_time = 0.0;

    for (int i = 0; i < num_trials; ++i) {
        int *a = generateRandomArray(num_elements);

        auto start = std::chrono::steady_clock::now();

        nth_element(a, a + num_elements, std::less<>(), num_elements / 2);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        total_time += diff.count();
        delete[] a;
    }

    log_file << (total_time / num_trials) << "\n";
}


void stdPerformanceTest(std::size_t num_elements, int num_trials, std::ofstream& log_file) {
    double total_time = 0.0;

    for (int i = 0; i < num_trials; ++i) {
        int *a = generateRandomArray(num_elements);

        auto start = std::chrono::steady_clock::now();

        std::nth_element(a, a + num_elements / 2, a + num_elements);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        total_time += diff.count();
        delete[] a;
    }

    log_file << (total_time / num_trials) << "\n";
}


void blockPerformanceTest(std::size_t num_elements, int num_trials, std::ofstream& log_file) {
    double total_time = 0.0;

    for (int i = 0; i < num_trials; ++i) {
        int *a = generateRandomArray(num_elements);

        auto start = std::chrono::steady_clock::now();

        original_block::nth_element(a, a + num_elements, std::less<>(), num_elements / 2);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        total_time += diff.count();
        delete[] a;
    }

    log_file << (total_time / num_trials) << "\n";
}


void nintherPerformanceTest(std::size_t num_elements, int num_trials, std::ofstream& log_file) {
    double total_time = 0.0;

    for (int i = 0; i < num_trials; ++i) {
        int *a = generateRandomArray(num_elements);

        auto start = std::chrono::steady_clock::now();

        adaptiveQuickselect(a, num_elements / 2, num_elements);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        total_time += diff.count();
        delete[] a;
    }

    log_file << std::setprecision(10) << total_time / num_trials << "\n";
}


template <void (*F)(std::size_t, int, std::ofstream&)>
void testAllSizes(std::ofstream& log_file) {
    printf("Small array test, num_trials = %ld\n", 1000000);

    for (int i = 1; i < 10; ++i) {
        F(1lu << i, 1, log_file);
    }

    printf("Medium array test, num_trials = %ld\n", 10000);

    for (int i = 10; i < 20; ++i) {
        F(1lu << i, 1, log_file);
    }


    printf("Large array test, num_trials = %ld\n", 1000);
    for (int i = 20; i <= 32; ++i) {
        F(1lu << i, 1, log_file);
    }
}