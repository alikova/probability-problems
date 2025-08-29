// Programming Assessment

// --------------------------------------------
// Problem 5 - Progressive Jackpot Simulation


#include <iostream>
#include <random>
#include <iomanip>

int main() {
    std::cout << "=== PROBLEM 5: PROGRESSIVE JACKPOT SIMULATION ===\n";

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 2598960);

    double jackpot = 5000.0, total100 = 0.0, total10 = 0.0;
    int count100 = 0, count10 = 0;

    for (int i = 0; i < 10000000; i++) {
        jackpot += 0.41;
        int outcome = dist(rng);

        if (outcome <= 4) { total100 += jackpot; jackpot = 5000.0; count100++; }
        else if (outcome <= 40) { total10 += jackpot * 0.10; count10++; }
    }

    std::cout << std::fixed << std::setprecision(2);
    if (count100) std::cout << "Avg 100% Jackpot: $" << total100 / count100 << " (" << count100 << " wins)\n";
    if (count10)   std::cout << "Avg 10% Jackpot: $" << total10 / count10 << " (" << count10 << " wins)\n";

    return 0;
}

// clang++ -std=c++17 problem5.cpp -o problem5