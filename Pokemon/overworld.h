#include <iostream>

using namespace std;


class Monster{
	public:
	/*
	virtual char* GetName()=0;
	virtual void Hit()=0;
	virtual void physAttack()=0;
	virtual void specAttack()=0;
	virtual int GetHP()=0;
	*/
	 Monster();
	//~Monster();
	//Monster& operator=(const Monster& M);
	//virtual char* GetName()=0;
	protected:
	char* name;
	int nameSize;
	int HP;
	int DMG;
	int type;
};
class BigMonster: public Monster{
	public:
	BigMonster();
	BigMonster& operator=(const BigMonster& a);
	~BigMonster();
	void SetName(char* _name);
	void Hit(int d);
	char* GetName()const;
	int GetHP()const;
	int GetDMG()const;
	int GetType()const;
	int GetSpecDMG() const;
	private:
	char* name;
	int nameSize;
	int HP;
	int DMG;
	int temptype;
	int type;
	int SpecialDMG;
};

class SmallMonster : public Monster{
	public:
	SmallMonster();
	~SmallMonster();
	SmallMonster& operator=(const SmallMonster& a);
	void Hit(int d);
	char* GetName()const;
	void SetName(char* _name);
	int GetHP()const;
	int GetDMG()const;
	int GetType()const;
	private:
	int nameSize;
	char* name;
	int HP;
	int DMG;
	int temptype;
	int type;
};

class Player{
	friend ostream& operator<<(ostream& s, const Player);
	public:
	Player();
	~Player();
	void AddCoin();
	int GetCoin();
	void Print();
	BigMonster PokemonList[3];
	private:
	int coins;
	int pokemonCount;
	int bigsmall;

	
};

class Map {
	friend ostream& operator<<(ostream& s, const Map& M);
	public:
		Map(int _size);
		~Map();
		void BeginCombat();
		void MovePlayer(int direction);
		void PrintCoin();
		void PrintMonster();
		int WhichMonster();
		void CombatMenu();
	private:
		const int maxItems;
		int numItems;
		const int maxMonsters;
		int numMonsters;
		int size;
		char** mapState;
		int** items;
		int** monsters;
		Player P1;
		int playerX;
		int playerY;
		void setupMonsters();
		void setupItems();
		void setupPlayer();
};