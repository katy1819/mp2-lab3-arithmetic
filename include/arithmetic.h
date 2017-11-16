// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>

using namespace std;

enum LexType {OP_BR, CL_BR, VAR, VAL, OPER}; 

struct Lexem
{
	char str[10];
	LexType type;
	Lexem(char *s, LexType t);
	Lexem(const Lexem &p);
	Lexem & operator=(const Lexem &p);
	bool operator==(const Lexem &p) const;
};


class Ariphmetic
{

};