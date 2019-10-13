#include<iostream>
using namespace std;

const char tab = '\t';

template<typename T>class List;
template<typename T>
class Element
{
	T Data;
	int Size;
	Element<T>* pNext;
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr)
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
	friend class List<T>;
};

template<typename T>
int Element<T>::count = 0;

template<typename T>
class List
{
	Element<T>* Head;
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
	List(initializer_list<T> il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List<T>& other) :List()
	{
		for (Element<T>* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
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

	void push_front(T Data)
	{
		Element<T>* New = new Element<T>(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}

	void push_back(T Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		//Доходим до конца списка.
		Element<T>* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//Добавляем элемент.
		Temp->pNext = new Element<T>(Data);
		size++;
	}

	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		while (Head)
		{
			pop_front();
		}
		for (Element<T>* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		cout << "CopyAssignment:" << tab << this << endl;
		return *this;
	}

	T& operator[](const int Index)
	{
		Element<T>* Temp = Head;
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
		Element<T>* to_del = Head;
		//Исключаем элемент из списка.
		Head = Head->pNext;
		//Удаляем элемент из памяти.
		delete to_del;
		size--;
	}

	void insert(int Index, T Data)
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
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		//Добавить элемент в список.
		Element<T>* New = new Element<T>(Data);
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
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element<T>* to_del = Temp->pNext;
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
		Element<T>* Temp = Head;
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
		Element<T>* Temp = Head;
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
	List<int> list(n);
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
	List<int> list1 = { 3, 5, 8, 13, 21 };
	list1 = list1;
	list1.print();
	//List list2 = { 34, 55, 89 };
	//list2.print();
	//List list3;
	//list3 = list1;
	//list3.print();
	List<double> dbl_list = { 2.5, 3.14, 8, 2 };
	dbl_list.print();
}