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
		d_fitness = c_binary_knapsack_evaluation.dEvaluate(*pv_genotype);
		b_is_evaluated = true;
		if (c_binary_knapsack_evaluation.EGetPressureMode() == Evaluations::EEvolutionaryPressure::PUNISHABLE) {
			dPunish();
		} 
		else if (c_binary_knapsack_evaluation.EGetPressureMode() == Evaluations::EEvolutionaryPressure::LAMARCK) {
			dOptimize(true);
		}
		else if (c_binary_knapsack_evaluation.EGetPressureMode() == Evaluations::EEvolutionaryPressure::BALDWIN) {
			dOptimize(true);
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