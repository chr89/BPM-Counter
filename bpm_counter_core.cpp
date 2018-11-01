

#include "bpm_counter_core.h"

CHR_Cl::time_stamp CHR_Cl::getTime() {
	return std::chrono::high_resolution_clock::now();
}

double CHR_Cl::elapsedSeconds(CHR_Cl::time_stamp &t1, CHR_Cl::time_stamp &t2) {
	return std::chrono::duration<double>(t2-t1).count();
}

CHR_Cl::BPMCounter::BPMCounter() {}

void CHR_Cl::BPMCounter::addBeat() {
	this->data.push_back(getTime());
}

double CHR_Cl::BPMCounter::getBPM_consider2Vals() {
	int numb = this->data.size();
	if (numb > 1) {
		return 60.d/elapsedSeconds(this->data[numb-2],this->data[numb-1]);
	} else return 0;
}

double CHR_Cl::BPMCounter::getBPM_consider3Vals() {
	int numb = this->data.size();
	if (numb > 2) {
		return 120.d/elapsedSeconds(this->data[numb-3],this->data[numb-1]);
	} else return 0;
}

double CHR_Cl::BPMCounter::getBPM_considerNVals(int N) {
	int numb = this->data.size();
	if (numb > N) {
		return 60.d/elapsedSeconds(this->data[numb-N],this->data[numb-1])*(N-1);
	} else return 0;
}

void CHR_Cl::BPMCounter::printBPM() {
	std::cout << "BPM:\t" << getBPM_considerNVals(5) << "\n";
}