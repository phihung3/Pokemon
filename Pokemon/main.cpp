#include <iostream>
#include "overworld.h"

using namespace std;
void moveMenu();
//couldnt get the list working for monsters so i made the monster list just consist of bigmonsters only
//Special damage is a bit messed up it always says it does extra damage and it actaully does 0 but I'm not sure why
//sorry for very long code copy and pasted my move function for the combat portion
int main(){
srand(time(NULL));
Map M((rand() % 20)+10);
cout<<M<<endl;
char input;
while(input != '7'){
moveMenu();

cout<<"Enter option: ";
cin>>input;
cin.ignore();
if(input == '7'){
	cout<<"GAME OVER"<<endl;
	break;
}
switch(input){
	case '1': M.MovePlayer(1);
				break;
	case '2': M.MovePlayer(2);
				break;
	case '3': M.MovePlayer(3);
				break;
	case '4': M.MovePlayer(4);
				break;
	case '5': M.PrintCoin();			
				break;
	case '6': M.PrintMonster();
				break;
}				
cout<<M<<endl;
}
}


void moveMenu(){
	cout<<"\t Player Menu"<<endl;
	cout<<"1.Move North"<<endl;
	cout<<"2.Move East"<<endl;
	cout<<"3.Move South"<<endl;
	cout<<"4.Move West"<<endl;
	cout<<"5.Display Items"<<endl;
	cout<<"6.Display Player's Pokemon"<<endl;
	cout<<"7.End Game"<<endl;
}