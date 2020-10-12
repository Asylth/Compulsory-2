#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

int drawcard(int); //places the player draw
int gencard();
bool pscorecheck();
int playeraction();
void printhand();
void house();
int wincheck();

bool run = true;
int pchoice;
std::vector <int> Vplayer;
std::vector <int> Vhcard;

struct card {
	int val;
	int name;
};
int pscore = 0;
int hscore = 0;
int housedraw = 0;
bool match = false;
bool pvic = false;
bool hvic = false;


int main()
{
	do {
		playeraction(); //player draw
		house(); //house draws
	} while (wincheck == 0 && pscorecheck() == true);
}

int drawcard(int val) {
	pscore = pscore + val;
	Vplayer.push_back(val);
	//for (int i = 0; i < (Vplayer.size()); i++) {
	//	//if (Vplayer.at(i) == 0) {
	//		Vplayer.at(i) = val;
	//		return 0;
	//	//}
	//}
	return 0;
}

void printhand() {
	std::cout << "Your hand: ";
	for (int i = 0; i < Vplayer.size(); i++) {
		if (Vplayer[i] != 0) {
		std::cout << Vplayer[i] << ", ";
		}
	}
}

int playeraction() {
	bool con = true;
	char yorn;

	do{
		std::cout << "Pick a card from 1-10: ";
		std::cin >> pchoice;
		drawcard(pchoice);
		printhand();
		std::cout << "Your total: " << pscore << std::endl;
		std::cout << std::endl;
		if (pscorecheck() == false) {
			return 0;
		}
		std::cout << "Wanna draw another card? (Y/N): ";
		std::cin >> yorn;
		std::cout << std::endl;
		switch (yorn) {
		case 'Y':case 'y':
			con = true;
			break;
		case 'N':case 'n':
			con = false;
			break;
		}
	} while (con == true);
}

int gencard() {
	//int nrof10 = 0;
	srand(time(NULL));
	return rand() % 10 + 1;
	////std::srand(static_cast<unsigned int>(std::time(nullptr)));
	//Vhcard.push_back(0);
	//for (int i = 0; i < (Vhcard.size()); i++) {
	//	if (Vhcard.at(i) == 0) {
	//		Vhcard.at(i) = rand() % 10 + 1;
	//		//if (Vhcard.at(i) == 10) {
	//		//	nrof10++;
	//		//}
	//		//if (nrof10 >= 4) {
	//		//	Vhcard.at(i) = rand() % 10 + 1;
	//		//}
	//		std::cout << "The house draws: ";
	//		std::cout << Vhcard.at(i) << std::endl;
	//		return 0;
	//	}
	//}
}

bool pscorecheck() {
	if (pscore >= 21) {
		return false;
	}
	else {
		return true;
	}
	
}

void house() {
	bool con = true;
	while (con == true){
		housedraw = gencard();
		hscore = hscore + housedraw;
		Vhcard.push_back(housedraw);
		//for (int i = 0; i < Vhcard.size(); i++) {
		//	Vhcard.at(i) = housedraw;
		//}
		
		/*std::cout << "The house draws: " << housedraw << std::endl;*/
		std::cout << "The house draws " << housedraw << " and now has the hand: ";
		for (int i = 0; i < Vhcard.size(); i++) {
			if (Vhcard[i] != 0) {
				std::cout << Vhcard[i] << ", ";
			}
		}
		std::cout << std::endl;
		std::cout << "House total: " << hscore << std::endl;
		wincheck();
		if (wincheck() == 1 || wincheck() == 2) {
			con = false;
		}

		//if (wincheck() == 1) {
		//	con = false;
		//}
		//else if (wincheck() == 2) {
		//	//gencard();
		//}
		//else if (hscore = pscore) {
		//	match = true;
		//	std::cout << "Match!";
		//}
	};
}

int wincheck() {
	if (hscore > pscore) {
		return 1;
		std::cout << "You lose!";
	}
	else if (hscore < pscore) {
		return 0;
	}
	else if (hscore = pscore) {
		return 2;
		std::cout << "Match!";
	}
}