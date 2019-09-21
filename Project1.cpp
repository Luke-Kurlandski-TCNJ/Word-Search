#include <string>
#include <iostream>
#include <vector>
#include "colormod.h"
#include <fstream>
using namespace std;

//Searching Methods
void search(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis);
void checkDwnLftUpRt(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis, int row, int col, int dir);
void checkVert(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis, int row, int col, int dirVert);
void checkHor(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis, int row, int col, int dirHor);
void checkDwnRtUpLft(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis, int row, int col, int dir);
void checkDwnLftUpRt(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis, int row, int col, int dir);

//Other methods
void populate(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln);
void print(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln);
void parseString(string &findThese, vector<string> &findThis);

//Functional method to populate matricies and read file from user
void populate(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln) {
	//Deals with the matrix file
	cout << "Which matrix to use (enter file name)\n";
	string use;
	getline(cin, use);
	ifstream in;
	in.open(use);
	//Acquire information about the size of the matrix (from file)
	int row, col;
	in >> row;
	in >> col;
	//Resizes the letter and boolean matricies
	mtrxLttr.resize(row);
	mtrxBlln.resize(row);
	for(int j=0; j<row; j++) {
		mtrxLttr[j].resize(col);
		mtrxBlln[j].resize(col);
	}
	//Populates the letter and boolean matrix
	for(int i=0; i<row; i++) {
		for(int j=0; j<col; j++) {
			in >> mtrxLttr[i][j];
			mtrxBlln[i][j] = false;
		}
	}
}

//Functional method to search for words within the character matrix
void search(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, vector<string> &findThis) {
	//Loop through every element of the letter vector
	for(int i=0; i<mtrxLttr.size(); i++) {
		for(int j=0; j<mtrxLttr[0].size(); j++) {
			//Check if the letter matches for every string in findThis
			for (int k=0 ; k<findThis.size() ; k++) {
				if(mtrxLttr[i][j] == findThis.at(k).at(0)) {
					//Checks adjacent letter paths
					string findThisWord = findThis.at(k);
					checkVert(mtrxLttr, mtrxBlln, findThisWord, i, j, 1); //Check Down
					checkVert(mtrxLttr, mtrxBlln, findThisWord, i, j, -1); //Check Up
					checkHor(mtrxLttr, mtrxBlln, findThisWord, i, j, 1); //Check Right
					checkHor(mtrxLttr, mtrxBlln, findThisWord, i, j, -1); //Check Left
					checkDwnRtUpLft(mtrxLttr, mtrxBlln, findThisWord, i, j, 1); //Check Down/Right
					checkDwnRtUpLft(mtrxLttr, mtrxBlln, findThisWord, i, j, -1); //Check Up/Left
					checkDwnLftUpRt(mtrxLttr, mtrxBlln, findThisWord, i, j, 1);  //Checks Up/Right
					checkDwnLftUpRt(mtrxLttr, mtrxBlln, findThisWord, i, j, -1);  //Checks Down/Left
				}
			}
		}
	}
}

//Functional method to check the diagonal path, from top-right to bottom-left
void checkDwnLftUpRt(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis, int row, int col, int dir) {
	int incI = 1; int incC = 1; int c = 0; bool present = false;
	int endVal = findThis.size() + 1;

	for(int i=0 ; i < endVal ; i=i+incI) {
		if(row-(dir*i)<0 || row-(dir*i)>mtrxLttr.size()-1 || col+(dir*i)<0 || col+(dir*i)>mtrxLttr[0].size()-1 || c==-1) 
			break;
		
		if(mtrxLttr[row-(dir*i)][col+(dir*i)]==findThis.at(c)) 
			c=c+incC;
		else
			break;
		
		if(c==findThis.size()) {
			present=true;
			incI = incI * -1;
			incC = -1;
			c = c -2;
		}
		
		if(present==true)
			mtrxBlln[row-(dir*i)][col+(dir*i)]=true;
	}
}

//Functional method to check the diagonal path, from top-left to bottom-right
void checkDwnRtUpLft(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis, int row, int col, int dir) {
	int incI = dir; int incC = 1; int c = 0; bool present = false;
	int endVal = findThis.size() + 1; //No idea why this is neccicary

	for(int i=0 ; i<endVal ; i=i+incI) {
		if(row+i<0 || row+i>mtrxLttr.size()-1 || col+i<0 || col+i>mtrxLttr[0].size()-1 || c==-1) 
			break;
		
		if(mtrxLttr[row+i][col+i]==findThis.at(c)) 
			c=c+incC;
		else 
			break;
		
		if(c==findThis.size()) {
			present=true;
			incI = incI * -1;
			incC = -1;
			c = c -2;
		}
		
		if(present==true)
			mtrxBlln[row+i][col+i]=true; 
	}
}

//Functional method to check the vertical path
void checkVert(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis, int row, int col, int dirVert) {
	int incI = dirVert; int incC = 1; int c = 0; bool present = false;
	for(int i=row ; i < findThis.size() + row ; i=i+incI) {
		if(i<0 || i>mtrxLttr.size()-1 || c==-1) 
			break;
		
		if(mtrxLttr[i][col]==findThis.at(c)) 
			c=c+incC;
		else
			break;
		
		if(c==findThis.size()) {
			present=true;
			incI = incI * -1;
			incC = -1;
			c = c -2;
		}
		
		if(present==true)
			mtrxBlln[i][col]=true;
	}
}

//Functional method to check the hortizontal path
void checkHor(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln, string &findThis, int row, int col, int dirHor) {
	int incI = dirHor; int incC = 1; int c = 0; bool present = false;
	for(int i=col ; i < findThis.size() + col ; i=i+incI) {
		if(i<0 || i>mtrxLttr[0].size()-1 || c==-1) 
			break;
		
		if(mtrxLttr[row][i]==findThis.at(c)) 
			c=c+incC;
		else
			break;
		
		if(c==findThis.size()) {
			present=true;
			incI = incI * -1;
			incC = -1;
			c = c -2;
		}
		
		if(present==true)
			mtrxBlln[row][i]=true;
	}
}

//Functional method to print the matrix
void print(vector< vector<char> > &mtrxLttr, vector< vector<bool> > &mtrxBlln) {
	//Sets up the color alterations
	Color::Setting red(Color::FG_RED);
	Color::Setting def(Color::FG_DEFAULT);

	//Prints the letter matrix
	for(int i=0; i<mtrxLttr.size(); i++) {
		for(int j=0; j<mtrxLttr[0].size(); j++) {
			if(mtrxBlln[i][j]==true) 
				cout << red << mtrxLttr[i][j] << def << " ";
			else 
				cout << mtrxLttr[i][j] << " ";
		}
		cout << "\n";
	}
}

//Functional method to parse the user's entry into a vector of individual words
void parseString(string &findThese, vector<string> &findThis) {
	int endLoc = 0; int startLoc = 0;
	while(endLoc != -1) { 
		endLoc = findThese.find(" ");
		if(endLoc == -1)  
			findThis.push_back(findThese);
		else {
			findThis.push_back(findThese.substr(startLoc, endLoc));
			findThese = findThese.substr(endLoc+1);
		}
	}
}

//Main method
int main() {
	//Sets up the matrix of characters and the matrix of booleans
	vector< vector<char> > mtrxLttr;
	vector< vector<bool> > mtrxBlln;
	populate(mtrxLttr, mtrxBlln);

	//Acquires the words to be searched from user
	cout << "Which words would you like to search for (enter words separated by spaces)\n";
	string findThese;
	getline(cin, findThese);
	vector<string> findThis;
	parseString(findThese, findThis);

	//Searches the matrix
	search(mtrxLttr, mtrxBlln, findThis);

	//Prints the matrix
	print(mtrxLttr, mtrxBlln);
	return 0;
}

/*
	To run program, type in the following into terminal: "./a.out"
*/

/*
	All of the "check" method essentially operate in the same manner:
		The method searches along a specified path. If the word is located along this path, 
		the method then moves backward, along the same path, changing the corresponding
		boolean matrix entries to true.
*/