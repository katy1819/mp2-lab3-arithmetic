// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

//Структура лексем:

TEST(Lexem, can_create_lexem)
{
	string s = "121";
	Lexem c1(s,VAL);
	EXPECT_EQ("121",c1.c);
	EXPECT_EQ(VAL, c1.t);
}

TEST(Lexem, copy) //копирование
{
	Lexem c1;
	Lexem c2(c1);
	EXPECT_EQ(c1, c2);
}

TEST(Lexem, can_prirav_lex) //равенство
{
	string s1 = "121";
	string s2 = "+";
	Lexem c1(s1, VAL);
	Lexem c2(s2, OPER);
	c2 = c1;
	EXPECT_EQ("121", c2.c);
	EXPECT_EQ(VAL, c2.t);
}

TEST(Lexem, sravnenie1) //сравнение
{
	string s1 = "121";
	string s2 = "+";
	Lexem c1(s1, VAL);
	Lexem c2(s2, OPER);
	EXPECT_EQ(c2 != c1, true);
}

TEST(Lexem, sravnenie2) //сравнение
{
	string s1 = "121";
	string s2 = "121";
	Lexem c1(s1, VAL);
	Lexem c2(s2, VAL);
	EXPECT_EQ(c2 == c1, true);
}
 
//Класс Arithmetic:

//Проверка на подсчет:

TEST(Arithmetic, calcul11) 
{
	Arithmetic A("5+4");
	EXPECT_EQ(9, A.Calcul());
}

TEST(Arithmetic, calcul2) 
{
	Arithmetic A("5.7+4");
	EXPECT_EQ(9.7, A.Calcul());
}

TEST(Arithmetic, calcul3)
{
	Arithmetic A("50*2-(100+70)*2");
	EXPECT_EQ(-240, A.Calcul());
}

TEST(Arithmetic, calcul4)
{
	Arithmetic A("5+2*3");
	EXPECT_EQ(11, A.Calcul());
}

// Проверка на символы: ---------------------------------------------

TEST(Arithmetic, prov_na_symbols1)
{
	Arithmetic A("5&61");
	EXPECT_EQ(false, A.ProverkaNaSimv());
}

TEST(Arithmetic, prov_na_symbols2)
{
	Arithmetic A("5%61");
	EXPECT_EQ(false, A.ProverkaNaSimv());
}

TEST(Arithmetic, prov_na_symbols3)
{
	Arithmetic A("5??61");
	EXPECT_EQ(false, A.ProverkaNaSimv());
}

TEST(Arithmetic, prov_na_symbols4)
{
	Arithmetic A("5!=61");
	EXPECT_EQ(false, A.ProverkaNaSimv());
}


// Тесты на проверку операции: ---------------------------------------

TEST(Arithmetic, prov_na_prop1)
{
	Arithmetic A("5+)6*89");
	EXPECT_EQ(false,A.ProverkaNaProp());
}
TEST(Arithmetic, prov_na_prop2)
{
	Arithmetic A("+5*9");
	EXPECT_EQ(false, A.ProverkaNaProp());
}

TEST(Arithmetic, prov_na_prop3)
{
	Arithmetic A("*5-9");
	EXPECT_EQ(false, A.ProverkaNaProp());
}

TEST(Arithmetic, prov_na_prop4)
{
	Arithmetic A("/5*9");
	EXPECT_EQ(false, A.ProverkaNaProp());
}
TEST(Arithmetic, prov_na_prop5)
{
	Arithmetic A("5+7/");
	EXPECT_EQ(false, A.ProverkaNaProp());
}
TEST(Arithmetic, prov_na_prop6)
{
	Arithmetic A("5()+7");
	EXPECT_EQ(false, A.ProverkaNaProp());
}
TEST(Arithmetic, prov_na_prop7)
{
	Arithmetic A(")(5+7");
	EXPECT_EQ(false, A.ProverkaNaProp());
}
TEST(Arithmetic, prov_na_prop8)
{
	Arithmetic A("5+-7");
	EXPECT_EQ(false, A.ProverkaNaProp());
}
//------------------------------------------------------

//Разбивка:

TEST(Arithmetic, razbivka)
{
	Arithmetic A("5+4*7");
	int res;
	Lexem c[100];
	res = A.PerevVPol(c);
	EXPECT_EQ(5, res);
}

// Проверка на скобки:

TEST(Arithmetic, pr_na_br1)
{
	Arithmetic A("(5+7)-4");
	EXPECT_EQ(true, A.ProverkaNaBR());
}

TEST(Arithmetic, pr_na_br2)
{
	Arithmetic A(")5+4)");
	EXPECT_EQ(false, A.ProverkaNaBR());
}

// На создание arithmetic:

TEST(Arithmetic, can_pr_arith)
{
	string s1 = "5+6*(8-5)";
	string s2 = "5+6*(7-5)";
	Arithmetic A1(s1), A2(s2);
	A2 = A1;
	EXPECT_EQ(true, A2 == A1);
}

TEST(Arithmetic, can_sr1_arith)
{
	string s1 = "5+6*(8-5)";
	string s2 = "5+6*(7-5)";
	Arithmetic A1(s1), A2(s2);
	EXPECT_EQ(false, A2 == A1);
}

TEST(Arithmetic, can_sr2_arith)
{
	string s1 = "5+6*(8-5)";
	string s2 = "5+6*(8-5)";
	Arithmetic A1(s1), A2(s2);
	EXPECT_EQ(true, A1 == A2);
}
