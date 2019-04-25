// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#pragma pack(1)
using namespace std;
struct gamedate
{
	char name[16];
	short hp;
	short strength;
	short physique;
	short skill;
	int money;
	int fame;
	int charm;
	long long energy;	//预留值，暂不用
	char move_speed;
	char att_speed;
	char att_range;
	char empty2;	//预留值，暂不用
	short attack;
	short defense;
	char agile;
	char intelligence;
	char exp;
	char level;
	short magic_value;
	char magic_spend;
	char magic_damage;
	char hit_rate;
	char magic_defense;
	char crit_rate;
	char stamina;
};

int menu(gamedate *date) {
	cout << '(' << 1 << setw(16) << "玩家昵称：" << date->name << endl;
	cout << '(' << 2 << setw(16) << "生命值：" << date->hp << endl;
	cout << '(' << 3 << setw(16) << "力量值：" << date->strength << endl;
	cout << '(' << 4 << setw(16) << "体质值：" << date->physique << endl;
	cout << '(' << 5 << setw(16) << "灵巧值：" << date->skill << endl;
	cout << '(' << 6 << setw(16) << "金钱值：" << date->money << endl;
	cout << '(' << 7 << setw(16) << "名声值：" << date->fame << endl;
	cout << '(' << 8 << setw(16) << "魅力值：" << date->charm << endl;
	cout << '(' << 9 << setw(16) << "活力值：" << date->energy << endl;
	cout << '(' << 'A' << setw(16) << "移动速度值：" << (int)date->move_speed << endl;
	cout << '(' << 'B' << setw(16) << "攻击速度值：" << (int)date->att_speed << endl;
	cout << '(' << 'C' << setw(16) << "攻击范围值：" << (int)date->att_range << endl;
	cout << '(' << 'D' << setw(16) << "攻击力值：" << date->attack << endl;
	cout << '(' << 'E' << setw(16) << "防御力值：" << date->defense << endl;
	cout << '(' << 'F' << setw(16) << "敏捷度值：" << (int)date->agile << endl;
	cout << '(' << 'G' << setw(16) << "智力值：" << (int)date->intelligence << endl;
	cout << '(' << 'H' << setw(16) << "经验值：" << (int)date->exp << endl;
	cout << '(' << 'I' << setw(16) << "等级值：" << (int)date->level << endl;
	cout << '(' << 'J' << setw(16) << "魔法值：" << date->magic_value << endl;
	cout << '(' << 'K' << setw(16) << "消耗魔法值：" << (int)date->magic_spend << endl;
	cout << '(' << 'L' << setw(16) << "魔法伤害力值：" << (int)date->magic_damage << endl;
	cout << '(' << 'M' << setw(16) << "命中率值：" << (int)date->hit_rate << endl;
	cout << '(' << 'N' << setw(16) << "魔法防御力值：" << (int)date->magic_defense << endl;
	cout << '(' << 'O' << setw(16) << "暴击率值：" << (int)date->crit_rate << endl;
	cout << '(' << 'P' << setw(16) << "耐力值：" << (int)date->stamina << endl;
	cout << "(Q   退出并保存" << endl << "请输入修改项：" << endl;
	char ch;
	while (1) {
		cin >> ch;
		if (ch >= '1'&&ch <= '9')
			return ch - '1';
		else if (ch >= 'a'&&ch <= 'q')
			return ch - 'a' + 9;
		else if (ch >= 'A'&&ch <= 'Q')
			return ch - 'A' + 9;
		else
			cout << "输入错误，请重新输入：" << endl;
	}
}

int main()
{
	gamedate date;
	ifstream fi;
	fi.open("game2.dat", ios::in | ios::binary);
	if (!fi.is_open()) {
		cout << "存档打开失败！" << endl;
		return 0;
	}
	fi.read((char*)&date, sizeof(gamedate));
	fi.close();
	long long min_max[][2] = {
		-1,-1,
		0,10000,
		0,10000,
		0,8192,
		0,1024,
		0,100000000,
		0,1000000,
		0,1000000,
		100000000000,200000000000,
		0,100,
		0,100,
		0,100,
		0,2000,
		0,2000,
		0,100,
		0,100,
		0,100,
		0,100,
		0,10000,
		0,100,
		0,100,
		0,100,
		0,100,
		0,100,
		0,100
	};
	while (1) {
		int t = menu(&date);
		if (t == 0) {
			char s[16];
			cout << "请输入修改值：";
			cin >> s;
			if (strlen(s) < 16)
				strcpy(date.name, s);
		}
		else if (t == 'Q' - 'A' + 9)
			break;
		else {
			long long n;
			while (1) {
				cout << "请输入修改值：[" << min_max[t][0] << " - " << min_max[t][1] << ']' << endl;
				cin >> n;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (n< min_max[t][0] || n>min_max[t][1])
					continue;
				break;
			}
			switch (t)
			{
				case 1:
					date.hp = (short)n;
					break;
				case 2:
					date.strength = (short)n;
					break;
				case 3:
					date.physique = (short)n;
					break;
				case 4:
					date.skill = (short)n;
					break;
				case 5:
					date.money = (int)n;
					break;
				case 6:
					date.fame = (int)n;
					break;
				case 7:
					date.charm = (int)n;
					break;
				case 8:
					date.energy = n;
					break;
				case 9:
					date.move_speed = (char)n;
					break;
				case 10:
					date.att_speed = (char)n;
					break;
				case 11:
					date.att_range = (char)n;
					break;
				case 12:
					date.attack = (short)n;
					break;
				case 13:
					date.defense = (short)n;
					break;
				case 14:
					date.agile = (char)n;
					break;
				case 15:
					date.intelligence = (char)n;
					break;
				case 16:
					date.exp = (char)n;
					break;
				case 17:
					date.level = (char)n;
					break;
				case 18:
					date.magic_value = (short)n;
					break;
				case 19:
					date.magic_spend = (char)n;
					break;
				case 20:
					date.magic_damage = (char)n;
					break;
				case 21:
					date.hit_rate = (char)n;
					break;
				case 22:
					date.magic_defense = (char)n;
					break;
				case 23:
					date.crit_rate = (char)n;
					break;
				case 24:
					date.stamina = (char)n;
					break;
				default:
					break;
			}
		}
	}
	ofstream fo;
	fo.open("game2.dat", ios::out | ios::binary);
	fo.write((char*)&date, sizeof(gamedate));
	fo.close();
	return 0;
}