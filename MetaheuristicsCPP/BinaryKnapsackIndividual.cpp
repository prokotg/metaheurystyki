#include "BinaryKnapsackIndividual.h"

using namespace Optimizers;

CBinaryKnapsackIndividual::CBinaryKnapsackIndividual(vector<bool> *pvGenotype, CBinaryKnapsackEvaluation &cBinaryKnapsackEvaluation, IMutation<bool> &cMutation)
	: pv_genotype(pvGenotype), c_binary_knapsack_evaluation(cBinaryKnapsackEvaluation), c_mutation(cMutation)
{
	b_is_evaluated = false;
}//CBinaryKnapsackIndividual::CBinaryKnapsackIndividual(vector<bool> *pvGenotype, CBinaryKnapsackEvaluation &cBinaryKnapsackEvaluation, IMutation<bool> &cMutation)

CBinaryKnapsackIndividual::CBinaryKnapsackIndividual(const CBinaryKnapsackIndividual &cOther)
	: c_binary_knapsack_evaluation(cOther.c_binary_knapsack_evaluation), c_mutation(cOther.c_mutation)
{
	pv_genotype = new vector<bool>(*cOther.pv_genotype);

	d_fitness = cOther.d_fitness;
	b_is_evaluated = cOther.b_is_evaluated;
}//CBinaryKnapsackIndividual::CBinaryKnapsackIndividual(const CBinaryKnapsackIndividual &cOther)

CBinaryKnapsackIndividual::~CBinaryKnapsackIndividual()
{
	delete pv_genotype;
}//CBinaryKnapsackIndividual::~CBinaryKnapsackIndividual()

double CBinaryKnapsackIndividual::dEvaluate()
{
	if (!b_is_evaluated)
	{
		if (c_binary_knapsack_evaluation.EGetPressureMode() == Evaluations::EEvolutionaryPressure::LAMARCK) {
			dOptimize(true);
		}
		else if (c_binary_knapsack_evaluation.EGetPressureMode() == Evaluations::EEvolutionaryPressure::BALDWIN) {
			dOptimize(false);
		}
		d_fitness = c_binary_knapsack_evaluation.dEvaluate(*pv_genotype);
		b_is_evaluated = true;
		if (c_binary_knapsack_evaluation.EGetPressureMode() == Evaluations::EEvolutionaryPressure::PUNISHABLE) {
			dPunish();
		} 

	}//if (!b_is_evaluated)

	return dGetFitness();
}

void Optimizers::CBinaryKnapsackIndividual::dPunish()
{
	auto weight = c_binary_knapsack_evaluation.dCalculateWeight(*pv_genotype);
	auto cap = c_binary_knapsack_evaluation.dGetCapacity();
	if (weight > cap) {
		float rep = (weight / cap) - 1.0;
		if (rep > 0.3) {
			rep = 1;
		}
		d_fitness *=  (1 -  rep);

	}

}
void Optimizers::CBinaryKnapsackIndividual::dOptimize(bool keep)
{
	auto weight = c_binary_knapsack_evaluation.dCalculateWeight(*pv_genotype);
	auto cap = c_binary_knapsack_evaluation.dGetCapacity();
	auto difference = weight - cap;
	vector<bool>* new_genotype = new vector<bool>;
	if (difference > 0) {
		// too much load, release some
		auto buffer = difference;
		
		*new_genotype = *pv_genotype;
		std::vector<int> v(pv_genotype->size());
		std::iota(v.begin(), v.end(), 0);
		std::random_shuffle(v.begin(), v.end());
		for (auto idx : v) {
			if (new_genotype->at(idx)) {
				new_genotype->at(idx) = !new_genotype->at(idx);
				auto item_weight = c_binary_knapsack_evaluation.vGetWeights()[idx];
				buffer -= item_weight;
			}
			if (buffer <= 0) {
				break;
			}
		}
	
	}
	else if (difference < 0) {
		// you can load some more
		auto buffer = difference;
		*new_genotype = *pv_genotype;
		std::vector<int> v(pv_genotype->size());
		std::iota(v.begin(), v.end(), 0);
		std::random_shuffle(v.begin(), v.end());
		for (auto idx : v) {
			if (!new_genotype->at(idx)) {
				auto item_weight = c_binary_knapsack_evaluation.vGetWeights()[idx];
				if (-item_weight < buffer) {
					continue;
				}
				new_genotype->at(idx) = !new_genotype->at(idx);
				
				buffer += item_weight;
			}

		}

	}

	if (keep) {
		pv_genotype = new_genotype;
	}
}
//double CBinaryKnapsackIndividual::dEvaluate()

bool CBinaryKnapsackIndividual::bMutate()
{
	bool b_successful_mutation = c_mutation.bMutate(*pv_genotype);

	if (b_successful_mutation)
	{
		b_is_evaluated = false;
	}//if (b_successful_mutation)

	return b_successful_mutation;
}//bool CBinaryKnapsackIndividual::bMutate()