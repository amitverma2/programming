/*

Assume that we have a string in English lower case. We can obtain its substrings by picking two positions and concatenating consecutive characters between them.  

If two positions are the same, we get a substring of length 1. For example, all the substrings of a string love are l, o, v, e, lo, ov, ve, lov, ove, and love.  

Also, all the substrings of another string food are f, o, d, fo, oo, od, foo, ood, and food. Note that we consider duplicated substrings as one.  



Now consider the problem of sorting them in the lexicographical order. We compare two different strings from left to right.

Once we find a difference, the one with the character which appears before in the alphabetical order precedes the other.  

For example, we show the lexicographical sorting of two strings love and food.  



                     


order
 
substrings of love
 
substrings of food
 

1
 
e
 
d
 

2
 
l
 
f
 

3
 
lo
 
fo
 

4
 
lov
 
foo
 

5
 
love
 
food
 

6
 
o
 
o
 

7
 
ov
 
od
 

8
 
ove
 
oo
 

9
 
v
 
ood
 

10
 
ve
 
 
 



Write a program that, given the text and an integer K, prints the substring whose lexicographical rank is K. Check the input/output conditions below thoroughly.



[Input]

﻿T test cases are given continuously as standard input.  

﻿

 

Each test case starts with a line containing one integer K, followed by another line containing a string in English lower case. 



[Output]

For each test case, you should print “#C” in the first line where C is the case number. Then, in the same line after a space there should be the string whose lexicographic order is K.  

If Kth string does not exist, print “none”.  



[Input Output Example]

Input 

 


﻿2 ← Value of T, the number of test cases

7 ← Value of K, Start of Case 1

love 

10 ← Value of K, Start of Case 2

food
 



Output

 


#1 ov

#2 none
 

*/

#include <iostream>

using namespace std;

#define MAX_CHAR 26

#define STR_LEN 99999

class Stack
{
public:
	char arr[STR_LEN];
	int pos;
	void push(char c) { arr[pos++] = c;}
	void pop() { pos-- ;}
	Stack() {pos = 0;}
	~Stack() {pos = 0;}
};


class Trie {
	struct node {
		struct node* edge[MAX_CHAR];
	};

	node* root;

	void insertStringUtil(char* str, node* rt);
	void initializeNode(node* nd);
	int findStringRankUtil(int rank, node* cur, Stack& s);
	void destroy(node* cur);

public:
	Trie();
	~Trie();
	void insertString(char* str);
	void findStringRank(int rank, char* final);
};

Trie::~Trie()
{
	destroy(root);
}

void Trie::destroy(node* cur)
{
	for(int i=0; i<MAX_CHAR;i++)
	{
		if(cur->edge[i] != NULL)
		{
			destroy(cur->edge[i]);
		}
	}
	delete cur;
}

void Trie::initializeNode(node* nd)
{
	for(int i=0; i<MAX_CHAR; i++)
		nd->edge[i] = NULL;
}

Trie::Trie()
{
	root = new node;
	initializeNode(root);
}

void Trie::insertStringUtil(char* str, node* rt) {
	if(str[0] == '\0')
		return;

	int index = str[0] - 'a';
	if(rt->edge[index] == NULL)
	{
		node* temp = new node;
		initializeNode(temp);
		rt->edge[index] = temp;
	}
	insertStringUtil(++str, rt->edge[index]);
}
int glevel = 0;
int Trie::findStringRankUtil(int rank, node* cur, Stack& s)
{
	int result;

	if (rank == 0)
		return -1;

	if(cur == NULL)
		return -1;

	if(glevel == rank)
		return 1;

	for(int i=0; i<MAX_CHAR;i++)
	{
		if(cur->edge[i] != NULL)
		{
			s.push('a'+i);
			glevel++;
			result = findStringRankUtil(rank, cur->edge[i], s);
			if( result == 1)
				return result;
			s.pop();
		}
	}
	return -1;
}

void strcpy(char* src, char* dst, int length)
{
	while(length--)
		*dst++ = *src++;
	*dst = '\0';
}

void Trie::findStringRank(int rank, char* final)
{
	Stack s;
	int result;
	glevel = 0;
    result = findStringRankUtil(rank, root, s);
	if (result == -1)
		strcpy("none", final, 4);
	else
		strcpy(s.arr, final, s.pos);
}


void Trie::insertString(char* str)
{
	insertStringUtil(str, root);
}

int strlen(char *str)
{
	int len = 0;
	
	while(*str++)
		len++;

	return len;
}

void findsub(char *ptr, char* substr, int width) {
	while(width--)
		*substr++ = *ptr++;
	*substr = '\0';
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin>>T;

	char string[STR_LEN];
	int rank;

	char final[STR_LEN];

	int len;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> rank;
		cin >> string;

		Trie t;

		len = strlen(string);

		char* ptr;
		ptr = string;
		while(*ptr)
		{
			t.insertString(ptr);
			ptr++;
		}

		t.findStringRank(rank, final);

		cout << "#" << test_case << " " << final << endl;
	}
	return 0;
}