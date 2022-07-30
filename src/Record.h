#pragma once
#include <string>
using namespace std;
struct Record {
	long long runTime;
	string option;
	string dataStruct;
	Record(string option, string dataStruct, int runTime);
};

Record::Record(string option, string dataStruct, int runTime) {
	this->option = option;
	this->dataStruct = dataStruct;
	this->runTime = runTime;
}
