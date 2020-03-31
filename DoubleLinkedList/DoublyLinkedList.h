#pragma once

#include <memory>

namespace lab10
{
	template<typename T>
	class Node;

	template<typename T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList();
		void Insert(std::unique_ptr<T> data);
		void Insert(std::unique_ptr<T> data, unsigned int index);
		bool Delete(const T& data);
		bool Search(const T& data) const;

		std::shared_ptr<Node<T>> operator[](unsigned int index) const;
		unsigned int GetLength() const;
	private:
		unsigned int mLength;
		std::shared_ptr<Node<T>> mHead;
	};

	template<typename T> DoublyLinkedList<T>::DoublyLinkedList()
		: mLength(0)
		, mHead(nullptr)
	{
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		if (mLength == 0)
		{
			mHead = std::make_shared<Node<T>>(std::move(data));
			++mLength;
			return;
		}
		std::shared_ptr<Node<T>> currentPtr = mHead;
		for (unsigned int i = 1; i < mLength; ++i)
		{
			currentPtr = currentPtr->Next;
		}
		currentPtr->Next = std::make_shared<Node<T>>(std::move(data), currentPtr);
		++mLength;
		return;
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		if (index >= mLength)
		{
			Insert(std::move(data));
			return;
		}
		std::shared_ptr<Node<T>> currentPtr = mHead;
		if (index == 0)
		{
			mHead = std::make_shared<Node<T>>(std::move(data));
			mHead->Next = currentPtr;
			mHead->Next->Previous = mHead;
			++mLength;
			return;
		}
		for (unsigned int i = 1; i < index; ++i)
		{
			currentPtr = currentPtr->Next;
		}
		std::shared_ptr<Node<T>> currentNextPtr = currentPtr->Next;
		currentPtr->Next = std::make_shared<Node<T>>(std::move(data), currentPtr);
		currentPtr = currentPtr->Next;
		currentPtr->Next = currentNextPtr;
		currentPtr->Next->Previous = currentPtr;
		++mLength;
		return;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Delete(const T& data)
	{
		if (mLength == 0)
		{
			return false;
		}
		if (mLength == 1)
		{
			if (*mHead->Data == data)
			{
				mHead = nullptr;
				--mLength;
				return true;
			}
			else
			{
				return false;
			}
		}
		if (*mHead->Data == data)
		{
			mHead = mHead->Next;
			--mLength;
			return true;
		}
		std::shared_ptr<Node<T>> currentPtr = mHead;
		for (unsigned int i = 1; i < mLength; ++i)
		{
			if (*currentPtr->Next->Data == data)
			{
				currentPtr->Next = currentPtr->Next->Next;
				if (i < mLength - 1)
				{
					currentPtr->Next->Previous = currentPtr;
				}
				--mLength;
				return true;
			}
			else
			{
				currentPtr = currentPtr->Next;
			}
		}
		return false;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Search(const T& data) const
	{
		std::shared_ptr<Node<T>> currentPtr = mHead;
		for (unsigned int i = 0; i < mLength; ++i)
		{
			if (*currentPtr->Data == data)
			{
				return true;
			}
			else
			{
				currentPtr = currentPtr->Next;
			}
		}
		return false;
	}

	template<typename T>
	std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
	{
		if (index >= mLength)
		{
			return nullptr;
		}
		std::shared_ptr<Node<T>> currentPtr = mHead;
		for (unsigned int i = 0; i < index; ++i)
		{
			currentPtr = currentPtr->Next;
		}
		return currentPtr;
	}

	template<typename T>
	unsigned int DoublyLinkedList<T>::GetLength() const
	{
		return mLength;
	}
}