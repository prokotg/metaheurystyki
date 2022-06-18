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

template <typename TElement>
void report_to_file_ga(std::ofstream& file, 
	std::string run_name,
	std::string strategy,
	std::string crosstype,
	float pcross,
	float pmut,
	int64_t pop_size,
	int64_t gene_length, 
	int64_t run_id, 
	COptimizationResult<TElement>& cOptimizationResult) {



	file << run_name << "," << strategy << "," << crosstype << ",";
	file << pcross << "," << pmut << "," << pop_size << ",";
	file << gene_length << "," << run_id << ",";
	file << cOptimizationResult.dGetBestValue() << ",";
	file << cOptimizationResult.dGetBestTime() << ",";
	file << cOptimizationResult.iGetBestIteration() << ",";
	file << cOptimizationResult.iGetBestFFE() << ",";
	file << endl;
}

void initialize_result_file(std::ofstream& ofs, std::string name);
void initialize_result_file_ga(std::ofstream& ofs, std::string name);