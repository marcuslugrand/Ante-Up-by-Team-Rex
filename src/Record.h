#pragma once
#include <string>
using namespace std;
struct Record {
	int runTime;
	int option;
	string dataStruct;
	Record(int option, string dataStruct, int runTime);
};

Record::Record(int option, string dataStruct, int runTime) {
	this->option = option;
	this->dataStruct = dataStruct;
	this->runTime = runTime;
}
