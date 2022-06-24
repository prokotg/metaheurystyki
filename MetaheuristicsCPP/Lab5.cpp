#include "BinaryCrossovers.h"
#include "BinaryGeneticAlgorithm.h"
#include "BinaryKnapsackGeneticAlgorithm.h"
#include "BinaryKnapsackSelections.h"
#include "BinaryMutations.h"
#include "BinaryRandomSearch.h"
#include "OptimizationResult.h"
#include "RealCMAES.h"
#include "RealEvolutionStrategy11.h"
#include "RealMutations.h"
#include "RealMutationES11Adaptations.h"
#include "Selections.h"
#include "StopConditions.h"
#include "Labs.h"
#include "ReportUtils.h"

#include <BinaryEvaluationInstances.h>
#include <BinaryEvaluations.h>
#include <iostream>
#include <random>
#include <RealEvaluations.h>

using namespace Crossovers;
using namespace Mutations;
using namespace Optimizers;
using namespace Selections;
using namespace StopConditions;

using namespace Evaluations;
using namespace std;



KnapsackResults  v_lab_5_penalty(mt19937& cRandomEngine, Evaluations::EEvolutionaryPressure ev_press)
{
	CBinaryKnapsackEvaluation c_evaluation(EBinaryKnapsackInstance::f8_l_d_kp_23_10000, ev_press); // knapPI_1_100_1000_1
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 1000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CBinaryKnapsackTournamentSelection c_selection(2, cRandomEngine);

	CBinaryKnapsackGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);

	c_ga.vRun();
	KnapsackResults res(*c_ga.pcGetResult(), c_ga.count_ill_solutions());


	return res;
}//void v_lab_5(mt19937 &cRandomEngine)

void run_lab_5_penalty(ofstream& myfile) {
	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	for (size_t run_id = 0; run_id < 10; ++run_id) {
		std::cout << "Calcluating run id " << run_id << std::endl;
		for (EEvolutionaryPressure punishable : {EEvolutionaryPressure::NONE, EEvolutionaryPressure::PUNISHABLE}) {
			auto res = v_lab_5_penalty(c_random_engine, punishable);
			std::cout << std::get<0>(res.ill_count) << std::endl;
			std::cout << std::get<1>(res.ill_count) << std::endl;
			report_to_file_knapsack(myfile, "none", 0.5, 1.0, true, 100, run_id, res.cRes);
		}
	}
}

void run_lab_5_optimize(ofstream& myfile) {
	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	for (size_t run_id = 0; run_id < 10; ++run_id) {
		std::cout << "Calcluating run id " << run_id << std::endl;
		for (EEvolutionaryPressure punishable : {EEvolutionaryPressure::LAMARCK, EEvolutionaryPressure::BALDWIN}) {
			auto res = v_lab_5_penalty(c_random_engine, punishable);
			std::cout << std::get<0>(res.ill_count) << std::endl;
			std::cout << std::get<1>(res.ill_count) << std::endl;
			report_to_file_knapsack(myfile, "none", 0.5, 1.0, true, 100, run_id, res.cRes);
		}
	}
}


void run_lab_5() {
	//ofstream lab5_penalty;
	//initialize_result_file_knapsack(lab5_penalty, std::string("lab5_penalty"));
	//run_lab_5_penalty(lab5_penalty);
	//lab5_penalty.close();

	ofstream lab5_optimize;
	initialize_result_file_knapsack(lab5_optimize, std::string("lab5_optimize"));
	run_lab_5_optimize(lab5_optimize);
	lab5_optimize.close();
}