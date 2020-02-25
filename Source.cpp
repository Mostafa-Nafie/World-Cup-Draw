#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>

void inTxt(std::string A[][3], int rows);
void arrange(std::string A[][3], int rows1, std::string B[][8][2], int rows2);
void shuffle(std::string A[][8][2], int rows1, std::string B[][4][2], int rows2);
void printTxt(std::string A[][4][2], int rows);


using namespace std;
void main()
{

	string countries[32][3];						  //The array which takes the data from the txt file

	inTxt(countries, 32);

	string	arranged[4][8][2];						  //the array which the countries are arranged in , where each row represents a class(first row class 1,second row class 2...)
	//when the third dimension is equal to 0 it represents the countries name when its equal to 1 it represents their continents

	arrange(countries, 32, arranged, 4);

	srand(time(0));

	string draw[8][4][2];							  //Array where each row represents a group each column represents a class

	shuffle(arranged, 4, draw, 8);

	printTxt(draw, 8);
	
	system("pause");

}



void inTxt(std::string A[][3], int rows)			//Function to save the data from the txt file into an array
{
	ifstream inFile;
	inFile.open("countries.txt");

	if (inFile.fail())								//To print an error in case of read fail and exit without crash
	{
		cerr << "Error reading text file";
		exit(1);
	}


	while (!inFile.eof())
	{
		for (int i = 0; i < 32; i++)				//for loop to fill the "countries" array 
			for (int j = 0; j < 3; j++)
				inFile >> A[i][j];
	}
	inFile.close();
}




void arrange(std::string A[][3], int rows1, std::string B[][8][2], int rows2)
{
	for (int i = 0, j = 0; i < 32; i++)				//for loop to search the third column of each row in "countries" array for the value (1) and then filling the country name into first row of "arranged" array
	{
		if (A[i][2] == "1")
		{
			B[0][j][0] = A[i][0];
			B[0][j][1] = A[i][1];
			j++;
		}
	}
	for (int i = 0, j = 0; i < 32; i++)				//for loop to search the third column of each row in "countries" array for the value (2) and then filling the country name into second row of "arranged" array
	{

		if (A[i][2] == "2")
		{
			B[1][j][0] = A[i][0];
			B[1][j][1] = A[i][1];
			j++;
		}
	}
	for (int i = 0, j = 0; i < 32; i++)				//for loop to search the third column of each row in "countries" array for the value (3) and then filling the country name into third row of "arranged" array
	{

		if (A[i][2] == "3")
		{
			B[2][j][0] = A[i][0];
			B[2][j][1] = A[i][1];
			j++;
		}
	}
	for (int i = 0, j = 0; i < 32; i++)				//for loop to search the third column of each row in "countries" array for the value (4) and then filling the country name into forth row of "arranged" array
	{

		if (A[i][2] == "4")
		{
			B[3][j][0] = A[i][0];
			B[3][j][1] = A[i][1];
			j++;
		}
	}
}





void shuffle(std::string A[][8][2], int rows1, std::string B[][4][2], int rows2)
{
	for (int i = 0; i < 4; i++)						//for loop to swap elements of each row of "arranged" array in a random way 
	{
		for (int j = 0; j < 8; j++)
		{
			int index = rand() % 8;
			string temp1 = A[i][j][0];
			string temp2 = A[i][j][1];
			A[i][j][0] = A[i][index][0];
			A[i][j][1] = A[i][index][1];
			A[i][index][0] = temp1;
			A[i][index][1] = temp2;
		}
	}



	for (int j = 0; j < 4; j++)						//for loop fill elements of each row in "arranged" array into the each column of "draw" array
	{
		for (int i = 0; i < 8; i++)
		{
			B[i][j][0] = A[j][i][0];
			B[i][j][1] = A[j][i][1];
		}
	}


	for (int i = 0; i < 8; i++)
	{
		if ((B[i][0][1] == B[i][1][1]) && (B[i][0][1] != "europe")) 
			shuffle(A, 4, B, 8);
		if ((B[i][0][1] == B[i][2][1]) && (B[i][0][1] != "europe"))
			shuffle(A, 4, B, 8);
		if ((B[i][0][1] == B[i][3][1]) && (B[i][0][1] != "europe"))
			shuffle(A, 4, B, 8);
		if ((B[i][1][1] == B[i][2][1]) && (B[i][1][1] != "europe"))
			shuffle(A, 4, B, 8);
		if ((B[i][1][1] == B[i][3][1]) && (B[i][1][1] != "europe"))
			shuffle(A, 4, B, 8);
		if ((B[i][2][1] == B[i][3][1]) && (B[i][2][1] != "europe"))
			shuffle(A, 4, B, 8);

		if ((B[i][0][1] == B[i][1][1]) && (B[i][0][1] == B[i][2][1]))
			shuffle(A, 4, B, 8);
		if ((B[i][0][1] == B[i][1][1]) && (B[i][0][1] == B[i][3][1]))
			shuffle(A, 4, B, 8);
		if ((B[i][0][1] == B[i][2][1]) && (B[i][0][1] == B[i][3][1]))
			shuffle(A, 4, B, 8);
		if ((B[i][1][1] == B[i][2][1]) && (B[i][1][1] == B[i][3][1]))
			shuffle(A, 4, B, 8);
	}
}






void printTxt(std::string A[][4][2], int rows)			//Function to save the Draw array into txt file.
{
	ofstream outFile;
	outFile.open("out.txt");
	for (int i = 0, num = 1; i < 8; i++, num++)
	{
		outFile << "Group " << num << ':' << "\t";
		for (int j = 0; j < 4; j++)
		{
			outFile << left << setw(15) << A[i][j][0] << "\t";
		}
		outFile << endl << endl;
	}
	outFile.close();

}