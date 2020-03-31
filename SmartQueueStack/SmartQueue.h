#pragma once
#include <cmath>
#include <queue>
#include <limits>

namespace SmartQueueStack
{
	template<typename T>
	class SmartQueue
	{
	public:
		SmartQueue();
		~SmartQueue();
		void Enqueue(const T& number);
		T Peek() const;
		T Dequeue();
		T Max() const;
		T Min() const;
		double Average() const;
		T Sum() const;
		double Variance() const;
		double StandardDeviation() const;
		unsigned int Count() const;

	private:
		std::queue<T> mNumericQueue;
		T mSum;
		double mSquareSum;
	};
	template<typename T>
	inline SmartQueue<T>::SmartQueue()
		: mSum(0)
		, mSquareSum(0.0)
	{
	}
	template<typename T>
	inline SmartQueue<T>::~SmartQueue()
	{
	}
	template<typename T>
	inline void SmartQueue<T>::Enqueue(const T& number)
	{
		mSum += number;
		mSquareSum += pow(number, 2.0);
		mNumericQueue.push(number);
	}
	template<typename T>
	inline T SmartQueue<T>::Peek() const
	{
		return mNumericQueue.front();
	}
	template<typename T>
	inline T SmartQueue<T>::Dequeue()
	{
		T result = mNumericQueue.front();
		mNumericQueue.pop();
		mSum -= result;
		mSquareSum -= pow(result, 2.0);
		return result;
	}
	template<typename T>
	inline T SmartQueue<T>::Max() const
	{
		std::queue<T> tempQueue = mNumericQueue;
		T max = std::numeric_limits<T>::lowest();
		while (!tempQueue.empty())
		{
			if (tempQueue.front() > max)
			{
				max = tempQueue.front();
			}
			tempQueue.pop();
		}
		return max;
	}
	template<typename T>
	inline T SmartQueue<T>::Min() const
	{
		std::queue<T> tempQueue = mNumericQueue;
		T min = std::numeric_limits<T>::max();
		while (!tempQueue.empty())
		{
			if (tempQueue.front() < min)
			{
				min = tempQueue.front();
			}
			tempQueue.pop();
		}
		return min;
	}
	template<typename T>
	inline double SmartQueue<T>::Average() const
	{
		double result = static_cast<double>(mSum) / static_cast<double>(mNumericQueue.size());
		return round(result * 1000) / 1000;
	}
	template<typename T>
	inline T SmartQueue<T>::Sum() const
	{
		return mSum;
	}
	template<typename T>
	inline double SmartQueue<T>::Variance() const
	{
		double average = static_cast<double>(mSum) / mNumericQueue.size();
		double result = abs(mSquareSum / static_cast<double>(mNumericQueue.size()) - pow(average, 2.0));
		return round(result * 1000) / 1000;
	}
	template<typename T>
	inline double SmartQueue<T>::StandardDeviation() const
	{
		double average = static_cast<double>(mSum) / mNumericQueue.size();
		double variance = abs(mSquareSum / static_cast<double>(mNumericQueue.size()) - pow(average, 2.0));
		double result = sqrt(variance);
		return round(result * 1000) / 1000;
	}
	template<typename T>
	inline unsigned int SmartQueue<T>::Count() const
	{
		return mNumericQueue.size();
	}
}