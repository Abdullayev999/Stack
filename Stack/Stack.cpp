#include <iostream>
#include<iostream>

/*
	   ДОМАШНЕЕ ЗАДАНИЕ:

	   Задание 1: Реализуйте шаблонный класс stack
	   Методы стека:
	   + top() возвращает ссылку на элемнет из вершины стека
	   + pop() удаляет элемент из вершины стека
	   + push(element) добавляет элемент на вершину стека
	   + size() возвращает количество элементов в стеке
	   + swap(other_stack) обменивает содержимым два стека
	   + empty() возвращает true если стек пуст и false в противном случае
	   + конструкторы/операторы копирования/перемещения
	   + распечатайте содержимое стека за пределами класса stack
   */

template<typename T>
class Stack
{
public:
	Stack() = default;

	T& top()const
	{
		return  m_arr[m_index - 1];
	}

	void swap(Stack<T>& other)
	{
		Stack<T> tmp = std::move(other);
		other = std::move(*this);
		*this = std::move(tmp);
	}

	void pop()
	{
		if (m_index)
		{
			T* tmp = new T[m_size];
			for (int i = 0; i < m_index - 1; i++) {
				tmp[i] = m_arr[i];
			}
			delete[] m_arr;
			m_arr = tmp;
			m_index--;
		}
	}

	int size()const
	{
		return m_index;
	}

	void push(const T& value) {
		if (m_index == m_size)capacityUp();
		m_arr[m_index++] = value;
	}

	bool empty()const
	{
		return m_index == 0;
	}

	~Stack()
	{
		delete[] m_arr;
	}

	Stack(const Stack<T>& other)
	{
		m_capacity = other.m_capacity;
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = new T[m_size];

		for (int i = 0; i < m_size; i++)
			m_arr[i] = other.m_arr[i];
	}

	Stack(Stack<T>&& other)
	{
		m_capacity = other.m_capacity;
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = other.m_arr;
		other.m_arr = nullptr;
	}

	Stack& operator=(const Stack<T>& other)
	{
		m_capacity = other.m_capacity;
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = new T[m_size];

		for (int i = 0; i < m_index; i++)
			m_arr[i] = other.m_arr[i];

		return *this;
	}

	Stack& operator=(Stack<T>&& other)
	{
		m_capacity = other.m_capacity;
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = other.m_arr;
		other.m_arr = nullptr;

		return *this;
	}

private:
	template<typename T2>
	friend std::ostream& operator<<(std::ostream& os, const Stack<T2>& n);

	void capacityUp()
	{
		m_size += m_capacity;

		T* tmp = new T[m_size];

		for (int i = 0; i < m_index; i++) {
			tmp[i] = m_arr[i];
		}

		delete[] m_arr;
		m_arr = tmp;
	}


	int m_size = 10;
	int m_capacity = 10;
	int m_index = 0;
	T* m_arr = new T[m_size]{};
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& n) {
	if (n.m_index) {
		for (int i = 0; i < n.m_index; i++) {
			os << n.m_arr[i] << '\n';
		}
		os << '\n';
	}
	else {
		os << "Stack empty\n";
	}
	return os;
}

int main()
{
	std::cout << std::boolalpha;
	Stack<std::string> a;
	a.push("Farid");
	a.push("Cavid");
	Stack<std::string> b;
	b.push("Orxan");
	b.push("Sadiq");
	b.push("Rauf");
	std::cout << "a.top() = " << a.top() << '\n';
	std::cout << "a.empty() = " << a.empty() << '\n';
	std::cout << " a = " << a << '\n';
	std::cout << " b = " << b << '\n';
	std::cout << "\n\n==============\n\n";
	a.swap(b);
	std::cout << " a = " << a << '\n';
	std::cout << " b = " << b << '\n';
	std::cout << a.top();



}
