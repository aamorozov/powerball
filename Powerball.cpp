#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

string AskName();
string CheckResults(int UserNum[], int userRed, int CompNum[], int compRed);
void setSeed();
void WriteHeader();
int SelfOrAutoPick(string typeOfBall);
void AskPlayerForWhiteNumber(int UserWhite[]);
void AskPlayerForRedNumber(int *userRed);
void GenerateWhiteNumbers(int UserWhite[]);
void GenerateRedNumber(int &userRed);
void GenerateGameNum(int CompWhite[], int &compRed);
void Sort(int Num[], int total);
void PrintNumbers(string name, int white[], int red);
void WriteNumbers(string username, string compname, int userwhite[], int compwhite[], int userred, int compred);

int main()
{
	int userWhite[5] = {};
	int compWhite[5] = {};
	int userRed, compRed;
	string userName, results;
	string answer;
	int decisionForWhiteNumber;
	int decisionForRedNumber;

	setSeed();
	WriteHeader();
	userName = AskName();

	do
	{
		decisionForWhiteNumber = SelfOrAutoPick("white");

		if (decisionForWhiteNumber == 1)
		{
			AskPlayerForWhiteNumber(userWhite);
		}
		else
		{
			GenerateWhiteNumbers(userWhite);
		}

		decisionForRedNumber = SelfOrAutoPick("red");

		if (decisionForRedNumber == 1)
		{
			AskPlayerForRedNumber(&userRed);
		}
		else
		{
			GenerateRedNumber(userRed);
		}

		GenerateGameNum(compWhite, compRed);

		Sort(userWhite, 5);
		Sort(compWhite, 5);

		results = CheckResults(userWhite, userRed, compWhite, compRed);

		PrintNumbers(userName, userWhite, userRed);
		PrintNumbers("Winning", compWhite, compRed);

		WriteNumbers(userName, "winning", userWhite, compWhite, userRed, compRed);

		cout << "\n\nWould you like to play again (y/n)? ";
		getline(cin, answer);
	} while (answer == "y");

	cout << "\nThank You For Playing!!"
			 << "\nPROGRAMMER: Andrey Morozov";
	return 0;
}

void WriteHeader()
{
	//Header File: Game Rules & Ask User for Name
	cout << "\nNumber Guessing Game\n"
			 << "\n====================\n"
			 << "\nGame Rules:\n"
			 << "\n 1. Select FIVE numbers from 1 to 69 for the white balls."
			 << "\n 2. Select ONE number from 1 to 26 for the red Powerball."
			 << "\n 3. Prize determined by how many of your numbers match the winning numbers";
}

string AskName()
{
	string playerName;

	cout << "\n\nLet's Start!\n"
			 << "\n\nPlease enter your name: ";
	getline(cin, playerName);

	return playerName;
}

int SelfOrAutoPick(string typeOfBall)
{
	int status;
	string answer;
	cout << "\nDo you want to self pick your " << typeOfBall << " ball numbers?(Y or N): ";
	getline(cin, answer);
	if (answer == "Y" || answer == "y")
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void AskPlayerForWhiteNumber(int UserWhite[])
{
	bool again = true;	 //Do While Loop 1
	bool inside = false; //If Loop
	int ball;
	//For Loop: Fills the Users White Ball Array
	for (int row = 0; row < 5; row++)
	{
		//Do While Loop: Checks the whiteball number entered, if it is in range
		//and not repeated
		do
		{
			cout << "Please enter a White Ball number: ";
			cin >> ball;
			cin.ignore();
			//Check IF: the white ball number is within range of 1-69
			if (ball <= 69 && ball >= 1)
			{
				//For Loop: moves the IF statement along each position of the array
				for (int i = 0; i < row; i++)
				{
					inside = false;
					//IF Check: to see if the ball has already been used in the array
					if (UserWhite[i] == ball)
					{
						cout << "\n***This number has already been picked***\n\n";
						inside = true;
						row--;
					}
				}
				if (inside == false)
				{
					UserWhite[row] = ball;
					again = false;
				}
			}
			else
			{
				cout << "\n***This number is not within range***\n\n";
				row--;
			}
		} while (again == true);
	}
}

void AskPlayerForRedNumber(int *userRed)
{
	bool again2 = true; //Do while loop 2
	int rBall;
	do
	{
		//Ask User for powerball number
		cout << "Please enter a number for the Powerball: ";
		cin >> rBall;
		cin.ignore();
		if (rBall <= 26 && rBall >= 1)
		{
			*userRed = rBall;
			again2 = false;
		}
		else
		{
			cout << "\n***Your Powerball number was not in range***\n\n";
		}
	} while (again2 == true);
}

void GenerateWhiteNumbers(int CompWhite[])
{
	//Declaring and Intializing Variables and Check Array
	int row, value, i;
	bool Check[70];
	bool again = true;

	//Sets the Check[] to false
	for (i = 1; i < 70; ++i)
	{
		Check[i] = false;
	}
	//For Loop: continues to fill CompWhite array until all 5 positions have been filled
	for (row = 0; row < 5; row++)
	{
		//Do While Loop:
		do
		{
			//Generating numbers using rand
			value = rand() % 69 + 1;

			if (value == 0)
			{
				return;
			}

			//Check Array for Repeat Numbers
			if (Check[value] == false)
			{
				CompWhite[row] = value;
				Check[value] = true;
				again = false;
			}
		} while (again == true);
	}
}

void GenerateRedNumber(int &compRed)
{
	compRed = rand() % 26 + 1;
}

//Computer Generated Numbers
void GenerateGameNum(int CompWhite[], int &compRed)
{
	//Declaring and Intializing Variables and Check Array
	int row, value, i;
	bool Check[70];
	bool again = true;

	//Sets the Check[] to false
	for (i = 1; i < 70; ++i)
	{
		Check[i] = false;
	}

	//For Loop: continues to fill CompWhite array until all 5 positions have been filled
	for (row = 0; row < 5; row++)
	{
		//Do While Loop:
		do
		{
			//Generating numbers using rand
			value = rand() % 69 + 1;

			//Check Array for Repeat Numbers
			if (Check[value] == false)
			{
				CompWhite[row] = value;
				Check[value] = true;
				again = false;
			}
		} while (again == true);
	}

	//Generate Random Number for Red Ball
	compRed = rand() % 26 + 1;
}

//Sorting User and Computer White Ball Number Arrays
void Sort(int Num[], int total)
{
	//Declaring Variables
	int i, j, temp;

	//Bubble Sort
	for (i = 0; i < total - 1; ++i)
	{
		for (j = 1; j < total; ++j)
		{
			if (Num[j - 1] > Num[j])
			{
				temp = Num[j];
				Num[j] = Num[j - 1];
				Num[j - 1] = temp;
			}
		}
	}
}

//Checks Users Numbers Against the Computer's for Winning Results
string CheckResults(int UserNum[], int userRed, int CompNum[], int compRed)
{
	//Variable Decleration
	string results;
	bool again = true;
	int whiteMatch = 0;

	cout << "\n\n****************** Game Report: ******************\n";

	//IF Check: Red Powerballs 1st, they when Jackpot if they match
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (UserNum[i] == CompNum[j])
			{
				whiteMatch++;
			}
		}
	}
	if (whiteMatch == 5 && userRed == compRed)
	{
		cout << "\n~~~ All White Balls & Powerball Matched ~~~ You won the Jackpot ~~~ "
				 << "\n                !!! You Won $1,000,000,000.00 !!!\n";
		again = false;
	}
	else if (whiteMatch == 5)
	{
		cout << "\n"
				 << whiteMatch << " Match";
		cout << "\n~~~ You Won $1, 000, 000 ~~~\n";
		again = false;
	}
	else if (whiteMatch == 4 && userRed == compRed)
	{
		cout << "\n"
				 << whiteMatch << " Match";
		cout << "\n Powerball: Matched";
		cout << "\n~~~ You Won $50, 000 ~~~\n";
		again = false;
	}
	else if (whiteMatch == 4)
	{
		cout << "\n"
				 << whiteMatch << " Match";
		cout << "\n~~~ You Won $100 ~~~\n";
		again = false;
	}
	else if (whiteMatch == 3 && userRed == compRed)
	{
		cout << "\n"
				 << whiteMatch << " Match";
		cout << "\nPowerball: Matched";
		cout << "\n~~~ You Won $100 ~~~\n";
		again = false;
	}
	else if (whiteMatch == 3)
	{
		cout << "\n"
				 << whiteMatch << " Match";
		cout << "\n~~~ You Won $7 ~~~\n";
		again = false;
	}
	else if (whiteMatch == 2 && userRed == compRed)
	{
		cout << "\n"
				 << whiteMatch << " Match";
		cout << "\n~~~ You Won $7 ~~~\n";
		again = false;
	}
	else if (whiteMatch == 2)
	{
		cout << "\n"
				 << whiteMatch << " Match";
		cout << "\n~~~ You Won $4 ~~~\n";
		again = false;
	}
	else if (whiteMatch == 0 && userRed == compRed)
	{
		cout << "\n"
				 << whiteMatch << " Match";
		cout << "\nPowerball: Matched";
		cout << "\n~~~ You Won $4 ~~~\n";
		again = false;
	}
	else
	{
		cout << "I'm sorry, none of your picks matched.  :(\n";
		again = false;
	}

	results = again;
	return results;
}

void PrintNumbers(string name, int white[], int red)
{
	if (name == "Winning")
	{
		cout << "\n\n"
				 << name << "'s Lottery Numbers: ";
		cout << "\n     White Ball Numbers: ";
	}
	else
	{
		cout << "\n\n"
				 << name << "'s Picked Lottery Numbers: ";
		cout << "\n     White Ball Numbers: ";
	}

	for (int i = 0; i < 5; ++i)
	{
		cout << white[i] << " ";
	}
	cout << "\n     Powerball Number:  " << red << endl;
}

void WriteNumbers(string username, string compname, int userwhite[], int compwhite[], int userred, int compred)
{
	// generating timestamp
	time_t tt;
	char *localTime;
	struct tm *ti;
	time(&tt);
	ti = localtime(&tt);
	localTime = asctime(ti);

	ofstream myfile("numbers.txt");

	if (myfile.is_open())
	{
		myfile << localTime << "\n";
		myfile << username << "'s Lottery Numbers: ";
		myfile << "\n     White Ball Numbers: ";
		for (int i = 0; i < 5; ++i)
		{
			myfile << userwhite[i] << " ";
		}
		myfile << "\n     Powerball Number:  " << userred << endl;

		myfile << compname << "'s Picked Lottery Numbers: ";
		myfile << "\n     White Ball Numbers: ";
		for (int i = 0; i < 5; ++i)
		{
			myfile << compwhite[i] << " ";
		}
		myfile << "\n     Powerball Number:  " << compred << endl;
	}

	myfile.close();
}

void setSeed()
{
	long seed;
	seed = time(0);
	unsigned int sseed = static_cast<unsigned int>(seed);
	srand(sseed);
}
