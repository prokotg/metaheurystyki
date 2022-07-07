#include "BinaryGeneticAlgorithm.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace Optimizers;

CBinaryGeneticAlgorithm::CBinaryGeneticAlgorithm(IEvaluation<bool> &cEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGeneration, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, ISelection<bool> &cSelection, mt19937 &cRandomEngine, int iPopulationSize)
	: CPopulationOptimizer<bool>(cEvaluation, cStopCondition, cGeneration, cSelection, cMutation, iPopulationSize), c_crossover(cCrossover), c_random_engine(cRandomEngine)
{

}//CBinaryGeneticAlgorithm::CBinaryGeneticAlgorithm(IEvaluation<bool> &cEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGeneration, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, ISelection<bool> &cSelection,  mt19937 &cRandomEngine, int iPopulationSize)

bool CBinaryGeneticAlgorithm::b_run_iteration(long long iIterationNumber, clock_t tStartTime)
{
	v_selection();

	v_crossover();
	v_evaluation();
	//std::cout <<  std::endl << iIterationNumber << "|";
	bool b_new_best = b_check_new_best();
	//std::cout  <<  std::endl <<  "|";
	v_mutation();
	v_evaluation();
	check_stuck();
	auto n = b_check_new_best();
	//std::cout << "|";
	return  n || b_new_best;
	
}//bool CBinaryGeneticAlgorithm::b_run_iteration(long long iIterationNumber, clock_t tStartTime)

void CBinaryGeneticAlgorithm::v_crossover()
{
	vector<CIndividual<bool>*> *pv_new_population = new vector<CIndividual<bool>*>();
	pv_new_population->reserve(pv_population->size());

	vector<size_t> v_indexes(pv_population->size());
	
	iota(v_indexes.begin(), v_indexes.end(), 0);
	shuffle(v_indexes.begin(), v_indexes.end(), c_random_engine);

	CIndividual<bool> *pc_parent_0, *pc_parent_1, *pc_child_0, *pc_child_1;
	vector<bool> *pv_child_0_genotype, *pv_child_1_genotype;

	for (size_t i = 0; i < pv_population->size(); i += 2)
	{
		pc_parent_0 = pv_population->at(i + 0);
		pc_parent_1 = pv_population->at(i + 1);

		pv_child_0_genotype = new vector<bool>((size_t)c_evaluation.iGetSize());
		pv_child_1_genotype = new vector<bool>((size_t)c_evaluation.iGetSize());

		if (c_crossover.bCross(pc_parent_0->vGetGenotype(), pc_parent_1->vGetGenotype(), *pv_child_0_genotype, *pv_child_1_genotype))
		{
			delete pc_parent_0;
			delete pc_parent_1;

			pc_child_0 = pc_create_individual(pv_child_0_genotype);
			pc_child_1 = pc_create_individual(pv_child_1_genotype);

			pv_population->at(i + 0) = pc_child_0;
			pv_population->at(i + 1) = pc_child_1;
		}//if (c_crossover.bCross(pc_parent_0->vGetGenotype(), pc_parent_1->vGetGenotype(), *pv_child_0_genotype, *pv_child_1_genotype))
		else
		{
			delete pv_child_0_genotype;
			delete pv_child_1_genotype;
		}//else if (c_crossover.bCross(pc_parent_0->vGetGenotype(), pc_parent_1->vGetGenotype(), *pv_child_0_genotype, *pv_child_1_genotype))
	}//for (size_t i = 0; i < pv_population->size(); i += 2)
}
void Optimizers::CBinaryGeneticAlgorithm::check_stuck()
{
	std::sort(pv_population->begin(), pv_population->end());
	if (pv_population->at(pv_population->size()-1)->dGetFitness() == pv_population->at(int(pv_population->size() / 2))->dGetFitness()) {
		global_mutation();
	}
}
void Optimizers::CBinaryGeneticAlgorithm::global_mutation()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(pv_population->begin(), pv_population->end(), g);
	auto old_prob = c_mutation.dGetProbability();
	c_mutation.vSetProbability(0.5);
	for (auto idx = 0; idx < (pv_population->size()); ++idx) {
		pv_population->at(idx)->bMutate();
	}
	c_mutation.vSetProbability(old_prob);
}
//void CBinaryGeneticAlgorithm::v_crossover()


void Optimizers::DSM::calculate_single_ind(std::vector<bool> genotype)
{
	for (auto idx = 0; idx < genotype.size(); ++idx) {
		for (auto nidx = idx + 1; nidx < genotype.size(); ++nidx) {
			if (idx == nidx) {
				continue;
			}
			dsm[idx][nidx].increment_count(genotype[idx], genotype[nidx]);
		}
	}
}


void Optimizers::DSM::collect(std::vector<CIndividual<bool>*>* pv_population)
{
	for (auto ind : *pv_population) {
		auto gen = ind->vGetGenotype();
		calculate_single_ind(gen);
	}
}


const void Optimizers::DSM::to_file(std::string filename, int iteration)
{
	std::vector<std::vector<float>> mi = calculate_mi();
	std::ofstream ofs;
	std::ostringstream oss;
	
	oss << "C:\\mount_dummy\\" << filename << "_" << iteration << ".csv";
	ofs.open(oss.str(), ios::out);
	for (auto row = 0; row < mi.size(); ++row) {
		for (auto col = 0; col < mi.size(); ++col) {
			ofs << std::setprecision(2) <<  std::to_string(mi[row][col]) << ", ";
		}
		ofs << "\n";
	}

}

std::vector<std::vector<float>> Optimizers::DSM::calculate_mi()
{
	std::vector<std::vector<float>> mi;
	mi.resize(dsm.size(), std::vector<float>(dsm.size(), 0));
	for (auto idx = 0; idx < dsm.size(); ++idx) {
		for (auto nidx = idx + 1; nidx < dsm.size(); ++nidx) {
			if (idx == nidx) {
				continue;

			}
			mi[idx][nidx] = calculate_single_mi(idx, nidx);

		}
	}
	return mi;

}

float Optimizers::DSM::calculate_single_mi(size_t g1, size_t g2)
{
	return single_mi_part(g1, g2, 0, 0) + single_mi_part(g1, g2, 0, 1) + single_mi_part(g1, g2, 1, 0) + single_mi_part(g1, g2, 1, 1);
}

float Optimizers::DSM::single_mi_part(size_t g1, size_t g2, int v1, int v2)
{
	auto jp = dsm[g1][g2].get_joint_probabiloty(v1, v2);
	auto denom = dsm[g1][g2].get_gene_v_prob(0, v1) * dsm[g1][g2].get_gene_v_prob(1, v2);
	return jp * log(jp / denom);
}

Optimizers::CBinaryGeneticAlgorithmDSM::CBinaryGeneticAlgorithmDSM(IEvaluation<bool>& cEvaluation, IStopCondition& cStopCondition, IGenerator<bool>& cGeneration, ICrossover<bool>& cCrossover, IMutation<bool>& cMutation, ISelection<bool>& cSelection, mt19937& cRandomEngine, int iPopulationSize, std::string filepath):
	CBinaryGeneticAlgorithm(cEvaluation, cStopCondition, cGeneration, cCrossover, cMutation, cSelection, cRandomEngine, iPopulationSize), dsm_filepath(filepath), dsm(cEvaluation.iGetSize())
{
}

bool Optimizers::CBinaryGeneticAlgorithmDSM::b_run_iteration(long long iIterationNumber, clock_t tStartTime)
{
	bool res = CBinaryGeneticAlgorithm::b_run_iteration(iIterationNumber, tStartTime);
	dsm.collect(pv_population);
	if (iIterationNumber % 200 == 0 && iIterationNumber != 0) {
		
		dsm.collect(pv_population);
		dsm.to_file(dsm_filepath, iIterationNumber);
		//dsm = DSM(c_evaluation.iGetSize());
	}
	return res;
}
