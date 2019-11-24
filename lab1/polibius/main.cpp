// CriptarePolybiusCPP.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include<iostream>
#include<string>

using namespace std;

char pc[6][6], c[1000], decy[1000];
int enc[1000];

struct index
{
	int x, y;
};

void table(string k)
{
	int l = 0, i = 0, j = 0, v[10] = { 0 }, av[26] = { 0 };
	while (l < k.size())
	{
		if (k[l] >47 && k[l]<58 && v[k[l] - 48] == 0)
		{
			pc[i][j] = k[l];
			v[k[l] - 48] = 1;
			j++;
		}

		else if (k[l] >96 && k[l]<123 && av[k[l] - 97] == 0)
		{
			pc[i][j] = k[l];
			av[k[l] - 97] = 1;
			j++;
		}

		if (j>5)
		{
			j = 0;
			i++;
		}
		l++;
	}

	for (l = 0; l<10; l++)
	{
		if (v[l] == 0)
		{
			pc[i][j] = l + 48;
			j++;
		}

		if (j>5)
		{
			j = 0;
			i++;
		}
	}

	for (l = 0; l<26; l++)
	{
		if (av[l] == 0)
		{
			pc[i][j] = l + 97;
			j++;
		}

		if (j>5)
		{
			j = 0;
			i++;
		}
	}
}

struct index findIndex(char ch)
{
	int i, j;
	struct index f;
	for (i = 0; i<6; i++)
	{
		for (j = 0; j<6; j++)
		{
			if (pc[i][j] == ch)
			{
				f.x = i;
				f.y = j;
				i = 6;
				j = 6;
			}
		}
	}
	return f;
}

void encrypt(string s)
{
	int i, ax, ay, bx, by;
	struct index f;
	for (i = 0; i<s.size(); i++)
	{
		if (s[i] >47 && s[i]<58)
		{
			f = findIndex(s[i]);
			ax = f.x;
			ay = f.y;
			enc[i] = ax * 10 + ay;
			cout << enc[i];
		}
		else if (s[i] >96 && s[i]<123)
		{
			f = findIndex(s[i]);
			ax = f.x;
			ay = f.y;
			enc[i] = ax * 10 + ay;
			cout << enc[i];
		}
	}
}

void decrypt(string s)
{
	int i, ax, ay, bx, by;
	struct index f;
	for (i = 0; i<s.size(); i++)
	{
		ax = enc[i] / 10;
		ay = enc[i] % 10;
		decy[i] = pc[ax][ay];
		if (s[i] >47 && s[i]<58)
		{
			cout << decy[i];
		}
		else if (s[i] >96 && s[i]<123)
		{
			cout << decy[i];
		}
		else
		{
			cout << s[i];
		}
	}
}

int main()
{
	string s, k;
	cout << "Introduceti textul de criptat: " << endl;
	getline(cin, s);
	cout << "Introduceti cheia de criptare : " << endl;
	cin >> k;
	int i, j, f = 0;
	cout << "\n5x5 Patratul lui Polybius : " << endl;
	table(k);
	for (i = 0; i<5; i++)
	{
		for (j = 0; j<5; j++)
		{
			cout << pc[i][j] << " ";

		}
		cout << endl;
	}
	cout << "\nMesajul criptat : ";
	encrypt(s);
	cout << endl;
	cout << "\nMesajul decriptat : ";
	decrypt(s);
	cout << endl;
//	system("pause");
}
