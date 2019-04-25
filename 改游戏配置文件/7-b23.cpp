// 1752762 ��1�� κ�ٴ�
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
	long long empty1;	//Ԥ��ֵ���ݲ���
	char move_speed;
	char att_speed;
	char att_range;
	char empty2;	//Ԥ��ֵ���ݲ���
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
	cout << '(' << 1 << setw(16) << "����ǳƣ�" << date->name << endl;
	cout << '(' << 2 << setw(16) << "����ֵ��" << date->hp << endl;
	cout << '(' << 3 << setw(16) << "����ֵ��" << date->strength << endl;
	cout << '(' << 4 << setw(16) << "����ֵ��" << date->physique << endl;
	cout << '(' << 5 << setw(16) << "����ֵ��" << date->skill << endl;
	cout << '(' << 6 << setw(16) << "��Ǯֵ��" << date->money << endl;
	cout << '(' << 7 << setw(16) << "����ֵ��" << date->fame << endl;
	cout << '(' << 8 << setw(16) << "����ֵ��" << date->charm << endl;
	cout << '(' << 9 << setw(16) << "�ƶ��ٶ�ֵ��" << (int)date->move_speed << endl;
	cout << '(' << 'A' << setw(16) << "�����ٶ�ֵ��" << (int)date->att_speed << endl;
	cout << '(' << 'B' << setw(16) << "������Χֵ��" << (int)date->att_range << endl;
	cout << '(' << 'C' << setw(16) << "������ֵ��" << date->attack << endl;
	cout << '(' << 'D' << setw(16) << "������ֵ��" << date->defense << endl;
	cout << '(' << 'E' << setw(16) << "���ݶ�ֵ��" << (int)date->agile << endl;
	cout << '(' << 'F' << setw(16) << "����ֵ��" << (int)date->intelligence << endl;
	cout << '(' << 'G' << setw(16) << "����ֵ��" << (int)date->exp << endl;
	cout << '(' << 'H' << setw(16) << "�ȼ�ֵ��" << (int)date->level << endl;
	cout << '(' << 'I' << setw(16) << "ħ��ֵ��" << date->magic_value << endl;
	cout << '(' << 'J' << setw(16) << "����ħ��ֵ��" << (int)date->magic_spend << endl;
	cout << '(' << 'K' << setw(16) << "ħ���˺���ֵ��" << (int)date->magic_damage << endl;
	cout << '(' << 'L' << setw(16) << "������ֵ��" << (int)date->hit_rate << endl;
	cout << '(' << 'M' << setw(16) << "ħ��������ֵ��" << (int)date->magic_defense << endl;
	cout << '(' << 'N' << setw(16) << "������ֵ��" << (int)date->crit_rate << endl;
	cout << '(' << 'O' << setw(16) << "����ֵ��" << (int)date->stamina << endl;
	cout << "(P   �˳�������" << endl << "�������޸��" << endl;
	char ch;
	while (1) {
		cin >> ch;
		if (ch >= '1'&&ch <= '9')
			return ch - '1';
		else if (ch >= 'a'&&ch <= 'p')
			return ch - 'a' + 9;
		else if (ch >= 'A'&&ch <= 'P')
			return ch - 'A' + 9;
		else
			cout << "����������������룺" << endl;
	}
}

int main()
{
	gamedate date;
	ifstream fi;
	fi.open("game1.dat", ios::in | ios::binary);
	if (!fi.is_open()) {
		cout << "�浵��ʧ�ܣ�" << endl;
		return 0;
	}
	fi.read((char*)&date, sizeof(gamedate));
	fi.close();
	int min_max[][2] = {
		-1,-1,
		0,10000,
		0,10000,
		0,8192,
		0,1024,
		0,100000000,
		0,1000000,
		0,1000000,
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
			cout << "�������޸�ֵ��";
			cin >> s;
			if (strlen(s) < 16)
				strcpy(date.name, s);
		}
		else if (t == 'P' - 'A' + 9)
			break;
		else {
			int n;
			while (1) {
				cout << "�������޸�ֵ��[" << min_max[t][0] << " - " << min_max[t][1] << ']' << endl;
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
					date.hp = n;
					break;
				case 2:
					date.strength = n;
					break;
				case 3:
					date.physique = n;
					break;
				case 4:
					date.skill = n;
					break;
				case 5:
					date.money = n;
					break;
				case 6:
					date.fame = n;
					break;
				case 7:
					date.charm = n;
					break;
				case 8:
					date.move_speed = n;
					break;
				case 9:
					date.att_speed = n;
					break;
				case 10:
					date.att_range = n;
					break;
				case 11:
					date.attack = n;
					break;
				case 12:
					date.defense = n;
					break;
				case 13:
					date.agile = n;
					break;
				case 14:
					date.intelligence = n;
					break;
				case 15:
					date.exp = n;
					break;
				case 16:
					date.level = n;
					break;
				case 17:
					date.magic_value = n;
					break;
				case 18:
					date.magic_spend = n;
					break;
				case 19:
					date.magic_damage = n;
					break;
				case 20:
					date.hit_rate = n;
					break;
				case 21:
					date.magic_defense = n;
					break;
				case 22:
					date.crit_rate = n;
					break;
				case 23:
					date.stamina = n;
					break;
				default:
					break;
			}
		}
	}
	ofstream fo;
	fo.open("game1.dat", ios::out | ios::binary);
	fo.write((char*)&date, sizeof(gamedate));
	fo.close();
	return 0;
}