#include "singlelist.h"

template<typename Type>
SinglyList<Type>::SinglyList() : elementCount(0), firstElement(nullptr), lastElement(nullptr) {}

template<typename Type>
SinglyList<Type>::SinglyList(const SinglyList& source) : elementCount(0), firstElement(nullptr), lastElement(nullptr) 
{
	for (Element* node = source.firstElement; node; node = node->next)
		addToEnd(node->data);
}

template<typename Type>
SinglyList<Type>::SinglyList(SinglyList&& source) noexcept
	: firstElement(source.firstElement), lastElement(source.lastElement), elementCount(source.elementCount) 
{
	source.firstElement = source.lastElement = nullptr;
	source.elementCount = 0;
}

template<typename Type>
SinglyList<Type>::~SinglyList() 
{ 
	reset(); 
}

template<typename Type>
typename SinglyList<Type>::Element* SinglyList<Type>::fetchElement(size_t index) const {
	if (index >= elementCount) 
		throw std::out_of_range("Index out of range");
	Element* temp = firstElement;
	for (size_t i = 0; i < index; ++i)
		temp = temp->next;
	return temp;
}

template<typename Type>
size_t SinglyList<Type>::length() const noexcept 
{
	return elementCount; 
}

template<typename Type>
bool SinglyList<Type>::empty() const noexcept 
{ 
	return elementCount == 0; 
}

template<typename Type>
void SinglyList<Type>::addToEnd(const Type& data) 
{
	Element* newNode = new Element{ data };
	if (lastElement)
		lastElement->next = newNode;
	else
		firstElement = newNode;
	lastElement = newNode;
	++elementCount;
}

template<typename Type>
void SinglyList<Type>::addToStart(const Type& data) {
	Element* newNode = new Element{ data, firstElement };
	firstElement = newNode;
	if (!lastElement)
		lastElement = newNode;
	++elementCount;
}

template<typename Type>
void SinglyList<Type>::eraseAt(size_t index) 
{
	if (index >= elementCount) 
		throw std::out_of_range("Index out of range");
	Element* toRemove = nullptr;
	if (index == 0) 
	{
		toRemove = firstElement;
		firstElement = firstElement->next;
		if (!firstElement) lastElement = nullptr;
	}
	else 
	{
		Element* prev = fetchElement(index - 1);
		toRemove = prev->next;
		prev->next = toRemove->next;
		if (index == elementCount - 1) 
			lastElement = prev;
	}
	delete toRemove;
	--elementCount;
}

template<typename Type>
void SinglyList<Type>::reset() 
{
	while (firstElement) 
	{
		Element* temp = firstElement;
		firstElement = firstElement->next;
		delete temp;
	}
	lastElement = nullptr;
	elementCount = 0;
}

template<typename Type>
Type& SinglyList<Type>::getItem(size_t index) 
{ 
	return fetchElement(index)->data; 
}

template<typename Type>
const Type& SinglyList<Type>::getItem(size_t index) const 
{ 
	return fetchElement(index)->data; 
}

template<typename Type>
bool SinglyList<Type>::operator==(const SinglyList& source) const noexcept 
{
	if (elementCount != source.elementCount) 
		return false;
	Element* current1 = firstElement;
	Element* current2 = source.firstElement;
	while (current1) 
	{
		if (current1->data != current2->data) 
			return false;
		current1 = current1->next;
		current2 = current2->next;
	}
	return true;
}

template<typename Type>
bool SinglyList<Type>::operator!=(const SinglyList& source) const noexcept 
{ 
	return !(*this == source); 
}

template<typename Type>
SinglyList<Type>& SinglyList<Type>::operator=(const SinglyList& source) 
{
	if (this == &source) 
		return *this;
	reset();
	for (Element* node = source.firstElement; node; node = node->next)
		addToEnd(node->data);
	return *this;
}

template<typename Type>
SinglyList<Type>& SinglyList<Type>::operator=(List&& source) noexcept 
{
	if (this == &source) 
		return *this;
	reset();
	firstElement = source.firstElement;
	lastElement = source.lastElement;
	elementCount = source.elementCount;
	source.firstElement = source.lastElement = nullptr;
	source.elementCount = 0;
	return *this;
}
