#pragma once

namespace CustomizedVector
{
	template<size_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector();
		~FixedVector();
		bool Add(const bool data);
		bool Remove(const bool data);
		bool Get(const unsigned int num) const;
		bool operator[](const unsigned int index);
		int32_t GetIndex(const bool value) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		enum
		{
			BIT = 32
		};
		size_t mSize;
		int32_t mArray[((N % BIT) == 0) ? (N / BIT) : ((N / BIT) + 1)];
	};

	template<size_t N>
	inline FixedVector<bool, N>::FixedVector()
		: mSize(0)
	{
		unsigned int ArraySize = ((N % BIT) == 0) ? (N / BIT) : ((N / BIT) + 1);
		for (unsigned int i = 0; i < ArraySize; ++i)
		{
			mArray[i] = 0;
		}
	}
	template<size_t N>
	inline FixedVector<bool, N>::~FixedVector()
	{

	}
	template<size_t N>
	inline bool FixedVector<bool, N>::Add(const bool data)
	{
		if (mSize >= N)
		{
			return false;
		}
		int arrayIndex = mSize / BIT;
		int index = mSize % BIT;
		if (data)
		{
			mArray[arrayIndex] |= (1 << index);
		}
		else
		{
			mArray[arrayIndex] &= ~(1 << index);
		}
		++mSize;
		return true;
	}
	template<size_t N>
	inline bool FixedVector<bool, N>::Remove(const bool data)
	{
		unsigned int temp, arrayIndex, index, firstBit;
		unsigned int currentSize;
		if (mSize == 0)
		{
			return false;
		}

		if (GetIndex(data) == -1)
		{
			return false;
		}

		temp = GetIndex(data);
		arrayIndex = temp / BIT;
		index = temp % BIT;
		currentSize = ((mSize % BIT) == 0) ? (mSize / BIT) : ((mSize / BIT) + 1);
		if (data)
		{
			mArray[arrayIndex] = mArray[arrayIndex] >> 1;
			if (temp > 0)
			{
				mArray[arrayIndex] &= ~(1 << (index - 1));
			}
			if ((currentSize - 1) > arrayIndex)
			{
				firstBit = mArray[arrayIndex + 1] & 1;
				if (firstBit == 1)
				{
					mArray[arrayIndex] |= (1 << (BIT - 1));
				}
				else
				{
					mArray[arrayIndex] &= ~(1 << (BIT - 1));
				}
			}
		}
		else
		{
			mArray[arrayIndex] = mArray[arrayIndex] >> 1;
			if (temp > 0)
			{
				mArray[arrayIndex] |= (1 << (index - 1));
			}
			if ((currentSize - 1) > arrayIndex)
			{
				firstBit = mArray[arrayIndex + 1] & 1;
				if (firstBit == 1)
				{
					mArray[arrayIndex] |= (1 << (BIT - 1));
				}
				else
				{
					mArray[arrayIndex] &= ~(1 << (BIT - 1));
				}
			}
		}
		
		for (unsigned int j = arrayIndex + 1; j < currentSize; ++j)
		{
			mArray[j] = mArray[j] >> 1;;
			if ((currentSize - 1) > j)
			{
				firstBit = mArray[j + 1] & 1;
				if (firstBit == 1)
				{
					mArray[j] |= (1 << (BIT - 1));
				}
				else
				{
					mArray[arrayIndex] &= ~(1 << (BIT - 1));
				}
			}
		}
		--mSize;
		return true;
	}
	template<size_t N>
	inline bool FixedVector<bool, N>::Get(const unsigned int num) const
	{
		int arrayIndex = num / BIT;
		int index = num % BIT;
		int temp = mArray[arrayIndex] & (1 << index);
		if (temp != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	template<size_t N>
	inline bool FixedVector<bool, N>::operator[](const unsigned int num)
	{
		int arrayIndex = num / BIT;
		int index = num % BIT;
		int temp = mArray[arrayIndex] & (1 << num);
		if (temp != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	template<size_t N>
	inline int32_t FixedVector<bool, N>::GetIndex(const bool value) const
	{
		int temp, arrayIndex, index;
		if (value)
		{
			for (unsigned int i = 0; i < mSize; ++i)
			{
				arrayIndex = i / BIT;
				index = i % BIT;
				temp = mArray[arrayIndex] & (1 << index);
				if (temp != 0) // finding true bit
				{
					return i;
				}
			}
			return -1;
		}
		else
		{
			for (unsigned int i = 0; i < mSize; ++i)
			{
				arrayIndex = i / BIT;
				index = i % BIT;
				temp = mArray[arrayIndex] & (1 << index);
				if (temp == 0) // finding false bit
				{
					return i;
				}
			}
			return -1;
		}
	}
	template<size_t N>
	size_t FixedVector<bool, N>::GetSize() const
	{
		return mSize;
	}
	template<size_t N>
	size_t FixedVector<bool, N>::GetCapacity() const
	{
		return N;
	}
}