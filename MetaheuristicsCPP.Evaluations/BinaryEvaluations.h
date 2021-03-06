#pragma once

#include "BinaryEvaluationInstances.h"
#include "BinaryConstraints.h"
#include "Constraint.h"
#include "Evaluation.h"
#include "P3Configuration.h"
#include "P3Evaluation.h"

#include <cmath>
#include <fstream>
#include <string>
#include <vector>

using namespace Constraints;

namespace Evaluations
{
	enum class EEvolutionaryPressure
	{
		NONE,
		PUNISHABLE,
		BALDWIN,
		LAMARCK
	};

	class CBinaryEvaluation : public CEvaluation<bool>
	{
	public:
		CBinaryEvaluation(int iSize, double dMaxValue);

		virtual IConstraint<bool>& cGetConstraint() { return c_constraint; }

	private:
		CBinaryNoConstraint c_constraint;
	};//class CBinaryEvaluation : public IEvaluation<bool>


	class CBinaryOneMaxEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryOneMaxEvaluation(int iSize);

	protected:
		virtual double d_evaluate(vector<bool>& vSolution);
	};//class CBinaryOneMaxEvaluation : public CBinaryEvaluation


	class CBinaryDeceptiveConcatenationEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, double dMaxValue, bool randomize = false);

	protected:
		virtual double d_evaluate(vector<bool>& vSolution);

		virtual double d_evaluate(int iUnitation) = 0;

		int i_block_size;

	private:
		std::vector<size_t> order;
		int i_number_of_blocks;
	};//class CBinaryDeceptiveConcatenationEvaluation : public CBinaryEvaluation


	class CBinaryStandardDeceptiveConcatenationEvaluation : public CBinaryDeceptiveConcatenationEvaluation
	{
	public:
		CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, bool randomize = false);

	protected:
		virtual double d_evaluate(int iUnitation);
	};//class CBinaryStandardDeceptiveConcatenationEvaluation : public CBinaryEvaluation


	class CBinaryBimodalDeceptiveConcatenationEvaluation : public CBinaryDeceptiveConcatenationEvaluation
	{
	public:
		CBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, bool randomize = false);

	protected:
		virtual double d_evaluate(int iUnitation);
	};//class CBinaryBimodalDeceptiveConcatenationEvaluation : public CBinaryDeceptiveConcatenationEvaluation

	class CBinaryStandardStepDeceptiveConcatenationEvaluation : public CBinaryDeceptiveConcatenationEvaluation
	{
	public:
		CBinaryStandardStepDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, int step, bool randomize = false);
	protected:
		virtual double d_evaluate(int iUnitation);
	private:
		int step;
	};


	class CBinaryIsingSpinGlassEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed = 0);

		virtual ~CBinaryIsingSpinGlassEvaluation();

	protected:
		virtual double d_evaluate(vector<bool>& vSolution);

	private:
		IsingSpinGlass* pc_p3_ising_spin_glass;
	};//class CBinaryIsingSpinGlassEvaluation : public CBinaryEvaluation


	class CBinaryMax3SatEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryMax3SatEvaluation(int iSize, int iProblemSeed = 0, float fClauseRatio = 4.27f);

		virtual ~CBinaryMax3SatEvaluation();

	protected:
		virtual double d_evaluate(vector<bool>& vSolution);

	private:
		MAXSAT* pc_p3_max_sat;
	};//class CBinaryMax3SatEvaluation : public CBinaryEvaluation


	class CBinaryNKLandscapesEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed = 0);

		virtual ~CBinaryNKLandscapesEvaluation();

	protected:
		virtual double d_evaluate(vector<bool>& vSolution);

	private:
		NearestNeighborNK* pc_p3_nk_landscapes;
	};//class CBinaryNKLandscapesEvaluation : public CBinaryEvaluation


	class CBinaryKnapsackEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryKnapsackEvaluation(EBinaryKnapsackInstance eInstance, EEvolutionaryPressure pressuremode);

		double dCalculateWeight(vector<bool>& vSolution);

		vector<double>& vGetWeights() { return v_weights; }
		vector<double>& vGetProfits() { return v_profits; }
		double dGetCapacity() { return d_capacity; }
		EEvolutionaryPressure EGetPressureMode() { return EPressureMode; }

	protected:
		virtual double d_evaluate(vector<bool>& vSolution);

	private:
		EEvolutionaryPressure EPressureMode;
		void v_load(EBinaryKnapsackInstance eInstance);
		void v_load_definition_file(string& sDefinitionFilePath);
		void v_load_optimum_file(string& sOptimumFilePath);

		vector<double> v_weights;
		vector<double> v_profits;
		double d_capacity;
	};//class CBinaryKnapsackEvaluation : public CBinaryEvaluation


}//namespace Evaluations
