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


template <typename TElement>
void v_report_optimization_result(COptimizationResult<TElement>& cOptimizationResult)
{
	cout << "value: " << cOptimizationResult.dGetBestValue() << endl;
	cout << "\twhen (time): " << cOptimizationResult.dGetBestTime() << " s" << endl;
	cout << "\twhen (iteration): " << cOptimizationResult.iGetBestIteration() << endl;
	cout << "\twhen (FFE): " << cOptimizationResult.iGetBestFFE() << endl;
}//void v_report_optimization_result(COptimizationResult<TElement> &cOptimizationResult)


void v_lab_5(mt19937& cRandomEngine)
{
	CBinaryKnapsackEvaluation c_evaluation(EBinaryKnapsackInstance::knapPI_1_100_1000_1);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 100);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CBinaryKnapsackTournamentSelection c_selection(2, cRandomEngine);

	CBinaryKnapsackGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);

	c_ga.vRun();

	v_report_optimization_result(*c_ga.pcGetResult());
}//void v_lab_5(mt19937 &cRandomEngine)


void v_lab_4_max_3_sat(mt19937& cRandomEngine)
{
	CBinaryMax3SatEvaluation c_evaluation(100);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 100);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);

	c_ga.vRun();

	v_report_optimization_result(*c_ga.pcGetResult());
}//void v_lab_4_max_3_sat(mt19937 &cRandomEngine)

void v_lab_4_trap_tournament_selection_one_point_crossover(mt19937& cRandomEngine)
{
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(3, 50);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 100);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);

	c_ga.vRun();

	v_report_optimization_result(*c_ga.pcGetResult());
}//void v_lab_4_trap_tournament_selection_one_point_crossover(mt19937 &cRandomEngine)

void v_lab_4_trap_roulette_wheel_selection_uniform_crossover(mt19937& cRandomEngine)
{
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(3, 50);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 100);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryUniformCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CRouletteWheelSelection<bool> c_selection(cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);

	c_ga.vRun();

	v_report_optimization_result(*c_ga.pcGetResult());
}//void v_lab_4_trap_roulette_wheel_selection_uniform_crossover(mt19937 &cRandomEngine)
