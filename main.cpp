#include <iostream>
#include <string>
#include <fstream>
#include <vector>
//#include "Token.h"
//#include "Parser.h"
#include "Interpreter.h"
#include "DLP.h"

using std::cout;
using std::string;
using std::endl;

int main(int argc, char* argv[]) {
    string filename = argv[1];

	DLP dataLP;

	dataLP = DLP();

	dataLP.lab1(filename);
	dataLP.lab2();

  Interpreter interp;

	interp = Interpreter(dataLP);
  cout << "Dependency Graph" << endl;
  interp.makeGraph();
  cout << endl;
	cout << "Rule Evaluation" << endl;
  interp.evalAllRules();
  interp.evalAllQueries();

	return 0;
}
