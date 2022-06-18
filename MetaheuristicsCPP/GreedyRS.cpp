#include "GreedyRS.h"

using namespace Optimizers;

CGreedyRS::CGreedyRS(IEvaluation<bool>& cEvaluation, IStopCondition& cStopCondition, mt19937& cRandomEngine, bool bShuffle, size_t iRepetitions = 1)
	: CSamplingOptimizer<bool>(cEvaluation, cStopCondition, c_random_generation), c_random_generation(cEvaluation.cGetConstraint(), cRandomEngine), c_greed_algorithm(cEvaluation, bShuffle, iRepetitions)
{
	
}

bool CGreedyRS::b_run_iteration(long long iIterationNumber, clock_t tStartTime)
{
	vector<bool>* pv_solution = c_generation.pvCreate(this->c_evaluation.iGetSize());

	vector<bool> v_solution = c_greed_algorithm.run(*pv_solution);
	
	double d_value = this->c_evaluation.dEvaluate(*pv_solution);

	bool b_best_updated = this->b_check_new_best(*pv_solution, d_value);

	delete pv_solution;

	return b_best_updated;
}//virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime)
