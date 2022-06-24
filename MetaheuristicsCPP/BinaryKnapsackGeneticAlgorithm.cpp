#include "BinaryKnapsackGeneticAlgorithm.h"
#include <algorithm>
using namespace Optimizers;

CBinaryKnapsackGeneticAlgorithm::CBinaryKnapsackGeneticAlgorithm(CBinaryKnapsackEvaluation &cBinaryKnapsackEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGenerator, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, IBinaryKnapsackSelection &cBinaryKnapsackSelection, mt19937 &cRandomEngine, int iPopulationSize, bool stuckness = false)
	: COptimizer<bool>(cBinaryKnapsackEvaluation, cStopCondition), c_binary_knapsack_evaluation(cBinaryKnapsackEvaluation), c_generator(cGenerator), c_binary_knapsack_selection(cBinaryKnapsackSelection), c_crossover(cCrossover), c_mutation(cMutation), c_random_engine(cRandomEngine), i_population_size(iPopulationSize), bestmean(5)
{
	pv_population = new vector<CBinaryKnapsackIndividual*>();
	bEscapeStuck = stuckness;
}//CBinaryKnapsackGeneticAlgorithm::CBinaryKnapsackGeneticAlgorithm(CBinaryKnapsackEvaluation &cBinaryKnapsackEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGenerator, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, IBinaryKnapsackSelection &cBinaryKnapsackSelection, mt19937 &cRandomEngine, int iPopulationSize)

CBinaryKnapsackGeneticAlgorithm::~CBinaryKnapsackGeneticAlgorithm()
{
	VectorUtils::vClear(*pv_population);
	delete pv_population;
}//CBinaryKnapsackGeneticAlgorithm::~CBinaryKnapsackGeneticAlgorithm()

void CBinaryKnapsackGeneticAlgorithm::v_initialize(clock_t tStartTime)
{
	VectorUtils::vClear(*pv_population);
	pv_population->reserve((size_t)i_population_size);

	for (int i = 0; i < i_population_size; i++)
	{
		pv_population->push_back(pc_create_individual());
	}//for (int i = 0; i < i_population_size; i++)

	v_evaluation();
	b_check_new_best();
}//void CBinaryKnapsackGeneticAlgorithm::v_initialize(clock_t tStartTime)

bool CBinaryKnapsackGeneticAlgorithm::b_run_iteration(long long iIterationNumber, clock_t tStartTime)
{
	v_selection();

	v_crossover();
	v_evaluation();

	bool b_new_best = b_check_new_best();

	v_mutation();
	v_evaluation();
	if (bEscapeStuck) {
		v_check_stuck();
	}


	return b_check_new_best() || b_new_best;
}//bool CBinaryKnapsackGeneticAlgorithm::b_run_iteration(long long iIterationNumber, clock_t tStartTime)

void CBinaryKnapsackGeneticAlgorithm::v_evaluation()
{
	for (size_t i = 0; i < pv_population->size(); i++)
	{
		pv_population->at(i)->dEvaluate();
	}//for (size_t i = 0; i < pv_population->size(); i++)
}//void CBinaryKnapsackGeneticAlgorithm::v_evaluation()

void CBinaryKnapsackGeneticAlgorithm::v_selection()
{
	c_binary_knapsack_selection.vSelect(&pv_population);
}//void CBinaryKnapsackGeneticAlgorithm::v_selection()

void CBinaryKnapsackGeneticAlgorithm::v_crossover()
{
	vector<CBinaryKnapsackIndividual*> *pv_new_population = new vector<CBinaryKnapsackIndividual*>();
	pv_new_population->reserve(pv_population->size());

	vector<size_t> v_indexes(pv_population->size());

	iota(v_indexes.begin(), v_indexes.end(), 0);
	shuffle(v_indexes.begin(), v_indexes.end(), c_random_engine);

	CBinaryKnapsackIndividual *pc_parent_0, *pc_parent_1, *pc_child_0, *pc_child_1;
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
}//void CBinaryKnapsackGeneticAlgorithm::v_crossover()

void CBinaryKnapsackGeneticAlgorithm::v_mutation()
{
	for (size_t i = 0; i < pv_population->size(); i++)
	{
		pv_population->at(i)->bMutate();
	}//for (size_t i = 0; i < pv_population->size(); i++)
}
void Optimizers::CBinaryKnapsackGeneticAlgorithm::v_check_stuck()
{
	std::sort(pv_population->begin(), pv_population->end());
	size_t tenth_perc = size_t(pv_population->size() * 0.1);
	double sum = std::accumulate(pv_population->end() - tenth_perc, pv_population->end(), 0.0);
	double mean = sum / pv_population->size();
	bestmean.insert(mean);
	if (bestmean.is_full()) {
		auto rsd = bestmean.get_rsd();
		if (rsd < 0.05) {
			global_mutation();
		}
	}


}
void Optimizers::CBinaryKnapsackGeneticAlgorithm::global_mutation()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(pv_population->begin(), pv_population->end(), g);
	for (auto idx = 0; idx < (pv_population->size() / 3); ++idx) {
		pv_population->at(idx)->bMutate();
	}
}
//void CBinaryKnapsackGeneticAlgorithm::v_mutation()

bool CBinaryKnapsackGeneticAlgorithm::b_check_new_best(bool bOnlyImprovements)
{
	CBinaryKnapsackIndividual *pc_current_best_individual = pv_population->front();

	for (size_t i = 1; i < pv_population->size(); i++)
	{
		if (pv_population->at(i)->dGetFitness() > pc_current_best_individual->dGetFitness())
		{
			pc_current_best_individual = pv_population->at(i);
		}//if (pv_population->at(i)->dGetFitness() > pc_current_best_individual->dGetFitness())
	}//for (size_t i = 1; i < pv_population->size(); i++)

	return COptimizer<bool>::b_check_new_best(pc_current_best_individual->vGetGenotype(), pc_current_best_individual->dGetFitness(), bOnlyImprovements);
}//bool CBinaryKnapsackGeneticAlgorithm::b_check_new_best(bool bOnlyImprovements)

CBinaryKnapsackIndividual * CBinaryKnapsackGeneticAlgorithm::pc_create_individual(vector<bool> *pvGenotype)
{
	if (pvGenotype == nullptr)
	{
		pvGenotype = c_generator.pvCreate(c_evaluation.iGetSize());
	}//if (pvGenotype == nullptr)

	return new CBinaryKnapsackIndividual(pvGenotype, c_binary_knapsack_evaluation, c_mutation);
}//CBinaryKnapsackIndividual * CBinaryKnapsackGeneticAlgorithm::pc_create_individual(vector<bool> *pvGenotype)

std::tuple<size_t, float> CBinaryKnapsackGeneticAlgorithm::count_ill_solutions() {
	std::vector<Optimizers::CBinaryKnapsackIndividual*>::iterator iter, end;
	size_t count = 0;
	float acc = 0;
	for (iter = pv_population->begin(), end = pv_population->end(); iter != end; ++iter) {
		CBinaryKnapsackIndividual ind = *(*iter);
		float ind_weight = c_binary_knapsack_evaluation.dCalculateWeight(ind.vGetGenotype());
		if (ind_weight > c_binary_knapsack_evaluation.dGetCapacity()) {
			++count;
			acc += (ind_weight - c_binary_knapsack_evaluation.dGetCapacity()) ;
		}
	}
	return std::make_pair(count, acc / count);
}

float Optimizers::SimpleRingBuffer::get_rsd() const
{
	double sum = std::accumulate(std::begin(buffer), std::end(buffer), 0.0);
	double m = sum / buffer.size();

	double accum = 0.0;
	std::for_each(std::begin(buffer), std::end(buffer), [&](const double d) {
		accum += (d - m) * (d - m);
		});

	double stdev = sqrt(accum / (buffer.size() - 1));
	return stdev / m;
}

void Optimizers::SimpleRingBuffer::insert(float val)
{
	if (buffer.size() != max_size) {
		buffer.push_back(val);
		index += 1;
	}
	else {
		if (index == buffer.size()) {
			index = 0;
		}
		buffer[index] = val;
		index += 1;
	}
}
