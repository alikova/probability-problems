// Programming Assessment

// --------------------------------------------
// Problem 1 - Card symbols in a slot machine

#include <iostream>
#include <vector>
#include <string>

std::pair<std::string, int> getConsecutiveFromLeft(const std::vector<std::string>& symbols) {
    if (symbols.empty()) return {"", 0};
    int count = 1;
    while (count < symbols.size() && symbols[count] == symbols[0]) count++;
    return {symbols[0], count};
}

void runTest(const std::vector<std::string>& testCase, const std::string& description) {
    std::cout << "\n" << description << "\nInput: [";
    for (size_t i = 0; i < testCase.size(); i++)
        std::cout << "\"" << testCase[i] << "\"" << (i + 1 < testCase.size() ? ", " : "");
    std::cout << "]\n";

    auto [symbol, count] = getConsecutiveFromLeft(testCase);
    std::cout << "Output: " << count << " consecutive \"" << symbol << "\"(s)\n";
}

int main() {
    std::cout << "=== PROBLEM 1: CONSECUTIVE SYMBOL COUNTER ===\n";

    runTest({"Ace", "Ace", "Jack", "Ace", "Ace"}, "Test Case 1: Problem Example");
    runTest({"King", "King", "King", "King", "King"}, "Test Case 2: All Same Symbols");
    runTest({"Queen", "Jack", "Ace", "King"}, "Test Case 3: No Consecutive Symbols");
    runTest({"Jack"}, "Test Case 4: Single Symbol");
    runTest({}, "Test Case 5: Empty Array");
    runTest({"Bell", "Bell", "Cherry", "Bell", "Bell"}, "Test Case 6: Two Consecutive Then Different");
    runTest({"Cherry", "Cherry", "Cherry", "Bell", "Grape"}, "Test Case 7: Slot Machine Example");

    std::cout << "\n=== SUMMARY ===\nAll test cases executed successfully.\n";
    return 0;
}

// clang++ -std=c++17 problem1.cpp -o problem1