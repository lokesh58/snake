#include <iostream>
using namespace std;
#include <string.h>
#include "headers//Game.h"

int main() {
	Game snake;
	bool play = true;
	
	while (play) {
		snake.play();
		cout << "Do you want to play another round? (y/n): ";
		char choice;
		cin >> choice;
		choice = tolower(choice);
		while (choice != 'y' && choice != 'n') {
			cout << "Your choice is not valid! Enter again: ";
			cin >> choice;
			choice = tolower(choice);
		}
		play = (choice == 'y');
	}
	cout << "\n\nThanks for playing my game! Hope you enjoyed :)" << endl;
	

	return 0;
}
