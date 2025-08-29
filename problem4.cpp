// Programming Assessment

// --------------------------------------------
// Problem 4 - Jackpot Simulation


#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <iomanip>

enum class Jackpot { GRAND, MAJOR, MINOR, MINI };

struct Symbol { Jackpot level; int weight; };

class JackpotSimulation {
    std::vector<Symbol> pool;
    std::mt19937 rng;
    std::map<Jackpot,int> wins;
    int totalGames{};

public:
    JackpotSimulation() : rng(std::random_device{}()) {
        pool = {
            {Jackpot::GRAND, 36000}, {Jackpot::GRAND, 36000}, {Jackpot::GRAND, 7},
            {Jackpot::MAJOR, 36000}, {Jackpot::MAJOR, 36000}, {Jackpot::MAJOR, 200},
            {Jackpot::MINOR, 36000}, {Jackpot::MINOR, 36000}, {Jackpot::MINOR, 6500},
            {Jackpot::MINI,  36000}, {Jackpot::MINI,  36000}, {Jackpot::MINI,  53800}
        };
    }

    int weightedPick(const std::vector<Symbol>& v) {
        long long total = 0; for (auto& s : v) total += s.weight;
        std::uniform_int_distribution<long long> dist(1, total);
        long long r = dist(rng), acc = 0;
        for (int i = 0; i < v.size(); i++) if ((acc += v[i].weight) >= r) return i;
        return v.size()-1;
    }

    Jackpot playOne() {
        std::vector<Symbol> avail = pool;
        std::map<Jackpot,int> count;
        while (true) {
            int idx = weightedPick(avail);
            Jackpot j = avail[idx].level;
            if (++count[j] == 3) return j;
            avail.erase(avail.begin() + idx);
        }
    }

    void run(int n) {
        totalGames = n; wins.clear();
        for (int i = 0; i < n; i++) wins[playOne()]++;
        showResults();
    }

    void showResults() {
        std::cout << std::fixed << std::setprecision(10);
        for (auto&& [lvl, name] : {
            std::pair{Jackpot::GRAND,"Grand"},
            std::pair{Jackpot::MAJOR,"Major"},
            std::pair{Jackpot::MINOR,"Minor"},
            std::pair{Jackpot::MINI, "Mini"}
        }) {
            double p = 100.0 * wins[lvl] / totalGames;
            std::cout << name << ": " << p << "% (" << wins[lvl] << ")\n";
        }
    }
};

int main() {
    JackpotSimulation sim;
    sim.run(1000000); // 1 million games
}


// clang++ -std=c++17 problem4.cpp -o problem4