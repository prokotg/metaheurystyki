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


//template <typename TElement>
//void v_report_optimization_result(COptimizationResult<TElement>& cOptimizationResult)
//{
//	cout << "value: " << cOptimizationResult.dGetBestValue() << endl;
//	cout << "\twhen (time): " << cOptimizationResult.dGetBestTime() << " s" << endl;
//	cout << "\twhen (iteration): " << cOptimizationResult.iGetBestIteration() << endl;
//	cout << "\twhen (FFE): " << cOptimizationResult.iGetBestFFE() << endl;
//}//void v_report_optimization_result(COptimizationResult<TElement> &cOptimizationResult)


//void v_lab_5(mt19937& cRandomEngine)
//{
//	CBinaryKnapsackEvaluation c_evaluation(EBinaryKnapsackInstance::knapPI_1_100_1000_1);
//	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 100);
//
//	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
//	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
//	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
//	CBinaryKnapsackTournamentSelection c_selection(2, cRandomEngine);
//
//	CBinaryKnapsackGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);
//
//	c_ga.vRun();
//
//	v_report_optimization_result(*c_ga.pcGetResult());
//}//void v_lab_5(mt19937 &cRandomEngine)

//COptimizationResult<bool>  v_lab_4_ising(mt19937& cRandomEngine, float pcross = 0.5, float pmut_mult = 1, size_t pop_size = 50)
//{
//	CBinaryIsingSpinGlassEvaluation c_evaluation(100);
//	CFFEStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 10000);
//
//	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
//	CBinaryOnePointCrossover c_crossover(pcross, cRandomEngine);
//	CBinaryBitFlipMutation c_mutation(1.0 / (c_evaluation.iGetSize() * pmut_mult), c_evaluation, cRandomEngine);
//	CTournamentSelection<bool> c_selection(2, cRandomEngine);
//
//	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, pop_size);
//
//	c_ga.vRun();
//
//	return *c_ga.pcGetResult();
//}//void v_lab_4_max_3_sat(mt19937 &cRandomEngine)

//COptimizationResult<bool>  v_lab_4_nk(mt19937& cRandomEngine, float pcross = 0.5, float pmut_mult = 1, size_t pop_size = 50)
//{
//	CBinaryNKLandscapesEvaluation c_evaluation(100);
//	CFFEStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 10000);
//
//	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
//	CBinaryOnePointCrossover c_crossover(pcross, cRandomEngine);
//	CBinaryBitFlipMutation c_mutation(1.0 / (c_evaluation.iGetSize() * pmut_mult), c_evaluation, cRandomEngine);
//	CTournamentSelection<bool> c_selection(2, cRandomEngine);
//
//	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, pop_size);
//
//	c_ga.vRun();
//
//	return *c_ga.pcGetResult();
//}//void v_lab_4_max_3_sat(mt19937 &cRandomEngine)

COptimizationResult<bool>  v_lab_6_max_3_sat(mt19937& cRandomEngine, float pcross = 1.0, float pmut_mult = 1.2, size_t pop_size = 50)
{
	CBinaryIsingSpinGlassEvaluation c_evaluation(100);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 100);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(pcross, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(0.0, c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, pop_size);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}//void v_lab_4_max_3_sat(mt19937 &cRandomEngine)

//COptimizationResult<bool> v_lab_4_trap(mt19937& cRandomEngine, float pcross = 0.5, float pmut_mult = 1, size_t pop_size = 50, size_t block_size = 50)
//{
//	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(3, block_size);
//	CFFEStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 10000);
//
//	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
//	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
//	CBinaryBitFlipMutation c_mutation(1.0 / (c_evaluation.iGetSize() * pmut_mult), c_evaluation, cRandomEngine);
//	CTournamentSelection<bool> c_selection(2, cRandomEngine);
//
//	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, pop_size);
//
//	c_ga.vRun();
//
//	return *c_ga.pcGetResult();
//}//void v_lab_4_trap_tournament_selection_one_point_crossover(mt19937 &cRandomEngine)
//
//// #############################################


void run_lab_6_stuck(ofstream& myfile) {
	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	auto res = v_lab_6_max_3_sat(c_random_engine);
	report_to_file_ga(myfile,
		std::string("ising"), std::string("tournament"), std::string("onepoint"),
		1, 0.05, 100, 100, 0, res);
}

void run_lab_6() {
	ofstream myfile;
	initialize_result_file_ga(myfile, std::string("lab6"));
	run_lab_6_stuck(myfile);
}