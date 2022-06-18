#include "RealEvolutionStrategy11.h"
#include <numeric>
#include <iostream>
using namespace Optimizers;

CRealEvolutionStrategy11::CRealEvolutionStrategy11(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, IRealMutationES11Adaptation &cMutationAdaptation, mt19937 &cRandomEngine)
	: COptimizer<double>(cEvaluation, cStopCondition), c_mutation_adaptation(cMutationAdaptation), c_random_engine(cRandomEngine)
{

}//CRealEvolutionStrategy11::CRealEvolutionStrategy11(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, IRealMutationES11Adaptation &cMutationAdaptation, mt19937 &cRandomEngine)

void CRealEvolutionStrategy11::v_initialize(clock_t tStartTime)
{
	CRealRandomGenerator c_random_generation(c_evaluation.cGetConstraint(), c_random_engine);
	
	vector<double> v_initial_solution((size_t)c_evaluation.iGetSize());
	c_random_generation.vFill(v_initial_solution);

	b_check_new_best(v_initial_solution, c_evaluation.dEvaluate(v_initial_solution));
}//void CRealEvolutionStrategy11::v_initialize(clock_t tStartTime)

bool CRealEvolutionStrategy11::b_run_iteration(long long iIterationNumber, clock_t tStartTime)
{
	//CRealGaussianMutation &c_mutation = c_mutation_adaptation.cGetMutation();

	//vector<double> v_candidate_solution(pcGetResult()->vGetBestSolution());

	//c_mutation.bMutate(v_candidate_solution);
	//double d_candidate_value = c_evaluation.dEvaluate(v_candidate_solution);
	//if (nfails > 5) {
	//	auto v = isNoisy(pcGetResult()->vGetBestSolution());
	//	double sum = std::accumulate(v.begin(), v.end(), 0.0);
	//	double mean = sum / v.size();
	//	std::cout << mean << std::endl;
	//	if (mean > 0.1) {
	//		std::cout << "triggered" << std::endl;
	//		vector<double> v_initial_solution((size_t)c_evaluation.iGetSize());
	//	}

	//}
	//c_mutation_adaptation.vAdapt(pcGetResult()->dGetBestValue(), pcGetResult()->vGetBestSolution(), d_candidate_value, v_candidate_solution);

	//return b_check_new_best(v_candidate_solution, d_candidate_value);


	CRealGaussianMutation& c_mutation = c_mutation_adaptation.cGetMutation();

	vector<double> v_candidate_solution(pcGetResult()->vGetBestSolution());

	c_mutation.bMutate(v_candidate_solution);
	double d_candidate_value = c_evaluation.dEvaluate(v_candidate_solution);

	c_mutation_adaptation.vAdapt(pcGetResult()->dGetBestValue(), pcGetResult()->vGetBestSolution(), d_candidate_value, v_candidate_solution);

	return b_check_new_best(v_candidate_solution, d_candidate_value);
}//bool CRealEvolutionStrategy11::b_run_iteration(long long iIterationNumber, clock_t tStartTime)

std::vector<double> CRealEvolutionStrategy11::isNoisy(std::vector<double> vBestSolution) {

	std::vector<std::vector<double>> sampled_space{ {} };
	auto membersize = 10;
	for(int step = -membersize; step != membersize; ++step){
		std::vector<double> member(vBestSolution.size());
		for (int belem_idx = 0; belem_idx < vBestSolution.size(); ++belem_idx) {
			auto lower_bound = c_evaluation.cGetConstraint().tGetLowerBound(belem_idx);
			auto upper_bound = c_evaluation.cGetConstraint().tGetUpperBound(belem_idx);
			auto step_size = step * ((upper_bound - lower_bound) / 1000);
			if (vBestSolution[belem_idx] + step_size > upper_bound) {
				step_size = upper_bound - vBestSolution[belem_idx];
			}
			else if (vBestSolution[belem_idx] + step_size < lower_bound) {
				step_size = vBestSolution[belem_idx] - lower_bound;
			}
			member[belem_idx] = vBestSolution[belem_idx] + step_size;
		}

	}
	std::vector<double> direction_change(vBestSolution.size(), 0);

	std::vector<bool> global_direction(vBestSolution.size(), true);
	//bool direction;
	std::vector<bool> direction(vBestSolution.size(), true);
	for (auto idx = 0; idx != vBestSolution.size()-2; ++idx) {
		auto vec_a = sampled_space[idx];
		auto vec_b = sampled_space[idx + 1];
		for (auto i = 0; i != vBestSolution.size(); ++i) {
			direction[i] = (vec_b[i] > vec_a[i]);
		}
		if (idx != 0) {
			for (auto i = 0; i != vBestSolution.size(); ++i) {
				if (direction[i] != global_direction[i]) {
					direction_change[i]++;
				}
			}
		}
		global_direction = direction;

		
	}
	auto noisesum = std::accumulate(direction_change.begin(), direction_change.end(),
		decltype(direction_change)::value_type(0));

	std::for_each(direction_change.begin(), direction_change.end(), [membersize](double& el) {el /= 2 * membersize; });
	return direction_change;

}