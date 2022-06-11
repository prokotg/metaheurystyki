#include "Lab1.h"
#include "ReportUtils.h"
#include "BinaryRandomSearch.h"
#include "GreedyRS.h"
#include "OptimizationResult.h"
#include "RealCMAES.h"
#include "RealEvolutionStrategy11.h"
#include "RealMutations.h"
#include "RealMutationES11Adaptations.h"
#include "StopConditions.h"

#include <BinaryEvaluations.h>
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include <RealEvaluations.h>

using namespace Optimizers;
using namespace StopConditions;

using namespace Evaluations;
using namespace std;

// ######################### RANDOM SEARCH ##############################

COptimizationResult<bool> v_lab_1_one_max(mt19937& cRandomEngine, int64_t gene_length = 5)
{
	CBinaryOneMaxEvaluation c_evaluation(gene_length);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();
	return *c_random_search.pcGetResult();
}//void v_lab_1_one_max(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_1_standard_deceptive_concatenation(mt19937& cRandomEngine, int64_t gene_length = 5)
{
	int64_t block_size = gene_length / 5;
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(gene_length, block_size);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	return *c_random_search.pcGetResult();
}//void v_lab_1_standard_deceptive_concatenation(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_1_bimodal_deceptive_concatenation(mt19937& cRandomEngine, int64_t gene_length = 10)
{
	int64_t block_size = gene_length / 10;
	CBinaryBimodalDeceptiveConcatenationEvaluation c_evaluation(gene_length, block_size);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	return *c_random_search.pcGetResult();
}//void v_lab_1_bimodal_deceptive_concatenation(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_1_ising_spin_glass(mt19937& cRandomEngine, int64_t gene_length = 25)
{
	CBinaryIsingSpinGlassEvaluation c_evaluation(25);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	return *c_random_search.pcGetResult();
}//void v_lab_1_ising_spin_glass(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_1_nk_landscapes(mt19937& cRandomEngine, int64_t gene_length = 10)
{
	CBinaryNKLandscapesEvaluation c_evaluation(gene_length);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	return *c_random_search.pcGetResult();
}//void v_lab_1_nk_landscapes(mt19937 &cRandomEngine)

void run_lab_1_rs(ofstream& myfile) {


	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_1_one_max(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("one_max"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_1_standard_deceptive_concatenation(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("standard_deceptive_concatenation"), gen_len, run_id, res);
		}
	}


	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 10, 50 }) {
			auto res = v_lab_1_bimodal_deceptive_concatenation(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("bimodal_deceptive_concatenation"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 25, 49, 100, 484 }) {
			auto res = v_lab_1_ising_spin_glass(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("ising_spin_glass"), gen_len, run_id, res);
		}
	}


	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 10, 50, 100, 200 }) {
			auto res = v_lab_1_nk_landscapes(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("nk_landscapes"), gen_len, run_id, res);
		}
	}
}

// ######################### Greedy SEARCH ##############################

COptimizationResult<bool> v_lab_1_one_max_greedy(mt19937& cRandomEngine, int64_t gene_length = 5, size_t reps=1)
{
	CBinaryOneMaxEvaluation c_evaluation(gene_length);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CGreedyRS c_random_search(c_evaluation, c_stop_condition, cRandomEngine, true, reps);

	c_random_search.vRun();
	return *c_random_search.pcGetResult();
}//void v_lab_1_one_max(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_1_standard_deceptive_concatenation_greedy(mt19937& cRandomEngine, int64_t gene_length = 5, size_t reps = 1)
{
	int64_t block_size = gene_length / 5;
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(gene_length, block_size);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CGreedyRS c_random_search(c_evaluation, c_stop_condition, cRandomEngine, true, reps);
	c_random_search.vRun();

	return *c_random_search.pcGetResult();
}//void v_lab_1_standard_deceptive_concatenation(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_1_bimodal_deceptive_concatenation_greedy(mt19937& cRandomEngine, int64_t gene_length = 10, size_t reps = 1)
{
	int64_t block_size = gene_length / 10;
	CBinaryBimodalDeceptiveConcatenationEvaluation c_evaluation(gene_length, block_size);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CGreedyRS c_random_search(c_evaluation, c_stop_condition, cRandomEngine, true, reps);
	c_random_search.vRun();

	return *c_random_search.pcGetResult();
}//void v_lab_1_bimodal_deceptive_concatenation(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_1_ising_spin_glass_greedy(mt19937& cRandomEngine, int64_t gene_length = 25, size_t reps = 1)
{
	CBinaryIsingSpinGlassEvaluation c_evaluation(25);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CGreedyRS c_random_search(c_evaluation, c_stop_condition, cRandomEngine, true, reps);
	c_random_search.vRun();

	return *c_random_search.pcGetResult();
}//void v_lab_1_ising_spin_glass(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_1_nk_landscapes_greedy(mt19937& cRandomEngine, int64_t gene_length = 10, size_t reps = 1)
{
	CBinaryNKLandscapesEvaluation c_evaluation(gene_length);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CGreedyRS c_random_search(c_evaluation, c_stop_condition, cRandomEngine, true, reps);
	c_random_search.vRun();

	return *c_random_search.pcGetResult();
}//void v_lab_1_nk_landscapes(mt19937 &cRandomEngine)

void run_lab_1_rs_greedy(ofstream& myfile) {


	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_1_one_max_greedy(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("one_max_greedy"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_1_standard_deceptive_concatenation_greedy(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("standard_deceptive_concatenation_greedy"), gen_len, run_id, res);
		}
	}


	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 10, 50 }) {
			auto res = v_lab_1_standard_deceptive_concatenation_greedy(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("bimodal_deceptive_concatenation_greedy"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 25, 49, 100, 484 }) {
			auto res = v_lab_1_standard_deceptive_concatenation_greedy(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("ising_spin_glass_greedy"), gen_len, run_id, res);
		}
	}


	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 10, 50, 100, 200 }) {
			auto res = v_lab_1_standard_deceptive_concatenation_greedy(c_random_engine, gen_len);
			report_to_file<bool>(myfile, std::string("nk_landscapes_greedy"), gen_len, run_id, res);
		}
	}
}


void run_lab_1() {

	ofstream myfile;
	initialize_result_file(myfile);
	std::cout << "Calculating random search" << std::endl;
	run_lab_1_rs(myfile);
	std::cout << "Calculating greedy random search" << std::endl;
	run_lab_1_rs_greedy(myfile);
	myfile.close();
}