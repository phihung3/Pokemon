#include <iostream>
#include "overworld.h"
#include <cstring>

using namespace std;
//map portion
Map::Map(int _size=10):maxItems(_size/2),maxMonsters(_size) {
	size = _size;
	mapState = new char*[size];
	for(int i = 0; i < size; i++) {
		mapState[i] = new char[size];
		for(int j = 0; j < size; j++) {
			if(i == 0 || i == size-1) {
				mapState[i][j]= '-';
				continue;
			} else if (j == 0 || j == size-1) {
				mapState[i][j] = '|';
				continue;
			}
			mapState[i][j] = ' ';
		}
	}
	
	setupItems();
	setupMonsters();
	setupPlayer();
}

Map::~Map() {
	for(int i = 0; i < size; i++) {
		delete [] mapState[i];
	}
	delete [] mapState;
	
	for(int i = 0; i < numMonsters; i++) {
		delete [] monsters[i];
	}
	delete [] monsters;
	
	for(int i = 0; i < numItems; i++) {
		delete [] items[i];
	}
	delete [] items;
}

ostream& operator<<(ostream& s, const Map& M) {
	for(int i = 0; i < M.size; i++) {
		for(int j = 0; j < M.size; j++) {
			s << M.mapState[i][j] << "\t";
		}
		s << endl<<endl;
	}
	
	return s;
}

void Map::setupPlayer(){
	int row = rand()%(size-2) + 1;
	int column = rand()%(size-2) + 1;
	playerY = column;
	playerX = row;
	mapState[row][column] = 'P';
	//had the player x and y kind of backwards and had to swtich all the movement
	Player P1;
}
//sorry for very ugly code in move player and everywhere else too;
void Map::MovePlayer(int direction){
	switch(direction){
		case 1:{
			//checking each position above and changing the spaces
			cout<<"Moving North 1 Block"<<endl;
			if(mapState[playerX-1][playerY] == ' '){
				mapState[playerX][playerY] = ' ';
				mapState[playerX-1][playerY] = 'P';
				playerX--;
			}
			//another if statement to check the position of the block above then changing the icons
			else if(mapState[playerX-1][playerY] == 'I'){
				mapState[playerX][playerY]= ' ';
				mapState[playerX-1][playerY] = 'P';
				playerX--;
				P1.AddCoin();
				cout<<"Coin Collected!"<<endl;
			}//combat option
			else if(mapState[playerX-1][playerY] == 'M'){
				cout<<"Combat started!"<<endl;
				char input;
				while(input != '4'){
					srand(time(NULL));
					int monsterType;
					monsterType = ((rand()%2) + 1);
					if (monsterType == 1){
						BigMonster wild;
						cout<<"The Monster is a "<<wild.GetName()<<"\n with "<<wild.GetHP()<<" HP" <<"\n and "<<wild.GetDMG()<<" DMG"<<endl;
						int monsterNum = WhichMonster();
					while(input != '4'){
						CombatMenu();
						cin>>input;
						cin.ignore();
					switch(input){
						case '1':{cout<<"Player Has chosen to Wait"<<endl;
											break;
						}
						case '2':{cout<<"Physical Attack!"<<endl;		
								if(monsterNum == 1){
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(monsterNum == 2){
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
						}
						case '3':{
							cout<<"Special Attack!"<<endl;
							//first pokemon in list
								if(monsterNum == 1){
								if(wild.GetType() == 1 && P1.PokemonList[0].GetType() == 3){
									wild.Hit((P1.PokemonList[0].GetDMG()*P1.PokemonList[0].GetDMG()));
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetDMG()*P1.PokemonList[0].GetDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[0].GetSpecDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								}
								//2nd pokemon in pokemon list
								else if(monsterNum == 2){
									if(wild.GetType() == 1 && P1.PokemonList[1].GetType() == 3){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
									}
								else if(wild.GetType() == 2 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								}
								//3rd pokemon in list
								else if(monsterNum == 3){
									if(wild.GetType() == 1 && P1.PokemonList[2].GetType() == 3)
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								}
							}
						}
					}		
								
						else{
							SmallMonster wild;
							cout<<"The Monster is a "<<wild.GetName()<<"\n with "<<wild.GetHP()<<"HP" <<"\n and "<<wild.GetDMG()<<"DMG"<<endl;
						int monsterNum = WhichMonster();
					while(input != '4'){
						CombatMenu();
						cin>>input;
						cin.ignore();
					switch(input){
						case '1':{cout<<"Player Has chosen to Wait"<<endl;
											break;
						}
						case '2':{cout<<"Physical Attack!"<<endl;		
								if(monsterNum == 1){
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(monsterNum == 2){
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
						}
						case '3':{
							cout<<"Special Attack!"<<endl;
							//first pokemon in list
								if(monsterNum == 1){
								if(wild.GetType() == 1 && P1.PokemonList[0].GetType() == 3){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								}
								//2nd pokemon in pokemon list
								else if(monsterNum == 2){
									if(wild.GetType() == 1 && P1.PokemonList[1].GetType() == 3){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
									}
								else if(wild.GetType() == 2 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								}
								//3rd pokemon in list
								else if(monsterNum== 3){
									if(wild.GetType() == 1 && P1.PokemonList[2].GetType() == 3)
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX-1][playerY] = 'P';
										playerX--;
										input = '4';
									}
									break;
								}
								}
							}
						}
								
								
						}
					}
				}
			else if(mapState[playerX-1][playerY] == '-'){
				cout<<"Player has hit a wall!"<<endl;
			}
			break;
			}
		
		case 2:{
			cout<<"Moving East 1 Block"<<endl;
			if(mapState[playerX][playerY+1] == ' '){
				mapState[playerX][playerY] = ' ';
				mapState[playerX][playerY+1] = 'P';
				playerY++;
			}
			//another if statement to check the position of the block above then changing the icons
			else if(mapState[playerX][playerY+1] == 'I'){
				mapState[playerX][playerY]= ' ';
				mapState[playerX][playerY+1] = 'P';
				playerY++;
				P1.AddCoin();
				cout<<"Coin Collected!"<<endl;
			}//combat option
			else if(mapState[playerX][playerY+1] == 'M'){
				cout<<"Combat started!"<<endl;
				char input;
				while(input != '4'){
					srand(time(NULL));
					int monsterType;
					monsterType = ((rand()%2) + 1);
					if (monsterType == 1){
						BigMonster wild;
						cout<<"The Monster is a "<<wild.GetName()<<"\n with "<<wild.GetHP()<<" HP" <<"\n and "<<wild.GetDMG()<<" DMG"<<endl;
						int monsterNum = WhichMonster();
					while(input != '4'){
						CombatMenu();
						cin>>input;
						cin.ignore();
					switch(input){
						case '1':{cout<<"Player Has chosen to Wait"<<endl;
											break;
						}
						case '2':{cout<<"Physical Attack!"<<endl;		
								if(monsterNum == 1){
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(monsterNum == 2){
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
						}
						case '3':{
							cout<<"Special Attack!"<<endl;
							//first pokemon in list
								if(monsterNum == 1){
								if(wild.GetType() == 1 && P1.PokemonList[0].GetType() == 3){
									wild.Hit((P1.PokemonList[0].GetSpecDMG()));
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								}
								//2nd pokemon in pokemon list
								else if(monsterNum == 2){
									if(wild.GetType() == 1 && P1.PokemonList[1].GetType() == 3){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
									}
								else if(wild.GetType() == 2 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								}
								//3rd pokemon in list
								else if(monsterNum == 3){
									if(wild.GetType() == 1 && P1.PokemonList[2].GetType() == 3)
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								}
							}
						}
					}		
								
						else{
							SmallMonster wild;
							cout<<"The Monster is a "<<wild.GetName()<<"\n with "<<wild.GetHP()<<"HP" <<"\n and "<<wild.GetDMG()<<"DMG"<<endl;
						int monsterNum = WhichMonster();
					while(input != '4'){
						CombatMenu();
						cin>>input;
						cin.ignore();
					switch(input){
						case '1':{cout<<"Player Has chosen to Wait"<<endl;
											break;
						}
						case '2':{cout<<"Physical Attack!"<<endl;		
								if(monsterNum == 1){
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(monsterNum == 2){
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
						}
						case '3':{
							cout<<"Special Attack!"<<endl;
							//first pokemon in list
								if(monsterNum == 1){
								if(wild.GetType() == 1 && P1.PokemonList[0].GetType() == 3){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								}
								//2nd pokemon in pokemon list
								else if(monsterNum == 2){
									if(wild.GetType() == 1 && P1.PokemonList[1].GetType() == 3){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
									}
								else if(wild.GetType() == 2 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								}
								//3rd pokemon in list
								else if(monsterNum== 3){
									if(wild.GetType() == 1 && P1.PokemonList[2].GetType() == 3)
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY+1] = 'P';
										playerY++;
										input = '4';
									}
									break;
								}
								}
							}
						}
								
								
						}
					}
				}
			else if(mapState[playerX][playerY+1] == '-'){
				cout<<"Player has hit a wall!"<<endl;
			}
			break;
		}
		case 3:{
			cout<<"Moving South 1 Block"<<endl;
			if(mapState[playerX+1][playerY] == ' '){
				mapState[playerX][playerY] = ' ';
				mapState[playerX+1][playerY] = 'P';
				playerX++;
			}
			else if(mapState[playerX+1][playerY] == 'I'){
				mapState[playerX][playerY]= ' ';
				mapState[playerX+1][playerY] = 'P';
				playerX++;
				P1.AddCoin();
				cout<<"Coin Collected!"<<endl;
			}
			else if(mapState[playerX+1][playerY] == 'M'){
				cout<<"Combat started!"<<endl;
				char input;
				while(input != '4'){
					srand(time(NULL));
					int monsterType;
					monsterType = ((rand()%2) + 1);
					if (monsterType == 1){
						BigMonster wild;
						cout<<"The Monster is a "<<wild.GetName()<<"\n with "<<wild.GetHP()<<" HP" <<"\n and "<<wild.GetDMG()<<" DMG"<<endl;
						int monsterNum = WhichMonster();
					while(input != '4'){
						CombatMenu();
						cin>>input;
						cin.ignore();
					switch(input){
						case '1':{cout<<"Player Has chosen to Wait"<<endl;
											break;
						}
						case '2':{cout<<"Physical Attack!"<<endl;		
								if(monsterNum == 1){
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(monsterNum == 2){
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
						}
						case '3':{
							cout<<"Special Attack!"<<endl;
							//first pokemon in list
								if(monsterNum == 1){
								if(wild.GetType() == 1 && P1.PokemonList[0].GetType() == 3){
									wild.Hit((P1.PokemonList[0].GetSpecDMG()));
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								}
								//2nd pokemon in pokemon list
								else if(monsterNum == 2){
									if(wild.GetType() == 1 && P1.PokemonList[1].GetType() == 3){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
									}
								else if(wild.GetType() == 2 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								}
								//3rd pokemon in list
								else if(monsterNum == 3){
									if(wild.GetType() == 1 && P1.PokemonList[2].GetType() == 3)
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								}
							}
						}
					}		
								
						else{
							SmallMonster wild;
							cout<<"The Monster is a "<<wild.GetName()<<"\n with "<<wild.GetHP()<<"HP" <<"\n and "<<wild.GetDMG()<<"DMG"<<endl;
						int monsterNum = WhichMonster();
					while(input != '4'){
						CombatMenu();
						cin>>input;
						cin.ignore();
					switch(input){
						case '1':{cout<<"Player Has chosen to Wait"<<endl;
											break;
						}
						case '2':{cout<<"Physical Attack!"<<endl;		
								if(monsterNum == 1){
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(monsterNum == 2){
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
						}
						case '3':{
							cout<<"Special Attack!"<<endl;
							//first pokemon in list
								if(monsterNum == 1){
								if(wild.GetType() == 1 && P1.PokemonList[0].GetType() == 3){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								}
								//2nd pokemon in pokemon list
								else if(monsterNum == 2){
									if(wild.GetType() == 1 && P1.PokemonList[1].GetType() == 3){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
									}
								else if(wild.GetType() == 2 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								}
								//3rd pokemon in list
								else if(monsterNum== 3){
									if(wild.GetType() == 1 && P1.PokemonList[2].GetType() == 3)
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX+1][playerY] = 'P';
										playerX++;
										input = '4';
									}
									break;
								}
								}
							}
						}
								
								
						}
					}
				}
			
			else if(mapState[playerX+1][playerY] == '-'){
				cout<<"Player has hit a wall!"<<endl;
			}
			break;
		}
		case 4:{
			cout<<"Moving West 1 Block"<<endl;
			if(mapState[playerX][playerY-1] == ' '){
				mapState[playerX][playerY] = ' ';
				mapState[playerX][playerY-1] = 'P';
				playerY--;
			}
			//another if statement to check the position of the block above then changing the icons
			else if(mapState[playerX][playerY-1] == 'I'){
				mapState[playerX][playerY]= ' ';
				mapState[playerX][playerY-1] = 'P';
				playerY--;
				P1.AddCoin();
				cout<<"Coin Collected!"<<endl;
			}//combat option
			else if(mapState[playerX][playerY-1] == 'M'){
				cout<<"Combat started!"<<endl;
				char input;
				while(input != '4'){
					srand(time(NULL));
					int monsterType;
					monsterType = ((rand()%2) + 1);
					if (monsterType == 1){
						BigMonster wild;
						cout<<"The Monster is a "<<wild.GetName()<<"\n with "<<wild.GetHP()<<" HP" <<"\n and "<<wild.GetDMG()<<" DMG"<<endl;
						int monsterNum = WhichMonster();
					while(input != '4'){
						CombatMenu();
						cin>>input;
						cin.ignore();
					switch(input){
						case '1':{cout<<"Player Has chosen to Wait"<<endl;
											break;
						}
						case '2':{cout<<"Physical Attack!"<<endl;		
								if(monsterNum == 1){
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(monsterNum == 2){
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
						}
						case '3':{
							cout<<"Special Attack!"<<endl;
							//first pokemon in list
								if(monsterNum == 1){
								if(wild.GetType() == 1 && P1.PokemonList[0].GetType() == 3){
									wild.Hit((P1.PokemonList[0].GetSpecDMG()));
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;	
										input = '4';
									}
									break;
								}
								}
								//2nd pokemon in pokemon list
								else if(monsterNum == 2){
									if(wild.GetType() == 1 && P1.PokemonList[1].GetType() == 3){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
									}
								else if(wild.GetType() == 2 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								}
								//3rd pokemon in list
								else if(monsterNum == 3){
									if(wild.GetType() == 1 && P1.PokemonList[2].GetType() == 3)
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								}
							}
						}
					}		
								
						else{
							SmallMonster wild;
							cout<<"The Monster is a "<<wild.GetName()<<"\n with "<<wild.GetHP()<<"HP" <<"\n and "<<wild.GetDMG()<<"DMG"<<endl;
						int monsterNum = WhichMonster();
					while(input != '4'){
						CombatMenu();
						cin>>input;
						cin.ignore();
					switch(input){
						case '1':{cout<<"Player Has chosen to Wait"<<endl;
											break;
						}
						case '2':{cout<<"Physical Attack!"<<endl;		
								if(monsterNum == 1){
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(monsterNum == 2){
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Physical Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
						}
						case '3':{
							cout<<"Special Attack!"<<endl;
							//first pokemon in list
								if(monsterNum == 1){
								if(wild.GetType() == 1 && P1.PokemonList[0].GetType() == 3){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[0].GetType() == 1){
									wild.Hit(P1.PokemonList[0].GetSpecDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[0].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[0].GetDMG());
									cout<<P1.PokemonList[0].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[0].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[0].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[0].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								}
								//2nd pokemon in pokemon list
								else if(monsterNum == 2){
									if(wild.GetType() == 1 && P1.PokemonList[1].GetType() == 3){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
									}
								else if(wild.GetType() == 2 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[1].GetType() == 1){
									wild.Hit(P1.PokemonList[1].GetSpecDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[1].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[1].GetDMG());
									cout<<P1.PokemonList[1].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[1].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[1].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[1].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								}
								//3rd pokemon in list
								else if(monsterNum== 3){
									if(wild.GetType() == 1 && P1.PokemonList[2].GetType() == 3)
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 2 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else if(wild.GetType() == 3 && P1.PokemonList[2].GetType() == 1){
									wild.Hit(P1.PokemonList[2].GetSpecDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << (P1.PokemonList[2].GetSpecDMG())<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								else{
									wild.Hit(P1.PokemonList[2].GetDMG());
									cout<<P1.PokemonList[2].GetName()<<" Has Done a Special Attack Dealing " << P1.PokemonList[2].GetDMG()<<" DMG"<<endl;
									P1.PokemonList[2].Hit(wild.GetDMG());
									cout<<wild.GetName()<<" Has Done a Physical Attack Dealing " << wild.GetDMG()<<" DMG"<<endl;
									cout<<"Current Wild Monster Health is: "<<wild.GetHP()<<endl;
									cout<<"Current Pokemon Health is: "<<P1.PokemonList[2].GetHP()<<endl;
									if(wild.GetHP() <= 0){
										cout<<wild.GetName()<<" Has died"<<endl;
										mapState[playerX][playerY] = ' ';
										mapState[playerX][playerY-1] = 'P';
										playerY--;
										input = '4';
									}
									break;
								}
								}
							}
						}
								
								
						}
					}
				}
			else if(mapState[playerX][playerY-1] == '-'){
				cout<<"Player has hit a wall!"<<endl;
			}
			break;
		}
	}
}
	

void Map::setupItems(){
	numItems = rand() % maxItems + 1;
	items = new int*[numItems];
	for(int i = 0; i < numItems; i++) {
		//get row
		int row = rand()%(size-2) + 1;
		//get column
		int column = rand()%(size-2) + 1;
		//place treasures
		mapState[row][column] = 'I';

		items[i] = new int[2];
		items[i][0] = row;
		items[i][1] = column;
	}
}

void Map::setupMonsters() {
	numMonsters = rand() % maxMonsters + 1;
	monsters = new int*[numMonsters];
	for(int i = 0; i < numMonsters; i++) {
		//get row
		int row = rand()%(size-2) + 1;
		//get column
		int column = rand()%(size-2) + 1;
		//place treasures
		mapState[row][column] = 'M';
		monsters[i] = new int[2];
		monsters[i][0] = row;
		monsters[i][1] = column;
	}
}

void Map::PrintCoin() {
	cout<<"Player has "<<P1.GetCoin()<<" coins"<<endl;
}

void Map::PrintMonster(){
	P1.Print();
}

void Map::CombatMenu(){
	cout<<"\t COMBAT MENU"<<endl;
	cout<<"1.Wait"<<endl;
	cout<<"2.Physical Attack"<<endl;
	cout<<"3.Special Attack"<<endl;
	cout<<"4.RUN"<<endl;
}

int Map::WhichMonster(){
	char input;
	cout<<"Which Pokemon would you like to send out?"<<endl;
	cout<<"1."<<P1.PokemonList[0].GetName()<<endl;
	cout<<"2."<<P1.PokemonList[1].GetName()<<endl;
	cout<<"3."<<P1.PokemonList[2].GetName()<<endl;
	cin>>input;
	if(input == 1){
		return 1;
	}
	else if (input == 2){
		return 2;
	}
	else{
		return 3;
	}
}
//PLAYER

Player::Player(){
	coins = 0;
	pokemonCount = 3;
	for(int i=0;i<3;i++){
		BigMonster B;
		PokemonList[i] = B;
	}
	/*
	cout<<"creating small monster"<<endl;
	SmallMonster S;
	PokemonList[2] = S;
	cout<<"Small Monster added at 2"<<endl;
	*/
}

Player::~Player(){
	//delete [] PokemonList;
}

void Player::AddCoin(){
	coins++;
}

int Player::GetCoin(){
	return coins;
}

void Player::Print() {
	cout<<"\t Pokemon List "<<endl;
	for(int i=0;i<3;i++){
		cout<<PokemonList[i].GetName()<<endl;
	}
}

//Monster ignore

Monster::Monster(){
	
}
/*
Monster::Monster(const Monster& M){
	delete [] name;
	HP = M.HP;
	HP = M.HP;
	DMG = M.DMG;
	type = M.type;
	nameSize = M.nameSize;
	name = new char[strlen(M.name)+1];
	cout<<"Copied monster over"<<endl;
}

Monster& Monster::operator=(const Monster& M){
	cout<<name<<endl;
	delete [] name;
	HP = M.HP;
	DMG = M.DMG;
	type = M.type;
	nameSize = M.nameSize;
	name = new char[strlen(M.name)+1];
	strcpy(name,M.name);
	cout<<"Copied monster over"<<endl;
	cout<<name<<endl;
	cout<<HP<<endl;
	return *this;
}

char* Monster::GetName(){
	return name;
}

Monster::~Monster(){
	delete [] name;
}

int Monster::GetHP(){
	return HP;
}
*/
//big monster

BigMonster::BigMonster(){
	nameSize = 20;
	name = new char[nameSize];
	HP = 120;
	DMG = 20;
	SpecialDMG = 40;
	srand(time(NULL));
	temptype = ((rand() % 3) + 1);
	if(temptype == 1){
		//1 meaning fire
		type = 1;
	}
	else if(temptype == 2){
		//2 meaning grass
		type = 2;
	}
	else if(temptype == 3){
		//3 meaning water
		type = 3;
	}
	//name setting for water grass and fire
	if(type == 1){
		char name1[20] = "Big Fire Monster";
		SetName(name1);
	}
	else if(type == 2){
		char name2[20] = "Big Grass Monster";
		SetName(name2);
	}
	else{
		char name3[20] = "Big Water Monster";
		SetName(name3);
	}
}

BigMonster::~BigMonster(){
	delete [] name;
}

BigMonster& BigMonster::operator=(const BigMonster& a){
	HP = a.HP;
	DMG = a.DMG;
	nameSize = a.nameSize;
	type = a.type;
	SpecialDMG = a.SpecialDMG;
	
	delete [] name;
	
	name = new char[strlen(a.name)+1];
	strcpy(name,a.name);
	return *this;
}

void BigMonster::SetName(char* _name){
	delete [] name;
	int size = strlen(_name)+1;
	name = new char[size];
	strcpy(name,_name);
}

int BigMonster::GetType()const{
	return  type;
}

char* BigMonster::GetName()const{
	return name;
}

int BigMonster::GetHP()const{
	return HP;
}

int BigMonster::GetDMG()const{
	return DMG;
}

int BigMonster::GetSpecDMG() const{
	return SpecialDMG;
}

void BigMonster::Hit(int d){
	if(GetHP() > 0){
		HP -= d;
	}
	else{
		cout<<"Monster is DEAD"<<endl;
	}
}

//small monster

SmallMonster::SmallMonster(){
	nameSize = 30;
	name = new char[nameSize];
	HP = 80;
	DMG = 5;
	srand(time(NULL));
	type = (rand() % 10 + 1);
	if(type <= 3){
		//1 meaning fire
		type = 1;
	}
	else if(type > 3 && type <=6){
		//2 meaning grass
		type = 2;
	}
	else if(type > 6){
		//3 meaning water
		type = 3;
	}
	//name setting for water grass and fire
	if(type == 1){
		char name1[20] = "Small Fire Monster";
		SetName(name1);
	}
	else if(type == 2){
		char name2[20] = "Small Grass Monster";
		SetName(name2);
	}
	else{
		char name3[20] = "Small Water Monster";
		SetName(name3);
	}
}

SmallMonster& SmallMonster::operator=(const SmallMonster& a){
	HP = a.HP;
	DMG = a.DMG;
	nameSize = a.nameSize;
	type = a.type;
	
	delete [] name;
	
	name = new char[strlen(a.name)+1];
	strcpy(name,a.name);
	return *this;
}

SmallMonster::~SmallMonster(){
	delete [] name;
}

void SmallMonster::SetName(char* _name){
	delete [] name;
	int size = strlen(_name)+1;
	name = new char[size];
	strcpy(name,_name);
}

int SmallMonster::GetType()const{
	return type;
}

char* SmallMonster::GetName()const{
	return name;
}

int SmallMonster::GetHP() const{
	return HP;
}

int SmallMonster::GetDMG()const{
	return DMG;
}

void SmallMonster::Hit(int d){
	if(GetHP() > 0){
		HP -= d;
	}
	else{
		cout<<"Monster is DEAD"<<endl;
	}
}