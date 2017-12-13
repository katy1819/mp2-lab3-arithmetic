/// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

Lexem::	Lexem(string& c1, LexType t1)
{
	c = c1;
	t = t1;
}
Lexem::Lexem(const Lexem& c1)
{
	c = c1.c;
	t = c1.t;
}
Lexem& Lexem::operator=(const Lexem &c1)
{
	c = c1.c;
	t = c1.t;
	return *this;
}
bool Lexem::operator==(const Lexem &c1) const
{
	if((c1.c == c)&&(c1.t == t))
		return true;
	else
		return false;
}
bool Lexem::operator!=(const Lexem &c1) const
{
	return !(*this == c1);
}
Arithmetic::Arithmetic(const string& inputstr1)
{
	inputstr = inputstr1;
	lexems = new Lexem[inputstr.length()];
	nLex = 0;
	Razbivka(); //разбивка на лексемы
}
Arithmetic& Arithmetic::operator=(const Arithmetic& inputstr2)
{
	inputstr = inputstr2.inputstr;
	nLex = inputstr2.nLex;
	delete [] lexems;
	lexems = new Lexem[nLex];
	for(int i=0; i<nLex; i++)
		lexems[i] = inputstr2.lexems[i];
	return *this;
}
bool Arithmetic::ProverkaNaBR() //соответствие скобок
{

	int len = inputstr.length();
	TStack<int> st(len);
	for(int i=0; i<len; i++)
	{
		if(inputstr[i] =='(')
		{
			st.Push(i+1);
		}
		else
		{
			if(inputstr[i] == ')')
			{
				if(!(st.IsEmpty()))
					st.Pop();
				else
					return false;
			}
		}
	}
	return true;
}
bool Arithmetic::ProverkaNaSimv()
{
	int k = 0;
	for(int i=0; i<nLex; i++)
	{
		if(lexems[i].t == UNKMOWN)
		{
			return false;
		}
		else
			if(lexems[i].t == VAL)
			{
				for(int j=0; i<lexems[i].c.length(); j++)
					if(lexems[i].c[i] == '.')
						k++;
				if(k>1 || lexems[i].c[0] == '.' || lexems[i].c[nLex-1] == '.')
					return false;
			}
	}
	return true;
}
bool Arithmetic::ProverkaNaProp()
{
	int pos = -1;
	if(!(lexems[0].t == VAL || lexems[0].t == OP_BR || lexems[0].c[0] == '-'))
	{
		return false;
	}
	for(int i=0; i<nLex-1; i++)
	{
		pos += lexems[i].c.length();

		if((lexems[i].t == CL_BR || lexems[i].t == VAL) && (lexems[i+1].t  == OP_BR || lexems[i+1].t == VAL))
		{
			return false;
		}

		if(lexems[i].t == OP_BR && ((lexems[i+1].t == OPER || lexems[i+1].c[0] == '-') || lexems[i+1].t == CL_BR))
		{
			return false;
		}
		if(lexems[i].t == OPER && (lexems[i+1].t == OPER || lexems [i+1].t == CL_BR))
		{
			return false;
		}
	}
	return true;
}
void Arithmetic::Razbivka()
{
	for( int i=0; i<inputstr.length(); i++)
	{
		char c1 = inputstr[i];
		int pos = znaky.find(c1);
		if(pos!=string::npos) //пока не конец
		{
			if(pos<4)
				lexems[nLex].t = OPER;
			else
				if(pos = 5)
					lexems[nLex].t = OP_BR;
				else
					if(pos = 6)
						lexems[nLex].t = CL_BR;
			lexems[nLex].c = c1;
			nLex++;
		}
		else
			if(isdigit(c1)) //является ли с десятичной цифрой
			{
				int j = i;
				while(j<inputstr.length() && (isdigit(inputstr[j]) || inputstr[j] == '.'))
					j++;
				lexems[nLex].c = inputstr.substr(i, j-i); //возвращает строку, явл подстрокой строки с i эл-та j-i эл-в
				i = j-1;
				lexems[nLex].t = VAL;
				nLex++;
			}
			else
			{
				lexems[nLex].t = UNKMOWN;
				lexems[nLex].c = c1;
				nLex++;
			}
	}
}
bool Arithmetic::prioritet(Lexem a, Lexem b)
{

	int p1, p2;
	switch (a.c[0])
	{ 
	case '(': case ')':
		p1=0;
		break;
	case '+': case '-':
		p1 = 1;
		break;
	default:
		p1 = 2;		
	}

	switch (b.c[0])
	{
	case '(': case ')':
		p2 = 0;
		break;
	case '+': case '-':
		p2 = 1;
		break;
	default:
		p2 = 2;
	}
	if(p1 > p2)
		return true;
	else
		return false;
}
bool Arithmetic::ProvVce()
{
	bool s1, s2, s3;
	if(inputstr != "")
	{
		s2 =  ProverkaNaBR();
		s1 = ProverkaNaSimv();
		if(s1 == true && s2 == true)
		{
			s3 = ProverkaNaProp();
			if(s3 == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}

////////////////////
int Arithmetic::PerevVPol(Lexem* lex)
{
	LexType t1;
	int j = 0;
	Lexem z;
	z.t = VAL;
	z.c = "0";
	TStack<Lexem> s(nLex);
	for(int i = 0; i < nLex; i++)
	{
		t1 = lexems[i].t;
		if(t1 == OPER)
		{
			if(lexems[i].c[0] == '-' && (i == 0 || lexems[i-1].c[0] == '('))
			{
				lex[j] = z;
				j++;
			}
			if(!s.IsEmpty() && !prioritet(lexems[i], s.Top()))
			{
				lex[j] = s.Pop();
				j++;
			}
			s.Push(lexems[i]);
		}
		if(t1 == OP_BR)
		{
			s.Push(lexems[i]);
		}
		if(t1 == CL_BR)
		{
			while((s.Top()).t != OP_BR)
			{
				lex[j] = s.Pop();
				j++;
			}
			s.Pop();
		}
		if(t1 == VAL)
		{
			lex[j] = lexems[i];
			j++;
		}
	}
	while(!s.IsEmpty())
	{
		lex[j] = s.Pop();
		j++;
	}
	return j;
}

double Arithmetic::Calcul()
{
	Lexem* lex = new Lexem[2*nLex];
	int p = PerevVPol(lex);
	TStack<double> res(2*p);
	for(int i = 0; i< p; i++)
		if(lex[i].t == VAL)
			res.Push(stod(lex[i].c));
		else
		{
			double r = res.Pop(), r1 = res.Pop();
			switch(lex[i].c[0])
			{
			case '+':
				res.Push(r+r1);
				break;
			case '-': 
				res.Push(r1 - r);
				break;
			case '*': 
				res.Push(r1*r);
				break;
			default:
				res.Push(r1/r);
			}
		}
		return res.Top();
}
