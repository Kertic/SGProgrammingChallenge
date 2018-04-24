/**
Brennan Rodriguez
Scientific Games Coding Challenge: Problem 1
*/

#include <random>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>


#define PEOPLECOUNT 50
#define MIN_YEAR 1900
#define MAX_YEAR 2000
//#define WRITE_OUT
//Un-Comment the above line to regenerate new values

using namespace std;
struct Person {
	unsigned int personID;
	unsigned int birthYear;
	unsigned int deathYear;

};
int main()
{



#pragma region Generate File based data set
#ifdef WRITE_OUT
	{//Scoped out to reuse variable names outside this block
		srand(time(NULL));
		Person* outDataSet = new Person[PEOPLECOUNT];
		std::fstream outFile;
		outFile.open("Dataset.bin", std::fstream::out | std::fstream::binary);
		unsigned int peopleCt = PEOPLECOUNT;
		outFile.write((char*)&peopleCt, sizeof(unsigned int));
		for (int i = 0; i < PEOPLECOUNT; i++)
		{
			
			outDataSet[i].birthYear = (rand() % (MAX_YEAR - MIN_YEAR))+ MIN_YEAR ;
			outDataSet[i].deathYear = (rand() % (MAX_YEAR - outDataSet[i].birthYear)) + outDataSet[i].birthYear + 1;
			outDataSet[i].personID = i;

			outFile.write((char*)&outDataSet[i].personID, sizeof(unsigned int));
			outFile.write((char*)&outDataSet[i].birthYear, sizeof(unsigned int));
			outFile.write((char*)&outDataSet[i].deathYear, sizeof(unsigned int));
		}
		outFile.close();
		outFile.open("Dataset.txt", std::fstream::out);
		for (int i = 0; i < PEOPLECOUNT; i++)
		{
			outFile << "Person: " << i << ", Birth Year: " << outDataSet[i].birthYear << ", Death Year: " << outDataSet[i].deathYear << "\n";
		}
		outFile.close();
		delete[] outDataSet;
	}
#endif  
#pragma endregion

#pragma region Read in Data set
	std::fstream readFile;
	readFile.open("DataSet.bin", std::fstream::in | std::fstream::binary);
	unsigned int peopleCt = 0;
	readFile.read((char*)&peopleCt, sizeof(unsigned int));
	Person* dataSetPeople = new Person[peopleCt];
	for (unsigned int i = 0; i < peopleCt; i++)
	{
		readFile.read((char*)&dataSetPeople[i].personID, sizeof(unsigned int));
		readFile.read((char*)&dataSetPeople[i].birthYear, sizeof(unsigned int));
		readFile.read((char*)&dataSetPeople[i].deathYear, sizeof(unsigned int));
	}
	readFile.close();
#pragma endregion


	unsigned int* peopleAliveDuringThisYear = new unsigned int[MAX_YEAR - MIN_YEAR];//Make an array of ints to track amount of alive people per year (each index represents one year between within the range)
	for (int i = 0; i < MAX_YEAR - MIN_YEAR; i++)//Initialize the array
		peopleAliveDuringThisYear[i] = 0;

	//Generate a count, per year, of how many people are alive during this year.
	for (unsigned int i = 0; i < peopleCt; i++)//For each person
	{
		for (unsigned int j = dataSetPeople[i].birthYear; j < dataSetPeople[i].deathYear; j++)//For each year that person was alive
		{
			peopleAliveDuringThisYear[j - MIN_YEAR]++;//Add one to that year
		}
	}
	unsigned int greatestYear = MIN_YEAR;
	for (int i = 0; i < MAX_YEAR - MIN_YEAR; i++)
	{
		if (peopleAliveDuringThisYear[greatestYear - MIN_YEAR] < peopleAliveDuringThisYear[i])
			greatestYear = i + MIN_YEAR;
	}
		
	std::fstream resultFile;
	resultFile.open("Results.txt", std::fstream::out);

	resultFile << "\nThe year with the highest amount of people was: " << greatestYear << " with " << peopleAliveDuringThisYear[greatestYear - MIN_YEAR] << " people.";
	std::cout << "\nThe year with the highest amount of people was: " << greatestYear << " with " << peopleAliveDuringThisYear[greatestYear - MIN_YEAR] << " people.";

	resultFile.close();
	delete[] dataSetPeople;
	delete[] peopleAliveDuringThisYear;
	return 0;
}

