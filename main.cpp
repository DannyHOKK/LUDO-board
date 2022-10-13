#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include <windows.h>

using namespace std;

void menu();
void game();
void setting();
void GameDemo();
void instructions();
void credit();

void mode();//player status
void playerone();
void playertwo();
void playerthree();
void playerfour();

void player_detail();
void chessboard();
void chesseating(int chess);//eating chess when overlapping

void triplesix();
void homerun();
void selfchesswonteat();

void leave();



char chesspath[5][50] = {
	".........................................",".....",".....",".....","....."
};
int player_no = 2;//total number of player
int human_no = 1;//number of human player
int computer_no = 1;//number of computer
int dice;//dice means the number of move player can move in that turn 
bool jumpout = 0;//exit the main game function
bool confirmleaving = 0;//exit the whole program

class player {
public:
	player(char chessone, char chesstwo, char chessthree, char chessfour, int player) {
		chess1 = chessone;
		chess2 = chesstwo;
		chess3 = chessthree;
		chess4 = chessfour;
		route = player;//player routine
		basepoint = 1 + 10 * (player - 1);//basepoint means the starting point of each player's chess
		chess_no1 = chess_no2 = chess_no3 = chess_no4 = 0;
		enterTrack1 = enterTrack2 = enterTrack3 = enterTrack4 = 0;//enterTrack represent the chess entering to their corresponding track.
		end1 = end2 = end3 = end4 = circleEnd = endGame = 0; //circleEnd means that the chess finish a circle
	}

	int chess_no1, chess_no2, chess_no3, chess_no4, step, route, basepoint;
	bool enterTrack1, enterTrack2, enterTrack3, enterTrack4, end1, end2, end3, end4, circleEnd, endGame, backtobasepoint[5], started[5];//started mean chess is started or not
	char playertype; //computer or human	
	void start() {
		char option, check[100];
		dice = rand() % 6 + 1;
		cout << "Player " << route << " rolled a dice and got " << dice << endl; \
			switch (dice) {
			case 1:
				cout << "+-------+\n|       |\n|   *   |\n|       |\n+-------+\n";
				break;
			case 2:
				cout << "+-------+\n|   *   |\n|       |\n|   *   |\n+-------+\n";
				break;
			case 3:
				cout << "+-------+\n|   *   |\n|       |\n| *   * |\n+-------+\n";
				break;
			case 4:
				cout << "+-------+\n| *   * |\n|       |\n| *   * |\n+-------+\n";
				break;
			case 5:
				cout << "+-------+\n| *   * |\n|   *   |\n| *   * |\n+-------+\n";
				break;
			case 6:
				cout << "+-------+\n| *   * |\n| *   * |\n| *   * |\n+-------+\n";
				break;
			}
		if (availability() == 0) {
			return;
		}

		if (endGame == 1)return;
		for (;;) {
			cout << "Choice:";
			if (playertype == 'h') {
				while (!(cin >> check) || check[1] != '\0' || (check[0] != 'q') && (check[0] != 'Q') && (check[0] != chess1) && (check[0] != chess2) && (check[0] != chess3) && (check[0] != chess4) || ((check[0] == chess1) && started[1] == 0) || (check[0] == chess2 && started[2] == 0) || ((check[0] == chess3) && started[3] == 0) || (check[0] == chess4 && started[4] == 0))
				{
					cout << "Error! Please input again with the given choices!" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}
				option = check[0];
			}
			for (;;) {
				if (playertype == 'c') {
					switch (rand() % 4 + 1) {
					case 1:
						option = chess1;
						if (started[1] == 1) {
							break;
						}
					case 2:
						option = chess2;
						if (started[2] == 1) {
							break;
						}
					case 3:
						option = chess3;
						if (started[3] == 1) {
							break;
						}
					case 4:
						option = chess4;
						if (started[4] == 1) {
							break;
						}
					default:
						continue;
					}
					cout << option << endl;
				}

				break;
			}

			if (option == 'q' || option == 'Q') {
				char exitGame[100];
				cout << "Are you sure to jumpout? Y or N " << endl;
				while (!(cin >> exitGame) || exitGame[1] != '\0' || exitGame[0] != 'Y' && exitGame[0] != 'y' && exitGame[0] != 'N' && exitGame[0] != 'n') {
					cout << "Error! Please input again with the given choices!" << endl; 
					cin.clear();
					cin.ignore(256, '\n');
				}
				if (exitGame[0] == 'Y' || exitGame[0] == 'y') {
					jumpout = 1; return;
				}
				continue;
			}
			break;
		}
		action(chessSelection(option), option);
	}

	void info(char coh) {

		playertype = coh;
		cout << endl << "Player " << route << ": ";
		if (coh == 'h') {
			cout << "Human" << endl;
		}else if (coh == 'c') {
			cout << "CPU" << endl;
		}
		cout << "Base: ";
		if (chess_no1 == 0)
			cout << chess1 << " ";
		if (chess_no2 == 0)
			cout << chess2 << " ";
		if (chess_no3 == 0)
			cout << chess3 << " ";
		if (chess_no4 == 0)
			cout << chess4 << " ";
		cout << endl

			<< "Home: ";
		if (end1 == 1) {
			cout << chess1 << " ";
		}
		if (end2==1) {
			cout << chess2 << " ";
		}
		if (end3==1) {
			cout << chess3 << " ";
		}
		if (end4==1) {
			cout << chess4 << " ";
		}
		cout << endl;
	}

	bool availability() {//availability means option chess player can take a action

		if ((chess_no1 == 0 && dice == 6 || chess_no1 != 0) && end1 == 0 && sameplayerchess(chess_no1, backtobasepoint[1], enterTrack1) == 0) {
			started[1] = 1;
		}
		if ((chess_no2 == 0 && dice == 6 || chess_no2 != 0) && end2 == 0 && sameplayerchess(chess_no2, backtobasepoint[2], enterTrack2) == 0) {
			started[2] = 1;
		}
		if ((chess_no3 == 0 && dice == 6 || chess_no3 != 0) && end3 == 0 && sameplayerchess(chess_no3, backtobasepoint[3], enterTrack3) == 0) {
			started[3] = 1;
		}
		if ((chess_no4 == 0 && dice == 6 || chess_no4 != 0) && end4 == 0 && sameplayerchess(chess_no4, backtobasepoint[4], enterTrack4) == 0) {
			started[4] = 1;
		}
		if ((started[1] == 0 || end1==1) && (started[2] == 0 || end2==1) && (started[3] == 0 || end3==1) && (started[4] == 0 || end4==1)) {
			cout << "This chess is not available. " << endl; return 0;
		}

		cout << "Available chess: ";
		if (started[1]) {
			cout << chess1 << " ";
		}
		if (started[2]) {
			cout << chess2 << " ";
		}
		if (started[3]) {
		cout << chess3 << " ";
		}
		if (started[4]) {
			cout << chess4 << " ";
		}
		cout << endl;
		return 1;
	}

	int chessSelection(char option) {
		if (option == chess1) {
			backtobasepoint[0] = backtobasepoint[1];
			step = chess_no1;
			circleEnd = enterTrack1;
			return 1;
		}
		if (option == chess2) {
			backtobasepoint[0] = backtobasepoint[2];
			step = chess_no2;
			circleEnd = enterTrack2;
			return 2;
		}
		if (option == chess3) {
			backtobasepoint[0] = backtobasepoint[3];
			step = chess_no3;
			circleEnd = enterTrack3;
			return 3;
		}
		if (option == chess4) {
			backtobasepoint[0] = backtobasepoint[4];
			step = chess_no4;
			circleEnd = enterTrack4;
			return 4;
		}
	}

	void chessmoving(int option) {
		if (option == 1) {
		backtobasepoint[1] = backtobasepoint[0];
		chess_no1 = step;
		enterTrack1 = circleEnd;
		}
		if (option == 2)
		{
			backtobasepoint[2] = backtobasepoint[0];
			chess_no2 = step;
			enterTrack2 = circleEnd;
		}
		if (option == 3) {
			backtobasepoint[3] = backtobasepoint[0];
			chess_no3 = step;
			enterTrack3 = circleEnd;
		}
		if (option == 4) {
			backtobasepoint[4] = backtobasepoint[0];
			chess_no4 = step;
			enterTrack4 = circleEnd;
		}

		if (chess_no1 == 5 && backtobasepoint[1]) {
			end1 = 1;
		}
		if (chess_no2 == 5 && backtobasepoint[2]) {
			end2 = 1;
		}
		if (chess_no3 == 5 && backtobasepoint[3]) {
			end3 = 1;
		}
		if (chess_no4 == 5 && backtobasepoint[4]) {
			end4 = 1;
		}
		started[1] = started[2] = started[3] = started[4] = 0;
	}

	void action(int option, char chess) {

		if (backtobasepoint[0] == 1) {
			chesspath[route][step] = '.';
		}
		else {
			chesspath[0][step] = '.';
		}
		step += step == 0 ? basepoint : dice;

		if (step >= 41) {
			step -= 40;
			circleEnd = 1;
		}

		if (circleEnd == 1 && step > basepoint && backtobasepoint[0] == 0) {
			backtobasepoint[0] = 1;
			step = step - basepoint;
		}

		if (step > 5 && backtobasepoint[0] == 1) {
			step = 10 - step;
		}
		if (backtobasepoint[0] == 1 && step == 0) {
			backtobasepoint[0] = 0;
			step = basepoint;
		}
		if (backtobasepoint[0] == 0) {
			chesseating(step);
		}
		if (backtobasepoint[0] == 1) {
			chesspath[route][step] = chess;
		}
		else {
			chesspath[0][step] = chess;
		}
		chessmoving(option);

		if (end1 && end2 && end3 && end4) {
			endGame = 1;
		}
	}

	bool sameplayerchess(int chessno, bool reach, bool circleEnd) {
		int original = chessno;
		chessno += chessno == 0 ? basepoint : dice;
		if (chessno >= 41) {
			chessno -= 40;
			circleEnd = 1;
		}
		if (circleEnd == 1 && chessno > basepoint && reach == 0) {
			reach = 1;
			chessno = chessno - basepoint;
		}
		if (chessno >= 5 && reach == 1)
			chessno = 10 - chessno;

		if (reach == 1 && chessno == 0) {
			reach = 0; chessno = basepoint;
		}
		if (chessno == 5 && reach == 1 && circleEnd == 1)
			return 0;
		if (original == chessno)
			return 0;

		if ((chessno) == chess_no1 && reach == backtobasepoint[1])
			return 1;
		if ((chessno) == chess_no2 && reach == backtobasepoint[2])
			return 1;
		if ((chessno) == chess_no3 && reach == backtobasepoint[3])
			return 1;
		if ((chessno) == chess_no4 && reach == backtobasepoint[4])
			return 1;
		return 0;
	}

private:
	char chess1, chess2, chess3, chess4;
};


player player1('a', 'b', 'c', 'd', 1);
player player2('e', 'f', 'g', 'h', 2);
player player3('i', 'j', 'k', 'l', 3);
player player4('m', 'n', 'o', 'p', 4);

void chessboard() {
	cout << chesspath[0][1] << " " << chesspath[0][2] << " " << chesspath[0][3] << " " << chesspath[0][4] << " " << chesspath[0][5] << " " << chesspath[0][6] << " " << chesspath[0][7] << " " << chesspath[0][8] << " " << chesspath[0][9] << " " << chesspath[0][10] << " " << chesspath[0][11] << " " << endl << chesspath[0][40] << " " << chesspath[1][1] << " " << setw(14) << " " << chesspath[2][1] << " " << chesspath[0][12] << " " << endl << chesspath[0][39] << " " << setw(2) << " " << chesspath[1][2] << " " << setw(10) << " " << chesspath[2][2] << " " << setw(2) << " " << chesspath[0][13] << " " << endl << chesspath[0][38] << " " << setw(4) << " " << chesspath[1][3] << " " << setw(6) << " " << chesspath[2][3] << " " << setw(4) << " " << chesspath[0][14] << " " << endl << chesspath[0][37] << " " << setw(6) << " " << chesspath[1][4] << " " << setw(2) << " " << chesspath[2][4] << " " << setw(6) << " " << chesspath[0][15] << " " << endl << chesspath[0][36] << " " << setw(8) << " " << "X" << " " << setw(8) << " " << chesspath[0][16] << " " << endl << chesspath[0][35] << " " << setw(6) << " " << chesspath[4][4] << " " << setw(2) << " " << chesspath[3][4] << " " << setw(6) << " " << chesspath[0][17] << " " << endl << chesspath[0][34] << " " << setw(4) << " " << chesspath[4][3] << " " << setw(6) << " " << chesspath[3][3] << " " << setw(4) << " " << chesspath[0][18] << " " << endl << chesspath[0][33] << " " << setw(2) << " " << chesspath[4][2] << " " << setw(10) << " " << chesspath[3][2] << " " << setw(2) << " " << chesspath[0][19] << " " << endl << chesspath[0][32] << " " << chesspath[4][1] << " " << setw(14) << " " << chesspath[3][1] << " " << chesspath[0][20] << " " << endl << chesspath[0][31] << " " << chesspath[0][30] << " " << chesspath[0][29] << " " << chesspath[0][28] << " " << chesspath[0][27] << " " << chesspath[0][26] << " " << chesspath[0][25] << " " << chesspath[0][24] << " " << chesspath[0][23] << " " << chesspath[0][22] << " " << chesspath[0][21] << " " << endl;
}

void game() {
	srand(time(0));

	for (; player1.endGame == 0 && player2.endGame == 0 && player3.endGame == 0 && player4.endGame == 0;) {

		if (player_no >= 1) {
			playerone();
			if (jumpout)
				return;
		}
		if (player_no >= 2) {
			playertwo();
			if (jumpout)
				return;
		}
		if (player_no >= 3) {
			playerthree();
			if (jumpout)
				return;
		}
		if (player_no >= 4) {
			playerfour();
			if (jumpout)
				return;
		}
	}
	mode();

	if (player1.endGame == 1)
		cout << "The winner is Player 1." << endl;
	if (player2.endGame == 1)
		cout << "The winner is Player 2." << endl;
	if (player3.endGame == 1)
		cout << "The winner is Player 3." << endl;
	if (player4.endGame == 1)
		cout << "The winner is Player 4." << endl;
	cout << "Victory!Thank You!" << endl;
	system("pause");
	system("cls");
}

void playerone() {
	for (int i = 1; i <= 3; i++) {
		if (player1.endGame == 1 || player2.endGame == 1 || player3.endGame == 1 || player4.endGame == 1)
			return;
		mode();

		if (jumpout == 1)
			return;
		player1.start();

		if (player1.endGame == 1)
			break;

		if (dice == 6 && i != 3 && jumpout != 1) {
			cout << "Congraduation! You got a bonus turn!" << endl;
			continue;
		}
		if (i == 3 && dice == 6 && jumpout != 1) {
			cout << "Next Player's turn." << endl;
		}
		else break;
	}
}

void playertwo() {

	for (int i = 1; i <= 3; i++) {
		if (player1.endGame == 1 || player2.endGame == 1 || player3.endGame == 1 || player4.endGame == 1)
			return;
		mode();

		if (jumpout == 1)
			return;
		player2.start();

		if (player2.endGame == 1)
			break;

		if (dice == 6 && i != 3 && jumpout != 1) {
			cout << "Congraduation! You got a bonus turn!" << endl;
			continue;
		}
		if (i == 3 && dice == 6 && jumpout != 1) {
			cout << "Next Player's turn." << endl;
		}
		else break;
	}
}

void playerthree() {

	for (int i = 1; i <= 3; i++) {
		if (player1.endGame == 1 || player2.endGame == 1 || player3.endGame == 1 || player4.endGame == 1)
			return;
		mode();

		if (jumpout == 1)
			return;
		player3.start();

		if (player3.endGame == 1)
			break;

		if (dice == 6 && i != 3 && jumpout != 1) {
			cout << "Congraduation! You got a bonus turn!" << endl;
			continue;
		}
		if (i == 3 && dice == 6 && jumpout != 1)
			cout << "Next Player's turn." << endl;
		else break;
	}
}

void playerfour() {

	for (int i = 1; i <= 3; i++) {
		if (player1.endGame == 1 || player2.endGame == 1 || player3.endGame == 1 || player4.endGame == 1)
			return;
		mode();

		if (jumpout == 1)
			return;
		player4.start();

		if (player4.endGame == 1)
			break;

		if (dice == 6 && i != 3 && jumpout != 1) {
			cout << "Congraduation! You got a bonus turn!" << endl;
			continue;
		}
		if (i == 3 && dice == 6 && jumpout != 1) {
			cout << "Next Player's turn." << endl;
		}
		else break;
	}
}

void chesseating(int chess) {
	switch (chesspath[0][chess]) {
	case 'a':
		player1.chess_no1 = 0;
		player1.enterTrack1 = 0;
		break;
	case 'b':
		player1.chess_no2 = 0;
		player1.enterTrack2 = 0;
		break;
	case 'c':
		player1.chess_no3 = 0;
		player1.enterTrack3 = 0;
		break;
	case 'd':
		player1.chess_no4 = 0;
		player1.enterTrack4 = 0;
		break;
	case 'e':
		player2.chess_no1 = 0;
		player2.enterTrack1 = 0;
		break;
	case 'f':
		player2.chess_no2 = 0;
		player2.enterTrack2 = 0;
		break;
	case 'g':
		player2.chess_no3 = 0;
		player2.enterTrack3 = 0;
		break;
	case 'h':
		player2.chess_no4 = 0;
		player2.enterTrack4 = 0;
		break;
	case 'i':
		player3.chess_no1 = 0;
		player3.enterTrack1 = 0;
		break;
	case 'j':
		player3.chess_no2 = 0;
		player3.enterTrack2 = 0;
		break;
	case 'k':
		player3.chess_no3 = 0;
		player3.enterTrack3 = 0;
		break;
	case 'l':
		player3.chess_no4 = 0;
		player3.enterTrack4 = 0;
		break;
	case 'm':
		player4.chess_no1 = 0;
		player4.enterTrack1 = 0;
		break;
	case 'n':
		player4.chess_no2 = 0;
		player4.enterTrack2 = 0;
		break;
	case 'o':
		player4.chess_no3 = 0;
		player4.enterTrack3 = 0;
		break;
	case 'p':
		player4.chess_no4 = 0;
		player4.enterTrack4 = 0;
		break;
	}
}

void instructions() {
	cout << "The game is for 2-4 players." << endl << endl <<

		"Object of the game :" << endl <<
		"Each player has 4 chesses in 'Base' at the start of the game." << endl <<
		"To be the first person to send all your chesses to 'Home' from your 'Base'." << endl <<
		"The distance from 'Base' to 'Home' is 45 steps." << endl << endl <<

		"Play :" << endl <<
		"Players take turns to throw a die(1 - 6) in a clockwise order, begin with player1 at the top - left corner." << endl << endl <<

		"Case1 : Player rolls a '6', he has 2 options." << endl <<
		"Option1 : The player can send  one of the chesses in 'Base' to the first position on the game board." << endl <<
		"Option2 : The player can option one of the chesses on the game board, and move 6 steps toward 'Home'." << endl << endl <<

		"Case2 : Player rolls a  '1 ' /  '2 ' /  '3 ' /  '4 ' /  '5 '." << endl <<
		"The player can option one of the chess on the game board, and move  '1 ' /  '2 ' /  '3 ' /  '4 ' /  '5 ' steps toward 'Home'." << endl <<
		"If the player has no chess on the game board, turn skipped." << endl << endl <<

		"Special Rules : (Showed in Game Demo)" << endl <<
		"1.If player rolls a  '6 ', he gets a bonus turn.If he rolls a  '6 ' again, he gets a more bonus turns." << endl <<
		"If he rolls a  '6 ' for the third time in a row, turn skipped." << endl << endl <<

		"2.If a chess ends on a position occupied by an opponent’s chess," << endl <<
		"the opponent chess is sent back to the opponent’s  'Base '." << endl << endl <<

		"3.A chess can only reaches Home if it exactly steps on 'X'.If the rolling value" << endl <<
		"exceeded the number of steps required, the chess will move backward for the" << endl <<
		"remaining steps." << endl << endl <<

		"4.Player cannot move a chess to the location that occupied by his other chess." << endl;

	system("pause");
}

void credit() {
	cout << "Group Leader:\nSha Chin Ho(17082240A)\n " << endl
		<< "Group Member: " << endl
		<< "Chan Muk Hang(17120585A)  " << endl
		<< "Luk Ka Chun(17085900A)" << endl
		<< "Yim Tin Long(17111761A)" << endl
		<< "Lam Cheuk Wai(17044105A)" << endl
		<< "Ho Kin Kwan(17114161A)" << endl;
	system("pause");
}

void mode() {
	system("pause");
	system("cls");
	chessboard();
	if (player_no >= 1)
		if (human_no <= 0)player1.info('c');
		else player1.info('h');
		if (player_no >= 2)
			if (human_no <= 1)
				player2.info('c');
			else player2.info('h');
			if (player_no >= 3)
				if (human_no <= 2)player3.info('c');
				else player3.info('h');
				if (player_no >= 4)
					if (human_no <= 3)player4.info('c');
					else player4.info('h');
}

void setting() {
	int option;
	cout << "*** Settings Menu ***\n"
		<< "[1] Number of players\n"
		<< "[2] Number of human players\n"
		<< "[3] Return to Game Menu\n"
		<< "*********************\n"
		<< "Option(1 - 3) :";
	cin >> option;
	switch (option) {
	case 1:
		do {
			system("cls");
			player_detail();
			cout << "\nPlease enter the total number of player( Computer players will be generate automatically when there isn't enough human player): ";
			cin >> player_no;
			cout << endl;
			if (player_no < 2 || player_no > 4) {
				cout << "Player number should be less than 5 and more than 1. Please enter again!\n";
				system("pause");
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (player_no < 2 || player_no>4);
		if (player_no > human_no) {
			computer_no = player_no - human_no;
		}
		else {
			cout << "\nBeacuse of the number of human player is greater the total number of player. The number of human player will be set to be the maximum number automatically.";
			human_no = player_no;
			computer_no = 0;
		}
		player_detail();
		system("pause");
		system("cls");
		setting();
	case 2:
		do {
			system("cls");
			player_detail();
			cout << "\nPlease enter number of human player( Computer players will be generate automatically when there isn't enough human players): ";
			cin >> human_no;
			cout << endl;
			if (human_no > player_no) {
				cout << "Player numbers should be less than or equal to the total number of player. Please enter again!\n";
				system("pause");
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (human_no>player_no);
		computer_no = player_no - human_no;
		player_detail();
		system("pause");
		system("cls");
		setting();

	case 3:
		menu();
break;
	default:
		cout << "Error!Please input again with the given choices!";
		cin.clear();
		cin.ignore(256, '\n');
		system("pause");
		system("cls");
		setting();
		break;
	}
}

void player_detail() {
	cout << "Now number of player: " << player_no << "\nNow number of computer player: " << computer_no << "\nNow number of human player: " << human_no << endl;
}

void GameDemo() {

	int option;

	cout << "**** Demo Menu *****" << endl
		<< "[1] Three consecutive '6'" << endl
		<< "[2] Chess touches home and reverses, reaches home and wins" << endl
		<< "[3] Chess does not self-overlap, and sends back opponent chess" << endl
		<< "[4] Return to Game Menu" << endl
		<< "*********************" << endl
		<< "Option (1 - 4):" << endl;

	cin >> option;

	switch (option) {
	case 1:
		triplesix();
		GameDemo();
		break;
	case 2:
		homerun();
		GameDemo();
		break;
	case 3:
		selfchesswonteat();
		GameDemo();
		break;
	case 4:
		menu();
		break;
	default:
		cout << "Error!Please input again with the given choices!";
		cin.clear();
		cin.ignore(256, '\n');
		system("pause");
		system("cls");
		GameDemo();
		break;
	}

}


void triplesix() {
system("cls");
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 5; j++)
			chesspath[j][i] = 46;
	}
	chesspath[0][3] = 'a';
	chessboard();

	cout << "Player 1: CPU" << endl << "Base: b c d" << endl << "Home:" << endl << " " << endl;
	cout << "Player 2: CPU" << endl << "Base: e f g h" << endl << "Home:" << endl << " " << endl;

	cout << "Player 1 rolled a dice and got 6" << endl << "+-------+\n| *   * |\n| *   * |\n| *   * |\n+-------+\n" << "Available: a b c d" << endl << "Choice(s) chess: a" << endl << "Congraduation! You got a bonus turn!" << endl;

	system("pause");
	system("cls");
	chesspath[0][3 + 6] = 'a';
	chesspath[0][3] = '.';


	chessboard();
	cout << "Player 1: CPU" << endl << "Base: b c d" << endl << "Home:" << endl << " " << endl;
	cout << "Player 2: CPU" << endl << "Base: e f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 1 rolled a dice and got 6" << endl << "+-------+\n| *   * |\n| *   * |\n| *   * |\n+-------+\n" << "Available: a b c d" << endl << "Choice(s) chess: a" << endl << "Congraduation! You got a bonus turn!" << endl;
	system("pause");
	system("cls");
	chesspath[0][3 + 12] = 'a';
	chesspath[0][3 + 6] = '.';


	chessboard();
	cout << "Player 1: CPU" << endl << "Base: b c d" << endl << "Home:" << endl << " " << endl;
	cout << "Player 2: CPU" << endl << "Base: e f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 1 rolled a dice and got 6" << endl << "+-------+\n| *   * |\n| *   * |\n| *   * |\n+-------+\n" << "Available: a b c d" << endl << "Choice(s) chess: a" << endl << "Next Player's turn!" << endl;
	system("pause");
	system("cls");
	chesspath[0][3 + 18] = 'a';
	chesspath[0][3 + 12] = '.';

	chessboard();
	cout << "Player 1: CPU" << endl << "Base: b c d" << endl << "Home:" << endl << " " << endl;
	cout << "Player 2: CPU" << endl << "Base: e f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 2 rolled a dice and got 3" << endl << "+-------+\n|   *   |\n|       |\n| *   * |\n+-------+\n" << "You cannot move!" << endl;
	system("pause");
	system("cls");
	chesspath[0][7 + 6 * 2] = '.';
}

void homerun() {
system("cls");
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 5; j++)
			chesspath[j][i] = 46;
	}
	chesspath[1][2] = 'a';
	chessboard();
	cout << "Player 1: CPU" << endl << "Base: b c d" << endl << "Home:" << endl << " " << endl;
	cout<< "Player 2: CPU" << endl << "Base: e f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 1 rolled a dice and got 1" << "\n+-------+\n|       |\n|   *   |\n|       |\n+-------+\n" << "Available: a" << endl << "Choice(s): a" << endl;
	system("pause");
	system("cls");

	chesspath[1][2] = 46, chesspath[1][3] = 'a';
	chessboard();
	cout << "Player 1: CPU" << endl << "Base: b c d" << endl << "Home:" << endl << " " << endl;
	cout<< "Player 2: CPU" << endl << "Base: e f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 2 rolled a dice and got 3" << "\n+-------+\n|   *   |\n|       |\n| *   * |\n+-------+\n" << "This chess is not available!" << endl;
	system("pause");
	system("cls");

	chessboard();
	cout << "Player 1: CPU" << endl << "Base: b c d" << endl << "Home:" << endl << " " << endl;
	cout<< "Player 2: CPU" << endl << "Base: e f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 1 rolled a dice and got 2" << "\n+-------+\n|   *   |\n|       |\n|   *   |\n+-------+\n" << "Available: a" << endl << "Choice(s): a" << endl;
	system("pause");
	system("cls");
	chesspath[1][3] = '.';
	chessboard();
	cout << "Player 1: CPU" << endl << "Base: b c d" << endl << "Home: a" << endl << " " << endl;
	cout<< "Player 2: CPU" << endl << "Base: e f g h" << endl << "Home:" << endl << " " << endl;
	system("pause");
	system("cls");

}

void selfchesswonteat() {
system("cls");
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 5; j++)
			chesspath[j][i] = 46;
	}
	chesspath[0][4] = 'a', chesspath[0][7] = 'b', chesspath[0][10] = 'e';
	chessboard();
	cout << "Player 1: CPU" << endl << "Base: c d" << endl << "Home:" << endl << " " << endl;
	cout<< "Player 2: CPU" << endl << "Base: f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 1 rolled a dice and got 2" << endl << "+-------+\n|   *   |\n|       |\n|   *   |\n+-------+\n" << "Avaiable chess: a b" << endl<<"Choice(s): b" << endl ;
	system("pause");
	system("cls");

	chesspath[0][7] = '.';
	chesspath[0][9] = 'b';
	chessboard();
	cout << "Player 1: CPU" << endl << "Base: c d" << endl << "Home:" << endl << " " << endl;
	cout<< "Player 2: CPU" << endl << "Base: f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 2 rolled a dice and got 4" << endl << "+-------+\n| *   * |\n|       |\n| *   * |\n+-------+\n" << "Avaiable chess: e" << endl << "Choice(s): e" << endl;
	system("pause");
	system("cls");

	chesspath[0][10] = '.';
	chesspath[0][14] = 'e';
	chessboard();
	cout << "Player 1: CPU" << endl << "Base: c d" << endl << "Home:" << endl << " " << endl;
	cout<< "Player 2: CPU" << endl << "Base: f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 1 rolled a dice and got 5" << endl << "+-------+\n| *   * |\n|   *   |\n| *   * |\n+-------+\n" << "Avaiable chess: b" << endl << "Choice(s): b" << endl;
	system("pause");
	system("cls");

	chesspath[0][9] = '.'; 
	chesspath[0][14] = 'b';
	chessboard();
	cout << "Player 1: CPU" << endl << "Base: c d" << endl << " " << endl;
	cout<< "Player 2: CPU" << endl << "Base: e f g h" << endl << "Home:" << endl << " " << endl;
	cout << "Player 2 rolled a dice and got 3" << endl << "+-------+\n|   *   |\n|       |\n| *   * |\n+-------+\n" << "This chess is not available!" << endl;
	system("pause");
	system("cls");
	chesspath[0][14] = '.', chesspath[0][4] = '.';
}

void leave() {
	char ans[100];
	cout << "Are you sure to jumpout? (Y or N) ";
	while (!(cin >> ans) || ans[1] != '\0' || ans[0] != 'Y'&&ans[0] != 'N'&&ans[0] != 'y'&&ans[0] != 'n') {

		cout << "Error! Please input again with the given choices!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
	}
	if (ans[0] == 'Y' || ans[0] == 'y') {
		cout << "Confirm leaving? (Y or N) ";
		while (!(cin >> ans) || ans[1] != '\0' || ans[0] != 'Y'&&ans[0] != 'N'&&ans[0] != 'y'&&ans[0] != 'n') {

			cout << "Error! Please input again with the given choices!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (ans[0] == 'Y' || ans[0] == 'y') { confirmleaving = 1; }
	}
}

void menu()
{
	int option;
	system("cls");
	cout <<"***Welcome to the LudoGame***\n";
	cout << "*** Game Menu ***" << endl
		<< "[1] Start Game" << endl
		<< "[2] Settings" << endl
		<< "[3] Game Demo" << endl
		<< "[4] Instructions" << endl
		<< "[5] Credits" << endl
		<< "[6] Exit" << endl
		<< "*****************" << endl
		<< "Option (1 - 6):" << endl;

	while (!(cin >> option) || option < 1 || option>6)	
	{
		cout << "Error! Please enter given option (1-6)!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
	}
	system("cls");

	switch (option) {
	case 1:
		game();
		jumpout = 0;
		menu();
		break;
	case 2:
		setting();
		menu();
		break;
	case 3:
		GameDemo();
		menu();
		break;
	case 4:
		instructions();
		menu();
		break;
	case 5:
		credit();
		menu();
		break;
	case 6:
		leave();
		if (confirmleaving == 1) {
			break;
		}
		menu();
	}

}

int main() {
	int t, i = 1;
	t = time(0); 
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 800, 1000, TRUE);//set the console's dimension
	cout << "Loading...";
	while (time(0) <= t + 3) {
		system("cls");
		cout << "Loading...";
		i++;
		if (i != 10) {
			for (int j = i; j >= 0; j--) {
				cout << ".";
			}
		}
		else {
			i = 1;
		}
	}
	system("cls");
	cout <<"***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "*************************** Welcome to Ludo Game **************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n"
		<< "***************************************************************************\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	system("pause");
	menu();
	return 0;
}
