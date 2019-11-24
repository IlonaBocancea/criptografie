// CriptarePlayfairCPP.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include<iostream>
#include<string>

using namespace std;

char pc[6][6], c[1000], ans[1000], decy[1000];

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

int convert(string s)
{
	int i, j = 0, f = 0;
	for (i = 0; i<s.size(); i++)
	{
		if ((s[i]>47 && s[i]<58) || (s[i]>96 && s[i]<123))
		{
			if ((i + f) % 2 != 0 && c[j - 1] == s[i])
			{
				c[j] = 'x';
			}
			else
			{
				c[j] = s[i];
			}
			cout << c[j];
			j++;
		}
		else
		{
			f++;
		}
	}
	if (j % 2 != 0)
	{
		c[j] = 'x';
		cout << c[j];
		j++;
	}
	return j;
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

void encrypt(int l)
{
	int i, ax, ay, bx, by;
	struct index f;
	for (i = 0; i<l; i = i + 2)
	{
		f = findIndex(c[i]);
		ax = f.x;
		ay = f.y;
		f = findIndex(c[i + 1]);
		bx = f.x;
		by = f.y;
		if (ax == bx)
		{
			ans[i] = pc[ax][(ay + 1) % 6];
			ans[i + 1] = pc[ax][(by + 1) % 6];
		}
		else if (ay == by)
		{
			ans[i] = pc[(ax + 1) % 6][by];
			ans[i + 1] = pc[(bx + 1) % 6][ay];
		}
		else
		{
			ans[i] = pc[ax][by];
			ans[i + 1] = pc[bx][ay];
		}
		cout << ans[i] << ans[i + 1];
	}
}

void decrypt(int l)
{
	int i, ax, ay, bx, by;
	struct index f;
	for (i = 0; i<l; i = i + 2)
	{
		f = findIndex(ans[i]);
		ax = f.x;
		ay = f.y;
		f = findIndex(ans[i + 1]);
		bx = f.x;
		by = f.y;
		if (ax == bx)
		{
			if (by - 1<0)
			{
				decy[i + 1] = pc[ax][5];
			}
			else
			{
				decy[i + 1] = pc[ax][(by - 1) % 6];
			}
			if (ay - 1<0)
			{
				decy[i] = pc[ax][5];
			}
			else
			{
				decy[i] = pc[ax][(ay - 1) % 6];
			}
		}
		else if (ay == by)
		{
			if (bx - 1<0)
			{
				decy[i + 1] = pc[5][by];
			}
			else
			{
				decy[i + 1] = pc[(bx - 1) % 6][by];
			}
			if (ax - 1<0)
			{
				decy[i] = pc[5][ay];
			}
			else
			{
				decy[i] = pc[(ax - 1) % 6][ay];
			}
		}
		else
		{
			decy[i] = pc[ax][by];
			decy[i + 1] = pc[bx][ay];
		}
		cout << decy[i] << decy[i + 1];
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
	cout << "\n5x5 Matricea Playfair : " << endl;
	table(k);
	for (i = 0; i<6; i++)
	{
		for (j = 0; j<6; j++)
		{
			cout << pc[i][j] << " ";
		}
		cout << endl;
	}
	int l;
	cout << "\nMesajul original de criptat : ";
	l = convert(s);
	cout << endl;
	cout << "\nMesajul criptat : ";
	encrypt(l);
	cout << endl;
	cout << "\nMesajul decriptat : ";
	decrypt(l);
	cout << endl;
//	system("pause");
}
