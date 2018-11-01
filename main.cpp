
#include "bpm_counter_core.h"
#include <pthread.h>
#include <conio.h>
#include <time.h>
#include <windows.h>


void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void* printBPMThread(void* input_counterObject) {
	CHR_Cl::BPMCounter* counter_pnt = static_cast<CHR_Cl::BPMCounter*>(input_counterObject);
	
	std::cout << "Started thread for printing\n\n";
	ShowConsoleCursor(false);
	
	struct timespec sleep_time;
	sleep_time.tv_nsec = 1000000;
	sleep_time.tv_sec = 0;
	
	while(true) {
		std::cout << "BPM:\t" << counter_pnt->getBPM_considerNVals(5) << "\t\r";
		nanosleep(&sleep_time,NULL);
	}
	std::cout << "Terminate thread!\n";
	pthread_exit(NULL);
}

int main() {
	
	CHR_Cl::BPMCounter counter;
	char button_pressed;
	
	// create second thread
	pthread_t thread;
	int rc = pthread_create(&thread,NULL,printBPMThread,(void*)&counter);
	
	if (rc) {
		std::cout << "error! abort!\n";
	}
	
	while(true) {
		while( !_kbhit() ) {
		}
		button_pressed = _getch();
		
		if (button_pressed != 'q') {
			counter.addBeat();
		} else break;
		
		
		// counter.printBPM();
	}
	
	std::cout << "Main thread terminating...\n";
	
	return 0;
}