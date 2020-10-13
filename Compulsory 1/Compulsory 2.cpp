#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdlib>

int drawcard(int); //places the player draw
int gencard();
bool pscorecheck();
int playeraction();
void printhand();
void house();
void wincheck();
int bet();
void restartgame();

std::vector <int> Vplayer;
std::vector <int> Vhcard;
int pscore = 0;
int hscore = 0;
int housedraw = 0;
int hmoney = 100;
int pmoney = 100;
int win = 0; // 0 = none, 1 = player, 2 = house, 3 = match
int nrof4;
int pbet = 0;
int hbet = 0;
int matchnr = 0;

int main()
{
	srand(time(nullptr));
	do {
		if (matchnr == 0) {
		std::cout << "Welcome to Blackjack!\n";
		}
		else if (matchnr != 0) {
			std::cout << "Welcome to round " << matchnr + 1 << "!\n";
		}
		playeraction(); //player draw
		bet();
		house(); //house draws
		switch (win) {
		case 1:
			std::cout << "You win!" << "\n";
			pmoney += hbet;
			break;
		case 2:
			std::cout << "You Lose!\n";
			hmoney += pbet;
			break;
		case 3:
			std::cout << "Match! Go again\n";
			std::cout << std::endl;
			//pmoney += pbet;
			//hmoney += hbet;
			matchnr++;
			restartgame();
			pscorecheck() == true;
			break;
		}
	} while (win == 0 && pscorecheck() == true);
}


int playeraction() {
	bool con = true;
	char yorn;
	char pchoice; //stores plater choice
	int tempdraw; //holds the drawn card val
	int looptime = 0;

	do{
		//if (looptime == 0) {
		//std::cout << "Draw a card? (Y/N): ";
		//}
		//std::cin >> pchoice;
		//std::cout << std::endl;
		//switch (pchoice) {
		//case 'Y':case 'y':
			tempdraw = gencard();
			drawcard(tempdraw);
			std::cout << "You drew a " << tempdraw << std::endl;
			//std::cout << "You drew a " << drawcard(gencard())<< std::endl;
			printhand();
		//	break;
		//case 'N':case 'n':
		//	printhand();
		//	break;
		//}
		std::cout << "Your total: " << pscore << std::endl;
		std::cout << std::endl;
		if (pscorecheck() == false) {
			return 0;
		}
		std::cout << "Wanna draw another card? (Y/N): ";
		//std::cin.clear();
		std::cin >> yorn;
		std::cout << std::endl;
		switch (yorn) {
		case 'Y':case 'y':
			con = true;
			looptime++;
			break;
		case 'N':case 'n':
			con = false;
			break;
		}
	} while (con == true);
}

int drawcard(int val) {
	int ace;
	if (val == 1) {
		std::cout << "You drew an ace, you can pick it's value (1 or 11): ";
		std::cin >> ace;
		pscore = pscore + ace;
		Vplayer.push_back(ace);
		return ace;
	}
	else {
		pscore = pscore + val;
		Vplayer.push_back(val);
		return val;
	}
}

void printhand() {
	std::cout << "Your hand: ";
	for (int i = 0; i < Vplayer.size(); i++) {
		if (Vplayer[i] != 0) {
			std::cout << Vplayer[i] << ", ";
		}
	}
}


int gencard() {
	int card = rand() % 10 + 1;
	if (card == 10) {
		nrof4++;
	}
	if (card == 10 && nrof4 == 4) {
		gencard();
	}
	return card;

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
	bool ace = false;

	while (con == true){
		housedraw = gencard();
		if (housedraw == 1) {
			std::cout << "The house draws a ace! ";
			ace = true;
			if (hscore <= 10){
				housedraw = 11;
			}
			else if (housedraw >= 10) {
				housedraw = 1;
			}
		}
		hscore = hscore + housedraw;
		Vhcard.push_back(housedraw);

		if (ace == false){
			ace = false;
			std::cout << "The house draws ";
		}
		std::cout << housedraw << " and now has the hand: ";
		for (int i = 0; i < Vhcard.size(); i++) {
			if (Vhcard[i] != 0) {
				std::cout << Vhcard[i] << ", ";
			}
		}
		std::cout << std::endl;
		std::cout << "House total: " << hscore << std::endl;
		wincheck();
		if (win != 0 && win != 1){
			con = false;
		}
	};
}

void wincheck() {
	if (hscore > pscore) {
		win = 2; //house win
	}
	else if (hscore < pscore) {
		win = 1; //player win
	}
	else if (hscore = pscore) {
		win = 3; //match
	}
	else {
		win = 0; //no winner yet
	}
}

void restartgame() {
	pscore = 0;
	hscore = 0;
	housedraw = 0;
	hmoney = 100;
	pmoney = 100;
	win = 0;
	nrof4;
	Vplayer.clear();
	Vhcard.clear();
}

int bet() {
	if (matchnr != 0) {
		return 0;
	}
	std::cout << "You have " << pmoney << "$\n";
	std::cout << "The house has " << hmoney << "$\n";
	std::cout << "Place your bet: ";
	std::cin >> pbet;
	std::cout << std::endl;
	if (pbet < 10) {
		bet();
	}
	else if (pbet > pmoney) {
		std::cout << "Your bet is to large! \n";
		bet();
	}
	else if (pbet > hmoney) {
		std::cout << "Your bet is to large! \n";
		bet();
	}
	else {
		hbet = pbet;
		std::cout << "You bet " << pbet << "$\n";
		std::cout << "The House bets " << hbet << "$\n";
		std::cout << std::endl;
	}
	return 0;
}