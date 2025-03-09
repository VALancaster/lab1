#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stdexcept>
#include <utility>

template<typename Type>
class SinglyList {
private:
	struct Element {
		Type data;
		Element* next = nullptr;
	};

	Element* firstElement;
	Element* lastElement;
	size_t elementCount;

	Element* fetchElement(size_t index) const;

public:
	SinglyList();
	SinglyList(const SinglyList& source);
	SinglyList(SinglyList&& source) noexcept;
	~SinglyList();

	size_t length() const noexcept;
	bool empty() const noexcept;

	void addToEnd(const Type& data);
	void addToStart(const Type& data);
	void eraseAt(size_t index);
	void reset();

	Type& getItem(size_t index);
	const Type& getItem(size_t index) const;

	bool operator==(const SinglyList& source) const noexcept;
	bool operator!=(const SinglyList& source) const noexcept;

	SinglyList& operator=(const SinglyList& source);
	SinglyList& operator=(SinglyList&& source) noexcept;

	class Iter {
	private:
		Element* currentElem;
	public:
		explicit Iter(Element* element) : currentElem(element) {}
		Iter& operator++() { currentElem = currentElem->next; return *this; }
		bool operator==(const Iter& other) const { return currentElem == other.currentElem; }
		bool operator!=(const Iter& other) const { return currentElem != other.currentElem; }
		Type& operator*() { return currentElem->data; }
	};

	Iter begin() const { return Iter(firstElement); }
	Iter end() const { return Iter(nullptr); }
};


#endif

