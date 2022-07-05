#include "BinaryCrossovers.h"
#include "BinaryGeneticAlgorithm.h"
#include "BinaryMutations.h"
#include "BinaryRandomSearch.h"
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



COptimizationResult<bool>  v_lab_7_constant_order_3(mt19937& cRandomEngine, bool randomize){
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(3, 20, randomize);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 1000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(0.2, c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithmDSM c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50, "somet");

	c_ga.vRun();

	return *c_ga.pcGetResult();
}//void v_lab_5(mt19937 &cRandomEngine)


void run_lab_7() {
	//ofstream lab5_penalty;
	//initialize_result_file_knapsack(lab5_penalty, std::string("lab5_penalty"));
	//run_lab_5_penalty(lab5_penalty);
	//lab5_penalty.close();

	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	v_lab_7_constant_order_3(c_random_engine, true);

}