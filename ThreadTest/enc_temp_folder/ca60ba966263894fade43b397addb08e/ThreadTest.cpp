#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <iostream>

template <class T>
bool cas(T* objPtr, T old, T newValue)
{
	if (*objPtr != old)
		return false;
	else
	{
		*objPtr = newValue;
		return true;
	}
}

template <class T>
struct Node
{
	T data;
	Node<T>* next;
};

template <class T>
class LinkedStack
{
private:
	Node<T>* m_Head;
public:
	LinkedStack();
	~LinkedStack();

	void push(T value);
	void pop();
};

template<class T>
LinkedStack<T>::LinkedStack()
	:m_Head{ nullptr }
{
}

template<class T>
LinkedStack<T>::~LinkedStack()
{
	delete m_Head;
	m_Head = nullptr;
}

template<class T>
void LinkedStack<T>::push(T value)
{
	Node<T>* node = new Node<T>;
	node->data = value;
	do {
		node->next = m_Head;
	} while (!cas(&m_Head, node->next, node));
}

template<class T>
void LinkedStack<T>::pop()
{
	auto current = m_Head;
	while (current) {
		if (cas(&m_Head, current, current->next))
		{
			return;
		}
		current = m_Head;
	}
}


int main()
{
	LinkedStack<std::string> myStack{};

	const int amtOfLoops{20};
	std::vector<std::thread> threads{};
	threads.resize(amtOfLoops);

	auto l = [&myStack]
	{
		myStack.push("five");
		myStack.push("help");
		myStack.push("please");
		myStack.pop();
		myStack.pop();
		myStack.push("seven");
	};

	auto timeStart = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < amtOfLoops; ++i)
	{
		threads[i] = std::thread(l);
	}
	for (int i = 0; i < amtOfLoops; ++i)
	{
		threads[i].join();
	}
	auto timeEnd = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart)<< '\n';
}

