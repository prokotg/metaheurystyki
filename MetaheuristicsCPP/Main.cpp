#include "BinaryRandomSearch.h"
#include "OptimizationResult.h"
#include "RealCMAES.h"
#include "RealEvolutionStrategy11.h"
#include "RealMutations.h"
#include "RealMutationES11Adaptations.h"
#include "StopConditions.h"

#include <BinaryEvaluations.h>
#include <iostream>

#include <random>
#include <sstream>
#include <RealEvaluations.h>
#include "Lab1.h"

using namespace Optimizers;
using namespace StopConditions;

using namespace Evaluations;
using namespace std;






//
//void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
//{
//	CRealSphereEvaluation c_sphere_evaluation(gene_length);
//
//	CIterationsStopCondition c_stop_condition(c_sphere_evaluation.dGetMaxValue(), 1000);
//
//	CRealCMAES c_cmaes(c_sphere_evaluation, c_stop_condition, cRandomEngine, 1);
//
//	c_cmaes.vRun();
//
//	v_report_optimization_result(*c_cmaes.pcGetResult());
//}//void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)
//
//void v_lab_3_sphere_10_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
//{
//	CRealSphere10Evaluation c_sphere_10_evaluation(gene_length);
//
//	CIterationsStopCondition c_stop_condition(c_sphere_10_evaluation.dGetMaxValue(), 1000);
//
//	CRealCMAES c_cmaes(c_sphere_10_evaluation, c_stop_condition, cRandomEngine, 1);
//
//	c_cmaes.vRun();
//
//	v_report_optimization_result(*c_cmaes.pcGetResult());
//}//void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)
//
//void v_lab_3_ellipsoid_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
//{
//	CRealEllipsoidEvaluation c_ellipsoid_evaluation(gene_length);
//
//	CIterationsStopCondition c_stop_condition(c_ellipsoid_evaluation.dGetMaxValue(), 1000);
//
//	CRealCMAES c_cmaes(c_ellipsoid_evaluation, c_stop_condition, cRandomEngine, 1);
//
//	c_cmaes.vRun();
//
//	v_report_optimization_result(*c_cmaes.pcGetResult());
//}//void v_lab_3_ellipsoid_cmaes(mt19937 &cRandomEngine)
//
//void v_lab_3_step_2_sphere_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
//{
//	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(gene_length);
//
//	CIterationsStopCondition c_stop_condition(c_step_2_sphere_evaluation.dGetMaxValue(), 1000);
//
//	CRealCMAES c_cmaes(c_step_2_sphere_evaluation, c_stop_condition, cRandomEngine, 1);
//
//	c_cmaes.vRun();
//
//	v_report_optimization_result(*c_cmaes.pcGetResult());
//}//void v_lab_3_step_2_sphere_cmaes(mt19937 &cRandomEngine)
//
//void v_lab_3_rastrigin_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
//{
//	CRealRastriginEvaluation c_rastrigin_evaluation(gene_length);
//
//	CIterationsStopCondition c_stop_condition(c_rastrigin_evaluation.dGetMaxValue(), 1000);
//
//	CRealCMAES c_cmaes(c_rastrigin_evaluation, c_stop_condition, cRandomEngine, 1);
//
//	c_cmaes.vRun();
//
//	v_report_optimization_result(*c_cmaes.pcGetResult());
//}//void v_lab_3_rastrigin_cmaes(mt19937 &cRandomEngine)
//
//void v_lab_3_ackley_cmaes(mt19937 &cRandomEngine, int64_t gene_length = 10)
//{
//	CRealAckleyEvaluation c_ackley_evaluation(gene_length);
//
//	CIterationsStopCondition c_stop_condition(c_ackley_evaluation.dGetMaxValue(), 1000);
//
//	CRealCMAES c_cmaes(c_ackley_evaluation, c_stop_condition, cRandomEngine, 1);
//
//	c_cmaes.vRun();
//
//	v_report_optimization_result(*c_cmaes.pcGetResult());
//}//void v_lab_3_ackley_cmaes(mt19937 &cRandomEngine)
//
//void v_lab_2_sphere(mt19937 &cRandomEngine, int64_t gene_length = 2)
//{
//	CRealSphereEvaluation c_sphere_evaluation(gene_length);
//
//	vector<double> v_sigmas((size_t)c_sphere_evaluation.iGetSize(), 0.1);
//
//	CIterationsStopCondition c_stop_condition(c_sphere_evaluation.dGetMaxValue(), 10000);
//	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_evaluation, cRandomEngine);
//	//CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);
//	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);
//
//	CRealEvolutionStrategy11 c_es11(c_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);
//
//	c_es11.vRun();
//
//	v_report_optimization_result(*c_es11.pcGetResult());
//}//void v_lab_2_sphere(mt19937 &cRandomEngine)
//
//void v_lab_2_sphere_10(mt19937 &cRandomEngine, int64_t gene_length = 2)
//{
//	CRealSphere10Evaluation c_sphere_10_evaluation(gene_length);
//
//	vector<double> v_sigmas((size_t)c_sphere_10_evaluation.iGetSize(), 0.1);
//
//	CIterationsStopCondition c_stop_condition(c_sphere_10_evaluation.dGetMaxValue(), 1000);
//	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_10_evaluation, cRandomEngine);
//	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);
//
//	CRealEvolutionStrategy11 c_es11(c_sphere_10_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);
//
//	c_es11.vRun();
//
//	v_report_optimization_result(*c_es11.pcGetResult());
//}//void v_lab_2_sphere_10(mt19937 &cRandomEngine)
//
//void v_lab_2_ellipsoid(mt19937 &cRandomEngine, int64_t gene_length = 2)
//{
//	CRealEllipsoidEvaluation c_ellipsoid_evaluation(gene_length);
//
//	vector<double> v_sigmas((size_t)c_ellipsoid_evaluation.iGetSize(), 1);
//
//	CIterationsStopCondition c_stop_condition(c_ellipsoid_evaluation.dGetMaxValue(), 1000);
//	CRealGaussianMutation c_mutation(v_sigmas, c_ellipsoid_evaluation, cRandomEngine);
//	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);
//
//	CRealEvolutionStrategy11 c_es11(c_ellipsoid_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);
//
//	c_es11.vRun();
//
//	v_report_optimization_result(*c_es11.pcGetResult());
//}//void v_lab_2_ellipsoid(mt19937 &cRandomEngine)
//
//void v_lab_2_step_2_sphere(mt19937 &cRandomEngine, int64_t gene_length = 2)
//{
//	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(gene_length);
//
//	vector<double> v_sigmas((size_t)c_step_2_sphere_evaluation.iGetSize(), 0.1);
//
//	CIterationsStopCondition c_stop_condition(c_step_2_sphere_evaluation.dGetMaxValue(), 1000);
//	CRealGaussianMutation c_mutation(v_sigmas, c_step_2_sphere_evaluation, cRandomEngine);
//	CRealOneFifthRuleMutationES11Adaptation c_mutation_adaptation(200, 1.5 , c_mutation);
//
//	CRealEvolutionStrategy11 c_es11(c_step_2_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);
//
//	c_es11.vRun();
//
//	v_report_optimization_result(*c_es11.pcGetResult());
//}//void v_lab_2_step_2_sphere(mt19937 &cRandomEngine)



int main()
{


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


	// ########################### >>  LAB 1  RANDOM SEARCH << ###########################




	run_lab_1();
	/*v_lab_1_standard_deceptive_concatenation(c_random_engine);
	v_lab_1_bimodal_deceptive_concatenation(c_random_engine);
	v_lab_1_ising_spin_glass(c_random_engine);
	v_lab_1_nk_landscapes(c_random_engine);*/
	system("PAUSE");
	return 0;
}//int main()