#pragma once
#include <limits>
#include <stack>
#include <queue>
#include "SmartStack.h"
#include <cmath>

namespace SmartQueueStack
{
	template<typename T>
	class QueueStack
	{
	public:
		QueueStack(const unsigned int maxStackSize);
		~QueueStack();
		void Enqueue(const T& number);
		T Peek() const;
		T Dequeue();
		T Max() const;
		T Min() const;
		double Average() const;
		T Sum() const;
		unsigned int Count() const;
		unsigned int StackCount() const;

	private:
		unsigned int mCount;
		unsigned int mMaxStackSize;
		std::queue<SmartStack<T>> mNumericQueue;
		T mSum;
	};
	template<typename T>
	inline QueueStack<T>::QueueStack(const unsigned int maxStackSize)
		: mCount(0)
		, mMaxStackSize(maxStackSize)
		, mSum(0)
	{
		SmartStack<T> emptyStack;
		mNumericQueue.push(emptyStack);
	}
	template<typename T>
	inline QueueStack<T>::~QueueStack()
	{
	}
	template<typename T>
	inline void QueueStack<T>::Enqueue(const T& number)
	{
		if (mNumericQueue.back().Count() < mMaxStackSize)
		{
			mNumericQueue.back().Push(number);
		}
		else
		{
			SmartStack<T> emptyStack;
			mNumericQueue.push(emptyStack);
			mNumericQueue.back().Push(number);
		}
		++mCount;
		mSum += number;
	}
	template<typename T>
	inline T QueueStack<T>::Peek() const
	{
		return mNumericQueue.front().Peek();
	}
	template<typename T>
	inline T QueueStack<T>::Dequeue()
	{
		T result = mNumericQueue.front().Peek();
		if (mNumericQueue.front().Count() == 1 && mNumericQueue.size() > 1)
		{
			mNumericQueue.pop();
		}
		else
		{
			mNumericQueue.front().Pop();
		}
		--mCount;
		mSum -= result;

		return result;
	}
	template<typename T>
	inline T QueueStack<T>::Sum() const
	{
		return mSum;
	}
	template<typename T>
	inline unsigned int QueueStack<T>::Count() const
	{
		return mCount;
	}
	template<typename T>
	inline unsigned int QueueStack<T>::StackCount() const
	{
		if (mCount == 0)
		{
			return 0;
		}
		return mNumericQueue.size();
	}
	template<typename T>
	inline T QueueStack<T>::Max() const
	{
		std::queue<SmartStack<T>> tempQueue = mNumericQueue;
		T max = std::numeric_limits<T>::lowest();
		while (!tempQueue.empty())
		{
			if (tempQueue.front().Max() > max)
			{
				max = tempQueue.front().Max();
			}
			tempQueue.pop();
		}
		return max;
	}
	template<typename T>
	inline T QueueStack<T>::Min() const
	{
		std::queue<SmartStack<T>> tempQueue = mNumericQueue;
		T min = std::numeric_limits<T>::max();
		while (!tempQueue.empty())
		{
			if (tempQueue.front().Min() < min)
			{
				min = tempQueue.front().Min();
			}
			tempQueue.pop();
		}
		return min;
	}
	template<typename T>
	inline double QueueStack<T>::Average() const
	{
		double result = static_cast<double>(mSum) / static_cast<double>(mCount);
		return round(result * 1000) / 1000;
	}
}