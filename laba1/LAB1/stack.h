#ifndef __STACK_H__
#define __STACK_H__

using namespace std;

template <class T>
class TStack
{
	int top;
	size_t size;
	T* pMem;

public:
	TStack() : top(-1), size(1), pMem(new T[size]) {}

	~TStack();

	TStack(const TStack&) = delete;
	TStack& operator=(const TStack&) = delete;

	TStack(TStack&& other) noexcept;

	TStack& operator=(TStack&& other) noexcept;

	size_t GetSize() const;

	bool IsEmpty() const;

	T Pop();

	void Push(const T& val);
};

#endif
