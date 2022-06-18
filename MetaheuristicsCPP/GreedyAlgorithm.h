#pragma once

#include "Generator.h"
#include "Optimizer.h"

#include <vector>

using namespace Generators;

using namespace std;

namespace Optimizers 
{
	class CGreedyAlgorithm {
	public:
		CGreedyAlgorithm(IEvaluation<bool>& cEvaluation, bool bShuffle, size_t iReps)
			: c_evaluation(cEvaluation), b_shuffle( bShuffle ), i_reps(iReps) {
		}

		vector<bool> run(vector<bool>& vSolution);
	
	private:
		size_t i_reps;
		IEvaluation<bool>& c_evaluation;
		bool b_shuffle;
	};

}