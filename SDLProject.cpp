#include <iostream>
#include <SDL.h>

#include "Screen.h"

using namespace std;

int main() {

	tss::Screen screen;
	if(!screen.init() == false){
		cout << "Error initializing SDL" << endl;
	}

	while(true){
		// Update particles
		// Draw particles
		// Check for messages/events

		if(!screen.processEvents()){
			break;
		}

	}

	screen.close();

	return 0;
}
