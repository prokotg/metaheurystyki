#pragma once

#include <string>

using namespace std;

namespace Evaluations
{
	enum class EBinaryKnapsackInstance
	{
		f1_l_d_kp_10_269,
		f2_l_d_kp_20_878,
		f3_l_d_kp_4_20,
		f4_l_d_kp_4_11,
		f5_l_d_kp_15_375,
		f6_l_d_kp_10_60,
		f7_l_d_kp_7_50,
		f8_l_d_kp_23_10000,
		f9_l_d_kp_5_80,
		f10_l_d_kp_20_879,
		knapPI_1_100_1000_1,
		knapPI_1_200_1000_1,
		knapPI_1_500_1000_1,
		knapPI_1_1000_1000_1,
		knapPI_1_2000_1000_1,
		knapPI_1_5000_1000_1,
		knapPI_1_10000_1000_1,
		knapPI_2_100_1000_1,
		knapPI_2_200_1000_1,
		knapPI_2_500_1000_1,
		knapPI_2_1000_1000_1,
		knapPI_2_2000_1000_1,
		knapPI_2_5000_1000_1,
		knapPI_2_10000_1000_1,
		knapPI_3_100_1000_1,
		knapPI_3_200_1000_1,
		knapPI_3_500_1000_1,
		knapPI_3_1000_1000_1,
		knapPI_3_2000_1000_1,
		knapPI_3_5000_1000_1,
		knapPI_3_10000_1000_1
	};//enum class EBinaryKnapsackInstance


	struct SBinaryKnapsackInstanceFilePaths
	{
		static SBinaryKnapsackInstanceFilePaths *pcCreate(EBinaryKnapsackInstance eInstance);

		string sDefinitionFilePath;
		string sOptimumFilePath;
	};//struct SBinaryKnapsackInstanceFilePaths
};//namespace Evaluations