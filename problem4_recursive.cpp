// Programming Assessment


// --------------------------------------------
// Problem 4 (Recursive Solution) - Jackpot Simulation


#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

enum class JackpotLevel { GRAND, MAJOR, MINOR, MINI };

class RecursiveJackpot {
    std::vector<std::vector<long long>> weights{
        {36000, 36000, 7},
        {36000, 36000, 200},
        {36000, 36000, 6500},
        {36000, 36000, 53800}
    };
    std::map<std::vector<int>, std::map<JackpotLevel, long double>> memo;

    long long totalWeight(const std::vector<std::vector<int>>& avail) {
        long long sum = 0;
        for (int l = 0; l < 4; l++)
            for (int s = 0; s < 3; s++)
                if (avail[l][s]) sum += weights[l][s];
        return sum;
    }

public:
    std::map<JackpotLevel, long double> calculate(
        std::vector<std::vector<int>> avail,
        std::vector<int> matches = {0,0,0,0}
    ) {
        std::vector<int> key;
        for (int l = 0; l < 4; l++) { 
            key.push_back(matches[l]); 
            key.insert(key.end(), avail[l].begin(), avail[l].end()); 
        }
        if (memo.count(key)) return memo[key];

        // Base case: someone has 3 matches
        for (int l = 0; l < 4; l++)
            if (matches[l] >= 3) {
                std::map<JackpotLevel, long double> base{
                    {JackpotLevel::GRAND,0},
                    {JackpotLevel::MAJOR,0},
                    {JackpotLevel::MINOR,0},
                    {JackpotLevel::MINI,0}
                };
                base[static_cast<JackpotLevel>(l)] = 1.0; // winning level
                return memo[key] = base;
            }

        long long tw = totalWeight(avail);
        std::map<JackpotLevel, long double> totalProb{
            {JackpotLevel::GRAND,0},
            {JackpotLevel::MAJOR,0},
            {JackpotLevel::MINOR,0},
            {JackpotLevel::MINI,0}
        };

        for (int l = 0; l < 4; l++)
            for (int s = 0; s < 3; s++)
                if (avail[l][s]) {
                    long double p = (long double)weights[l][s]/tw;
                    auto newAvail = avail; newAvail[l][s]=0;
                    auto newMatches = matches; newMatches[l]++;
                    for (auto &[lvl, val] : calculate(newAvail,newMatches)) 
                        totalProb[lvl] += p*val;
                }
        return memo[key]=totalProb;
    }

    void display() {
        auto probs = calculate({{1,1,1},{1,1,1},{1,1,1},{1,1,1}});
        std::vector<std::pair<JackpotLevel,std::string>> levels{
            {JackpotLevel::GRAND,"Grand"},
            {JackpotLevel::MAJOR,"Major"},
            {JackpotLevel::MINOR,"Minor"},
            {JackpotLevel::MINI,"Mini"}
        };
        std::cout << "=== EXACT JACKPOT PROBABILITIES ===\n";
        std::cout << std::fixed << std::setprecision(12);
        long double total=0;
        for (auto &[lvl,name] : levels) { 
            long double p = probs[lvl]*100; 
            total += p; 
            std::cout << name << ": " << p << "%\n"; 
        }
        std::cout << "Total: " << total << "%\n";
    }
};

int main() {
    RecursiveJackpot rj;
    rj.display();
    return 0;
}

// clang++ -std=c++17 -O2 problem4_recursive.cpp -o problem4_recursive
