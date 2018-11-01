

#ifndef __BPM__COUNTER_CORE__
#define __BPM__COUNTER_CORE__

#include <chrono>
#include <iostream>
#include <vector>


namespace CROMEN_Cl {
	
	typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_stamp;
	time_stamp getTime();
	double elapsedSeconds(time_stamp &t1, time_stamp &t2);
	
	class BPMCounter {
		private:
			std::vector<CROMEN_Cl::time_stamp> data;
		public:
			BPMCounter();
			void addBeat();
			double getBPM_consider2Vals();
			double getBPM_consider3Vals();
			double getBPM_considerNVals(int N);
			void printBPM();
	};
	
}






#endif