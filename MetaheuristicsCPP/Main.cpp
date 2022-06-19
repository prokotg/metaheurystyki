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
#include "Labs.h"

using namespace Optimizers;
using namespace StopConditions;

using namespace Evaluations;
using namespace std;


int main()
{
	// ########################## RAPORT 1 ########################
	//run_lab_1();
	//run_lab_2();
	// ########################## RAPORT 2 ########################
	//run_lab_4();
	run_lab_5();
	system("PAUSE");
	return 0;
}//int main()