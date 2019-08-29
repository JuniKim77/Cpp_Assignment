#include "MyString.h"

namespace MyString
{
	MyString::MyString(const char* s)
		: mPtrString(nullptr)
		, mNumLength(0)
		, mNumCapacity(8)
	{
		mNumLength = countStringLength(s);
		setCapacity(mNumLength + 1);
		mPtrString = new char[mNumCapacity];
		copyString(mPtrString, s);
	}

	MyString::MyString(const MyString& other)
		: mPtrString(nullptr)
		, mNumLength(0)
		, mNumCapacity(8)
	{
		mNumLength = other.GetLength();
		setCapacity(mNumLength + 1);
		mPtrString = new char[mNumCapacity];
		copyString(mPtrString, other.GetCString());
	}

	MyString::~MyString()
	{
		delete[] mPtrString;
	}

	unsigned int MyString::GetLength() const
	{
		return mNumLength;
	}

	const char* MyString::GetCString() const
	{
		return mPtrString;
	}

	void MyString::Append(const char* s)
	{
		unsigned int nNewLength = countStringLength(s) + mNumLength;
		if (nNewLength >= mNumCapacity)
		{
			setCapacity(nNewLength + 1);
			char* temp = mPtrString;
			mPtrString = new char[mNumCapacity];
			copyString(mPtrString, temp);
			delete[] temp;
		}
		copyString(mPtrString + mNumLength, s);
		mNumLength = nNewLength;
	}

	MyString MyString::operator+(const MyString& other) const
	{
		MyString result(this->GetCString());
		result.Append(other.GetCString());
		return result;
	}

	int MyString::IndexOf(const char* s)
	{
		if (*s == '\0')
		{
			return 0;
		}
		const char* ptr = mPtrString;
		unsigned int i = 0;
		while ((i < mNumLength) && !findString(ptr, s))
		{
			++ptr;
			++i;
		}
		if (i == mNumLength)
		{
			return -1;
		}
		return i;
	}

	int MyString::LastIndexOf(const char* s)
	{
		if (*s == '\0')
		{
			return mNumLength;
		}
		const char* ptr = mPtrString;
		int i = mNumLength - 1;
		ptr += i;
		while ((i >= 0) && !findString(ptr, s))
		{
			--ptr;
			--i;
		}
		return i;
	}

	void MyString::Interleave(const char* s)
	{
		unsigned int nNewLength = countStringLength(s);
		bool bIsLeftBigger;
		unsigned int difference;
		if (mNumLength >= nNewLength)
		{
			bIsLeftBigger = true;
			difference = mNumLength - nNewLength;
		}
		else
		{
			bIsLeftBigger = false;
			difference = nNewLength - mNumLength;
		}
		unsigned int sum = mNumLength + nNewLength;
		if (sum >= mNumCapacity)
		{
			setCapacity(sum + 1);
			char* tempOrigin = mPtrString;
			mPtrString = new char[mNumCapacity];
			copyString(mPtrString, tempOrigin);
			delete[] tempOrigin;
		}
		char* temp = mPtrString + sum;
		char* ptrLeft = mPtrString + mNumLength - 1;
		const char* ptrRight = s + nNewLength - 1;
		mNumLength = sum;
		*temp-- = '\0';
		if (bIsLeftBigger)
		{
			for (unsigned int i = 0; i < difference; ++i)
				*temp-- = *ptrLeft--;
		}
		else
		{
			for (unsigned int i = 0; i < difference; ++i)
				*temp-- = *ptrRight--;
		}
		for (unsigned int i = mNumLength - difference; i > 0; --i)
		{
			if (i % 2 == 0)
				*temp-- = *ptrRight--;
			else
				*temp-- = *ptrLeft--;
		}
	}

	bool MyString::RemoveAt(unsigned int index)
	{
		if (index >= mNumLength)
		{
			return false;
		}
		copyString(mPtrString + index, mPtrString + index + 1);
		--mNumLength;
		return true;
	}

	void MyString::PadLeft(unsigned int totalLength)
	{
		PadLeft(totalLength, ' ');
	}

	void MyString::PadLeft(unsigned int totalLength, const char c)
	{
		if (totalLength <= mNumLength)
		{
			return;
		}
		if (totalLength >= mNumCapacity)
		{
			setCapacity(totalLength + 1);
		}
		const char* origin = mPtrString;
		mPtrString = new char[mNumCapacity];
		int padLength = totalLength - mNumLength;
		for (int i = 0; i < padLength; ++i)
		{
			*(mPtrString + i) = c;
		}
		copyString(mPtrString + padLength, origin);
		mNumLength = totalLength;
		delete[] origin;
	}

	void MyString::PadRight(unsigned int totalLength)
	{
		PadRight(totalLength, ' ');
	}

	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		if (totalLength <= mNumLength)
		{
			return;
		}
		if (totalLength >= mNumCapacity)
		{
			setCapacity(totalLength + 1);
		}
		const char* const ORIGIN = mPtrString;
		mPtrString = new char[mNumCapacity];
		int padLength = totalLength - mNumLength;
		copyString(mPtrString, ORIGIN);
		for (unsigned int i = totalLength - 1; i > mNumLength - 1; --i)
		{
			*(mPtrString + i) = c;
		}
		*(mPtrString + totalLength) = '\0';
		mNumLength = totalLength;
		delete[] ORIGIN;
	}

	void MyString::Reverse()
	{
		char* leftPtr = mPtrString;
		char* rightPtr = mPtrString + (mNumLength - 1);
		char temp;
		while (leftPtr < rightPtr)
		{
			temp = *leftPtr;
			*leftPtr = *rightPtr;
			*rightPtr = temp;
			++leftPtr;
			--rightPtr;
		}
	}

	bool MyString::operator==(const MyString& rhs) const
	{
		if (mNumLength != rhs.GetLength())
		{
			return false;
		}
		const char* leftPtr = mPtrString;
		const char* rightPtr = rhs.GetCString();
		while (*leftPtr != '\0')
		{
			if (*leftPtr++ != *rightPtr++)
			{
				return false;
			}
		}
		return true;
	}

	void MyString::ToLower()
	{
		char* tempPtr = mPtrString;
		while (*tempPtr != '\0')
		{
			if (*tempPtr >= 65 && *tempPtr <= 90)
			{
				*tempPtr += 32;
			}
			++tempPtr;
		}
	}

	void MyString::ToUpper()
	{
		char* tempPtr = mPtrString;
		while (*tempPtr != '\0')
		{
			if (*tempPtr >= 97 && *tempPtr <= 122)
			{
				*tempPtr -= 32;
			}
			++tempPtr;
		}
	}
	int MyString::countStringLength(const char* obj)
	{
		const char* ptr = obj;
		int count = 0;
		while (*ptr != '\0')
		{
			++count;
			++ptr;
		}
		return count;
	}
	void MyString::copyString(char* result, const char* obj)
	{
		const char* ptr = obj;
		char* ptrResult = result;
		while (*ptr != '\0')
		{
			*ptrResult = *ptr;
			ptr++;
			ptrResult++;
		}
		*ptrResult = '\0';
	}
	bool MyString::findString(const char* str1, const char* str2)
	{
		if (countStringLength(str1) < countStringLength(str2))
		{
			return false;
		}
		const char* ptr1 = str1;
		const char* ptr2 = str2;
		while (*ptr2 != '\0')
		{
			if (*ptr1 == *ptr2)
			{
				++ptr1;
				++ptr2;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	void MyString::setCapacity(const unsigned int newLength)
	{
		while (newLength > mNumCapacity)
		{
			mNumCapacity *= 2;
		}
	}
}