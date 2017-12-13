// реализация пользовательского приложения
#include "arithmetic.h"

int main()
{
	bool f = true;
	while (f)
	{
		string s;
		cout << "input string: ";
		cin >> s;
		Arithmetic A(s);
		Lexem src[1000];
		double res;
		int k;
		A.PerevVPol(src);
		res = A.Calcul();
		cout << res << endl;
		cout << "continue?" << endl;
		cin >> f;
	}
}

// 50 * 2 -(100+70)*2
// 7 - (-9 + 6)
// параметры??