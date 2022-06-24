#pragma once

#include "Mutation.h"

#include <BinaryEvaluations.h>
#include <vector>

using namespace Mutations;

using namespace Evaluations;
using namespace std;

namespace Optimizers
{
	class CBinaryKnapsackIndividual
	{
	public:
		CBinaryKnapsackIndividual(vector<bool> *pvGenotype, CBinaryKnapsackEvaluation &cBinaryKnapsackEvaluation, IMutation<bool> &cMutation);
		CBinaryKnapsackIndividual(const CBinaryKnapsackIndividual &cOther);
		friend bool operator <( CBinaryKnapsackIndividual const & lhs,  CBinaryKnapsackIndividual const & rhs)
		{
			return lhs.d_fitness < rhs.d_fitness;
		}

		~CBinaryKnapsackIndividual();

		double dEvaluate();



		bool bMutate();

		vector<bool> &vGetGenotype() { return *pv_genotype; }
		double dGetFitness() { return d_fitness; }

	private:
		void dPunish();
		void dOptimize(bool keep);
		vector<bool> *pv_genotype;

		CBinaryKnapsackEvaluation &c_binary_knapsack_evaluation;
		IMutation<bool> &c_mutation;

		bool b_is_evaluated;
		double d_fitness;
	};//class CBinaryKnapsackIndividual





}//namespace Optimizers