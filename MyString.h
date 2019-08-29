#pragma once
namespace MyString
{
	class MyString
	{
	public:
		MyString(const char* s);
		MyString(const MyString& other);
		~MyString();

		unsigned int GetLength() const;
		const char* GetCString() const;
		void Append(const char* s);
		MyString operator+(const MyString& other) const;
		int IndexOf(const char* s);
		int LastIndexOf(const char* s);
		void Interleave(const char* s);
		bool RemoveAt(unsigned int i);
		void PadLeft(unsigned int totalLength);
		void PadLeft(unsigned int totalLength, const char c);
		void PadRight(unsigned int totalLength);
		void PadRight(unsigned int totalLength, const char c);
		void Reverse();
		bool operator==(const MyString& rhs) const;
		void ToLower();
		void ToUpper();

	protected:
		int countStringLength(const char* obj);
		void copyString(char* result, const char* obj);
		bool findString(const char* str1, const char* str2);
		void setCapacity(const unsigned int newLength);

	private:
		char* mPtrString;
		unsigned int mNumLength;
		unsigned int mNumCapacity;
	};
}