#include "BinaryRandomSearch.h"
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


template <typename TElement>
void v_report_optimization_result(COptimizationResult<TElement> &cOptimizationResult)
{
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << std::endl;
	cout << "value: " << cOptimizationResult.dGetBestValue() << endl;
	cout << "\twhen (time): " << cOptimizationResult.dGetBestTime() << " s" << endl;
	cout << "\twhen (iteration): " << cOptimizationResult.iGetBestIteration() << endl;
	cout << "\twhen (FFE): " << cOptimizationResult.iGetBestFFE() << endl;
}//void v_report_optimization_result(COptimizationResult<TElement> &cOptimizationResult)

template <typename TElement>
void report_to_file(std::ofstream& file, std::string run_name, int64_t gene_length, int64_t run_id, COptimizationResult<TElement>& cOptimizationResult) {



	file << run_name << "," << gene_length << "," << run_id << ",";
	file << cOptimizationResult.dGetBestValue() << ",";
	file << cOptimizationResult.dGetBestTime() << ",";
	file << cOptimizationResult.iGetBestIteration() << ",";
	file << cOptimizationResult.iGetBestFFE() << ",";
	file << endl;
}

void initialize_result_file(std::ofstream& ofs) {
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << "C:\\mount_dummy\\" << "metresults_" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ".csv";
	ofs.open(oss.str(), ios::out);

	// treat ofs as csv file, initialize columns

	ofs << "name" << ",";
	ofs << "gene_length" << ",";
	ofs << "run_id" << ",";
	ofs << "best_value" << ",";
	ofs << "best_time" << ",";
	ofs << "best_iteration" << ",";
	ofs << "best_ffe" << "," << std::endl;

}


void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
{
	CRealSphereEvaluation c_sphere_evaluation(gene_length);

	CIterationsStopCondition c_stop_condition(c_sphere_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_sphere_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)

void v_lab_3_sphere_10_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
{
	CRealSphere10Evaluation c_sphere_10_evaluation(gene_length);

	CIterationsStopCondition c_stop_condition(c_sphere_10_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_sphere_10_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)

void v_lab_3_ellipsoid_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
{
	CRealEllipsoidEvaluation c_ellipsoid_evaluation(gene_length);

	CIterationsStopCondition c_stop_condition(c_ellipsoid_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_ellipsoid_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_ellipsoid_cmaes(mt19937 &cRandomEngine)

void v_lab_3_step_2_sphere_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
{
	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(gene_length);

	CIterationsStopCondition c_stop_condition(c_step_2_sphere_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_step_2_sphere_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_step_2_sphere_cmaes(mt19937 &cRandomEngine)

void v_lab_3_rastrigin_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
{
	CRealRastriginEvaluation c_rastrigin_evaluation(gene_length);

	CIterationsStopCondition c_stop_condition(c_rastrigin_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_rastrigin_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_rastrigin_cmaes(mt19937 &cRandomEngine)

void v_lab_3_ackley_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
{
	CRealAckleyEvaluation c_ackley_evaluation(gene_length);

	CIterationsStopCondition c_stop_condition(c_ackley_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_ackley_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_ackley_cmaes(mt19937 &cRandomEngine)

void v_lab_2_sphere(mt19937 &cRandomEngine, int64_t gene_length = 2)
{
	CRealSphereEvaluation c_sphere_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_sphere_evaluation.dGetMaxValue(), 10000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_evaluation, cRandomEngine);
	//CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_sphere(mt19937 &cRandomEngine)

void v_lab_2_sphere_10(mt19937 &cRandomEngine, int64_t gene_length = 2)
{
	CRealSphere10Evaluation c_sphere_10_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_sphere_10_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_sphere_10_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_10_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_10_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_sphere_10(mt19937 &cRandomEngine)

void v_lab_2_ellipsoid(mt19937 &cRandomEngine, int64_t gene_length = 2)
{
	CRealEllipsoidEvaluation c_ellipsoid_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_ellipsoid_evaluation.iGetSize(), 1);

	CIterationsStopCondition c_stop_condition(c_ellipsoid_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_ellipsoid_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);

	CRealEvolutionStrategy11 c_es11(c_ellipsoid_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_ellipsoid(mt19937 &cRandomEngine)

void v_lab_2_step_2_sphere(mt19937 &cRandomEngine, int64_t gene_length = 2)
{
	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(gene_length);

	vector<double> v_sigmas((size_t)c_step_2_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_step_2_sphere_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_step_2_sphere_evaluation, cRandomEngine);
	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);

	CRealEvolutionStrategy11 c_es11(c_step_2_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_step_2_sphere(mt19937 &cRandomEngine)

COptimizationResult<bool> v_lab_1_one_max(mt19937& cRandomEngine, ofstream& result_file, int64_t gene_length = 5)
{
	CBinaryOneMaxEvaluation c_evaluation(gene_length);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();
	return *c_random_search.pcGetResult();
}//void v_lab_1_one_max(mt19937 &cRandomEngine)

void v_lab_1_standard_deceptive_concatenation(mt19937 &cRandomEngine, int64_t gene_length = 5)
{
	int64_t block_size = gene_length / 5;
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(gene_length, block_size);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_standard_deceptive_concatenation(mt19937 &cRandomEngine)

void v_lab_1_bimodal_deceptive_concatenation(mt19937 &cRandomEngine, int64_t gene_length = 10)
{
	int64_t block_size = gene_length / 10;
	CBinaryBimodalDeceptiveConcatenationEvaluation c_evaluation(gene_length, block_size);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_bimodal_deceptive_concatenation(mt19937 &cRandomEngine)

void v_lab_1_ising_spin_glass(mt19937 &cRandomEngine, int64_t gene_length = 25)
{
	CBinaryIsingSpinGlassEvaluation c_evaluation(25);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_ising_spin_glass(mt19937 &cRandomEngine)

void v_lab_1_nk_landscapes(mt19937 &cRandomEngine, int64_t gene_length = 10)
{
	CBinaryNKLandscapesEvaluation c_evaluation(gene_length);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_nk_landscapes(mt19937 &cRandomEngine)

int main()
{
	ofstream myfile;
	initialize_result_file(myfile);


	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());

	/*v_lab_3_sphere_cmaes(c_random_engine);
	v_lab_3_sphere_10_cmaes(c_random_engine);
	v_lab_3_ellipsoid_cmaes(c_random_engine);
	v_lab_3_step_2_sphere_cmaes(c_random_engine);
	v_lab_3_rastrigin_cmaes(c_random_engine);
	v_lab_3_ackley_cmaes(c_random_engine);
	*/
	//v_lab_2_sphere(c_random_engine);
	//v_lab_2_sphere_10(c_random_engine);
	//v_lab_2_ellipsoid(c_random_engine);
	//v_lab_2_step_2_sphere(c_random_engine);
	std::list<int> gene_lengths = { 5, 10, 50 };
	for (size_t run_id = 0; run_id < 10; run_id++) {
		for (const int& gen_len : gene_lengths) {
			auto res = v_lab_1_one_max(c_random_engine, myfile, gen_len);
			report_to_file(myfile, std::string("one_max"), gen_len, run_id, res);
		}
	}


	myfile.close();
	/*v_lab_1_standard_deceptive_concatenation(c_random_engine);
	v_lab_1_bimodal_deceptive_concatenation(c_random_engine);
	v_lab_1_ising_spin_glass(c_random_engine);
	v_lab_1_nk_landscapes(c_random_engine);*/
	system("PAUSE");
	return 0;
}//int main()