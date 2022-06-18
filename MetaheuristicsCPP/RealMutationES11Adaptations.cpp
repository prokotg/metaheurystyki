#include "RealMutationES11Adaptations.h"
#include <iostream>
using namespace Mutations;


CRealNullRealMutationES11Adaptation::CRealNullRealMutationES11Adaptation(CRealGaussianMutation& cMutation)
	: c_mutation(cMutation)
{

}//CRealNullRealMutationES11Adaptation::CRealNullRealMutationES11Adaptation(CRealGaussianMutation &cMutation)


CRealOneFifthRuleMutationES11Adaptation::CRealOneFifthRuleMutationES11Adaptation(int iArchiveSize, double dModifier, CRealGaussianMutation& cMutation)
	: CRealNullRealMutationES11Adaptation(cMutation), i_archive_size(iArchiveSize), d_modifier(dModifier), i_successes_counter(0)
{

}//CRealOneFifthRuleMutationES11Adaptation::CRealOneFifthRuleMutationES11Adaptation(int iArchiveSize, double dModifier, CRealGaussianMutation &cMutation)

void CRealOneFifthRuleMutationES11Adaptation::vAdapt(double dBeforeMutationValue, vector<double>& vBeforeMutationSolution, double dAfterMutationValue, vector<double>& vAfterMutationSolution)
{

	// calculate distance and then pseudogradient



	//l_successes.push_back(dAfterMutationValue > dBeforeMutationValue);
	//double ratio = 1.0;
	//if (dAfterMutationValue > dBeforeMutationValue)
	//{
	//	i_successes_counter++;
	//	double ratio = dBeforeMutationValue / dAfterMutationValue ;
	//	double final_modifier = d_modifier * ratio;

	//	cGetMutation().vMultiplySigmas(1.0 / ratio);
	//	//std::cout << cGetMutation().dGetSigma(0) << std::endl;

	//}

	if (dAfterMutationValue > dBeforeMutationValue)


	while (l_successes.size() > (size_t)i_archive_size)
	{
		if (l_successes.front())
		{
			i_successes_counter--;
		}//if (l_successes.front())

		l_successes.pop_front();
	}//while (l_successes.size() > (size_t)i_archive_size)

	if (l_successes.size() == (size_t)i_archive_size)
	{
		double d_ratio = i_successes_counter / (double)i_archive_size;

		if (d_ratio > d_ONE_FIFTH)
		{
			cGetMutation().vMultiplySigmas(1.0 / d_modifier);
		}//if (d_ratio > d_ONE_FIFTH)
		else if (d_ratio < d_ONE_FIFTH)
		{
			cGetMutation().vMultiplySigmas(d_modifier);
		}//else if (d_ratio > d_ONE_FIFTH)
	}//if (l_successes.size() == (size_t)i_archive_size)
}//void CRealOneFifthRuleMutationES11Adaptation::vAdapt(double dBeforeMutationValue, vector<double> &vBeforeMutationSolution, double dAfterMutationValue, vector<double> &vAfterMutationSolution)

const double CRealOneFifthRuleMutationES11Adaptation::d_ONE_FIFTH = 0.2;

CRealCustomMutationES11Adaptation::CRealCustomMutationES11Adaptation(int iArchiveSize, double dModifier, CRealGaussianMutation& cMutation, CRealEvaluation& CEvaluation)
	: CRealNullRealMutationES11Adaptation(cMutation), i_archive_size(iArchiveSize), d_modifier(dModifier), i_successes_counter(0)
{

}


void CRealCustomMutationES11Adaptation::vAdapt(double dBeforeMutationValue, vector<double>& vBeforeMutationSolution, double dAfterMutationValue, vector<double>& vAfterMutationSolution)
{
}
