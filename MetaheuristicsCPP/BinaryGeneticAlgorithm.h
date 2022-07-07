#pragma once

#include "Crossover.h"
#include "Mutation.h"
#include "PopulationOptimizer.h"
#include "Selection.h"
#include "StopCondition.h"

#include <algorithm>
#include <ctime>
#include <numeric>
#include <random>
#include <vector>

using namespace Crossovers;
using namespace Mutations;
using namespace Selections;
using namespace StopConditions;

namespace Optimizers
{
	class CBinaryGeneticAlgorithm : public CPopulationOptimizer<bool>
	{
	public:
		CBinaryGeneticAlgorithm(IEvaluation<bool> &cEvaluation,
			IStopCondition &cStopCondition,
			IGenerator<bool> &cGeneration,
			ICrossover<bool> &cCrossover,
			IMutation<bool> &cMutation,
			ISelection<bool> &cSelection,
			mt19937 &cRandomEngine,
			int iPopulationSize);

	protected:
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime);

	private:
		void v_crossover();
		void check_stuck();
		void global_mutation();

		ICrossover<bool> &c_crossover;

		mt19937 &c_random_engine;
	};//class CBinaryGeneticAlgorithm : public CPopulationOptimizer<bool>
	class CountMatrix
	{
	public:
		// convention:
		// (0, 0), (0, 1)
		// (1, 0), (1, 1)
		CountMatrix() {
			m.resize(2, std::vector<size_t>(2, 0));
		};

		const float get_joint_probabiloty(int g1_v, int g2_v) {
			return m[g1_v][g2_v] / float(pop_size);
		}

		const float get_gene_v_prob(size_t gene, size_t value) {
			size_t cum_count;
			if (gene == 0 && value == 0) {
				cum_count = m[0][0] + m[0][1];
			}
			if (gene == 0 && value == 1) {
				cum_count = m[1][0] + m[1][1];
			}
			if (gene == 1 && value == 0) {
				cum_count = m[0][0] + m[1][0];
			}
			if (gene == 1 && value == 1) {
				cum_count = m[0][1] + m[1][1];
			}
			return cum_count / float(pop_size);
		}

		void increment_count(size_t g1_v, size_t g2_v) {
			m[g1_v][g2_v] += 1;
			pop_size += 1;
		}

	private:
		std::vector<std::vector<size_t>> m;
		size_t pop_size = 0;
	};


	class DSM {
	public:
		DSM(size_t gensize) {
			dsm.resize(gensize, std::vector<CountMatrix>(gensize));

		}
		const void to_file(std::string filename, int iteration);
		void collect(std::vector<CIndividual<bool>*>* pv_population);

	private:
		std::vector<std::vector<float>> calculate_mi();
		float single_mi_part(size_t g1, size_t g2, int v1, int v2);
		float calculate_single_mi(size_t g1, size_t g2);
		void calculate_single_ind(std::vector<bool> ind);
		vector<vector<CountMatrix>> dsm;

	};


	class CBinaryGeneticAlgorithmDSM : public CBinaryGeneticAlgorithm
	{
	public:

		CBinaryGeneticAlgorithmDSM(IEvaluation<bool>& cEvaluation,
			IStopCondition& cStopCondition,
			IGenerator<bool>& cGeneration,
			ICrossover<bool>& cCrossover,
			IMutation<bool>& cMutation,
			ISelection<bool>& cSelection,
			mt19937& cRandomEngine,
			int iPopulationSize,
			std::string filepath);

	protected:
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime);
	private:
		std::string dsm_filepath;
		DSM dsm;
		void dump_dsm();
		void collect_dsm();
	};
}//namespace Optimizers