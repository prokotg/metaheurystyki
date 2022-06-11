#pragma once

#include <sstream>
#include <fstream>
#include "OptimizationResult.h"
using namespace Optimizers;

template <typename TElement>
void report_to_file(std::ofstream& file, std::string run_name, int64_t gene_length, int64_t run_id, COptimizationResult<TElement>& cOptimizationResult) {



	file << run_name << "," << gene_length << "," << run_id << ",";
	file << cOptimizationResult.dGetBestValue() << ",";
	file << cOptimizationResult.dGetBestTime() << ",";
	file << cOptimizationResult.iGetBestIteration() << ",";
	file << cOptimizationResult.iGetBestFFE() << ",";
	file << endl;
}

void initialize_result_file(std::ofstream& ofs);