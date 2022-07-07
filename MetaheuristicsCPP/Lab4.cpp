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


template <typename TElement>
void v_report_optimization_result(COptimizationResult<TElement>& cOptimizationResult)
{
	cout << "value: " << cOptimizationResult.dGetBestValue() << endl;
	cout << "\twhen (time): " << cOptimizationResult.dGetBestTime() << " s" << endl;
	cout << "\twhen (iteration): " << cOptimizationResult.iGetBestIteration() << endl;
	cout << "\twhen (FFE): " << cOptimizationResult.iGetBestFFE() << endl;
}//void v_report_optimization_result(COptimizationResult<TElement> &cOptimizationResult)


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

COptimizationResult<bool>  v_lab_4_ising(mt19937& cRandomEngine, float pcross = 0.5, float pmut_mult = 1, size_t pop_size = 50)
{
	CBinaryIsingSpinGlassEvaluation c_evaluation(100);
	CFFEStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 10000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(pcross, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / (c_evaluation.iGetSize() * pmut_mult), c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, pop_size);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}//void v_lab_4_max_3_sat(mt19937 &cRandomEngine)

COptimizationResult<bool>  v_lab_4_nk(mt19937& cRandomEngine, float pcross = 0.5, float pmut_mult = 1, size_t pop_size = 50)
{
	CBinaryNKLandscapesEvaluation c_evaluation(100);
	CFFEStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 10000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(pcross, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / (c_evaluation.iGetSize() * pmut_mult), c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, pop_size);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}//void v_lab_4_max_3_sat(mt19937 &cRandomEngine)

COptimizationResult<bool>  v_lab_4_max_3_sat(mt19937& cRandomEngine, float pcross=0.5, float pmut_mult = 1, size_t pop_size = 50)
{
	CBinaryMax3SatEvaluation c_evaluation(100);
	CFFEStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 10000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(pcross, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / (c_evaluation.iGetSize() * pmut_mult), c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, pop_size);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}//void v_lab_4_max_3_sat(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_4_trap(mt19937& cRandomEngine, float pcross=0.5, float pmut_mult = 1, size_t pop_size=50, size_t block_size = 50)
{
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(3, block_size);
	CFFEStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 10000);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / (c_evaluation.iGetSize() * pmut_mult), c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, pop_size);

	c_ga.vRun();

	return *c_ga.pcGetResult();
}//void v_lab_4_trap_tournament_selection_one_point_crossover(mt19937 &cRandomEngine)

// #############################################

void run_lab_4_pop_change(ofstream& myfile) {
	float pcross = 0.5;
	float pmut_mult = 0.1;
	for (size_t run_id = 0; run_id < 10; run_id++) {


		for (auto pop : { 10, 50, 100, 300, 1000 }) {
			random_device c_seed_generator;
			mt19937 c_random_engine(c_seed_generator());

			for (auto blocks : { 10, 50, 100 }) {
				std::cout << "Calculating trap " << blocks << " ... run id  " << run_id << std::endl;
				auto trap_res = v_lab_4_trap(c_random_engine, pcross, pmut_mult, pop, blocks);
				report_to_file_ga(myfile,
					std::string("trap").append(std::to_string(blocks)), std::string("tournament"), std::string("onepoint"),
					pcross, pmut_mult, pop, 100, run_id, trap_res);
			}
			
			std::cout << "Calculating max3sat... run id  " << run_id << std::endl;
			auto max3sat_res = v_lab_4_max_3_sat(c_random_engine, pcross, pmut_mult, pop);
			report_to_file_ga(myfile, 
				std::string("max3sat"),  std::string("tournament"), std::string("onepoint"),  
				pcross, pmut_mult, pop, 100, run_id, max3sat_res);
			std::cout << "Calculating nk... run id  " << run_id << std::endl;

			auto nk_res = v_lab_4_nk(c_random_engine, pcross, pmut_mult, pop);
			report_to_file_ga(myfile, 
				std::string("nk"), std::string("tournament"), std::string("onepoint"),  
				pcross, pmut_mult, pop, 100, run_id, nk_res);
			std::cout << "Calculating ising... run id  " << run_id << std::endl;

			auto ising_res = v_lab_4_ising(c_random_engine, pcross, pmut_mult, pop);
			report_to_file_ga(myfile, 
				std::string("ising"), std::string("tournament"), std::string("onepoint"), 
				pcross, pmut_mult, pop, 100, run_id, ising_res);

		}
	}
}

void run_lab_4_params_change(ofstream& myfile) {
	size_t pop = 100;
	for (size_t run_id = 0; run_id < 10; run_id++) {


		for (auto pcross : { 0.0, 0.1, 0.25, 0.5, 0.75, 1.0 }) {
			for (auto pmut_mult : { 0.5, 0.8, 1.0, 1.2, 1.4 }) {
				random_device c_seed_generator;
				mt19937 c_random_engine(c_seed_generator());

				for (auto blocks : { 10, 50, 100 }) {
					std::cout << "Calculating trap " << blocks << " ... run id  " << run_id << std::endl;
					auto trap_res = v_lab_4_trap(c_random_engine, pcross, pmut_mult, pop, blocks);
					report_to_file_ga(myfile,
						std::string("trap").append(std::to_string(blocks)), std::string("tournament"), std::string("onepoint"),
						pcross, pmut_mult, pop, 100, run_id, trap_res);
				}

				std::cout << "Calculating max3sat... run id  " << run_id << std::endl;
				auto max3sat_res = v_lab_4_max_3_sat(c_random_engine, pcross, pmut_mult, pop);
				report_to_file_ga(myfile,
					std::string("max3sat"), std::string("tournament"), std::string("onepoint"),
					pcross, pmut_mult, pop, 100, run_id, max3sat_res);
				std::cout << "Calculating nk... run id  " << run_id << std::endl;

				auto nk_res = v_lab_4_nk(c_random_engine, pcross, pmut_mult, pop);
				report_to_file_ga(myfile,
					std::string("nk"), std::string("tournament"), std::string("onepoint"),
					pcross, pmut_mult, pop, 100, run_id, nk_res);
				std::cout << "Calculating ising... run id  " << run_id << std::endl;

				auto ising_res = v_lab_4_ising(c_random_engine, pcross, pmut_mult, pop);
				report_to_file_ga(myfile,
					std::string("ising"), std::string("tournament"), std::string("onepoint"),
					pcross, pmut_mult, pop, 100, run_id, ising_res);
			}
		}
	}
}

void run_lab_4() {
	ofstream myfile;
	initialize_result_file_ga(myfile, std::string("lab4pop"));
	run_lab_4_pop_change(myfile);
	/*ofstream myfile2;
	initialize_result_file_ga(myfile2, std::string("lab4params"));
	run_lab_4_params_change(myfile2);*/
}