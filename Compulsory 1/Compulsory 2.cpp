#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

int drawcard(int); //places the player draw
int gencard();
bool wincon();
int playeraction();
void printhand();
void house();

bool run = true;
int pchoice;
std::vector <int> Vplayer = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
std::vector <int> Vhcard = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

struct card {
	int val;
	int name;
};
int pscore = 0;
int hscore = 0;
bool match = false;
bool pvic = false;
bool hvic = false;


int main()
{
	do {
		playeraction(); //player draw
		house(); //house draws
	} while (wincon() == true);
	std::cout << "You lose!";
}

int drawcard(int val) {
	for (int i = 0; i < (Vplayer.size() + 1); i++) {
		if (Vplayer.at(i) == 0) {
			Vplayer.at(i) = val;
		return 0;
		}
	}
	return 0;
}

void printhand() {
	std::cout << "Your hand: ";
	for (int i = 0; i < Vplayer.size(); i++) {
		if (Vplayer[i] != 0) {
		std::cout << Vplayer[i] << ", ";
		}
	}
	for (int i = 0; i < Vplayer.size(); i++) {
		pscore = pscore + Vplayer.at(i);
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
		if (wincon() == false) {
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
	int nrof10 = 0;
	srand(time(NULL));
	//std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for (int i = 0; i < (Vhcard.size()); i++) {
		if (Vhcard.at(i) == 0) {
			Vhcard.at(i) = rand() % 10 + 1;
			if (Vhcard.at(i) == 10) {
				nrof10++;
			}
			if (nrof10 >= 4) {
				Vhcard.at(i) = rand() % 10 + 1;
			}
			std::cout << "The house draws: ";
			std::cout << Vhcard.at(i) << std::endl;
			return 0;
		}
	}
}

bool wincon() {
	if (pscore >= 21) {
		return false;
	}
	else {
		return true;
	}
	
}

void house() {
	bool con = true;
	do {
		gencard();
		for (auto i : Vhcard) {
			hscore += i;
		}
		std::cout << "House total: " << hscore;
		std::cout << hscore << std::endl;
		if (hscore > pscore) {
			con = false;
		}
		else if (hscore < pscore) {
			gencard();
		}
		else if (hscore = pscore) {
			match = true;
			std::cout << "Match!";
		}
	} while (con == true);
	


}