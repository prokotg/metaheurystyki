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


std::vector<double> get_domain_sigmas(IEvaluationProfile<double>& cEvaluation, double slice = 0.01) {
	auto& constraint = cEvaluation.cGetConstraint();
	auto size = cEvaluation.iGetSize();
	std::vector<double> sigmas(size);
	for (size_t i = 0; i < size; ++i) {
		double lower_bound = constraint.tGetLowerBound(i);
		double upper_bound = constraint.tGetUpperBound(i);
		double range = upper_bound - lower_bound;
		sigmas[i] = range * slice;
	}
	return sigmas;
}




// ############################### NULL ################################

COptimizationResult<double> v_lab_2_sphere(mt19937& cRandomEngine, int64_t gene_length = 2)
{
	CRealSphereEvaluation c_sphere_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_sphere_evaluation.dGetMaxValue(), 2000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_evaluation, cRandomEngine);
	//CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_sphere(mt19937 &cRandomEngine)

COptimizationResult<double> v_lab_2_sphere_10(mt19937& cRandomEngine, int64_t gene_length = 2)
{
	CRealSphere10Evaluation c_sphere_10_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_sphere_10_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_sphere_10_evaluation.dGetMaxValue(), 2000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_10_evaluation, cRandomEngine);
	//CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);


	CRealEvolutionStrategy11 c_es11(c_sphere_10_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_sphere_10(mt19937 &cRandomEngine)

COptimizationResult<double> v_lab_2_ellipsoid(mt19937& cRandomEngine, int64_t gene_length = 2)
{
	CRealEllipsoidEvaluation c_ellipsoid_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_ellipsoid_evaluation.iGetSize(), 1);

	CIterationsStopCondition c_stop_condition(c_ellipsoid_evaluation.dGetMaxValue(), 2000);
	CRealGaussianMutation c_mutation(v_sigmas, c_ellipsoid_evaluation, cRandomEngine);
	//CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_ellipsoid_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_ellipsoid(mt19937 &cRandomEngine)

COptimizationResult<double> v_lab_2_step_2_sphere(mt19937& cRandomEngine, int64_t gene_length = 2)
{
	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_step_2_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_step_2_sphere_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_step_2_sphere_evaluation, cRandomEngine);
	//CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_step_2_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_step_2_sphere(mt19937 &cRandomEngine)

// ############################## 1_FIFTH ################################

COptimizationResult<double> v_lab_2_sphere_fifth(mt19937& cRandomEngine, int64_t gene_length = 2)
{
	CRealSphereEvaluation c_sphere_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_sphere_evaluation.dGetMaxValue(), 2000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_sphere(mt19937 &cRandomEngine)

COptimizationResult<double> v_lab_2_sphere_10_fifth(mt19937& cRandomEngine, int64_t gene_length = 2)
{
	CRealSphere10Evaluation c_sphere_10_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_sphere_10_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_sphere_10_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_10_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_10_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_sphere_10(mt19937 &cRandomEngine)

COptimizationResult<double> v_lab_2_ellipsoid_fifth(mt19937& cRandomEngine, int64_t gene_length = 2)
{
	CRealEllipsoidEvaluation c_ellipsoid_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_ellipsoid_evaluation.iGetSize(), 1);

	CIterationsStopCondition c_stop_condition(c_ellipsoid_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_ellipsoid_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);

	CRealEvolutionStrategy11 c_es11(c_ellipsoid_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_ellipsoid(mt19937 &cRandomEngine)

COptimizationResult<double> v_lab_2_step_2_sphere_fifth(mt19937& cRandomEngine, int64_t gene_length = 2)
{
	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_step_2_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_step_2_sphere_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_step_2_sphere_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);

	CRealEvolutionStrategy11 c_es11(c_step_2_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_step_2_sphere(mt19937 &cRandomEngine)

// ############################## 1_FIFTH  DOMAIN ADAPT################################

COptimizationResult<double> v_lab_2_sphere_fifth_adapt(mt19937& cRandomEngine, int64_t gene_length = 2, double slice=0.01)
{
	CRealSphereEvaluation c_sphere_evaluation(gene_length);

	vector<double> v_sigmas = get_domain_sigmas(c_sphere_evaluation);

	CIterationsStopCondition c_stop_condition(c_sphere_evaluation.dGetMaxValue(), 2000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_sphere(mt19937 &cRandomEngine)

COptimizationResult<double> v_lab_2_sphere_10_fifth_adapt(mt19937& cRandomEngine, int64_t gene_length = 2, double slice = 0.01)
{
	CRealSphere10Evaluation c_sphere_10_evaluation(gene_length);

	vector<double> v_sigmas = get_domain_sigmas(c_sphere_10_evaluation, slice);

	CIterationsStopCondition c_stop_condition(c_sphere_10_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_10_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_10_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_sphere_10(mt19937 &cRandomEngine)

COptimizationResult<double> v_lab_2_ellipsoid_fifth_adapt(mt19937& cRandomEngine, int64_t gene_length = 2, double slice = 0.01)
{
	CRealEllipsoidEvaluation c_ellipsoid_evaluation(gene_length);

	vector<double> v_sigmas = get_domain_sigmas(c_ellipsoid_evaluation, slice);

	CIterationsStopCondition c_stop_condition(c_ellipsoid_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_ellipsoid_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);

	CRealEvolutionStrategy11 c_es11(c_ellipsoid_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_ellipsoid(mt19937 &cRandomEngine)

COptimizationResult<double> v_lab_2_step_2_sphere_fifth_adapt(mt19937& cRandomEngine, int64_t gene_length = 2, double slice = 0.01)
{
	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(gene_length);

	vector<double> v_sigmas = get_domain_sigmas(c_step_2_sphere_evaluation, slice);

	CIterationsStopCondition c_stop_condition(c_step_2_sphere_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_step_2_sphere_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5, c_mutation);

	CRealEvolutionStrategy11 c_es11(c_step_2_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	return *c_es11.pcGetResult();
}//void v_lab_2_step_2_sphere(mt19937 &cRandomEngine)


// ####################################################################################

void run_lab_2_null(ofstream& myfile) {

	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_sphere(c_random_engine, gen_len);
			report_to_file<double>(myfile, std::string("spheren"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_sphere_10(c_random_engine, gen_len);
			report_to_file<double>(myfile, std::string("sphere_10"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_ellipsoid(c_random_engine, gen_len);
			report_to_file<double>(myfile, std::string("ellipsoid"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_step_2_sphere(c_random_engine, gen_len);
			report_to_file<double>(myfile, std::string("step_2_sphere"), gen_len, run_id, res);
		}
	}
}

void run_lab_2_fifth(ofstream& myfile) {
	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_sphere_fifth(c_random_engine, gen_len);
			report_to_file<double>(myfile, std::string("spheren_fifth"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_sphere_10_fifth(c_random_engine, gen_len);
			report_to_file<double>(myfile, std::string("sphere_10_fifth"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_ellipsoid_fifth(c_random_engine, gen_len);
			report_to_file<double>(myfile, std::string("ellipsoid_fifth"), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_step_2_sphere_fifth(c_random_engine, gen_len);
			report_to_file<double>(myfile, std::string("step_2_sphere_fifth"), gen_len, run_id, res);
		}
	}
}

void run_lab_2_fifth_adapt(ofstream& myfile, double slice=0.01) {
	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());
	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_sphere_fifth_adapt(c_random_engine, gen_len, slice);
			report_to_file<double>(myfile, std::string("spheren_fifth_adapt_").append(std::to_string(slice)), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_sphere_10_fifth_adapt(c_random_engine, gen_len, slice);
			report_to_file<double>(myfile, std::string("sphere_10_fifth_adapt_").append(std::to_string(slice)), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_ellipsoid_fifth_adapt(c_random_engine, gen_len, slice);
			report_to_file<double>(myfile, std::string("ellipsoid_fifth_adapt_").append(std::to_string(slice)), gen_len, run_id, res);
		}
	}

	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : { 5, 10, 50 }) {
			auto res = v_lab_2_step_2_sphere_fifth_adapt(c_random_engine, gen_len, slice);
			report_to_file<double>(myfile, std::string("step_2_sphere_fifth_adapt_").append(std::to_string(slice)), gen_len, run_id, res);
		}
	}
}


void run_lab_2() {

	ofstream myfile;
	initialize_result_file(myfile, std::string("lab2"));
	std::cout << "Calculating null" << std::endl;
	run_lab_2_null(myfile);
	std::cout << "Calculating one fifth" << std::endl;
	run_lab_2_fifth(myfile);
	std::cout << "Calculating one fifth adapt 0.01" << std::endl;
	run_lab_2_fifth_adapt(myfile, 0.01);
	std::cout << "Calculating one fifth adapt 0.001" << std::endl;
	run_lab_2_fifth_adapt(myfile,0.001);
	myfile.close();
}


