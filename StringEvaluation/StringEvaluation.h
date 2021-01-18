// By Kacper "Nyjako" Tucholski 2021

#pragma once

#include <string>
#include <math.h>

namespace KT
{
	class StringEvaluation
	{
	private:
		static std::string clearWhitespaces(std::string stringToClear) // As name said: "1 + 1" -> "1+1"
		{
			std::string output = "";
			for (char c : stringToClear)
				if (c != ' ')
					output += c;
			return output;
		}

		static std::string getPart(std::string base, int startS, int endS) // Get part of string 
		{
			std::string out = "";
			for (int i = startS; i <= endS; i++)
				out += base[i];
			return out;
		}

		static bool isNumber(char c) // Check if c is number
		{
			return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '.' || c == 'N';
		}

		static std::string replacePart(std::string base, int delFirstIndex, int delLastIndex, std::string replaceString) // Replace part of string with other string
		{
			std::string s = "";
			for (int i = 0; i < delFirstIndex; i++)
				s += base[i];
			s += replaceString;
			for (int i = delLastIndex + 1; i < base.size(); i++)
				s += base[i];
			return s;
		}

		static std::string removeF(std::string s) // Remove first character from string
		{
			std::string out = "";
			for (int i = 1; i < s.size(); i++)
				out += s[i];
			return out;
		}

		static double* getExp(std::string tempExpression, int i, int& startPoint, int& endPoint) // Get numbers from string: "10+N1" -> [10,-1]
		{
			double* temp = new double[2];

			for (int j = i - 1; j >= 0; j--)
				if (!isNumber(tempExpression[j]) || j == 0)
				{
					startPoint = (j == 0) ? j : j + 1;
					std::string tempS = getPart(tempExpression, startPoint, i - 1);
					if (tempS[0] == 'N') tempS[0] = '-';
					temp[0] = std::stof(tempS);
					break;
				}
			for (int j = i + 1; j < tempExpression.size(); j++)
				if (!isNumber(tempExpression[j]) || j == tempExpression.size() - 1)
				{
					endPoint = (j == tempExpression.size() - 1) ? j : j - 1;
					std::string tempS = getPart(tempExpression, i + 1, endPoint);
					if (tempS[0] == 'N') tempS[0] = '-';
					temp[1] = std::stof(tempS);
					break;
				}

			return temp;
		}

		static std::string cutZeros(std::string base) // Removes unnecessary zeros: 1.010000 -> 1.01
		{
			for (int i = base.size() - 1; i >= 0; i--)
				if (base[i] != '0' || base[i] != '.')
					if (i == base.size() - 1)
						return base;
					else
						return getPart(base, 0, i);
			return base;
		}

	public:
		static double resolveMath(std::string expresion)
		{
			std::string tempExpression = clearWhitespaces(expresion);
			int counter = 0;
			std::string s = "";
			bool started = false;
			int startPoint, endPoint;
			for (int i = 0; i < tempExpression.size(); i++) // Brackets
			{
				char c = tempExpression[i];
				if (c == '(')
				{
					counter++;
					if (!started)
					{
						started = true;
						startPoint = i;
					}
				}
				else if (c == ')')
				{
					counter--;
					if (started && counter == 0 && s != "")
					{
						tempExpression = replacePart(tempExpression, startPoint, i, std::to_string(resolveMath(removeF(s))));
						started = false;
						i = 0;
						s = "";
					}
				}
				if (started) s += c;
			}

			for (int i = 0; i < tempExpression.size(); i++) // pow / sqrt
				if (tempExpression[i] == 'P' || tempExpression[i] == 'S')
				{
					double* temp = getExp(tempExpression, i, startPoint, endPoint);
					tempExpression = replacePart(tempExpression, startPoint, endPoint, std::to_string((tempExpression[i] == 'P') ? pow(temp[0], temp[1]) : pow(temp[1], 1 / temp[0])));
					i = 0;
				}
			for (int i = 0; i < tempExpression.size(); i++) // Multiplication / Division
				if (tempExpression[i] == '*' || tempExpression[i] == '/')
				{
					double* temp = getExp(tempExpression, i, startPoint, endPoint);
					tempExpression = replacePart(tempExpression, startPoint, endPoint, std::to_string((tempExpression[i] == '*') ? temp[0] * temp[1] : temp[0] / temp[1]));
					i = 0;
				}
			for (int i = 0; i < tempExpression.size(); i++) // Addition / Subtraction
				if (tempExpression[i] == '+' || tempExpression[i] == '-')
				{
					double* temp = getExp(tempExpression, i, startPoint, endPoint);
					tempExpression = replacePart(tempExpression, startPoint, endPoint, std::to_string((tempExpression[i] == '+') ? temp[0] + temp[1] : temp[0] - temp[1]));
					i = 0;
				}

			return std::stod(cutZeros(tempExpression));
		}
	};
}