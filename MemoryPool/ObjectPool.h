#pragma once
#include "IceCube.h"
#include <queue>

namespace lab9
{
	template<typename T>
	class ObjectPool
	{
	public:
		ObjectPool(size_t maxPoolSize);
		~ObjectPool();
		T* Get();
		void Return(T* const object);
		size_t GetFreeObjectCount() const;
		size_t GetMaxFreeObjectCount() const;

	private:
		ObjectPool(ObjectPool<T>& other);
		ObjectPool<T>& operator=(ObjectPool<T>& other);
		size_t mMaxPoolSize;
		std::queue<T*> mPool;
	};
	template<typename T>
	inline ObjectPool<T>::ObjectPool(size_t maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{
	}
	template<typename T>
	inline ObjectPool<T>::~ObjectPool()
	{
		while (!mPool.empty())
		{
			delete mPool.front();
			mPool.pop();
		}
	}
	template<typename T>
	inline T* ObjectPool<T>::Get()
	{
		// TODO: insert return statement here
		if (!mPool.empty())
		{
			T* result = mPool.front();
			mPool.pop();
			return result;
		}

		return new T();
		
	}
	template<typename T>
	inline void ObjectPool<T>::Return(T* const object)
	{
		if (mPool.size() == mMaxPoolSize)
		{
			delete object;
			return;
		}
		mPool.push(object);
		return;
	}
	template<typename T>
	inline size_t ObjectPool<T>::GetFreeObjectCount() const
	{
		return mPool.size();
	}
	template<typename T>
	inline size_t ObjectPool<T>::GetMaxFreeObjectCount() const
	{
		return mMaxPoolSize;
	}
}