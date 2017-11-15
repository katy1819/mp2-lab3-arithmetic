// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#ifndef __TSTACK_H__
#define __TSTACK_H__

#include <iostream>

using namespace std;

const int MAX_STACK_SIZE = 1000;

// Шаблон стека
template <class T>
class TStack
{
protected:
	T *pStack;
	int Size;
	int top;
public:
	TStack(int s = 10);
	TStack(const TStack &st);
	~TStack();
	//T & operator[](int pos);
	bool operator==(const TStack &st) const;
	TStack & operator=(const TStack &st);
	void Push(T Val); //вставка 
	T Pop(); // извлечение
	T Top(); //просмотр верхнего эл-та
	bool IsEmpty(); // проверка на пустоту
	bool IsFull(); //проверка на полноту
	int Quantity(); // получение кол-ва эл-в
	void Clean();
};

/*-------------------------------------------------------------------------*/

template <class T>
TStack<T>::TStack(int s) //тесты сделаны
{
	Size = s;
	if(Size<0 || Size>MAX_STACK_SIZE)
		throw "error";
	pStack = new T[s];
	top = 0;
}

/*-------------------------------------------------------------------------*/

template <class T>
TStack<T>::TStack(const TStack<T> &st) //тесты сделаны
{
	Size = st.Size;
	top = st.top;
	pStack = new T[Size];
	for(int i = 0; i<top; i++)
		pStack[i] = st.pStack[i];
}

/*-------------------------------------------------------------------------*/

template <class T>
TStack<T>::~TStack()
{
	delete [] pStack;
}

/*-------------------------------------------------------------------------*/

template <class T>
TStack<T> & TStack<T>::operator=(const TStack &st) //тесты сделаны
{
	if(this!=&st)
	{
		if(Size != st.Size)
		{
			delete [] pStack;
			pStack = new T [st.Size];
		}
		Size = st.Size;
		top = st.top;
		for(int i=0; i<top; i++)
			pStack[i] = st.pStack[i];
	}
	return *this;
}

/*-------------------------------------------------------------------------*/

template <class T>    
bool TStack<T>::operator==(const TStack &st) const  //тесты сделаны
{
	if(this!=&st)
	{
		if((Size == st.Size) && (top == st.top))
		{
			for(int i=0; i<top; i++)
				if(pStack[i] != st.pStack[i])
					return false;
			return true;
		}
		else
			return false;
	}
	return true;
}

/*-------------------------------------------------------------------------*/

template <class T>
bool TStack<T>::IsFull() //тесты сделаны
{
	if(top == Size)
		return true;
	else
		return false;
}

/*-------------------------------------------------------------------------*/

template <class T>
bool TStack<T>::IsEmpty() //тесты сделаны
{
	if(top==0)
		return true;
	else
		return false;
}

/*-------------------------------------------------------------------------*/

template<class T>
void TStack<T>::Push(T Val) //тесты сделаны
{
	if((Size - top)==0)
	{
		T* st1;
		st1 = new T [2*Size];
		for( int i=0; i<top; i++)
			st1[i] = pStack[i];
		delete [] pStack;
		pStack = st1;

		pStack[top] = Val;
		top++;

		Size = 2*Size;
	}
	else
	{ 
		pStack[top] = Val; 
		top+=1;
	}
}

/*-------------------------------------------------------------------------*/

template<class T>
T TStack<T>::Pop() //тесты сделаны
{
	if (!IsEmpty())
	{
		top = top-1;
		return pStack[top];
	}
	else 
		throw "empty";
}

/*-------------------------------------------------------------------------*/

template<class T>
T TStack<T>::Top() //тесты сделаны
{
	if (!IsEmpty())
	{
		return pStack[top - 1];
	}
	else throw "empty";
}

/*-------------------------------------------------------------------------*/

template<class T>
int TStack<T>::Quantity() //тесты сделаны
{
	return top;
}

/*-------------------------------------------------------------------------*/

template<class T>
void TStack<T>::Clean() //тесты сделаны
{
	top = 0;
}

/*-------------------------------------------------------------------------*/

#endif
