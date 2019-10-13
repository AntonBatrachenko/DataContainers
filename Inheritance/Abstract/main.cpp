#include<iostream>
using namespace std;

const char tab = '\t';

class Animal
{
public:
	virtual void sound() = 0;
};

class Cat : public Animal
{
public:
	void sound()
	{
		cout << "ּÿף" << endl;
	}
};

class Dog : public Animal
{
public:
	void sound()
	{
		cout << "ֳאג" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");
	Animal* zoo[] =
	{
		new Cat(),
		new Cat(),
		new Dog(),
		new Cat(),
		new Dog()
	};
	for (int i = 0; i < sizeof(zoo) / sizeof(Animal*); i++)
	{
		zoo[i]->sound();
	}
}