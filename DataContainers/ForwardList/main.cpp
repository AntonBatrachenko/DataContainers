#include<iostream>
using namespace std;

const char tab = '\t';

class Element
{
	int Data;
	int Size;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
		cout << "ElementConstructor:" << tab << this << endl;
	}
	~Element()
	{
		count--;
		cout << "ElementDestructor:" << tab << this << endl;
	}
	friend class List;
};

int Element::count = 0;

class List
{
	Element* Head;
	int data;
	int size;
public:
	int get_size() const
	{
		return this->size;
	}
	List()
	{
		this->Head = nullptr;
		cout << "ListConstructor:" << tab << this << endl;
		this->size = 0;
	}
	List(int size):List()
	{
		while (size--)
		{
			push_front(0);
		}
	}
	List(initializer_list<int> il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		cout << "CopyConstructor:" << tab << this << endl;
	}
	~List()
	{
		while (Head)
		{
			pop_front();
		}
		cout << "ListDestructor:" << tab << this << endl;
	}

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		//Доходим до конца списка.
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//Добавляем элемент.
		Temp->pNext = new Element(Data);
		size++;
	}

	List& operator=(const List& other)
	{
		if (this == &other)
		{
			return *this;
		}
		while (Head)
		{
			pop_front();
		}
		for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		cout << "CopyAssignment:" << tab << this << endl;
		return *this;
	}

	int& operator[](const int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}

	void pop_front()
	{
		if (Head == nullptr)
		{
			return;
		}
		//Запоминаем адрес удаляемого элемента.
		Element* to_del = Head;
		//Исключаем элемент из списка.
		Head = Head->pNext;
		//Удаляем элемент из памяти.
		delete to_del;
		size--;
	}

	void insert(int Index, int Data)
	{
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Index >= size)
		{
			push_back(Data);
			return;
		}
		//Дойти до нужной позиции.
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		//Добавить элемент в список.
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void erase(int Index)
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index == size - 1)
		{
			pop_back();
			return;
		}
		if (Index >= size)
		{
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* to_del = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete to_del;
		size--;
	}

	void pop_back()
	{
		//Если список пуст, удалять из него нечего, по-этому сразу же выходим из метода.
		if (Head == nullptr || Head->pNext == nullptr)
		{
			pop_front();
			return;
		}
		//Дойти до конца списка.
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//Удалить элемент.
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void print()
	{
		Element* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов в списке: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите размер списка: ";
	cin >> n;
	/*List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();*/
	/*List list2;
	for (int i = 0; i < 3; i++)
	{
		list2.push_back(rand());
	}
	list2.print();
	int Index;
	int Data;
	cout << "Введите индекс добавляемого элемента: ";
	cin >> Index;
	cout << "Введите значение добавляемого элемента: ";
	cin >> Data;
	list.insert(Index, Data);
	list.print();
	cout << "Введите индекс удаляемого элемента: ";
	cin >> Index;
	list.erase(Index);
	list.print();*/
	List list(n);
	list.print();
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
	List list1 = { 3, 5, 8, 13, 21 };
	list1 = list1;
	list1.print();
	//List list2 = { 34, 55, 89 };
	//list2.print();
	//List list3;
	//list3 = list1;
	//list3.print();
}