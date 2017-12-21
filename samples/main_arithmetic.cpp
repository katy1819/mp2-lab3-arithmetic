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
		double res;
		res = A.Calcul();
		cout << res << endl;
		cout << "continue?" << endl;
		cin >> f;
	}
}
