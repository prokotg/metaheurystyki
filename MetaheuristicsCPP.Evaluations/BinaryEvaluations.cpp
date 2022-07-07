#include "BinaryEvaluations.h"
#include <cmath>

using namespace Evaluations;

CBinaryEvaluation::CBinaryEvaluation(int iSize, double dMaxValue)
	: CEvaluation<bool>(iSize, dMaxValue)
{

}//CBinaryEvaluation::CBinaryEvaluation(int iSize, double dMaxValue)


CBinaryOneMaxEvaluation::CBinaryOneMaxEvaluation(int iSize)
	: CBinaryEvaluation(iSize, iSize)
{

}//CBinaryOneMaxEvaluation::CBinaryOneMaxEvaluation(int iSize)

double CBinaryOneMaxEvaluation::d_evaluate(vector<bool>& vSolution)
{
	double d_value = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		if (vSolution[i])
		{
			d_value++;
		}//if (vSolution[i])
	}//for (int i = 0; i < iGetSize(); i++)

	return d_value;
}//double CBinaryOneMaxEvaluation::d_evaluate(vector<bool> &cCoding)


CBinaryDeceptiveConcatenationEvaluation::CBinaryDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, double dMaxValue, bool randomize)
	: CBinaryEvaluation(iBlockSize* iNumberOfBlocks, dMaxValue), i_block_size(iBlockSize), i_number_of_blocks(iNumberOfBlocks)
{
	order = std::vector<size_t>(iBlockSize * iNumberOfBlocks);
	std:iota(order.begin(), order.end(), 0);
	if (randomize) {
		std::random_device rd;
		std::mt19937 g(0);
		std::shuffle(order.begin(), order.end(), g);
		for (size_t idx = 0; idx < 10; ++idx) {
			std::cout << order[idx] << ", ";
		}
		std::cout << std::endl;
	}

}//CBinaryDeceptiveConcatenationEvaluation::CBinaryDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, double dMaxValue)

double CBinaryDeceptiveConcatenationEvaluation::d_evaluate(vector<bool>& vSolution)
{
	double d_value = 0;

	int i_unitation;

	for (int i = 0; i < i_number_of_blocks; i++)
	{
		i_unitation = 0;

		for (int j = 0; j < i_block_size; j++)
		{
			size_t index = order[i * i_block_size + j];
			if (vSolution[index])
			{
				i_unitation++;
			}//if (vSolution[i * i_block_size + j])
		}//for (int j = 0; j < i_block_size; j++)

		d_value += d_evaluate(i_unitation);
	}//for (int i = 0; i < i_number_of_blocks; i++)

	return d_value;
}//double CBinaryDeceptiveConcatenationEvaluation::d_evaluate(vector<bool> &vSolution)


CBinaryStandardDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, bool randomize)
	: CBinaryDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks, iBlockSize* iNumberOfBlocks, randomize)
{

}//CBinaryStandardDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)

double CBinaryStandardDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)
{
	double d_value;

	if (iUnitation == i_block_size)
	{
		d_value = i_block_size;
	}//if (iUnitation == i_block_size)
	else
	{
		d_value = i_block_size - 1 - iUnitation;
	}//else if (iUnitation == i_block_size)

	return d_value;
}//double CBinaryStandardDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)


CBinaryBimodalDeceptiveConcatenationEvaluation::CBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, bool randomize)
	: CBinaryDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks, iBlockSize* iNumberOfBlocks / 2.0, randomize)
{

}//CBinaryBimodalDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)

double CBinaryBimodalDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)
{
	double d_value;

	if (iUnitation == i_block_size || iUnitation == 0)
	{
		d_value = i_block_size / 2.0;
	}//if (iUnitation == i_block_size)
	else
	{
		d_value = i_block_size / 2.0 - abs(iUnitation - i_block_size / 2.0) - 1;
	}//else if (iUnitation == i_block_size)

	return d_value;
}//double CBinaryBimodalDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)


CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed)
	: CBinaryEvaluation(iSize, 1.0)
{
	Configuration c_config;

	c_config.set("length", iSize);
	c_config.set("precision", 65536);
	c_config.set("problem_seed", iProblemSeed);
	c_config.set("problem_folder", string("EvaluationsInputs\\"));
	c_config.set("ising_type", string("pm"));

	pc_p3_ising_spin_glass = new IsingSpinGlass(c_config, 0);
}//CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed)

CBinaryIsingSpinGlassEvaluation::~CBinaryIsingSpinGlassEvaluation()
{
	delete pc_p3_ising_spin_glass;
}//CBinaryIsingSpinGlassEvaluation::~CBinaryIsingSpinGlassEvaluation()

double CBinaryIsingSpinGlassEvaluation::d_evaluate(vector<bool>& vSolution)
{
	return pc_p3_ising_spin_glass->evaluate(vSolution);
}//double CBinaryIsingSpinGlassEvaluation::d_evaluate(vector<bool> &vSolution)


CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio)
	: CBinaryEvaluation(iSize, 1.0)
{
	Configuration c_config;

	c_config.set("length", iSize);
	c_config.set("precision", 65536);
	c_config.set("problem_seed", iProblemSeed);
	c_config.set("clause_ratio", fClauseRatio);

	pc_p3_max_sat = new MAXSAT(c_config, 0);
}//CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio)

CBinaryMax3SatEvaluation::~CBinaryMax3SatEvaluation()
{
	delete pc_p3_max_sat;
}//CBinaryMax3SatEvaluation::~CBinaryMax3SatEvaluation()

double CBinaryMax3SatEvaluation::d_evaluate(vector<bool>& vSolution)
{
	return pc_p3_max_sat->evaluate(vSolution);
}//double CBinaryMax3SatEvaluation::d_evaluate(vector<bool> &vSolution)


CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed)
	: CBinaryEvaluation(iSize, 1.0)
{
	Configuration c_config;

	c_config.set("length", iSize);
	c_config.set("precision", 65536);
	c_config.set("problem_seed", iProblemSeed);
	c_config.set("k", 5);
	c_config.set("problem_folder", string("EvaluationsInputs\\"));

	pc_p3_nk_landscapes = new NearestNeighborNK(c_config, 0);
}//CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed)

CBinaryNKLandscapesEvaluation::~CBinaryNKLandscapesEvaluation()
{
	delete pc_p3_nk_landscapes;
}//CBinaryNKLandscapesEvaluation::~CBinaryNKLandscapesEvaluation()

double CBinaryNKLandscapesEvaluation::d_evaluate(vector<bool>& vSolution)
{
	return pc_p3_nk_landscapes->evaluate(vSolution);
}//double CBinaryNKLandscapesEvaluation::d_evaluate(vector<bool> &vSolution)


CBinaryKnapsackEvaluation::CBinaryKnapsackEvaluation(EBinaryKnapsackInstance eInstance, EEvolutionaryPressure pressuremode)
	: CBinaryEvaluation(0, 0), EPressureMode(pressuremode)
{
	v_load(eInstance);

}//CBinaryKnapsackEvaluation::CBinaryKnapsackEvaluation(EBinaryKnapsackInstance eInstance)

double CBinaryKnapsackEvaluation::dCalculateWeight(vector<bool>& vSolution)
{
	double d_weight = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		if (vSolution[i])
		{
			d_weight += v_weights[i];
		}//if (vSolution[i])
	}//for (int i = 0; i < iGetSize(); i++)

	return d_weight;
}//double CBinaryKnapsackEvaluation::dCalculateWeight(vector<bool> &vSolution)

double CBinaryKnapsackEvaluation::d_evaluate(vector<bool>& vSolution)
{
	double d_value = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		if (vSolution[i])
		{
			d_value += v_profits[i];
		}//if (vSolution[i])
	}//for (int i = 0; i < iGetSize(); i++)

	return d_value;
}//double CBinaryKnapsackEvaluation::d_evaluate(vector<bool> &vSolution)

void CBinaryKnapsackEvaluation::v_load(EBinaryKnapsackInstance eInstance)
{
	SBinaryKnapsackInstanceFilePaths* pc_file_paths = SBinaryKnapsackInstanceFilePaths::pcCreate(eInstance);

	v_load_definition_file(pc_file_paths->sDefinitionFilePath);
	v_load_optimum_file(pc_file_paths->sOptimumFilePath);

	delete pc_file_paths;
}//void CBinaryKnapsackEvaluation::v_load(EBinaryKnapsackInstance eInstance)

void CBinaryKnapsackEvaluation::v_load_definition_file(string& sDefinitionFilePath)
{
	ifstream f_definition_file(sDefinitionFilePath);

	if (!f_definition_file)
	{
		throw invalid_argument(sDefinitionFilePath + " not found");
	}//if (!f_definition_file)

	int i_size;
	f_definition_file >> i_size;
	v_set_size(i_size);

	f_definition_file >> d_capacity;

	double d_profit, d_weight;

	v_profits.clear();
	v_profits.reserve((size_t)i_size);

	v_weights.clear();
	v_weights.reserve((size_t)i_size);

	for (int i = 0; i < i_size; i++)
	{
		f_definition_file >> d_profit;
		f_definition_file >> d_weight;

		v_profits.push_back(d_profit);
		v_weights.push_back(d_weight);
	}//for (int i = 0; i < i_size; i++)

	f_definition_file.close();
}//void CBinaryKnapsackEvaluation::v_load_definition_file(string &sDefinitionFilePath)

void CBinaryKnapsackEvaluation::v_load_optimum_file(string& sOptimumFilePath)
{
	ifstream f_optimum_file(sOptimumFilePath);

	if (!f_optimum_file)
	{
		throw invalid_argument(sOptimumFilePath + " not found");
	}//if (!f_optimum_file)

	double d_max_value;
	f_optimum_file >> d_max_value;
	v_set_max_value(d_max_value);

	f_optimum_file.close();
}//void CBinaryKnapsackEvaluation::v_load_optimum_file(string &sOptimumFilePath)

Evaluations::CBinaryStandardStepDeceptiveConcatenationEvaluation::CBinaryStandardStepDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, int step, bool randomize):
	CBinaryDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks, iNumberOfBlocks * floor( ((iBlockSize - step) % step + iBlockSize) / step ), randomize), step(step)
{

}

double Evaluations::CBinaryStandardStepDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)
{
	double d_value;

	if (iUnitation == i_block_size)
	{
		d_value = i_block_size;
	}//if (iUnitation == i_block_size)
	else
	{
		d_value = i_block_size - 1 - iUnitation;
	}//else if (iUnitation == i_block_size)

	return floor(((i_block_size - step) % step + d_value) / step);
}
