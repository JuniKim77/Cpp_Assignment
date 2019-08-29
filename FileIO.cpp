#include "FileIO.h"

namespace FileIO
{
	void GenerateLine(std::ostream& out, int number)
	{
		out << std::setfill(' ') << std::setw(12) << std::oct << std::uppercase << number << " ";
		out << std::setw(10) << std::dec << number << " ";
		out << std::setw(8) << std::hex << number << "\n";
	}

	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		std::list<int> nInputList;
		int number;
		std::string trash;
		while (!in.eof())
		{
			in >> number;
			if (in.fail())
			{
				in.clear();
				in >> trash;
			}
			else
			{
				nInputList.push_back(number);
			}
		}
		out << std::setfill(' ') << std::setw(13) << "oct ";
		out << std::setw(11) << "dec ";
		out << std::setw(9) << "hex\n";
		out << std::setfill('-') << std::setw(13) << ' ';
		out << std::setw(11) << ' ';
		out << std::setw(9) << '\n';
		for (auto num : nInputList)
		{
			GenerateLine(out, num);
		}
	}

	void GenerateLine(std::ostream& out, float number, std::string str)
	{
		out << std::setfill(' ') << std::setw(5) << std::left << str;
		out << std::setw(15) << std::showpos << std::internal;
		out << std::fixed << std::setprecision(3) << number << "\n";
	}

	void PrintMaxFloat(std::istream& in, std::ostream& out)
	{
		std::list<float> nInputList;
		float number;
		std::string trash;
		while (!in.eof())
		{
			in >> number;
			if (in.fail())
			{
				in.clear();
				in >> trash;
			}
			else
			{
				nInputList.push_back(number);
			}
		}
		float max = nInputList.front();
		for (auto num : nInputList)
		{
			if (num > max)
				max = num;
			GenerateLine(out, num, "");
		}
		GenerateLine(out, max, "max:");
	}
}