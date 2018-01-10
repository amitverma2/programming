#include <iostream>

using namespace std;

/*

Given an input string and a dictionary of words, find out if the input string can be segmented into a space - separated sequence of dictionary words.See following examples for more details.
This is a famous Google interview question, also being asked by many other companies now a days.

Consider the following dictionary
{ i, like, sam, sung, samsung, mobile, ice,
cream, icecream, man, go, mango }

Input:  ilike
Output : Yes
The string can be segmented as "i like".

Input : ilikesamsung
Output : Yes
The string can be segmented as "i like samsung" or "i like sam sung".



*/

#include <iostream>

using namespace std;

int length(char* str)
{
	int len = 0;
	while (*str++)
		len++;

	return len;
}

void strncpy(char* src, char* dest, int beg, int n)
{
	for (int i = 0; i < n; i++)
		dest[i] = src[i + beg];
	dest[n] = '\0';
}


int strcmp(char* str1, char* str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
			return 0;
		str1++; str2++;
	}
	return *str1 - *str2;
}

/* A utility function to check whether a word is present in dictionary or not.
An array of strings is used for dictionary.  Using array of strings for
dictionary is definitely not a good idea. We have used for simplicity of
the program*/
int dictionaryContains(char* str, int beg, int width)
{
	char* dictionary[] = { "mobile", "samsung", "sam", "sung", "man", "mango",
		"icecream", "and", "go", "i", "like", "ice", "cream" };

	char* temp;

	temp = new char[width + 1];
	strncpy(str, temp, beg, width);


	int size = sizeof(dictionary) / sizeof(dictionary[0]);

	for (int i = 0; i < size; i++)
	{
		if (strcmp(dictionary[i], temp) == 0)
			return true;
	}
	return false;
}

// Returns true if string can be segmented into space separated
// words, otherwise returns false
bool wordBreak(char* str)
{
	int len = length(str);
	if (len == 0)   return true;

	// Create the DP table to store results of subroblems. The value wb[i]
	// will be true if str[0..i-1] can be segmented into dictionary words,
	// otherwise false.

	bool* wb;
	wb = new bool[len + 1];

	for (int i = 0; i <= len; i++)
		wb[i] = false;  // Initialize all values as false.

	for (int i = 1; i <= len; i++)
	{
		// if wb[i] is false, then check if current prefix can make it true.
		// Current prefix is "str.substr(0, i)"
		if (wb[i] == false && dictionaryContains(str, 0, i))
			wb[i] = true;

		// wb[i] is true, then check for all substrings starting from
		// (i+1)th character and store their results.
		if (wb[i] == true)
		{
			// If we reached the last prefix
			if (i == len)
			{
				delete[] wb;
				return true;
			}

			for (int j = i + 1; j <= len; j++)
			{
				// Update wb[j] if it is false and can be updated
				// Note the parameter passed to dictionaryContains() is
				// substring starting from index 'i' and length 'j-i'
				if (wb[j] == false && dictionaryContains(str, i, j - i))
					wb[j] = true;

				// If we reached the last character
				if (j == len && wb[j] == true)
				{
					delete[] wb;
					return true;
				}
			}
		}
	}

	//print all values of wb to get an understanding, if this string is not fitting in dicionary
	for (int i = 1; i <= len; i++)
		cout << "wb[" << i << "]: " << wb[i] << " ";
	cout << endl;

	delete[] wb;

	// If we have tried all prefixes and none of them worked
	return false;
}

// Driver program to test above functions
int main()
{
	wordBreak("ilikesamsung") ? cout << "Yes\n" : cout << "No\n";
	wordBreak("iiiiiiii") ? cout << "Yes\n" : cout << "No\n";
	wordBreak("") ? cout << "Yes\n" : cout << "No\n";
	wordBreak("ilikelikeimangoiii") ? cout << "Yes\n" : cout << "No\n";
	wordBreak("samsungandmango") ? cout << "Yes\n" : cout << "No\n";
	wordBreak("samsungandmangok") ? cout << "Yes\n" : cout << "No\n";
	return 0;
}