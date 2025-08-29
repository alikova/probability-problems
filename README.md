# probability-problems
C++ probability programming exercises: Monte Carlo simulations, dynamic programming, and combinatorial analysis.

Approach / Methods  
Problem 1-2: Chose simple linear that stops immediately when it finds a different symbol. Alternative approaches like regex or string parsing would add complexity without benefit since because we only need to count from the start. Used integer arrays to represent paylines because they provide direct grid indexing, since each number corresponds to which row to check in each column.  

Problem 3: Selected Monte Carlo over analytical calculation because the interdependent pick mechanics (extra picks affecting game length, stopper ending games) create complex probability trees. Simulation handles the state dependencies naturally without manual tree enumeration, while manually enumerating every possible game sequence could be more complex to fastly handle combinatorics (with 15 objects and variable game lengths, there would be hundreds of possible game paths while implementing complex conditional probability calculations for each branch).  

Problem 4: Implemented both approaches to validate accuracy. Chose recursive dynamic programming because the game has overlapping subproblems (same available symbols + match counts occur repeatedly), making memorization highly effective. Simulation served as cross-validation.  

Problem 5: Used direct simulation rather than analytical calculation. Since the jackpot grows predictably ($0.41 per game) but wins happen randomly, simulation works well here because a simple linear growth pattern is interrupted by rare random events, therefore simulation naturally captures this without needing to derive formulas for when those interruptions occur.  

Problem 6: Used brute force enumeration instead of combinatorial formulas because writing a hand evaluator is more straightforward (count how many of each rank appear, then apply simple rules (4 of same rank = four-of-a-kind)). Combinatorial formulas would need more calculating rules therefore would be more complex to implement.  
