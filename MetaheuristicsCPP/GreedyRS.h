#pragma once

#include "BinaryGenerators.h"
#include "SamplingOptimizer.h"
#include "GreedyAlgorithm.h"

using namespace Generators;

namespace Optimizers
{
	class CGreedyRS : public CSamplingOptimizer<bool>
	{
	public:
		CGreedyRS(IEvaluation<bool>& cEvaluation, IStopCondition& cStopCondition, mt19937& cRandomEngine, bool bShuffle, size_t iRepetitions);

	private:
		bool b_run_iteration(long long iIterationNumber, clock_t tStartTime);
		CBinaryRandomGenerator c_random_generation;
		CGreedyAlgorithm c_greed_algorithm;
		
	};//class CBinaryRandomSearch : public CSamplingOptimizer<bool>
}//namespace Optimizers