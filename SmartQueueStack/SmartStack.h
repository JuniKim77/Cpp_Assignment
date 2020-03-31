#pragma once
#include <limits>
#include <stack>
#include <cmath>

namespace SmartQueueStack
{
	template<typename T>
	class SmartStack
	{
	public:
		SmartStack();
		~SmartStack();
		void Push(const T& number);
		T Pop();
		T Peek() const;
		T Max() const;
		T Min() const;
		double Average() const;
		T Sum() const;
		double Variance() const;
		double StandardDeviation() const;
		unsigned int Count() const;

	private:
		std::stack<T> mNumericStack;
		std::stack<T> mMinStack;
		std::stack<T> mMaxStack;
		T mSum;
		double mSquareSum;
	};

	template<typename T>
	inline SmartStack<T>::SmartStack()
		: mSum(0)
		, mSquareSum(0.0)
	{
		mMinStack.push(std::numeric_limits<T>::max());
		mMaxStack.push(std::numeric_limits<T>::lowest());
	}

	template<typename T>
	inline SmartStack<T>::~SmartStack()
	{
	}

	template<typename T>
	inline void SmartStack<T>::Push(const T& number)
	{
		if (number > mMaxStack.top())
		{
			mMaxStack.push(number);
		}
		else
		{
			mMaxStack.push(mMaxStack.top());
		}
		if (number < mMinStack.top())
		{
			mMinStack.push(number);
		}
		else
		{
			mMinStack.push(mMinStack.top());
		}
		mSum += number;
		mSquareSum += pow(number, 2.0);
		mNumericStack.push(number);
	}

	template<typename T>
	inline T SmartStack<T>::Pop()
	{
		T result = mNumericStack.top();
		mNumericStack.pop();
		mMaxStack.pop();
		mMinStack.pop();
		mSum -= result;
		mSquareSum -= pow(result, 2.0);
		return result;
	}

	template<typename T>
	inline T SmartStack<T>::Peek() const
	{
		return mNumericStack.top();
	}

	template<typename T>
	inline T SmartStack<T>::Max() const
	{
		return mMaxStack.top();
	}

	template<typename T>
	inline T SmartStack<T>::Min() const
	{
		return mMinStack.top();
	}

	template<typename T>
	inline T SmartStack<T>::Sum() const
	{
		return mSum;
	}

	template<typename T>
	inline double SmartStack<T>::Variance() const
	{
		double average = static_cast<double>(mSum) / mNumericStack.size();
		double result = abs(mSquareSum / static_cast<double>(mNumericStack.size()) - pow(average, 2.0));
		return round(result * 1000) / 1000;
	}

	template<typename T>
	inline double SmartStack<T>::StandardDeviation() const
	{
		double average = static_cast<double>(mSum) / mNumericStack.size();
		double variance = abs(mSquareSum / static_cast<double>(mNumericStack.size()) - pow(average, 2.0));
		return round(sqrt(variance) * 1000) / 1000;
	}

	template<typename T>
	inline unsigned int SmartStack<T>::Count() const
	{
		return mNumericStack.size();
	}

	template<typename T>
	inline double SmartStack<T>::Average() const
	{
		double result = static_cast<double>(mSum) / static_cast<double>(mNumericStack.size());
		return round(result * 1000) / 1000;
	}

}