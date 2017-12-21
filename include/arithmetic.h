// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once

#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

enum LexType {OP_BR, CL_BR, OPER, VAL, UNKMOWN};

const string znaky = "+-*/()";

struct Lexem
{
	string c;
	LexType t;
	Lexem()
	{
		c = "";
	}
	Lexem(string &c1) 
	{
		c = c1;
	}
	Lexem(string& c1, LexType t1);
	Lexem(const Lexem& c1);
	Lexem& operator=(const Lexem &c1);
	bool operator==(const Lexem &c1) const;
	bool operator!=(const Lexem &c1) const;
};

class Arithmetic
{
	string inputstr;
	Lexem* lexems;
	int nLex;
public:
	Arithmetic(const string& inputstr1);
	~Arithmetic()
	{
		delete [] lexems;
	}
	Arithmetic& operator=(const Arithmetic& inputstr2);
	bool operator==(const Arithmetic& inputstr2) const;
	//функции

	bool ProverkaNaBR(); //соответствие скобок
	bool ProverkaNaSimv();
	bool ProverkaNaProp();
	void Razbivka();

	bool prioritet(Lexem a, Lexem b);

	//bool ProvVce();

	int PerevVPol(Lexem* lex);
	double Calcul();
};