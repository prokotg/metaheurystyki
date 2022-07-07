#pragma once
#include "OptimizationResult.h"
#include <tuple>
void run_lab_1();
void run_lab_2();

void run_lab_4();
void run_lab_5();
void run_lab_6();
void run_lab_7();

using namespace Optimizers;

struct KnapsackResults {
	KnapsackResults(COptimizationResult<bool> c_res, std::tuple<size_t, float> i_ill_count) : cRes(c_res), ill_count(i_ill_count) {};

	COptimizationResult<bool> cRes;
	std::tuple<size_t, float> ill_count;
};