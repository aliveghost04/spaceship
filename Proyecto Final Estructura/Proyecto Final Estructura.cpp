// Proyecto Final Estructura.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<iostream>
#include<conio.h>
#include<string>
#include<stdlib.h>
#include<thread>
#include<list>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESCAPE 27

using namespace std;

int static const MAX_VAL_X = 78;
int static const MAX_VAL_Y = 33;
int static const MIN_VAL_X = 1;
int static const MIN_VAL_Y = 1;
int static const MAX_VAL_X_SPACESHIP = (MAX_VAL_X - 9);
int static const MIN_VAL_X_SPACESHIP = (MIN_VAL_X + 1);
int static const MAX_VAL_Y_SPACESHIP = (MAX_VAL_Y - 5);
int static const MIN_VAL_Y_SPACESHIP = (MIN_VAL_Y + 1);
int static score;
	
bool gameOver = false;
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

class Position {
private:
	int posX;
	int posY;
public:
	Position() {
		this->posX = 0;
		this->posY = 0;
	}

	Position(int posX, int posY) {
		if (posX > MAX_VAL_X) {
			posX = MAX_VAL_X;
		} else if (posX < MIN_VAL_X) {
			posX = MIN_VAL_X;
		}

		if (posY > MAX_VAL_Y) {
			posY = MAX_VAL_Y;
		} else if (posY < MIN_VAL_Y) {
			posY = MIN_VAL_Y;
		}

		this->posX = posX;
		this->posY = posY;
	}
	
	int getPosX() {
		return posX;
	}
	int getPosY() {
		return posY;
	}
};

Position initialPosition((MAX_VAL_X / 2) - 5, (MAX_VAL_Y - 5));

void hideCursor() {
	
	CONSOLE_CURSOR_INFO cci;
	
	cci.bVisible = false;
	cci.dwSize = 2;

	SetConsoleCursorInfo(hCon, &cci);
}

void setCursorPosition(Position p) {
	
	COORD dwPos;

	dwPos.X = p.getPosX();
	dwPos.Y = p.getPosY();

	SetConsoleCursorPosition(hCon, dwPos);
}

void paintLimits() {
	
	for (int x = (MIN_VAL_X + 1); x < MAX_VAL_X; x++) {
		setCursorPosition(Position(x, (MIN_VAL_Y + 1)));
		printf("%c", 205);
		setCursorPosition(Position(x, MAX_VAL_Y));
		printf("%c", 205);
	}

	for (int y = (MIN_VAL_Y + 2); y < MAX_VAL_Y; y++) {
		setCursorPosition(Position(MIN_VAL_X, y));
		printf("%c", 186);
		setCursorPosition(Position(MAX_VAL_X, y));
		printf("%c", 186);
	}

	setCursorPosition(Position(MIN_VAL_X, (MIN_VAL_Y + 1))); 
	printf("%c", 201);
	setCursorPosition(Position(MAX_VAL_X, (MIN_VAL_Y + 1))); 
	printf("%c", 187);
	setCursorPosition(Position(MIN_VAL_X, MAX_VAL_Y)); 
	printf("%c", 200);
	setCursorPosition(Position(MAX_VAL_X, MAX_VAL_Y)); 
	printf("%c", 188);
}


void finishGame() {
	setCursorPosition(initialPosition);
	printf("GAME OVER");
	gameOver = true;
}

class SpaceShip {
private:
	int static const MAX_LIVES = 10;
	int tmpPos;
	Position startPosition;
	Position actualPosition;
	int lives;
	int realLives;
public: 
	SpaceShip(){
		this->startPosition = initialPosition;
		this->actualPosition = startPosition;
		this->lives = MAX_LIVES;
		this->realLives = 2;
	}

	void clean() {
		
		actualPosition = startPosition;
		setCursorPosition(actualPosition);

		setCursorPosition(actualPosition); printf("         ");
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
		setCursorPosition(actualPosition); printf("         ");
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
		setCursorPosition(actualPosition); printf("         ");
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
		setCursorPosition(actualPosition); printf("         ");
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
		setCursorPosition(actualPosition); printf("         ");
	}

	void explode() {

		int cantidad = 3;
		for (int x = 0; x < cantidad; x++) {
			clean();
			actualPosition = startPosition;
			setCursorPosition(actualPosition);
		
			printf("   ***   ");
			actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
			setCursorPosition(actualPosition);
			printf("  *****  ");
			actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
			setCursorPosition(actualPosition);
			printf(" ******* ");
			actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
			setCursorPosition(actualPosition);
			printf("  *****  ");
			actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
			setCursorPosition(actualPosition);
			printf("   ***   ");
			Sleep(500);

			clean();
			actualPosition = startPosition;
			setCursorPosition(actualPosition);
		
			printf("*  ***  *");
			actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
			setCursorPosition(actualPosition);
			printf(" ******* ");
			actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
			setCursorPosition(actualPosition);
			printf("  *****  ");
			actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
			setCursorPosition(actualPosition);
			printf(" ******* ");
			actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
			setCursorPosition(actualPosition);
			printf("*  ***  *");
			Sleep(500);
		}
	}

	void addLive() {
		if (lives < MAX_LIVES && lives > 0) {
			lives++;
		}
	}

	void removeLive() {
		if (lives > 1) {
			lives--;
		} else {
			explode();
			realLives--;
			lives = MAX_LIVES;
			if (realLives == 0) 
				finishGame();
		}
	}

	void printLives() {
		setCursorPosition(Position((MAX_VAL_X / 2) - (MAX_VAL_X / 4), MIN_VAL_Y));
		printf("Score: %d", score);
		setCursorPosition(Position(MAX_VAL_X - (MAX_VAL_X / 2), MIN_VAL_Y));
		printf("Vidas: %d", realLives);
		setCursorPosition(Position(MAX_VAL_X - (MAX_VAL_X / 3), MIN_VAL_Y));
		printf("Salud: ");
		setCursorPosition(Position((MAX_VAL_X + 7) - (MAX_VAL_X / 3), MIN_VAL_Y));
		printf("          ");
		for (int x = 0; x < lives; x++) {
			setCursorPosition(Position((MAX_VAL_X + 7) - (MAX_VAL_X / 3) + x, MIN_VAL_Y));
			printf("%c", 3);
		}
	}

	Position getPosition() {
		return startPosition;
	}

	void paint() {
		
		actualPosition = startPosition;
		setCursorPosition(actualPosition);

		setCursorPosition(actualPosition); printf("   #    ");
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
		setCursorPosition(actualPosition); printf("  /^%c   ", 92);
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
		setCursorPosition(actualPosition); printf(" /^^^%c  ", 92);
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
		setCursorPosition(actualPosition); printf("/()_()%c", 92);
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
		setCursorPosition(actualPosition); printf(" ** **  ");
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);

		printLives();

	}

	void move() {
		if (_kbhit()) {

			actualPosition = startPosition;
			clean();
			
			switch (_getch()) {
				case RIGHT:
					if ((startPosition.getPosX() + 1) > MAX_VAL_X_SPACESHIP) 
						tmpPos = MAX_VAL_X_SPACESHIP;
					else
						tmpPos = startPosition.getPosX() + 1;
					startPosition = Position(tmpPos, startPosition.getPosY());
					break;
				case LEFT:
					if ((startPosition.getPosX() - 1) < MIN_VAL_X_SPACESHIP) 
						tmpPos = MIN_VAL_X_SPACESHIP;
					else
						tmpPos = startPosition.getPosX() - 1;
					startPosition = Position(tmpPos, startPosition.getPosY());
					break;
				/*case UP:
					if ((startPosition.getPosY() - 1) < MIN_VAL_Y_SPACESHIP) 
						tmpPos = MIN_VAL_Y_SPACESHIP;
					else
						tmpPos = startPosition.getPosY() - 1;
					startPosition = Position(startPosition.getPosX(), tmpPos);
					break;
				case DOWN:
					if ((startPosition.getPosY() + 1) > MAX_VAL_Y_SPACESHIP) 
						tmpPos = MAX_VAL_Y_SPACESHIP;
					else
						tmpPos = startPosition.getPosY() + 1;
					startPosition = Position(startPosition.getPosX(), tmpPos);
					break;*/
			}
			
			paint();
			printLives();
		}	
	}
};

class Ammo {
private:
	Position startPosition;
public:
	Ammo(SpaceShip *spaceShip) : startPosition(spaceShip->getPosition()) {
		startPosition = Position(startPosition.getPosX() + 3, startPosition.getPosY() - 1);
	}

	Position getPosition() {
		return startPosition;
	}

	void clean() {
		
		setCursorPosition(startPosition);
		printf(" ");
	}

	void paint() {
		
		clean();
		setCursorPosition(startPosition);
		printf("^");
	}

	void move() {
		clean();
		startPosition = Position(startPosition.getPosX(), startPosition.getPosY() - 1);
		if (startPosition.getPosY() == (MIN_VAL_Y + 1)) {
			startPosition = Position(startPosition.getPosX(), (MIN_VAL_Y + 2));
		}
		paint();
	}
};

class Asteroid {
private:
	Position startPosition;
	Position actualPosition;
public:
	Asteroid() : startPosition(rand() % (MAX_VAL_X - 1), (MIN_VAL_Y + 2)) {
		if (startPosition.getPosX() <= (MIN_VAL_X + 1))
			startPosition = Position((MIN_VAL_X + 2), startPosition.getPosY());
	}

	void crash(SpaceShip *spaceShip) {
		if (startPosition.getPosX() >= spaceShip->getPosition().getPosX() && 
			startPosition.getPosX() < spaceShip->getPosition().getPosX() + 7 &&
			startPosition.getPosY() >= spaceShip->getPosition().getPosY() &&
			startPosition.getPosY() <= spaceShip->getPosition().getPosY() + 5) {
			
				spaceShip->removeLive();
				spaceShip->paint();

				startPosition = Position(rand() % (MAX_VAL_X - 1), (MIN_VAL_Y + 2));
				if (startPosition.getPosX() <= (MIN_VAL_X + 1))
					startPosition = Position((MIN_VAL_X + 2), startPosition.getPosY());
		}
	}

	Position getPosition() {
		return startPosition;
	}

	void paint() {
		setCursorPosition(startPosition);
		printf("%c", 64);
	}

	void clean() {
		setCursorPosition(startPosition);
		printf(" ");
	}

	void move() {
		actualPosition = startPosition;
		clean();
		actualPosition = Position(actualPosition.getPosX(), actualPosition.getPosY() + 1);
		startPosition = actualPosition;
		if (startPosition.getPosY() > (MAX_VAL_Y - 1)) {
			startPosition = Position(rand() % (MAX_VAL_X - 1), (MIN_VAL_Y + 2));
			if (startPosition.getPosX() <= (MIN_VAL_X + 1))
				startPosition = Position((MIN_VAL_X + 2), startPosition.getPosY());
			score+= 100;
		}
		paint();
	}
};

void printPlayerName(string *name) {
	setCursorPosition(Position(0, 0));
	cout << "Jugador: " + *name;
}

void threadSpaceShipMoves(SpaceShip *spaceShip) {
	spaceShip->move();
}

void startGame(string *name) {
	
	system("cls");
	printPlayerName(name);
	paintLimits();
	hideCursor();

	SpaceShip spaceShip;
	spaceShip.paint();
	spaceShip.printLives();

	list<Asteroid*> asteroids;
	list<Asteroid*>::iterator iteratorAsteroids;
	asteroids.push_back(new Asteroid);
	asteroids.push_back(new Asteroid);
	asteroids.push_back(new Asteroid);

	for(iteratorAsteroids = asteroids.begin(); iteratorAsteroids != asteroids.end(); iteratorAsteroids++) {
		(*iteratorAsteroids)->paint();
	}

	list<Ammo*> ammos;	
	list<Ammo*>::iterator iteratorAmmos;
	
	setCursorPosition(initialPosition);
	
	while(!gameOver) {

		if (_kbhit()) {
			switch(_getch()) {	
				case 'x':
					ammos.push_back(new Ammo(&spaceShip));
					break;
				case ESCAPE:
					setCursorPosition(Position((MAX_VAL_X / 4), (MAX_VAL_Y / 3) + 1));
					cout << "##########################################" << endl;
					setCursorPosition(Position((MAX_VAL_X / 4), (MAX_VAL_Y / 3) + 2));
					cout << "#     #       # #      |    ##       ### #" << endl;
					setCursorPosition(Position((MAX_VAL_X / 4), (MAX_VAL_Y / 3) + 3));
					cout << "#    # #      #   #        #  #     #    #" << endl;
					setCursorPosition(Position((MAX_VAL_X / 4), (MAX_VAL_Y / 3) + 4));
					cout << "#   #   #     #    #   #  #    #      #  #" << endl;
					setCursorPosition(Position((MAX_VAL_X / 4), (MAX_VAL_Y / 3) + 5));
					cout << "#  #  #  #    #   #    #   #  #        # #" << endl;
					setCursorPosition(Position((MAX_VAL_X / 4), (MAX_VAL_Y / 3) + 6));
					cout << "# #       #   # #      #    ##      ###  #" << endl;
					setCursorPosition(Position((MAX_VAL_X / 4), (MAX_VAL_Y / 3) + 7));
					cout << "##########################################" << endl;
					Sleep(3000);
					exit(EXIT_SUCCESS);
					break;
			}
		}
		
		for(iteratorAsteroids = asteroids.begin(); iteratorAsteroids != asteroids.end(); iteratorAsteroids++) {
			(*iteratorAsteroids)->move();
			(*iteratorAsteroids)->crash(&spaceShip);
		}
	
		for(iteratorAsteroids = asteroids.begin(); iteratorAsteroids != asteroids.end(); iteratorAsteroids++) {
			for(iteratorAmmos = ammos.begin(); iteratorAmmos != ammos.end(); ) {
				if ((*iteratorAmmos)->getPosition().getPosX() == (*iteratorAsteroids)->getPosition().getPosX() && 
					((*iteratorAsteroids)->getPosition().getPosY() + 1 == (*iteratorAmmos)->getPosition().getPosY() || (*iteratorAmmos)->getPosition().getPosY() == (*iteratorAsteroids)->getPosition().getPosY())) {
					
						score+= 100;
						(*iteratorAmmos)->clean();
						delete (*iteratorAmmos);
						iteratorAmmos = ammos.erase(iteratorAmmos);
						
						asteroids.push_back(new Asteroid);
						(*iteratorAsteroids)->clean();
						delete (*iteratorAsteroids);
						iteratorAsteroids = asteroids.erase(iteratorAsteroids);
						
				} else {
					iteratorAmmos++;
				}
			}
		}
		
		for(iteratorAmmos = ammos.begin(); iteratorAmmos != ammos.end(); ) {
			(*iteratorAmmos)->move();
			
			if ((*iteratorAmmos)->getPosition().getPosY() == (MIN_VAL_Y + 2)) {
				(*iteratorAmmos)->clean();
				delete(*iteratorAmmos);
				iteratorAmmos = ammos.erase(iteratorAmmos);
			} else {
				iteratorAmmos++;
			}
		}
		
		threadSpaceShipMoves(&spaceShip);
		if (score > 2000) {
			if ((rand() % 7) == 0) {
				if((rand() % 5) == 0)
					if (asteroids.size() < 10) 
						asteroids.push_back(new Asteroid);
			}
		}
		Sleep(70);
		
	}
}

int _tmain(int argc)
{
	cout << "Si desea salir en cualquier momento, utilice P" << endl << endl  ;
	
	cout << "Introduce tu nombre: ";
	string name;
	getline(cin, name);
	name = name.substr(0, 9);
	while (true) {
		startGame(&name);
		gameOver = false;
		system("pause>null");
	}

	return 0;
}
