#include "GreedyAlgorithm.h"
#include <algorithm>
#include <vector>
#include <numeric>

vector<bool> Optimizers::CGreedyAlgorithm::run(vector<bool>& vSolution)
{
    auto org_fitness = c_evaluation.dEvaluate(vSolution);
    
    std::vector<int> v(vSolution.size()); 
    // not necessary when we do not shuffle but simplifies logic 
    std::iota(std::begin(v), std::end(v), 0); 

    if (b_shuffle) {
        std::random_shuffle(std::begin(v), std::end(v));
    }
    for (auto& idx : v) {
        vSolution[idx] = !vSolution[idx];
        auto new_fitness = c_evaluation.dEvaluate(vSolution);
        if (new_fitness < org_fitness) {
            vSolution[idx] = !vSolution[idx];
        }
    
    }
    return vSolution;
}
