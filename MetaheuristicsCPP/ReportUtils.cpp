#include "ReportUtils.h"
#include <sstream>
#include <iomanip>
#include <fstream>

void initialize_result_file(std::ofstream& ofs) {
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << "C:\\mount_dummy\\" << "metresults_" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ".csv";
	ofs.open(oss.str(), ios::out);

	// treat ofs as csv file, initialize columns

	ofs << "name" << ",";
	ofs << "gene_length" << ",";
	ofs << "run_id" << ",";
	ofs << "best_value" << ",";
	ofs << "best_time" << ",";
	ofs << "best_iteration" << ",";
	ofs << "best_ffe" << "," << std::endl;
}