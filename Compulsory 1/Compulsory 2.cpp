#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdlib>

int drawcard(int); //places the player drawn card into the Vplayer array
int gencard(); //generates a random number as a card. also checks that there are no more than 10
int playeraction(); //player moves
void printhand(); //prints the player Vplayer array
void house(); //takes the actions of the house
void wincheck(); //checks who wins
int bet(); //placing and calcs bets
void restartgame(); //resets the values that neeeds it

std::vector <int> Vplayer; //holds player cards
std::vector <int> Vhcard; // holds house cards
int pscore = 0; //holds the total score of player
int hscore = 0; // holds the total score of house
int housedraw = 0; //hold the value of the card the house drew, temp
int hmoney = 100; //total money of house
int pmoney = 100; //total money of player
int win = 0; // 0 = none, 1 = player, 2 = house, 3 = match
int nrof4; //holds the nr of 10's that has been drawn
int pbet = 0; //bet of player
int hbet = 0; // bet of house
int matchnr = 0; //keeps track of rounds

int main()
{
	srand(time(nullptr)); //seeds rand
	do {
		if (matchnr == 0) { //checks to see if its the first round
		std::cout << "Welcome to Blackjack!\n";
		}
		else if (matchnr != 0) { //if its not the first round then prints this
			std::cout << "Welcome to round " << matchnr + 1 << "!\n";
		}
		playeraction();
		bet();
		house();
		switch (win) { //cases for win conditions
		case 1: //player win
			std::cout << "You win!" << "\n";
			pmoney += hbet;
			break;
		case 2: //house win
			std::cout << "You Lose!\n";
			hmoney += pbet;
			break;
		case 3: //match
			std::cout << "Match! Go again\n";
			std::cout << std::endl;
			matchnr++;
			restartgame();
			break;
		}
	} while (win == 0);
}


int playeraction() {
	bool con = true; //run condition of function
	char yorn; // stores player choice
	char pchoice; //stores plater choice
	int tempdraw; //holds the drawn card val

	do{

		tempdraw = gencard();
		drawcard(tempdraw);
		std::cout << "You drew a " << tempdraw << std::endl;
		printhand();
		std::cout << "Your total: " << pscore << std::endl;
		std::cout << std::endl;

		if (pscore >= 21) {
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

int drawcard(int val) {
	int ace;
	if (val == 1) { //if drew an ace then choose the outcome
		std::cout << "You drew an ace, you can pick it's value (1 or 11): ";
		std::cin >> ace;
		pscore = pscore + ace;
		Vplayer.push_back(ace);
		return ace;
	}
	else { //adds the drawn value to the array
		pscore = pscore + val;
		Vplayer.push_back(val);
		return val;
	}
}

void printhand() { //print the current hand of player
	std::cout << "Your hand: ";
	for (int i = 0; i < Vplayer.size(); i++) {
		if (Vplayer[i] != 0) {
			std::cout << Vplayer[i] << ", ";
		}
	}
}


int gencard() { //generates a random number for card draws
	int card = rand() % 10 + 1;
	if (card == 10) { //increments the number of 10s drawn
		nrof4++;
	}
	if (card == 10 && nrof4 == 4) {
		gencard();
	}
	return card;

}


void house() { //house "ai"
	bool con = true; //run condition
	bool ace = false; // if ace is drawn = true

	while (con == true){
		housedraw = gencard();
		if (housedraw == 1) { //check if ace is drawn 
			std::cout << "The house draws a ace! ";
			ace = true;
			if (hscore <= 10){ //"logic" for the house to choose which nr for the ace is best
				housedraw = 11;
			}
			else if (housedraw >= 10) {
				housedraw = 1;
			}
		}
		hscore = hscore + housedraw; //adds to the house score
		Vhcard.push_back(housedraw); //places draw in array

		if (ace == false){
			ace = false;
			std::cout << "The house draws ";
		}
		std::cout << housedraw << " and now has the hand: "; //prints the houses hand
		for (int i = 0; i < Vhcard.size(); i++) {
			if (Vhcard[i] != 0) {
				std::cout << Vhcard[i] << ", ";
			}
		}
		std::cout << std::endl;
		std::cout << "House total: " << hscore << std::endl;
		std::cout << std::endl;
		wincheck(); //checks who wins
		if (win != 0){ //runs only if win != 0
			con = false;
		}

	};
}

void wincheck() { //checks who wins
	if (hscore < pscore) { //win = 0 if the house score is lower than player score
		win = 0;
	}
	else { //if not then
		if (hscore > pscore) {
			win = 2; //house win
		}
		else if (hscore < pscore) {
			win = 1; //player win
		}
		else if (hscore = pscore) {
			win = 3; //match
		}
		else if (hscore >= 21) { 
			win = 1; //player wins
		}
		else if (pscore >= 21) {
			win = 2; // house wins
		}
		else {
			if (pscore > hscore) {
				win = 1; //player wins
			}
			else if (hscore > pscore) {
				win = 2; //house wins
			}
		}
	}

}

void restartgame() {
	pscore = 0;
	hscore = 0;
	housedraw = 0;
	//hmoney = 100;
	//pmoney = 100;
	win = 0;
	//nrof4;
	Vplayer.clear();
	Vhcard.clear();
}

int bet() {
	if (matchnr != 0) { //can only bet the first round since other rounds would be a match
		return 0;
	}
	std::cout << "You have " << pmoney << "$\n";
	std::cout << "The house has " << hmoney << "$\n";
	std::cout << "Place your bet (min 10$): ";
	std::cin >> pbet;
	std::cout << std::endl;
	if (pbet < 10) { //min bet = 10 else it repeats function
		std::cout << "Place a higher bet \n";
		bet();
	}
	else if (pbet > pmoney) { //makes sure you cant bet more than you have
		std::cout << "Your bet is to large! \n";
		bet();
	}
	else if (pbet > hmoney) { //makes sure you cant bet more than the house has
		std::cout << "Your bet is to large! \n";
		bet();
	}
	else { //house matches your bet
		hbet = pbet;
		std::cout << "You bet " << pbet << "$\n";
		std::cout << "The House bets " << hbet << "$\n";
		std::cout << std::endl;
	}
	return 0;
}