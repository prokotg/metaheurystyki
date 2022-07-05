#pragma once

#include "BinaryKnapsackIndividual.h"
#include "BinaryKnapsackSelection.h"
#include "Crossover.h"
#include "Mutation.h"
#include "PopulationOptimizer.h"
#include "StopCondition.h"
#include "VectorUtils.h"

#include <algorithm>
#include <BinaryEvaluations.h>
#include <ctime>
#include <numeric>
#include <random>

using namespace Crossovers;
using namespace Evaluations;
using namespace Mutations;
using namespace Selections;
using namespace StopConditions;

namespace Optimizers
{
	class SimpleRingBuffer {
	public: 
		SimpleRingBuffer(size_t size) {
			buffer.resize(1);
			max_size = size;
		}
		float get_rsd() const;
		void insert(float val);
		bool is_full() const { return max_size == buffer.size(); }
	private:
		std::vector<float> buffer;
		size_t max_size;
		size_t index = 0;
	};
	class CBinaryKnapsackGeneticAlgorithm : public COptimizer<bool>
	{
	public:
		CBinaryKnapsackGeneticAlgorithm(CBinaryKnapsackEvaluation &cBinaryKnapsackEvaluation,
			IStopCondition &cStopCondition,
			IGenerator<bool> &cGenerator,
			ICrossover<bool> &cCrossover,
			IMutation<bool> &cMutation,
			IBinaryKnapsackSelection &cBinaryKnapsackSelection,
			mt19937 &cRandomEngine,
			int iPopulationSize,
			bool stuckness = false);

		virtual ~CBinaryKnapsackGeneticAlgorithm();
		std::tuple<size_t, float> count_ill_solutions();
	protected:
		virtual void v_initialize(clock_t tStartTime);
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime);
		vector<CBinaryKnapsackIndividual*>* pv_population;
	private:
		bool bEscapeStuck;
		SimpleRingBuffer bestmean;
		void v_evaluation();

		void v_selection();
		void v_crossover();
		void v_mutation();
		void v_check_stuck();
		void global_mutation();

		bool b_check_new_best(bool bOnlyImprovements = true);

		CBinaryKnapsackIndividual *pc_create_individual(vector<bool> *pvGenotype = nullptr);


		CBinaryKnapsackEvaluation &c_binary_knapsack_evaluation;

		int i_population_size;
		

		IGenerator<bool> &c_generator;
		IBinaryKnapsackSelection &c_binary_knapsack_selection;
		ICrossover<bool> &c_crossover;
		IMutation<bool> &c_mutation;

		mt19937 &c_random_engine;
	};//class CBinaryKnapsackGeneticAlgorithm : public COptimizer<bool>





}//namespace Optimizers