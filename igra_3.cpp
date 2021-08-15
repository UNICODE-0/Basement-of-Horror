#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <string>
#include <vector>
#include <conio.h>
//#define DEBUG
const int stroki = 10, stolbi = 14, i = 6, j = 12;
const char pusto = ' ', stena = (char)219, govard = '@', dver = (char)206, bulletEnemy1 = (char)271 , Enemy1 = (char)257, bulletGovard = (char)253, river = (char)176, wall1 = (char)205, wall2 = (char)186, Enemy2 = (char)258;
int point_of_control = 0, point_of_control2 = 0, point_of_control3 = 0, temp = 0, temp2 = 0, handicap = 0, handicap2 = 0, health = 3, side_control = 0, once_for_Enemy1 = 0 ,once_for_govard = 0, Buffer[6][j];
using namespace std;
void setcur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};
void show(char mass[stroki][stolbi]) {
	if (mass[0][0] == ' ') mass[0][0] = stena;
	for (int i = 0; i < stroki; i++) {
		for (int j = 0; j < stolbi; j++) {
			cout << mass[i][j];
		}
		cout << endl;
	}
	cout << "\n\n\n\n\n------------------------------------------------\nWelcome to the basement of horror!\nGo through 10 rooms and you're free!!!\nYou only have three lives, don't waste them.\nBackground Information :\nyou \t" << govard << "\nEnemy\t" << Enemy1 << "\nEnemy2 \t" << Enemy2 << "\nbullet gowarad \t" << bulletGovard << "\nbullet enemy \t" << bulletEnemy1 << "\nRiver(abyss) \t" << river << "\nDoor \t" << dver << "\nWall \t" << stena <<"\nflimsy wall \t" << wall1<<" "<<wall2 << "\nHealth \t" << (char)3 << endl;
	cout << "Conrtols:\n" << "up\t'8'\n" << "down\t'2'\n" << "right\t'6'\n" << "left\t'4'\n";
	cout << "Shoot up\t'80'\n" << "Shoot down\t'20'\n" << "Shoot right\t'60'\n" << "Shoot left\t'40'\n";
	cout << "If the screen flickers very often, it means you have received damage, be careful!";
	setcur(0, 10);
}
void hit(char mass[stroki][stolbi]) {
	for (int i = 0; i < 20; i++)
	{
		show(mass);
		system("cls");
	}
}
void up(char mass[stroki][stolbi],const char who, int i,int j) {
	if (mass[i - 1][j] != river and mass[i - 1][j] != dver and mass[i - 1][j] != wall1 and mass[i - 1][j] != wall2) {
		mass[i][j] = pusto;
		mass[i - 1][j] = who;
	}
}
void down(char mass[stroki][stolbi], const char who, int const i, int const j) {
	if (mass[i + 1][j] != river and mass[i + 1][j] != dver and mass[i + 1][j] != wall1 and mass[i + 1][j] != wall2) {
		mass[i][j] = pusto;
		mass[i + 1][j] = who;
	}
}
void right(char mass[stroki][stolbi], const char who, int const i, int const j) {
	if (mass[i][j + 1] != river and mass[i][j + 1] != dver and mass[i][j + 1] != wall1 and mass[i][j + 1] != wall2) {
		mass[i][j] = pusto;
		mass[i][j + 1] = who;
	}
}
void left(char mass[stroki][stolbi], const char who, int const i, int const j) {
	if (mass[i][j - 1] != river and mass[i][j - 1] != dver and mass[i][j - 1] != wall1 and mass[i][j - 1] != wall2) {
		mass[i][j] = pusto;
		mass[i][j - 1] = who;
	}
}
void SearchGovard(char mass[stroki][stolbi],int Positions[i][j]) {
	for (int i = 0; i < stroki; i++) {
		for (int j = 0; j < stolbi; j++) {
			if (mass[i][j] == govard) {
				Positions[0][0] = i;
				Positions[0][1] = j;
			}
		}
	}
}
void SearchEnemy1(char mass[stroki][stolbi], int Positions[i][j]) {
	for (int k = 0; k <= 8 ;) {
		for (int i = 0; i < stroki; i++) {
			for (int j = 0; j < stolbi; j++) {
				if (mass[i][j] == Enemy1) {
					Positions[1][0 + k] = i;
					Positions[1][1 + k] = j;
					k += 4;
				}
			}
		}
		goto link1;
	}
	link1:
	return;
}
void SearchEnemy2(char mass[stroki][stolbi], int Positions2[i][j]) {
	for (int k = 0; k <= 8;) {
		for (int i = 0; i < stroki; i++) {
			for (int j = 0; j < stolbi; j++) {
				if (mass[i][j] == Enemy2) {
					Positions2[1][0 + k] = i;
					Positions2[1][1 + k] = j;
					k += 4;
				}
			}
		}
		goto link1;
	}
link1:
	return;
}
int count_of_Enemy1(char mass[stroki][stolbi]) {
	int count_of_Enemy1 = 0;
		for (int i = 0; i < stroki; i++) {
			for (int j = 0; j < stolbi; j++) {
				if (mass[i][j] == Enemy1) {
					count_of_Enemy1++;
				}
			}
		}
	return count_of_Enemy1;
}
int count_of_Enemy2(char mass[stroki][stolbi]) {
	int count_of_Enemy1 = 0;
	for (int i = 0; i < stroki; i++) {
		for (int j = 0; j < stolbi; j++) {
			if (mass[i][j] == Enemy2) {
				count_of_Enemy1++;
			}
		}
	}
	return count_of_Enemy1;
}
void SearchBulletEnemy1(char mass[stroki][stolbi], int Positions[i][j]) { 
int count_of_bullet = 0;
int queue[8] = { 0,0,0,0,0,0,0,0 };
	for (int k = count_of_Enemy1(mass) * 4 - 4; k >= 0; k -= 4) {
		for (int i = 0; i < stroki; i++) {
			for (int j = 0; j < stolbi; j++) {
				if (mass[i][j] == bulletEnemy1) {

					for (int p = 0; p <= 8; p += 4)
					{
						if (Positions[1][1 + p] == j and queue[4] != Positions[1][0 + p] and queue[5] != Positions[1][1 + p] and queue[6] != Positions[1][0 + p] and queue[7] != Positions[1][1 + p]) {
							if ((Positions[1][2 + p] - i == -1 or Positions[1][2 + p] - i == 1 or Positions[1][2 + p] - i == 0) and (Positions[1][3 + p] - j == -1 or Positions[1][3 + p] - j == 1 or Positions[1][3 + p] - j == 0)) {
								Positions[1][2 + p] = i;
								Positions[1][3 + p] = j;
								k -= 4;
							}
							else goto next;
							if (p == 0) {
								queue[0] = Positions[1][0 + p];
								queue[1] = Positions[1][1 + p];

							}
							if (p == 4) {
								queue[2] = Positions[1][0 + p];
								queue[3] = Positions[1][1 + p];
							}
							continue;
						}
						next:
						if (Positions[1][0 + p] == i and queue[0] != Positions[1][0 + p] and queue[1] != Positions[1][1 + p] and queue[2] != Positions[1][0 + p] and queue[3] != Positions[1][1 + p]) {
							if ((Positions[1][2 + p] - i == -1 or Positions[1][2 + p] - i == 1 or Positions[1][2 + p] - i == 0) and (Positions[1][3 + p] - j == -1 or Positions[1][3 + p] - j == 1 or Positions[1][3 + p] - j == 0)) {
								Positions[1][2 + p] = i;
								Positions[1][3 + p] = j;
								k -= 4;
							} else goto next2;
								if (p == 0) {
									queue[4] = Positions[1][0 + p];
									queue[5] = Positions[1][1 + p];
								}
								if (p == 4) {
									queue[6] = Positions[1][0 + p];
									queue[7] = Positions[1][1 + p];
								}
							next2:
								continue;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < 8; i +=4) {
		if (Positions[1][2 + i] != 0) count_of_bullet++;
	}
	if (count_of_bullet > temp or temp == 0) {
		temp = count_of_bullet;
	}
	if (Positions[1][2] == 0 and Positions[1][6] == 0 and Positions[1][10] == 0) temp = 0;
}
void SearchBulletEnemy2(char mass[stroki][stolbi], int Positions[i][j]) {
	int count_of_bullet = 0;
	int queue[8] = { 0,0,0,0,0,0,0,0 };
	for (int k = count_of_Enemy2(mass) * 4 - 4; k >= 0; k -= 4) {
		for (int i = 0; i < stroki; i++) {
			for (int j = 0; j < stolbi; j++) {
				if (mass[i][j] == bulletEnemy1) {

					for (int p = 0; p <= 8; p += 4)
					{
						if (Positions[1][1 + p] == j and queue[4] != Positions[1][0 + p] and queue[5] != Positions[1][1 + p] and queue[6] != Positions[1][0 + p] and queue[7] != Positions[1][1 + p]) {
							if ((Positions[1][2 + p] - i == -1 or Positions[1][2 + p] - i == 1 or Positions[1][2 + p] - i == 0) and (Positions[1][3 + p] - j == -1 or Positions[1][3 + p] - j == 1 or Positions[1][3 + p] - j == 0)) {
								Positions[1][2 + p] = i;
								Positions[1][3 + p] = j;
								k -= 4;
							}
							else goto next;
							if (p == 0) {
								queue[0] = Positions[1][0 + p];
								queue[1] = Positions[1][1 + p];

							}
							if (p == 4) {
								queue[2] = Positions[1][0 + p];
								queue[3] = Positions[1][1 + p];
							}
							continue;
						}
					next:
						if (Positions[1][0 + p] == i and queue[0] != Positions[1][0 + p] and queue[1] != Positions[1][1 + p] and queue[2] != Positions[1][0 + p] and queue[3] != Positions[1][1 + p]) {
							if ((Positions[1][2 + p] - i == -1 or Positions[1][2 + p] - i == 1 or Positions[1][2 + p] - i == 0) and (Positions[1][3 + p] - j == -1 or Positions[1][3 + p] - j == 1 or Positions[1][3 + p] - j == 0)) {
								Positions[1][2 + p] = i;
								Positions[1][3 + p] = j;
								k -= 4;
							}
							else goto next2;
							if (p == 0) {
								queue[4] = Positions[1][0 + p];
								queue[5] = Positions[1][1 + p];
							}
							if (p == 4) {
								queue[6] = Positions[1][0 + p];
								queue[7] = Positions[1][1 + p];
							}
						next2:
							continue;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < 8; i += 4) {
		if (Positions[1][2 + i] != 0) count_of_bullet++;
	}
	if (count_of_bullet > temp or temp == 0) {
		temp = count_of_bullet;
	}
	if (Positions[1][2] == 0 and Positions[1][6] == 0 and Positions[1][10] == 0) temp = 0;
}
void firstshootEnemy1(char mass[stroki][stolbi], int Positions[i][j], int const i, int const j, string side) {
	int one_in_arrow_i = 0, one_in_arrow_j = 0;
		if (side == "up" and one_in_arrow_j == 0 and mass[i - 1][j] != stena and mass[i - 1][j] != wall1 and mass[i - 1][j] != wall2 and mass[i - 1][j] != bulletEnemy1) {
			if (mass[i - 1][j] == govard) {
				health--;
				hit(mass);
				goto link1;
			}
			mass[i - 1][j] = bulletEnemy1;
			for (int k = 0; k <= 8; k+= 4)
			{
				if (Positions[1][0 + k] == i and Positions[1][1 + k] == j) {
					Positions[1][2+k] = i - 1;
					Positions[1][3 + k] = j;
				}
			}
		}
		link1:
		if (side == "down" and one_in_arrow_j == 0 and mass[i + 1][j] != stena and mass[i + 1][j] != wall1 and mass[i + 1][j] != wall2 and mass[i + 1][j] != bulletEnemy1) {
			if (mass[i + 1][j] == govard) {
				health--;
				hit(mass);
				goto link2;
			}
			mass[i + 1][j] = bulletEnemy1;
			for (int k = 0; k <= 8; k += 4)
			{
				if (Positions[1][0 + k] == i and Positions[1][1 + k] == j) {
					Positions[1][2 + k] = i + 1;
					Positions[1][3 + k] = j;
				}
			}
		}
		link2:
		if (side == "right" and one_in_arrow_i == 0 and mass[i][j + 1] != stena and mass[i][j + 1] != wall1 and mass[i][j + 1] != wall2 and mass[i][j + 1] != bulletEnemy1) {
			if (mass[i][j + 1] == govard) {
				health--;
				hit(mass);
				goto link3;
			}
			mass[i][j + 1] = bulletEnemy1;
			for (int k = 0; k <= 8; k += 4)
			{
				if (Positions[1][0 + k] == i and Positions[1][1 + k] == j) {
					Positions[1][2 + k] = i;
					Positions[1][3 + k] = j + 1;
				}
			}
		}
		link3:
		if (side == "left" and one_in_arrow_i == 0 and mass[i][j - 1] != stena and mass[i][j - 1] != wall1 and mass[i][j - 1] != wall2 and mass[i][j - 1] != bulletEnemy1) {
			if (mass[i][j - 1] == govard) {
				health--;
				hit(mass);
				goto link4;
			}
			mass[i][j - 1] = bulletEnemy1;
			for (int k = 0; k <= 8; k += 4)
			{
				if (Positions[1][0 + k] == i and Positions[1][1 + k] == j) {
					Positions[1][2 + k] = i;
					Positions[1][3 + k] = j - 1 ;
				}
			}
		}
		link4:
		show(mass);
}
void shootEnemy1(char mass[stroki][stolbi],int Positions[i][j], int Positions2[i][j],int &health,const int k) {

		if (Positions[4][0 + k] == 1) {
			mass[Positions[1][2 + k]][Positions[1][3 + k]] = pusto;
			if (mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == stena or mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == dver or mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == wall1 or mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == wall2) {

				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
			}
			else if (mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == govard) {
				health--;
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
				handicap++;
				hit(mass);
			}
			else if (mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == bulletEnemy1) {
				mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] = ' ';
					Positions2[1][2 + k] = 0;
					Positions2[1][3 + k] = 0;
					Positions2[4][0 + k] = 0;
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
			}
			else if (mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == Enemy1 or mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == Enemy2) {
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
				mass[Positions[1][2 + k]][Positions[1][3 + k]] = ' ';
			}
			else{
				mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] = bulletEnemy1;
			}
		}
		else if (Positions[4][0 + k] == 2) {
			mass[Positions[1][2 + k]][Positions[1][3 + k]] = pusto;
			if (mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == stena or mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == dver or mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == wall1 or mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == wall2) {

				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
			}
			else if (mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == govard) {
				health--;
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
				handicap++;
				hit(mass);
			}
			else if (mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == bulletEnemy1) {
				mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] = ' ';
					Positions2[1][2 + k] = 0;
					Positions2[1][3 + k] = 0;
					Positions2[4][0 + k] = 0;
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
			}
			else if (mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == Enemy1 or mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == Enemy2) {
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
				mass[Positions[1][2 + k]][Positions[1][3 + k]] = ' ';
			}
			else{
				mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] = bulletEnemy1;
			}
		}
		else if (Positions[4][0 + k] == 3) {
			mass[Positions[1][2 + k]][Positions[1][3 + k]] = pusto;
			if (mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == stena or mass[Positions[1][2 + k]][Positions[1][3 + k]+1] == dver or mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == wall1 or mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == wall2) {

				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
			}
			else if (mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == govard) {
				health--;
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
				handicap++;
				hit(mass);
			}
			else if (mass[Positions[1][2 + k]][Positions[1][3 + k]+1] == bulletEnemy1) {
				mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] = ' ';
					Positions2[1][2 + k] = 0;
					Positions2[1][3 + k] = 0;
					Positions2[4][0 + k] = 0;
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
			}
			else if (mass[Positions[1][2 + k]][Positions[1][3 + k]+1] == Enemy1 or mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == Enemy2) {
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
				mass[Positions[1][2 + k]][Positions[1][3 + k]] = ' ';
			}
			else {
				mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] = bulletEnemy1;
			}
		}
		else if (Positions[4][0 + k] == 4) {
			mass[Positions[1][2 + k]][Positions[1][3 + k]] = pusto;
			if (mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == stena or mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == dver or mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == wall1 or mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == wall2) {

				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
			}
			else if (mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == govard) {
				health--;
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
				handicap++;
				hit(mass);
			}
			else if (mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == bulletEnemy1) {
				mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] = ' ';
				Positions2[1][2 + k] = 0;
				Positions2[1][3 + k] = 0;
				Positions2[4][0 + k] = 0;
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
			}
			else if (mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == Enemy1 or mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == Enemy2) {
				Positions[1][2 + k] = 0;
				Positions[1][3 + k] = 0;
				Positions[4][0 + k] = 0;
				mass[Positions[1][2 + k]][Positions[1][3 + k]] = ' ';
			}
			else {
				mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] = bulletEnemy1;
			}
		}
	show(mass);
}
void shootEnemy2(char mass[stroki][stolbi], int Positions[i][j],int Positions2[i][j], int& health, const int k) {

	if (Positions[4][0 + k] == 1) {
		mass[Positions[1][2 + k]][Positions[1][3 + k]] = pusto;
		if (mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == stena or mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == dver or mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == wall1 or mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == wall2) {

			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
		}
		else if (mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == govard) {
			health--;
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			handicap2++;
			hit(mass);
		}
		else if (mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == bulletEnemy1) {
			mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] = ' ';
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			Positions2[1][2 + k] = 0;
			Positions2[1][3 + k] = 0;
			Positions2[4][0 + k] = 0;
		}
		else if (mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == Enemy1 or mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == Enemy2) {
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			mass[Positions[1][2 + k]][Positions[1][3 + k]] = ' ';
		}
		else {
			mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] = bulletEnemy1;
		}
	}
	else if (Positions[4][0 + k] == 2) {
		mass[Positions[1][2 + k]][Positions[1][3 + k]] = pusto;
		if (mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == stena or mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == dver or mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == wall1 or mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == wall2) {

			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
		}
		else if (mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == govard) {
			health--;
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			handicap2++;
			hit(mass);
		}
		else if (mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == bulletEnemy1) {
			mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] = ' ';
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			Positions2[1][2 + k] = 0;
			Positions2[1][3 + k] = 0;
			Positions2[4][0 + k] = 0;
		}
		else if (mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] == Enemy1 or mass[Positions[1][2 + k] - 1][Positions[1][3 + k]] == Enemy2) {
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			mass[Positions[1][2 + k]][Positions[1][3 + k]] = ' ';
		}
		else {
			mass[Positions[1][2 + k] + 1][Positions[1][3 + k]] = bulletEnemy1;
		}
	}
	else if (Positions[4][0 + k] == 3) {
		mass[Positions[1][2 + k]][Positions[1][3 + k]] = pusto;
		if (mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == stena or mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == dver or mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == wall1 or mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == wall2) {

			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
		}
		else if (mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == govard) {
			health--;
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			handicap2++;
			hit(mass);
		}
		else if (mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == bulletEnemy1) {
			mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] = ' ';
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			Positions2[1][2 + k] = 0;
			Positions2[1][3 + k] = 0;
			Positions2[4][0 + k] = 0;
		}
		else if (mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == Enemy1 or mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] == Enemy2) {
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			mass[Positions[1][2 + k]][Positions[1][3 + k]] = ' ';
		}
		else {
			mass[Positions[1][2 + k]][Positions[1][3 + k] + 1] = bulletEnemy1;
		}
	}
	else if (Positions[4][0 + k] == 4) {
		mass[Positions[1][2 + k]][Positions[1][3 + k]] = pusto;
		if (mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == stena or mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == dver or mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == wall1 or mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == wall2) {

			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
		}
		else if (mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == govard) {
			health--;
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			handicap2++;
			hit(mass);
		}
		else if (mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == bulletEnemy1) {
			mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] = ' ';
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			Positions2[1][2 + k] = 0;
			Positions2[1][3 + k] = 0;
			Positions2[4][0 + k] = 0;
		}
		else if (mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == Enemy1 or mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] == Enemy2) {
			Positions[1][2 + k] = 0;
			Positions[1][3 + k] = 0;
			Positions[4][0 + k] = 0;
			mass[Positions[1][2 + k]][Positions[1][3 + k]] = ' ';
		}
		else {
			mass[Positions[1][2 + k]][Positions[1][3 + k] - 1] = bulletEnemy1;
		}
	}
	show(mass);
}
void SearchBulletGovard(char mass[stroki][stolbi], int Positions[i][j]) {
	
		for (int i = 0; i < stroki; i++) {
			for (int j = 0; j < stolbi; j++) {
				if (mass[i][j] == bulletGovard) {
					Positions[0][2] = i;
					Positions[0][3] = j;

				}
			}
		}
}
void firstshootGovard(char mass[stroki][stolbi], int Positions[i][j], int const i, int const j, string side) {
	
	if (side == "up" and once_for_govard == 0) {
		if (mass[i - 1][j] == Enemy1) {
			mass[i - 1][j] = ' ';
			for (int j = 0; j < 12; j++) {
				Buffer[0][j] = Positions[1][j];
				if (Positions[1][j] == Positions[0][2] - 1 and Positions[1][j + 1] == Positions[0][3]) {
					Buffer[1][j + 2] = Positions[1][j + 2];
					Buffer[1][j + 3] = Positions[1][j + 3];
					Buffer[4][j] = Positions[4][j];
				}
				Positions[1][j] = 0;
				Positions[4][j] = 0;
			}
			goto link1;
		}
		if (mass[i - 1][j] == stena) goto link1;
		if (mass[i - 1][j] == wall1 or mass[i - 1][j] == wall2) {
			mass[i - 1][j] = ' ';
			goto link1;
		}
		mass[i - 1][j] = bulletGovard;
		for (int k = 0; k <= 8; k += 4)
		{
			if (Positions[0][0 + k] == i and Positions[0][1 + k] == j) {
				Positions[0][2 + k] = i - 1;
				Positions[0][3 + k] = j;
				Positions[5][0] = 1;
				once_for_govard++;
			}
		}
	}
link1:
	if (side == "down" and once_for_govard == 0) {
		if (mass[i + 1][j] == Enemy1) {
			mass[i + 1][j] = ' ';
			for (int j = 0; j < 12; j++) {
				Buffer[0][j] = Positions[1][j];
				if (Positions[1][j] == Positions[0][2] + 1 and Positions[1][j + 1] == Positions[0][3]) {
					Buffer[1][j + 2] = Positions[1][j + 2];
					Buffer[1][j + 3] = Positions[1][j + 3];
					Buffer[4][j] = Positions[4][j];
				}
				Positions[1][j] = 0;
				Positions[4][j] = 0;
			}
			goto link2;
		}
		if (mass[i + 1][j] == stena) goto link2;
		if (mass[i + 1][j] == wall1 or mass[i + 1][j] == wall2) {
			mass[i + 1][j] = ' ';
			goto link2;
		}
		mass[i + 1][j] = bulletGovard;
		for (int k = 0; k <= 8; k += 4)
		{
			if (Positions[0][0 + k] == i and Positions[0][1 + k] == j) {
				Positions[0][2 + k] = i + 1;
				Positions[0][3 + k] = j;
				Positions[5][0] = 2;
				once_for_govard++;
			}
		}
	}
link2:
	if (side == "right" and once_for_govard == 0) {
		if (mass[i][j + 1] == Enemy1) {
			mass[i][j + 1] = ' ';
			for (int j = 0; j < 12; j++) {
				Buffer[0][j] = Positions[1][j];
				if (Positions[1][j] == Positions[0][2] and Positions[1][j + 1] == Positions[0][3] + 1) {
					Buffer[1][j + 2] = Positions[1][j + 2];
					Buffer[1][j + 3] = Positions[1][j + 3];
					Buffer[4][j] = Positions[4][j];
				}
				Positions[1][j] = 0;
				Positions[4][j] = 0;
			}
			goto link3;
		}
		if (mass[i][j + 1] == stena) goto link3;
		if (mass[i][j+1] == wall1 or mass[i][j+1] == wall2) {
			mass[i][j+1] = ' ';
			goto link3;
		}
		mass[i][j + 1] = bulletGovard;
		for (int k = 0; k <= 8; k += 4)
		{
			if (Positions[0][0 + k] == i and Positions[0][1 + k] == j) {
				Positions[0][2 + k] = i;
				Positions[0][3 + k] = j + 1;
				Positions[5][0] = 3;
				once_for_govard++;
			}
		}
	}
link3:
	if (side == "left" and once_for_govard == 0) {
		if (mass[i][j - 1] == Enemy1) {
			mass[i][j - 1] = ' ';
			for (int j = 0; j < 12; j++) {
				Buffer[0][j] = Positions[1][j];
				if (Positions[1][j] == Positions[0][2] and Positions[1][j + 1] == Positions[0][3] - 1) {
					Buffer[1][j + 2] = Positions[1][j + 2];
					Buffer[1][j + 3] = Positions[1][j + 3];
					Buffer[4][j] = Positions[4][j];
				}
				Positions[1][j] = 0;
				Positions[4][j] = 0;
			}
			goto link4;
		}
		if (mass[i][j - 1] == stena) goto link4;
		if (mass[i][j - 1] == wall1 or mass[i][j - 1] == wall2) {
			mass[i][j - 1] = ' ';
			goto link4;
		}
		mass[i][j - 1] = bulletGovard;
		for (int k = 0; k <= 8; k += 4)
		{
			if (Positions[0][0 + k] == i and Positions[0][1 + k] == j) {
				Positions[0][2 + k] = i;
				Positions[0][3 + k] = j - 1;
				Positions[5][0] = 4;
				once_for_govard++;
			}
		}
	}
link4:
	cout << "";
}
void save_positions(int Positions[i][j],int Buffer[3][j]) {
		for (int k = 0; k <= 8; k+=4)
		{
			for (int p = 0; p <= 8; p+=4)
			{
				if (Positions[1][k] == Buffer[0][p] and Positions[1][k + 1] == Buffer[0][p + 1]) {
					Positions[1][k + 2] = Buffer[0][p + 2];
					Positions[1][k + 3] = Buffer[0][p + 3];
					Positions[4][k] = Buffer[5][p];
				}
			}
		}
}
void shootGovard(char mass[stroki][stolbi], int Positions[i][j], int Positions2[i][j], string side) {
	
	if (side == "up") {
		mass[Positions[0][2]][Positions[0][3]] = pusto;
		if (mass[Positions[0][2] - 1][Positions[0][3]] == stena) {

			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;
		}
		else if (mass[Positions[0][2] - 1][Positions[0][3]] == bulletEnemy1 or mass[Positions2[0][2] - 1][Positions2[0][3]] == bulletEnemy1) {
			mass[Positions[0][2] - 2][Positions[0][3]] = bulletGovard;
		}
		else if (mass[Positions[0][2] - 1][Positions[0][3]] == Enemy1) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			mass[Positions[0][2] - 1][Positions[0][3]] = ' ';
			for (int j = 0; j < 12; j ++) {
				Buffer[0][j] = Positions[1][j];
				Buffer[5][j] = Positions[4][j];
				if (Positions[1][j] == Positions[0][2] - 1 and Positions[1][j + 1] == Positions[0][3]) {
					Buffer[1][j+2] = Positions[1][j + 2];
					Buffer[1][j + 3] = Positions[1][j + 3];
					Buffer[4][j] = Positions[4][j];
				}
				Positions[1][j] = 0;
				Positions[4][j] = 0;
			}
			SearchEnemy1(mass, Positions);
			save_positions(Positions, Buffer);
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;

		}
		else if (mass[Positions[0][2] - 1][Positions[0][3]] == Enemy2) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;

		}
		else if (mass[Positions[0][2] - 1][Positions[0][3]] == wall1 or mass[Positions[0][2] - 1][Positions[0][3]] == wall2) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			mass[Positions[0][2] - 1][Positions[0][3]] = ' ';
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;
		}
		else {
			mass[Positions[0][2] - 1][Positions[0][3]] = bulletGovard;
		}
	}
	else if (side == "down") {
		mass[Positions[0][2]][Positions[0][3]] = pusto;
		if (mass[Positions[0][2] + 1][Positions[0][3]] == stena) {

			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;
		}
		else if (mass[Positions[0][2] + 1][Positions[0][3]] == bulletEnemy1 or mass[Positions2[0][2] + 1][Positions2[0][3]] == bulletEnemy1) {
			mass[Positions[0][2] + 2][Positions[0][3]] = bulletGovard;
		}
		else if (mass[Positions[0][2] + 1][Positions[0][3]] == Enemy1) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			mass[Positions[0][2] + 1][Positions[0][3]] = ' ';
			for (int j = 0; j < 12; j++) {
				Buffer[0][j] = Positions[1][j];
				Buffer[5][j] = Positions[4][j];
				if (Positions[1][j] == Positions[0][2] + 1 and Positions[1][j + 1] == Positions[0][3]) {
					Buffer[1][j+2] = Positions[1][j + 2];
					Buffer[1][j + 3] = Positions[1][j + 3];
					Buffer[4][j] = Positions[4][j];
				}
				Positions[1][j] = 0;
				Positions[4][j] = 0;
			}
			SearchEnemy1(mass, Positions);
			save_positions(Positions, Buffer);
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;

		}
		else if (mass[Positions[0][2] + 1][Positions[0][3]] == Enemy2) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;

		}
		else if (mass[Positions[0][2] + 1][Positions[0][3]] == wall1 or mass[Positions[0][2] + 1][Positions[0][3]] == wall2) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			mass[Positions[0][2] + 1][Positions[0][3]] = ' ';
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;
		}
		else {
			mass[Positions[0][2] + 1][Positions[0][3]] = bulletGovard;
		}
	}
	else if (side == "right") {
		mass[Positions[0][2]][Positions[0][3]] = pusto;
		if (mass[Positions[0][2]][Positions[0][3] + 1] == stena) {

			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;
		}
		else if (mass[Positions[0][2]][Positions[0][3] + 1] == bulletEnemy1 or mass[Positions2[0][2]][Positions2[0][3] + 1] == bulletEnemy1) {
			mass[Positions[0][2]][Positions[0][3] + 2] = bulletGovard;
		}
		else if (mass[Positions[0][2]][Positions[0][3] + 1] == Enemy1) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			mass[Positions[0][2]][Positions[0][3] + 1] = ' ';
			for (int j = 0; j < 12; j++) {
				Buffer[0][j] = Positions[1][j];
				Buffer[5][j] = Positions[4][j];
				if (Positions[1][j] == Positions[0][2]and Positions[1][j + 1] == Positions[0][3] + 1) {
					Buffer[1][j + 2] = Positions[1][j + 2];
					Buffer[1][j + 3] = Positions[1][j + 3];
					Buffer[4][j] = Positions[4][j];
				}
				Positions[1][j] = 0;
				Positions[4][j] = 0;
			}
			SearchEnemy1(mass, Positions);
			save_positions(Positions, Buffer);
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;

		}
		else if (mass[Positions[0][2]][Positions[0][3] + 1] == Enemy2) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;

		}
		else if (mass[Positions[0][2]][Positions[0][3]+1] == wall1 or mass[Positions[0][2]][Positions[0][3]+1] == wall2) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			mass[Positions[0][2]][Positions[0][3]+1] = ' ';
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;
		}
		else {
			mass[Positions[0][2]][Positions[0][3] + 1] = bulletGovard;
		}
	}
	else if (side == "left") {
		mass[Positions[0][2]][Positions[0][3]] = pusto;
		if (mass[Positions[0][2]][Positions[0][3] - 1] == stena) {

			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;
		}
		else if (mass[Positions[1][2]][Positions[1][3] - 1] == bulletEnemy1 or mass[Positions2[1][2]][Positions2[1][3] - 1] == bulletEnemy1) {
			Positions[1][0 + i] = 0;
			Positions[1][1 + i] = 0;
			mass[Positions[0][2]][Positions[0][3] - 2] = bulletGovard;
		}
		else if (mass[Positions[0][2]][Positions[0][3] - 1] == Enemy1) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			mass[Positions[0][2]][Positions[0][3] - 1] = ' ';
			for (int j = 0; j < 12; j++) {
				Buffer[0][j] = Positions[1][j];
				Buffer[5][j] = Positions[4][j];
				if (Positions[1][j] == Positions[0][2] and Positions[1][j + 1] == Positions[0][3] - 1) {
					Buffer[1][j + 2] = Positions[1][j + 2];
					Buffer[1][j + 3] = Positions[1][j + 3];
					Buffer[4][j] = Positions[4][j];
				}
				Positions[1][j] = 0;
				Positions[4][j] = 0;
			}
			SearchEnemy1(mass, Positions);
			save_positions(Positions, Buffer);
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;

		}
		else if (mass[Positions[0][2]][Positions[0][3] - 1] == Enemy2) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;

		}
		else if (mass[Positions[0][2]][Positions[0][3] - 1] == wall1 or mass[Positions[0][2]][Positions[0][3] - 1] == wall2) {
			mass[Positions[0][2]][Positions[0][3]] = ' ';
			mass[Positions[0][2]][Positions[0][3] - 1] = ' ';
			Positions[0][2] = 0;
			Positions[0][3] = 0;
			Positions[5][0] = 0;
			once_for_govard = 0;
		}
		else {
			mass[Positions[0][2]][Positions[0][3] - 1] = bulletGovard;
		}
	}
	show(mass);
}
void fill_rivers(char mass[stroki][stolbi], vector<int> &rivers_i, vector<int> &rivers_j) {
	for (int i = 0; i < stroki; i++) {
		for (int j = 0; j < stolbi; j++) {
			if (mass[i][j] == river) {
				rivers_i.push_back(i);
				rivers_j.push_back(j);
			}
		}
	}
}
int main()
{
	SetConsoleCP(1251);
	srand(time(0));
	int hod,ogr = 10000,completed_rooms = 0,room_in_arrow = -1;
	int Positions[i][j], Positions2[i][j];
	vector <int> rivers_i;
	vector <int> rivers_j;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			Positions[i][j] = 0;
			Positions2[i][j] = 0;
		}

	}



	//------------------------------------------------------
	char pole[stroki][stolbi] =
	{
		stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
		stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
		stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
		stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
		stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
		stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
		stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
		stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
		stena	,' '	,' '	,' '	,' '	,' '	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
		stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
	};
	fill_rivers(pole, rivers_i, rivers_j);
	show(pole);
		//------------------------------------------------------
		for (int s = 0; s < ogr; s++)
		{
			SearchGovard(pole, Positions);
			hod = _getch();
				if (hod == 224) {
					hod = _getch();
				}
			switch (hod) {
				
			case 119:
				if (Positions[0][0] > 0 and pole[Positions[0][0] - 1][Positions[0][1]] != stena) {
					if (pole[Positions[0][0] - 1][Positions[0][1]] == Enemy1 or pole[Positions[0][0] - 1][Positions[0][1]] == Enemy2) {
						health--;
						hit(pole);
						break;
					}
					if (rivers_i.size() != 0 and rivers_j.size() != 0) {
						for (int i = 0; i < rivers_i.size(); i++)
						{
							if (Positions[0][0] - 1 == rivers_i[i] and Positions[0][1] == rivers_j[i] and pole[Positions[0][0] - 1][Positions[0][1]] == bulletEnemy1)
							{
								goto link1;
							}
						}
					}

					up(pole, govard, Positions[0][0], Positions[0][1]);
				}
				setcur(0, 0);
				show(pole);
			link1:
				break;
			case 115:
				if (pole[Positions[0][0] + 1][Positions[0][1]] != stena) {
					if (pole[Positions[0][0] + 1][Positions[0][1]] == Enemy1 or pole[Positions[0][0] + 1][Positions[0][1]] == Enemy2) {
						health--;
						hit(pole);
						break;
					}
					if (rivers_i.size() != 0 and rivers_j.size() != 0) {
						for (int i = 0; i < rivers_i.size(); i++)
						{
							if (Positions[0][0] + 1 == rivers_i[i] and Positions[0][1] == rivers_j[i] and pole[Positions[0][0] + 1][Positions[0][1]] == bulletEnemy1)
							{
								goto link2;
							}
						}
					}

					down(pole, govard, Positions[0][0], Positions[0][1]);
				}
				setcur(0, 0);
				show(pole);
			link2:
				break;
			case 97:
				if (Positions[0][1] > 0 and pole[Positions[0][0]][Positions[0][1] - 1] != stena) {
					if (pole[Positions[0][0]][Positions[0][1] - 1] == Enemy1 or pole[Positions[0][0]][Positions[0][1] - 1] == Enemy2) {
						health--;
						hit(pole);
						break;
					}
					if (rivers_i.size() != 0 and rivers_j.size() != 0) {
						for (int i = 0; i < rivers_i.size(); i++)
						{
							if (Positions[0][0] == rivers_i[i] and Positions[0][1] - 1 == rivers_j[i] and pole[Positions[0][0]][Positions[0][1] - 1] == bulletEnemy1)
							{
								goto link3;
							}

						}
					}
					left(pole, govard, Positions[0][0], Positions[0][1]);
				}
				setcur(0, 0);
				show(pole);
			link3:
				break;
			case 100:
				if (Positions[0][1] > 0 and pole[Positions[0][0]][Positions[0][1] + 1] != stena) {
					if (pole[Positions[0][0]][Positions[0][1] + 1] == Enemy1 or pole[Positions[0][0]][Positions[0][1] + 1] == Enemy2) {
						health--;
						hit(pole);
						break;
					}
					if (rivers_i.size() != 0 and rivers_j.size() != 0) {
						for (int i = 0; i < rivers_i.size(); i++)
						{
							if (Positions[0][0] == rivers_i[i] and Positions[0][1] + 1 == rivers_j[i] and pole[Positions[0][0]][Positions[0][1] + 1] == bulletEnemy1)
							{
								goto link4;
							}
						}
					}
					right(pole, govard, Positions[0][0], Positions[0][1]);
				}
				setcur(0, 0);
				show(pole);
			link4:
				break;
			case 5:
				setcur(0, 0);
				show(pole);
				break;
			case 72:
				firstshootGovard(pole, Positions, Positions[0][0], Positions[0][1], "up");
				setcur(0, 0);
				show(pole);
				break;
			case 80:
				firstshootGovard(pole, Positions, Positions[0][0], Positions[0][1], "down");
				setcur(0, 0);
				show(pole);
				break;
			case 75:
				firstshootGovard(pole, Positions, Positions[0][0], Positions[0][1], "left");
				setcur(0, 0);
				show(pole);
				break;
			case 77:
				firstshootGovard(pole, Positions, Positions[0][0], Positions[0][1], "right");
				setcur(0, 0);
				show(pole);
				break;
			default:
				cerr << "\nerror";
				break;
			}
			//------------------------------------------------------------------
			SearchBulletEnemy1(pole, Positions);
			SearchBulletEnemy2(pole, Positions2);
			SearchBulletGovard(pole, Positions);
			SearchBulletGovard(pole, Positions2);
			SearchGovard(pole, Positions);
			SearchGovard(pole, Positions2);
			if (Positions[5][0] == 1) {
				setcur(0, 0);
				shootGovard(pole, Positions, Positions2, "up");
			}
			if (Positions[5][0] == 2) {
				setcur(0, 0);
				shootGovard(pole, Positions, Positions2, "down");
			}
			if (Positions[5][0] == 3) {
				setcur(0, 0);
				shootGovard(pole, Positions, Positions2, "right");
			}
			if (Positions[5][0] == 4) {
				setcur(0, 0);
				shootGovard(pole, Positions, Positions2, "left");
			}
			//------------------------------------------------------------------ 
			for (int k = 0; k <= 8; k += 4)
			{
				if (Buffer[4][0 + k] == 1) {
					setcur(0, 0);
					shootEnemy1(pole, Buffer,Positions2 ,health, k);
					if (Buffer[1][2 + k] != 0) Buffer[1][2 + k] -= 1;
				}
				if (Buffer[4][0 + k] == 2) {
					setcur(0, 0);
					shootEnemy1(pole, Buffer, Positions2, health, k);
					if (Buffer[1][2 + k] != 0) Buffer[1][2 + k] += 1;
				}
				if (Buffer[4][0 + k] == 3) {
					setcur(0, 0);
					shootEnemy1(pole, Buffer,Positions2, health, k);
					if (Buffer[1][2 + k] != 0) Buffer[1][3 + k] += 1;
				}
				if (Buffer[4][0 + k] == 4) {
					setcur(0, 0);
					shootEnemy1(pole, Buffer,Positions2, health, k);
					if (Buffer[1][2 + k] != 0) Buffer[1][3 + k] -= 1;
				}
			}
			//------------------------------------------------------------------
			SearchEnemy1(pole, Positions);
			SearchBulletEnemy1(pole, Positions);
			for (int k = 0; k <= 8; k += 4)
			{
				if (Positions[0][0] < Positions[1][0 + k] and Positions[0][1] == Positions[1][1 + k] and handicap == 0 and Positions[1][2 + k] == 0 and Positions[1][3 + k] == 0 and Positions[4][1 + k] == 0) {
					setcur(0, 0);
					firstshootEnemy1(pole, Positions, Positions[1][0 + k], Positions[1][1 + k], "up");
					point_of_control2 = 1;
				}
				if (Positions[0][0] > Positions[1][0 + k] and Positions[0][1] == Positions[1][1 + k] and handicap == 0 and Positions[1][2 + k] == 0 and Positions[1][3 + k] == 0 and Positions[4][1 + k] == 0) {
					setcur(0, 0);
					firstshootEnemy1(pole, Positions, Positions[1][0 + k], Positions[1][1 + k], "down");
					point_of_control2 = 2;
				}
				if (Positions[0][1] > Positions[1][1 + k] and Positions[0][0] == Positions[1][0 + k] and handicap == 0 and Positions[1][2 + k] == 0 and Positions[1][3 + k] == 0 and Positions[4][1 + k] == 0) {
					setcur(0, 0);
					firstshootEnemy1(pole, Positions, Positions[1][0 + k], Positions[1][1 + k], "right");
					point_of_control2 = 3;
				}
				if (Positions[0][1] < Positions[1][1 + k] and Positions[0][0] == Positions[1][0 + k] and handicap == 0 and Positions[1][2 + k] == 0 and Positions[1][3 + k] == 0 and Positions[4][1 + k] == 0) {
					setcur(0, 0);
					firstshootEnemy1(pole, Positions, Positions[1][0 + k], Positions[1][1 + k], "left");
					point_of_control2 = 4;
				}
			}
			for (int k = 0; k <= 8; k += 4)
			{
				for (int i = 0; i <= 8; i += 4)
				{
					for (int j = 1; j <= 4; j++)
					{
						if (Positions[1][2 + i] != 0 and point_of_control2 == j and Positions[4][0 + i] == 0) Positions[4][0 + i] = j;
					}
				}
				if (Positions[4][0 + k] == 1) {
					setcur(0, 0);
					shootEnemy1(pole, Positions, Positions2, health, k);
				}
				if (Positions[4][0 + k] == 2) {
					setcur(0, 0);
					shootEnemy1(pole, Positions, Positions2, health, k);
				}
				if (Positions[4][0 + k] == 3) {
					setcur(0, 0);
					shootEnemy1(pole, Positions, Positions2, health, k);
				}
				if (Positions[4][0 + k] == 4) {
					setcur(0, 0);
					shootEnemy1(pole, Positions, Positions2, health, k);
				}
			}
			handicap = 0;
			cout << "health: ";
			for (int i = 0; i < health; i++)
			{
				cout << (char)3;
			}
			cout << endl;
			//----------------------------------------------------------------------
			SearchEnemy2(pole, Positions2);
			SearchBulletEnemy2(pole, Positions2);
			for (int k = 0; k <= 8; k += 4)
			{
				if (Positions2[0][0] < Positions2[1][0 + k] and Positions2[0][1] == Positions2[1][1 + k] and handicap2 == 0 and Positions2[1][2 + k] == 0 and Positions2[1][3 + k] == 0 and Positions2[4][1 + k] == 0) {
					setcur(0, 0);
					firstshootEnemy1(pole, Positions2, Positions2[1][0 + k], Positions2[1][1 + k], "up");
					point_of_control3 = 1;
				}
				if (Positions2[0][0] > Positions2[1][0 + k] and Positions2[0][1] == Positions2[1][1 + k] and handicap2 == 0 and Positions2[1][2 + k] == 0 and Positions2[1][3 + k] == 0 and Positions2[4][1 + k] == 0) {
					setcur(0, 0);
					firstshootEnemy1(pole, Positions2, Positions2[1][0 + k], Positions2[1][1 + k], "down");
					point_of_control3 = 2;
				}
				if (Positions2[0][1] > Positions2[1][1 + k] and Positions2[0][0] == Positions2[1][0 + k] and handicap2 == 0 and Positions2[1][2 + k] == 0 and Positions2[1][3 + k] == 0 and Positions2[4][1 + k] == 0) {
					setcur(0, 0);
					firstshootEnemy1(pole, Positions2, Positions2[1][0 + k], Positions2[1][1 + k], "right");
					point_of_control3 = 3;
				}
				if (Positions2[0][1] < Positions2[1][1 + k] and Positions2[0][0] == Positions2[1][0 + k] and handicap2 == 0 and Positions2[1][2 + k] == 0 and Positions2[1][3 + k] == 0 and Positions2[4][1 + k] == 0) {
					setcur(0, 0);
					firstshootEnemy1(pole, Positions2, Positions2[1][0 + k], Positions2[1][1 + k], "left");
					point_of_control3 = 4;
				}
			}
			for (int k = 0; k <= 8; k += 4)
			{
				for (int i = 0; i <= 8; i += 4)
				{
					for (int j = 1; j <= 4; j++)
					{
						if (Positions2[1][2 + i] != 0 and point_of_control3 == j and Positions2[4][0 + i] == 0) Positions2[4][0 + i] = j;
					}
				}
				if (Positions2[4][0 + k] == 1) {
					setcur(0, 0);
					shootEnemy2(pole, Positions2, Positions, health, k);
				}
				if (Positions2[4][0 + k] == 2) {
					setcur(0, 0);
					shootEnemy2(pole, Positions2, Positions, health, k);
				}
				if (Positions2[4][0 + k] == 3) {
					setcur(0, 0);
					shootEnemy2(pole, Positions2, Positions, health, k);
				}
				if (Positions2[4][0 + k] == 4) {
					setcur(0, 0);
					shootEnemy2(pole, Positions2, Positions, health, k);
				}
			}
			handicap2 = 0;
			//----------------------------------------------------------------------
			if (health == 0) {
				system("cls");
				cout << "GAME OVER!";
				return 0;
			}
			//----------------------------------------------------------------------
			if (count_of_Enemy1(pole) == 0) { 
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						if (pole[i][j] == dver) {
							pole[i][j] = ' ';
						}
					}
				}
			}

		//----------------------------------------------------------------------
			if (Positions[0][0] == 0 or Positions[0][1] == 0 or Positions[0][0] == stroki-1 or Positions[0][1] == stolbi-1) {
				completed_rooms++;
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 12; j++) {
						Positions[i][j] = 0;
						Positions2[i][j] = 0;
					}
				}
				if (rivers_i.size() != 0 and rivers_j.size() != 0) {
					do {
						rivers_i.pop_back();
						rivers_j.pop_back();
					} while (rivers_i.size() != 0 and rivers_j.size() != 0);
				}
				setcur(0, 0);
			start:
				int rand_room;
				rand_room = rand() % 30;
				/*rand_room = 27;*/
				if (rand_room == 0 and rand_room != room_in_arrow) {
					char pole2[stroki][stolbi] =
					{
						stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,' '	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,' '	,river	,' '	,' '	,' '	,Enemy1	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,' '	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,Enemy1	,' '	,' '	,river	,' '	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,' '	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,' '	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,' '	,river	,' '	,' '	,' '	,Enemy1	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,govard	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					};
					for (int i = 0; i < stroki; i++) {
						for (int j = 0; j < stolbi; j++) {
							pole[i][j] = pole2[i][j];
						}
					}
					fill_rivers(pole, rivers_i, rivers_j);
					show(pole);
					room_in_arrow = rand_room;
				}
				else if (rand_room == 1 and rand_room != room_in_arrow) {
					char pole3[stroki][stolbi] =
					{
						stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
						stena	,Enemy1	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,river	,' '	,' '	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,' '	,river	,Enemy1	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,river	,' '	,' '	,stena	,
						stena	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,river	,river	,river	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,river	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,' '	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,Enemy1	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,' '	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					};
					for (int i = 0; i < stroki; i++) {
						for (int j = 0; j < stolbi; j++) {
							pole[i][j] = pole3[i][j];
						}
					}
					fill_rivers(pole, rivers_i, rivers_j);
					show(pole);
					room_in_arrow = rand_room;
				}
				else if (rand_room == 2 and rand_room != room_in_arrow) {
					char pole3[stroki][stolbi] =
					{
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,
						stena	,stena	,stena	,stena	,Enemy1	,' '	,' '	,' '	,stena	,stena	,' '	,stena	,stena	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,' '	,stena	,stena	,stena	,
						stena	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,river	,Enemy1	,stena	,
						stena	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
						stena	,Enemy1	,' '	,' '	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					};
					for (int i = 0; i < stroki; i++) {
						for (int j = 0; j < stolbi; j++) {
							pole[i][j] = pole3[i][j];
						}
					}
					fill_rivers(pole, rivers_i, rivers_j);
					show(pole);
					room_in_arrow = rand_room;
				}
				else if (rand_room == 3 and rand_room != room_in_arrow) {
					char pole3[stroki][stolbi] =
					{
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
						stena	,' '	,river	,' '	,' '	,' '	,' '	,' '	,river	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,' '	,stena	,
						stena	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,Enemy1	,stena	,
						stena	,govard	,river	,' '	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,' '	,stena	,
						stena	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,Enemy1	,stena	,
						stena	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,' '	,stena	,
						stena	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,' '	,' '	,river	,Enemy1	,stena	,
						stena	,' '	,' '	,' '	,' '	,river	,' '	,' '	,' '	,' '	,' '	,river	,' '	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,
					};
					for (int i = 0; i < stroki; i++) {
						for (int j = 0; j < stolbi; j++) {
							pole[i][j] = pole3[i][j];
						}
					}
					fill_rivers(pole, rivers_i, rivers_j);
					show(pole);
					room_in_arrow = rand_room;
				}
				else if (rand_room == 4 and rand_room != room_in_arrow) {
					char pole3[stroki][stolbi] =
					{
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
						stena	,Enemy1	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,' '	,stena	,
						stena	,' '	,' '	,' '	,stena	,stena	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,stena	,
						dver	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy1	,stena	,
						stena	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,stena	,
						stena	,' '	,' '	,' '	,stena	,' '	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
						stena	,' '	,' '	,' '	,stena	,stena	,stena	,' '	,' '	,' '	,' '	,stena	,' '	,stena	,
						stena	,Enemy1	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,' '	,stena	,
						stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					};
					for (int i = 0; i < stroki; i++) {
						for (int j = 0; j < stolbi; j++) {
							pole[i][j] = pole3[i][j];
						}
					}
					fill_rivers(pole, rivers_i, rivers_j);
					show(pole);
					room_in_arrow = rand_room;
				}
				else if (rand_room == 5 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,stena	,Enemy1	,' '	,river	,' '	,' '	,' '	,stena	,stena	,
					stena	,' '	,stena	,' '	,' '	,' '	,stena	,' '	,river	,stena	,' '	,stena	,' '	,stena	,
					stena	,stena	,' '	,' '	,stena	,' '	,' '	,stena	,river	,' '	,' '	,' '	,' '	,stena	,
					stena	,stena	,stena	,' '	,' '	,' '	,' '	,' '	,stena	,' '	,' '	,Enemy1	,stena	,stena	,
					stena	,' '	,govard	,' '	,' '	,stena	,' '	,stena	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,' '	,stena	,stena	,
					stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,' '	,' '	,' '	,stena	,
					stena	,Enemy1	,' '	,' '	,' '	,' '	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 6 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,stena	,stena	,stena	,river	,stena	,stena	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,' '	,' '	,stena	,
					stena	,govard	,' '	,river	,' '	,Enemy1	,stena	,Enemy1	,stena	,Enemy1	,river	,' '	,' '	,dver	,
					stena	,' '	,' '	,stena	,' '	,river	,' '	,' '	,' '	,river	,stena	,' '	,' '	,stena	,
					stena	,' '	,' '	,stena	,' '	,' '	,river	,river	,river	,' '	,stena	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 7 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				int answer;
				do {
					setcur(0, 0);
					show(pole);
					cout << "health: ";
					for (int i = 0; i < health; i++)
					{
						cout << (char)3;
					}
					cout << endl;
					cout << "What are the last 4 digits of pi, after the decimal point? Okay, okay, just kidding.\nWhat are the first four digits of pi?, after the decimal point: ";
					cin >> answer;
					if (answer == 1415) {
						cout << "You're right!\n";
							for (int i = 0; i < stroki; i++) {
								for (int j = 0; j < stolbi; j++) {
									if (pole[i][j] == dver) {
										pole[i][j] = ' ';
									}
								}
							}
					}
					else {
						cout << "You are wrong!";
						health--;
						hit(pole);
						if (health == 0) {
							cout << "GAME OVER!";
							return 0;
						}
					}
				}while (answer != 1415);
				room_in_arrow = rand_room;
				system("cls");
				setcur(0, 0);
				show(pole);
				}
				else if (rand_room == 8 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				string answer;
				do {
					setcur(0, 0);
					show(pole);
					cout << "health: ";
					for (int i = 0; i < health; i++)
					{
						cout << (char)3;
					}
					cout << endl;
					cout << "Do you like this game?: ";
					cin >> answer;
					if (answer == "yes") {
						cout << "Cool!\n";
						for (int i = 0; i < stroki; i++) {
							for (int j = 0; j < stolbi; j++) {
								if (pole[i][j] == dver) {
									pole[i][j] = ' ';
								}
							}
						}
					}
					else {
						cout << "Bad!";
						health--;
						hit(pole);
						if (health == 0) {
							cout << "GAME OVER!";
							return 0;
						}
					}

				} while (answer != "yes");
				room_in_arrow = rand_room;
				}
				else if (rand_room == 9 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,govard	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,river	,' '	,' '	,' '	,' '	,river	,' '	,' '	,' '	,Enemy1	,dver	,
					stena	,' '	,' '	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,' '	,stena	,stena	,stena	,
					stena	,' '	,' '	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,river	,Enemy1	,stena	,
					stena	,' '	,' '	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,river	,' '	,' '	,' '	,' '	,' '	,river	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,river	,' '	,' '	,Enemy1	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				system("cls");
				setcur(0, 0);
				show(pole);
				}
				else if (rand_room == 10 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				int answer;
				do {
					setcur(0, 0);
					show(pole);
					cout << "health: ";
					for (int i = 0; i < health; i++)
					{
						cout << (char)3;
					}
					cout << endl;
					cout << "how many millimeters in the km?: ";
					cin >> answer;
					if (answer == 1000000) {
						cout << "You're right!\n";
						for (int i = 0; i < stroki; i++) {
							for (int j = 0; j < stolbi; j++) {
								if (pole[i][j] == dver) {
									pole[i][j] = ' ';
								}
							}
						}
					}
					else {
						cout << "You are wrong!";
						health--;
						hit(pole);
						if (health == 0) {
							cout << "GAME OVER!";
							return 0;
						}
					}

				} while (answer != 1000000);
				room_in_arrow = rand_room;
				system("cls");
				setcur(0, 0);
				show(pole);
				}
				else if (rand_room == 11 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				int answer;
				do {
					setcur(0, 0);
					show(pole);
					cout << "health: ";
					for (int i = 0; i < health; i++)
					{
						cout << (char)3;
					}
					cout << endl;
					cout << "how much of the data type 'double' stored in memory?: ";
					cin >> answer;
					if (answer == 8) {
						cout << "You're right!\n";
						for (int i = 0; i < stroki; i++) {
							for (int j = 0; j < stolbi; j++) {
								if (pole[i][j] == dver) {
									pole[i][j] = ' ';
								}
							}
						}
					}
					else {
						cout << "You are wrong!";
						health--;
						hit(pole);
						if (health == 0) {
							cout << "GAME OVER!";
							return 0;
						}
					}

				} while (answer != 8);
				room_in_arrow = rand_room;
				system("cls");
				setcur(0, 0);
				show(pole);
				}
				else if (rand_room == 12 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,govard	,stena	,' '	,' '	,' '	,stena	,Enemy1	,' '	,' '	,stena	,' '	,stena	,stena	,
					stena	,' '	,stena	,' '	,stena	,' '	,stena	,river	,river	,river	,stena	,' '	,stena	,stena	,
					stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,stena	,
					stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,' '	,' '	,stena	,' '	,stena	,stena	,
					stena	,' '	,river	,' '	,river	,' '	,river	,' '	,river	,' '	,river	,' '	,Enemy1	,dver	,
					stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,stena	,
					stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,stena	,
					stena	,' '	,' '	,Enemy1	,stena	,' '	,' '	,' '	,stena	,' '	,' '	,' '	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 13 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,' '	,' '	,stena	,
					stena	,' '	,' '	,stena	,river	,river	,river	,river	,river	,stena	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,river	,stena	,' '	,' '	,' '	,stena	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,river	,' '	,stena	,Enemy1	,stena	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,river	,' '	,' '	,stena	,' '	,' '	,river	,' '	,' '	,' '	,stena	,
					stena	,Enemy1	,' '	,river	,' '	,' '	,stena	,' '	,' '	,river	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,river	,' '	,' '	,govard	,' '	,' '	,river	,' '	,' '	,Enemy1	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 14 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,river	,' '	,' '	,Enemy1	,stena	,
					stena	,' '	,' '	,stena	,stena	,stena	,stena	,stena	,' '	,stena	,' '	,stena	,' '	,stena	,
					stena	,' '	,' '	,stena	,stena	,' '	,' '	,' '	,' '	,stena	,' '	,stena	,' '	,stena	,
					stena	,govard	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,' '	,stena	,' '	,stena	,
					stena	,' '	,' '	,' '	,stena	,' '	,' '	,' '	,' '	,' '	,Enemy1	,stena	,' '	,stena	,
					stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,stena	,
					stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,stena	,
					stena	,Enemy1	,river	,' '	,' '	,' '	,' '	,river	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 15 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,Enemy1	,stena	,stena	,stena	,' '	,' '	,stena	,stena	,stena	,Enemy1	,stena	,stena	,
					stena	,stena	,' '	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,
					stena	,stena	,' '	,stena	,stena	,stena	,govard	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,
					stena	,stena	,' '	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,
					stena	,stena	,river	,stena	,stena	,stena	,Enemy1	,stena	,stena	,stena	,stena	,river	,stena	,stena	,
					stena	,stena	,' '	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,
					stena	,stena	,' '	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,' '	,stena	,stena	,
					stena	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 16 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,river	,river	,river	,river	,river	,' '	,' '	,stena	,stena	,stena	,river	,river	,stena	,
					stena	,wall2	,wall2	,wall2	,wall2	,wall2	,' '	,' '	,stena	,stena	,stena	,river	,river	,stena	,
					dver	,Enemy1	,wall2	,wall2	,wall2	,wall2	,' '	,' '	,wall2	,' '	,wall2	,river	,Enemy1	,stena	,
					stena	,wall2	,wall2	,wall2	,wall2	,wall2	,' '	,' '	,stena	,' '	,stena	,river	,river	,stena	,
					stena	,river	,river	,river	,river	,river	,' '	,' '	,stena	,' '	,stena	,river	,river	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,wall1	,stena	,river	,river	,stena	,
					stena	,govard	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy2	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 16 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,river	,river	,river	,river	,river	,river	,river	,stena	,stena	,stena	,river	,river	,stena	,
					stena	,wall1	,wall2	,wall2	,wall2	,wall2	,' '	,' '	,stena	,stena	,stena	,river	,river	,stena	,
					dver	,Enemy1	,wall2	,wall2	,wall2	,wall2	,' '	,' '	,wall2	,' '	,wall2	,river	,Enemy1	,stena	,
					stena	,wall1	,wall2	,wall2	,wall2	,wall2	,' '	,' '	,stena	,' '	,stena	,river	,river	,stena	,
					stena	,river	,river	,river	,river	,river	,river	,river	,stena	,' '	,stena	,river	,river	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,wall1	,stena	,river	,river	,stena	,
					stena	,govard	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy2	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 17 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,wall2	,Enemy1	,wall2	,' '	,wall2	,' '	,wall2	,' '	,wall2	,' '	,' '	,stena	,
					stena	,' '	,wall2	,stena	,wall2	,' '	,wall2	,' '	,wall2	,' '	,river	,' '	,Enemy2	,stena	,
					stena	,' '	,wall2	,stena	,wall2	,' '	,wall2	,' '	,wall2	,' '	,river	,' '	,Enemy2	,stena	,
					stena	,' '	,wall2	,stena	,wall2	,' '	,wall2	,' '	,stena	,' '	,wall2	,' '	,' '	,stena	,
					stena	,' '	,wall2	,stena	,wall2	,' '	,wall2	,' '	,stena	,' '	,wall2	,govard	,' '	,stena	,
					dver	,' '	,wall2	,stena	,wall2	,' '	,wall2	,' '	,stena	,' '	,wall2	,' '	,' '	,stena	,
					stena	,river	,wall2	,stena	,wall2	,' '	,wall2	,' '	,stena	,' '	,wall2	,' '	,' '	,stena	,
					stena	,Enemy1	,wall2	,stena	,wall2	,' '	,wall2	,Enemy1	,stena	,' '	,wall2	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 18 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,river	,' '	,' '	,' '	,' '	,river	,river	,river	,Enemy1	,' '	,' '	,dver	,
					stena	,' '	,' '	,' '	,' '	,river	,' '	,' '	,' '	,' '	,' '	,' '	,wall1	,stena	,
					stena	,river	,' '	,river	,Enemy1	,river	,' '	,river	,river	,wall2	,' '	,' '	,Enemy2	,stena	,
					stena	,Enemy1	,' '	,river	,' '	,river	,' '	,river	,river	,wall2	,river	,river	,' '	,stena	,
					stena	,stena	,river	,river	,' '	,river	,' '	,' '	,river	,wall2	,' '	,' '	,Enemy2	,stena	,
					stena	,river	,river	,river	,river	,river	,' '	,river	,river	,wall2	,river	,river	,' '	,stena	,
					stena	,govard	,' '	,river	,' '	,river	,river	,' '	,river	,' '	,' '	,' '	,' '	,stena	,
					stena	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy2	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 19 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,wall1	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,wall1	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy2	,stena	,
					stena	,wall1	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy1	,stena	,
					stena	,wall1	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy2	,stena	,
					stena	,wall1	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy1	,stena	,
					stena	,wall1	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy2	,stena	,
					stena	,wall1	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy1	,stena	,
					stena	,govard	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 20 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,stena	,' '	,river	,' '	,' '	,' '	,river	,' '	,' '	,' '	,Enemy2	,stena	,
					dver	,' '	,wall2	,' '	,river	,' '	,river	,' '	,river	,' '	,river	,' '	,' '	,stena	,
					stena	,stena	,stena	,' '	,river	,' '	,river	,' '	,river	,' '	,river	,' '	,' '	,stena	,
					stena	,Enemy1	,river	,' '	,river	,' '	,river	,' '	,river	,' '	,wall2	,govard	,' '	,stena	,
					stena	,stena	,stena	,' '	,river	,' '	,river	,' '	,river	,' '	,river	,' '	,Enemy2	,stena	,
					stena	,Enemy1	,river	,' '	,river	,' '	,river	,' '	,river	,' '	,river	,' '	,' '	,stena	,
					stena	,stena	,stena	,' '	,river	,' '	,river	,' '	,river	,' '	,river	,' '	,Enemy2	,stena	,
					stena	,Enemy1	,river	,' '	,' '	,' '	,river	,' '	,' '	,' '	,river	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 21 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,Enemy2	,stena	,
					dver	,wall2	,wall1	,wall1	,Enemy2	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall2	,stena	,
					stena	,wall2	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,Enemy1	,wall1	,wall1	,wall2	,stena	,
					stena	,wall2	,wall1	,wall1	,wall1	,wall1	,govard	,wall1	,wall1	,wall1	,wall1	,wall1	,wall2	,stena	,
					stena	,wall2	,wall1	,Enemy1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall2	,stena	,
					stena	,wall2	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall2	,stena	,
					stena	,Enemy2	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall2	,stena	,
					stena	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,wall1	,Enemy1	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 22 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,Enemy1	,wall2	,wall2	,wall2	,wall2	,river	,' '	,river	,wall2	,wall2	,wall2	,' '	,stena	,
					stena	,' '	,wall2	,wall2	,wall2	,wall2	,river	,' '	,river	,wall2	,wall2	,wall2	,Enemy1	,stena	,
					stena	,Enemy2	,river	,' '	,' '	,' '	,river	,' '	,river	,wall2	,wall2	,wall2	,' '	,stena	,
					stena	,' '	,wall2	,wall2	,wall2	,wall2	,river	,' '	,river	,' '	,' '	,river	,Enemy2	,stena	,
					stena	,' '	,wall2	,wall2	,wall2	,wall2	,river	,govard	,river	,wall2	,wall2	,wall2	,' '	,stena	,
					stena	,Enemy2	,river	,' '	,' '	,' '	,river	,' '	,river	,wall2	,wall2	,wall2	,' '	,stena	,
					stena	,' '	,wall2	,wall2	,wall2	,wall2	,river	,' '	,river	,wall2	,wall2	,wall2	,' '	,stena	,
					stena	,Enemy1	,wall2	,wall2	,wall2	,wall2	,river	,' '	,river	,wall2	,wall2	,wall2	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 23 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,Enemy1	,wall2	,wall2	,wall2	,wall2	,wall2	,wall2	,' '	,' '	,wall2	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,stena	,wall1	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,stena	,wall1	,stena	,stena	,stena	,
					stena	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy2	,stena	,
					stena	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,river	,stena	,river	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,' '	,stena	,stena	,stena	,river	,stena	,river	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,' '	,wall2	,wall2	,wall2	,wall2	,wall2	,wall2	,wall2	,Enemy1	,stena	,
					stena	,Enemy1	,' '	,' '	,' '	,stena	,stena	,stena	,Enemy2	,stena	,Enemy2	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 24 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,Enemy1	,' '	,wall2	,wall2	,stena	,wall2	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,Enemy1	,stena	,stena	,stena	,wall2	,stena	,wall2	,stena	,' '	,' '	,govard	,' '	,stena	,
					stena	,' '	,stena	,stena	,stena	,wall2	,stena	,wall2	,stena	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,stena	,stena	,wall2	,wall2	,wall2	,stena	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,stena	,stena	,wall2	,wall2	,stena	,' '	,river	,river	,river	,stena	,
					stena	,' '	,' '	,' '	,' '	,stena	,stena	,wall2	,stena	,' '	,river	,' '	,' '	,stena	,
					stena	,' '	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,' '	,river	,' '	,' '	,stena	,
					stena	,' '	,wall2	,wall2	,wall2	,wall2	,wall2	,wall2	,' '	,' '	,river	,' '	,Enemy1	,stena	,
					stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 25 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,Enemy1	,' '	,' '	,' '	,river	,river	,' '	,river	,river	,' '	,' '	,stena	,
					stena	,' '	,river	,' '	,river	,river	,river	,' '	,' '	,' '	,river	,' '	,Enemy2	,stena	,
					stena	,' '	,river	,' '	,river	,govard	,wall2	,wall2	,river	,' '	,river	,' '	,' '	,stena	,
					stena	,' '	,river	,' '	,river	,wall2	,wall2	,wall2	,river	,' '	,river	,' '	,' '	,stena	,
					stena	,' '	,river	,' '	,river	,wall2	,Enemy2	,wall2	,river	,' '	,river	,' '	,Enemy1	,stena	,
					stena	,' '	,river	,' '	,river	,wall2	,wall2	,wall2	,river	,' '	,river	,' '	,' '	,stena	,
					stena	,Enemy1	,river	,' '	,river	,river	,river	,river	,river	,' '	,river	,' '	,' '	,stena	,
					stena	,' '	,river	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,river	,' '	,Enemy2	,stena	,
					stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 26 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,Enemy1	,river	,wall2	,' '	,' '	,govard	,' '	,' '	,' '	,' '	,' '	,stena	,stena	,
					stena	,river	,river	,wall2	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,stena	,
					stena	,wall1	,wall1	,wall1	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,stena	,
					stena	,Enemy2	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,stena	,
					stena	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,Enemy2	,stena	,
					stena	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,wall1	,wall1	,wall1	,stena	,
					stena	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,wall2	,river	,river	,stena	,
					stena	,stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,wall2	,river	,Enemy1	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 27 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,Enemy1	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,wall1	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,wall1	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,wall1	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,wall1	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,wall1	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,wall1	,wall2	,wall2	,wall2	,wall2	,wall2	,Enemy1	,stena	,
					stena	,Enemy1	,wall2	,wall2	,wall2	,wall2	,govard	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				show(pole);
				room_in_arrow = rand_room;
				}
				else if (rand_room == 28 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				int answer;
				do {
					setcur(0, 0);
					show(pole);
					cout << "health: ";
					for (int i = 0; i < health; i++)
					{
						cout << (char)3;
					}
					cout << endl;
					cout << "What is the area of a right triangle with a hypotenuse of 6 and a cathetus of 4?(just a number ,without units): ";
					cin >> answer;
					if (answer == 6) {
						cout << "You're right!\n";
						for (int i = 0; i < stroki; i++) {
							for (int j = 0; j < stolbi; j++) {
								if (pole[i][j] == dver) {
									pole[i][j] = ' ';
								}
							}
						}
					}
					else {
						cout << "You are wrong!";
						health--;
						hit(pole);
						if (health == 0) {
							cout << "GAME OVER!";
							return 0;
						}
					}

				} while (answer != 6);
				room_in_arrow = rand_room;
				system("cls");
				setcur(0, 0);
				show(pole);
				}
				else if (rand_room == 29 and rand_room != room_in_arrow) {
				char pole3[stroki][stolbi] =
				{
					stena	,stena	,stena	,stena	,stena	,stena	,dver	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,' '	,' '	,' '	,' '	,' '	,govard	,' '	,' '	,' '	,' '	,' '	,' '	,stena	,
					stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,stena	,
				};
				for (int i = 0; i < stroki; i++) {
					for (int j = 0; j < stolbi; j++) {
						pole[i][j] = pole3[i][j];
					}
				}
				fill_rivers(pole, rivers_i, rivers_j);
				int answer;
				do {
					setcur(0, 0);
					show(pole);
					cout << "health: ";
					for (int i = 0; i < health; i++)
					{
						cout << (char)3;
					}
					cout << endl;
					cout << "calculate the area of this room.(just a number ,without units): ";
					cin >> answer;
					if (answer == 140) {
						cout << "You're right!\n";
						for (int i = 0; i < stroki; i++) {
							for (int j = 0; j < stolbi; j++) {
								if (pole[i][j] == dver) {
									pole[i][j] = ' ';
								}
							}
						}
					}
					else {
						cout << "You are wrong!";
						health--;
						hit(pole);
						if (health == 0) {
							cout << "GAME OVER!";
							return 0;
						}
					}

				} while (answer != 140);
				room_in_arrow = rand_room;
				system("cls");
				setcur(0, 0);
				show(pole);
				}
				else goto start;
			}
		//----------------------------------------------------------------------
			for (int i = 0; i < stroki; i++) {
				for (int j = 0; j < stolbi; j++) {
					if (pole[i][j] == ' ' ) {
						if (rivers_i.size() != 0 and rivers_j.size() != 0) {
							for (int k = 0; k < rivers_i.size(); k++)
							{
								if (rivers_i[k] == i and rivers_j[k] == j)
									pole[i][j] = river;
							}
						}
					}
				}
			}
		//----------------------------------------------------------------------
			if (completed_rooms == 10) {
				system("cls");
				cout << "You WIN!";
				return 0;
			}
		//----------------------------------------------------------------------
#ifdef DEBUG

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 12; j++) {
					cout << Positions[i][j];
				}
				cout << endl;
			}
			cout << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 12; j++) {
					cout << Buffer[i][j];
				}
				cout << endl;
			}
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 12; j++) {
					cout << Positions2[i][j];
				}
				cout << endl;
			}
#endif // DEBUG
			//------------------------------------------------------------------ 
		}



}
