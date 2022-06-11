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
		CGreedyAlgorithm(IEvaluation<bool>& cEvaluation, bool bShuffle)
			: c_evaluation(cEvaluation), b_shuffle( bShuffle ){
		}

		vector<bool> run(vector<bool>& vSolution);
	
	private:
		IEvaluation<bool>& c_evaluation;
		bool b_shuffle;
	};

}