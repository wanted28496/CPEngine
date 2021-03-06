// Sentences.cpp : creates a sentece from list of words
//

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG



#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<iostream>
using namespace std;

/**
 gets input from user

 @params o_length refrence variable for lenght of the sentence
 @params o_wordCount refrence varable to total number of words in sentence
 @params o_sentence refrence varaible to a 2D character array of words
*/

char* MakeSentence(char** &o_sentence) {
	
	int length = 1;
	int wordCount = 0;
	bool calculateLen = true;
	do {
		int len = 1;
		for (int i = 0; o_sentence[wordCount][i] != '\0'; i++) {
			len++;
		}
		length += len;
		wordCount++;
		if (o_sentence[wordCount][0] == '\n') {
			free(o_sentence[wordCount]);
			calculateLen = false;
		}
	} while (calculateLen);

	char* sentence = (char*)malloc(length * sizeof(char*));
	int len = 0;
	for (int i = 0; i < wordCount; i++) {
		for (int j = 0; o_sentence[i][j] != '\0'; j++) {
			sentence[len] = o_sentence[i][j];
			len++;
		}
		if (i == wordCount - 1) {
			sentence[len] = '.';
		}
		else {
			sentence[len] = ' ';
		}
		len++;
	}
	sentence[len] = '\0';
	return sentence;

}



int main()
{
	{
		
		char** wordList = (char**)malloc(50 * sizeof(char*));

		char choice = 'y';
		int length = 0;
		int wordCount = 0;
		char* temp = (char*)malloc(50 * sizeof(char*));
		do {
			cout << "Enter the word: ";
			cin >> temp;
			int len = 1;
			for (int i = 0; temp[i] != '\0'; i++) {
				len++;
			}
			length += len;
			wordList[wordCount] = (char*)malloc(len * sizeof(char*));

			for (int i = 0; i < temp[i] != '\0'; i++) {
				wordList[wordCount][i] = temp[i];
			}
			wordList[wordCount][len - 1] = '\0';

			wordCount++;
			cout << "Enter Y to add another word to sentence Else n to stop adding words: ";
			cin >> choice;
		} while (choice == 'y' || choice == 'Y');
		wordList[wordCount] = (char*)malloc(sizeof(char*));
		wordList[wordCount][0] = '\n';
		length++;
		free(temp);


		char* sentence = MakeSentence(wordList);
		printf("The Sentence is: %s", sentence);


		_getch();
		free(wordList);
		free(sentence);
	}
	
	#if defined(_DEBUG)
		_CrtDumpMemoryLeaks();
	#endif // _DEBUG

    return 0;

}




