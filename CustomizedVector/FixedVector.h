#pragma once

namespace CustomizedVector
{
	template <typename T, size_t N>
	class FixedVector
	{
	public:
		FixedVector();
		~FixedVector();
		bool Add(const T& t);
		bool Remove(const T& t);
		const T& Get(const unsigned int index) const;
		T& operator[](const unsigned int index);
		int GetIndex(const T& value) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		size_t mSize;
		T mArray[N];
	};

	template<typename T, size_t N>
	inline FixedVector<T, N>::FixedVector()
		: mSize(0)
	{
	}

	template<typename T, size_t N>
	inline FixedVector<T, N>::~FixedVector()
	{
	}

	template<typename T, size_t N>
	inline bool FixedVector<T, N>::Add(const T& t)
	{
		if (mSize == N)
		{
			return false;
		}
		mArray[mSize++] = t;
		return true;
	}

	template<typename T, size_t N>
	inline bool FixedVector<T, N>::Remove(const T& t)
	{
		if (mSize == 0)
		{
			return false;
		}

		for (unsigned int i = 0; i < mSize; ++i)
		{
			if (mArray[i] == t)
			{
				for (unsigned int j = i; j < mSize - 1; ++j)
				{
					mArray[j] = mArray[j + 1];
				}
				--mSize;
				return true;
			}
		}
		return false;
	}

	template<typename T, size_t N>
	inline const T& FixedVector<T, N>::Get(const unsigned int index) const
	{
		return mArray[index];
	}

	template<typename T, size_t N>
	inline T& FixedVector<T, N>::operator[](const unsigned int index)
	{
		return mArray[index];
	}

	template<typename T, size_t N>
	inline int FixedVector<T, N>::GetIndex(const T& value) const
	{
		for (unsigned int i = 0; i < mSize; ++i)
		{
			if (mArray[i] == value)
			{
				return static_cast<int>(i);
			}
		}
		return -1;
	}

	template<typename T, size_t N>
	inline size_t FixedVector<T, N>::GetSize() const
	{
		return mSize;
	}

	template<typename T, size_t N>
	inline size_t FixedVector<T, N>::GetCapacity() const
	{
		return N;
	}
}