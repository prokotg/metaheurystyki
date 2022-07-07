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



COptimizationResult<bool>  v_lab_7_constant_order_3_1p_cross(mt19937& cRandomEngine, bool randomize){
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(3, 20, randomize);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 1000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(0.2, c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);
	std::string name = "order_3_1p";
	if (randomize) {
		name.append("_rand");
	}
	CBinaryGeneticAlgorithmDSM c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50, name);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}

COptimizationResult<bool>  v_lab_7_constant_order_3_uniform(mt19937& cRandomEngine, bool randomize) {
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(3, 20, randomize);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 1000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryUniformCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(0.2, c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);
	std::string name = "order_3_uni";
	if (randomize) {
		name.append("_rand");
	}
	CBinaryGeneticAlgorithmDSM c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50, name);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}


COptimizationResult<bool>  v_lab_7_constant_order_10_1p_cross(mt19937& cRandomEngine, bool randomize) {
	CBinaryBimodalDeceptiveConcatenationEvaluation c_evaluation(10, 5, randomize);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 1000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(0.2, c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);
	std::string name = "order_10_1p";
	if (randomize) {
		name.append("_rand");
	}
	CBinaryGeneticAlgorithmDSM c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50, name);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}

COptimizationResult<bool>  v_lab_7_constant_order_10_uniform(mt19937& cRandomEngine, bool randomize) {
	CBinaryBimodalDeceptiveConcatenationEvaluation c_evaluation(10, 5, randomize);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 1000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryUniformCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(0.2, c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);
	std::string name = "order_10_uni";
	if (randomize) {
		name.append("_rand");
	}
	CBinaryGeneticAlgorithmDSM c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50, name);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}


COptimizationResult<bool>  v_lab_7_constant_order_7_1p_cross(mt19937& cRandomEngine, bool randomize) {
	CBinaryStandardStepDeceptiveConcatenationEvaluation c_evaluation(7, 5, 3, randomize);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 1000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(0.2, c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);
	std::string name = "order_7_1p";
	if (randomize) {
		name.append("_rand");
	}
	CBinaryGeneticAlgorithmDSM c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50, name);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}

COptimizationResult<bool>  v_lab_7_constant_order_7_uniform(mt19937& cRandomEngine, bool randomize) {
	CBinaryStandardStepDeceptiveConcatenationEvaluation c_evaluation(7, 5, 3, randomize);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 1000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryUniformCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(0.2, c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);
	std::string name = "order_7_uni";
	if (randomize) {
		name.append("_rand");
	}
	CBinaryGeneticAlgorithmDSM c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50, name);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}

void run_lab_7() {
	//ofstream lab5_penalty;
	//initialize_result_file_knapsack(lab5_penalty, std::string("lab5_penalty"));
	//run_lab_5_penalty(lab5_penalty);
	//lab5_penalty.close();

	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	//v_lab_7_constant_order_3_1p_cross(c_random_engine, false);
	//v_lab_7_constant_order_3_uniform(c_random_engine, false);

	//v_lab_7_constant_order_10_1p_cross(c_random_engine, false);
	//v_lab_7_constant_order_10_uniform(c_random_engine, false);

	v_lab_7_constant_order_7_1p_cross(c_random_engine, false);
	v_lab_7_constant_order_7_uniform(c_random_engine, false);



	v_lab_7_constant_order_3_1p_cross(c_random_engine, true);
	v_lab_7_constant_order_3_uniform(c_random_engine, true);

	v_lab_7_constant_order_10_1p_cross(c_random_engine, true);
	v_lab_7_constant_order_10_uniform(c_random_engine, true);

	v_lab_7_constant_order_7_1p_cross(c_random_engine, true);
	v_lab_7_constant_order_7_uniform(c_random_engine, true);

}