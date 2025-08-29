// Programming Assessment

// --------------------------------------------
// Problem 6 - Poker Hand Detection

#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include <iomanip>

enum class PokerLevel { GRAND, MAJOR, MINOR, MINI };

// Simple evaluator: 
// - 4-of-a-kind → GRAND
// - Full house → MAJOR
// - 3-of-a-kind → MINOR
// - Everything else → MINI
PokerLevel evaluateHand(const std::array<int,5>& ranks) {
    std::map<int,int> count;
    for(int r: ranks) count[r]++;
    int pairs=0, triples=0, quads=0;
    for(auto& [r,c]: count){
        if(c==2) pairs++;
        else if(c==3) triples++;
        else if(c==4) quads++;
    }
    if(quads) return PokerLevel::GRAND;
    if(triples && pairs) return PokerLevel::MAJOR;
    if(triples) return PokerLevel::MINOR;
    return PokerLevel::MINI;
}

int main() {
    std::vector<int> deck;
    for(int r=0;r<13;r++) for(int s=0;s<4;s++) deck.push_back(r); // only ranks matter

    std::map<PokerLevel,long long> counts;
    long long total = 0;

    std::array<int,5> idx = {0,1,2,3,4};
    int n = deck.size();

    auto next_comb = [&](std::array<int,5>& a) -> bool {
        for(int i=4;i>=0;i--){
            if(a[i] < n-5+i){
                a[i]++;
                for(int j=i+1;j<5;j++) a[j] = a[j-1]+1;
                return true;
            }
        }
        return false;
    };

    do {
        std::array<int,5> handRanks = {deck[idx[0]], deck[idx[1]], deck[idx[2]], deck[idx[3]], deck[idx[4]]};
        counts[evaluateHand(handRanks)]++;
        total++;
    } while(next_comb(idx));

    std::cout << std::fixed << std::setprecision(12);
    for(auto& [lvl,cnt]: counts){
        std::string name = (lvl==PokerLevel::GRAND?"Grand":lvl==PokerLevel::MAJOR?"Major":lvl==PokerLevel::MINOR?"Minor":"Mini");
        double prob = 100.0*cnt/total;
        std::cout << name << ": " << prob << "% (" << cnt << " hands)\n";
    }

    std::cout << "Total hands: " << total << std::endl;
}

// clang++ -std=c++17 problem6.cpp -o problem6

