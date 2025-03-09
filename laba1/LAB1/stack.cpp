#include "stack.h"

TStack::~TStack()
{
	delete[] pMem;
}

TStack::TStack(TStack&& other) noexcept : top(other.top), size(other.size), pMem(other.pMem)
{
	other.pMem = nullptr;
	other.top = -1;
	other.size = 0;
}

TStack& TStack::operator=(TStack&& other noexcept)
{
	if (this != &other)
	{
		delete[] pMem;
		top = other.top;
		size = other.size;
		pMem = other.pMem;
		other.pMem = nullptr;
		other.top = -1;
		other.size = 0;
	}
	return *this;
}

size_t TStack::GetSize() const
{
	return top + 1;
}

bool TStack::IsEmpty() const
{
	return top == -1;
}

T TStack::Pop()
{
	if (IsEmpty())
		throw std::underflow_error("Stack is empty");
	return pMem[top--];
}

void TStack::Push(const T& val)
{
	if (top == size - 1)
	{
		size *= 2;
		T* tmp = new T[size];
		std::copy(pMem, pMem + top + 1, tmp);
		delete[] pMem;
		pMem = tmp;
	}
	pMem[++top] = val;
}
