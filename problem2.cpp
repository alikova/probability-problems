// Programming Assessment

// --------------------------------------------
// Problem 2 - Slot Machine Line Evaluator


#include <iostream>
#include <vector>
#include <string>
#include <map>

struct PaytableEntry { int c3, c4, c5; };

class SlotMachine {
    std::vector<std::vector<std::string>> grid {
        {"Cherry", "Cherry", "Cherry", "Bell", "Grape"},
        {"Bell", "Bell", "Bell", "Cherry", "Grape"},
        {"Grape", "Grape", "Grape", "Bell", "Bell"}
    };
    std::vector<std::vector<int>> paylines {
        {0,0,0,0,0}, {1,1,1,1,1}, {2,2,2,2,2}, {1,1,1,0,0}, {1,1,1,2,2}
    };
    std::map<std::string, PaytableEntry> paytable {
        {"Cherry",{5,20,40}}, {"Bell",{3,18,35}}, {"Grape",{2,15,25}}
    };

    std::vector<std::string> getPaylineSymbols(int i) const {
        std::vector<std::string> symbols;
        for (int c = 0; c < 5; c++) symbols.push_back(grid[paylines[i][c]][c]);
        return symbols;
    }

    std::pair<std::string,int> getConsecutiveFromLeft(const std::vector<std::string>& s) const {
        if (s.empty()) return {"",0};
        int count = 1;
        while (count < s.size() && s[count] == s[0]) count++;
        return {s[0],count};
    }

    int getPayout(const std::string& sym, int n) const {
        auto it = paytable.find(sym);
        if (it == paytable.end()) return 0;
        const auto& p = it->second;
        return (n==3?p.c3 : n==4?p.c4 : n==5?p.c5 : 0);
    }

    void printScreen() const {
        for (auto& row : grid) {
            for (int i=0;i<5;i++) std::cout << row[i] << (i<4?" ":"");
            std::cout << "\n";
        }
    }

public:
    void evaluateAllLines() {
        std::cout << "=== PROBLEM 2: SLOT MACHINE LINE EVALUATOR ===\nScreen:\n";
        printScreen();
        std::cout << "\nLine Evaluation Results:\n";

        bool hasWins = false;
        for (int i=0;i<paylines.size();i++) {
            auto [sym,count] = getConsecutiveFromLeft(getPaylineSymbols(i));
            int payout = getPayout(sym,count);
            if (count >= 3 && payout > 0) {
                std::cout << "Line " << i+1 << ": " << count << "x " << sym
                          << " pays " << payout << "\n";
                hasWins = true;
            }
        }
        if (!hasWins) std::cout << "No winning lines.\n";
    }
};

int main() {
    SlotMachine().evaluateAllLines();
    return 0;
}

// clang++ -std=c++17 problem2.cpp -o problem2