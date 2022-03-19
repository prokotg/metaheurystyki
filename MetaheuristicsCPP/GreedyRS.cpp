#include "GreedyRS.h"

using namespace Optimizers;

CGreedyRS::CGreedyRS(IEvaluation<bool>& cEvaluation, IStopCondition& cStopCondition, mt19937& cRandomEngine, bool bShuffle, size_t iRepetitions)
	: CSamplingOptimizer<bool>(cEvaluation, cStopCondition, c_random_generation), c_random_generation(cEvaluation.cGetConstraint(), cRandomEngine), c_greed_algorithm(cEvaluation, bShuffle)
{
}
