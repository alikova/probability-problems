// Programming Assessment

// --------------------------------------------
// Problem 3 - Pick Game Simulation


#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <iomanip>
#include <algorithm>

enum class AwardType {
    CREDITS_500, CREDITS_50, FREE_GAMES_10, FREE_GAMES_5,
    EXTRA_PICKS_2, EXTRA_PICKS_1, BLANK, STOPPER
};

struct Award { AwardType type; int count; };

class PickGameSimulation {
    std::vector<Award> awardPool {
        {AwardType::CREDITS_500, 1}, {AwardType::CREDITS_50, 2},
        {AwardType::FREE_GAMES_10, 1}, {AwardType::FREE_GAMES_5, 2},
        {AwardType::EXTRA_PICKS_2, 2}, {AwardType::EXTRA_PICKS_1, 1},
        {AwardType::BLANK, 5}, {AwardType::STOPPER, 1}
    };
    
    std::mt19937 rng{std::random_device{}()};
    std::map<AwardType,int> counts;
    long long totalPicks=0, totalGames=0;
    
    std::string toString(AwardType t) {
        switch(t) {
            case AwardType::CREDITS_500: return "500 credits";
            case AwardType::CREDITS_50: return "50 credits";
            case AwardType::FREE_GAMES_10: return "10 free games";
            case AwardType::FREE_GAMES_5: return "5 free games";
            case AwardType::EXTRA_PICKS_2: return "+2 extra picks";
            case AwardType::EXTRA_PICKS_1: return "+1 extra pick";
            case AwardType::BLANK: return "Blank";
            case AwardType::STOPPER: return "Stopper";
        }
        return "";
    }
    
    std::vector<AwardType> makeGamePool() {
        std::vector<AwardType> pool;
        for (auto& a : awardPool) 
            pool.insert(pool.end(), a.count, a.type);
        std::shuffle(pool.begin(), pool.end(), rng);
        return pool;
    }
    
    int simulateOne() {
        auto pool = makeGamePool();
        int picks = 3, used=0;
        while (picks > 0 && !pool.empty()) {
            int idx = std::uniform_int_distribution<int>(0,pool.size()-1)(rng);
            AwardType a = pool[idx];
            pool.erase(pool.begin()+idx);
            counts[a]++; used++; picks--;
            if (a==AwardType::EXTRA_PICKS_2) picks+=2;
            else if (a==AwardType::EXTRA_PICKS_1) picks+=1;
            else if (a==AwardType::STOPPER) break;
        }
        return used;
    }
    
public:
    void run(int n) {
        counts.clear(); totalPicks=0; totalGames=n;
        for(int i=0;i<n;i++) totalPicks+=simulateOne();
        
        std::cout << "\n=== RESULTS ("<<n<<" games) ===\n";
        std::cout << "Avg picks: " << (double)totalPicks/n << "\n\n";
        
        for (auto& a : awardPool) {
            double p = (double)counts[a.type]/totalPicks;
            std::cout << std::setw(18) << toString(a.type) << ": "
                      << std::fixed << std::setprecision(10) << p 
                      << " (" << counts[a.type] << ")\n";
        }
    }
};

int main() {
    PickGameSimulation sim;
    sim.run(1'000'000);
}

// clang++ -std=c++17 problem3.cpp -o problem3