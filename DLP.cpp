#include "DLP.h"

DLP::DLP() {
	contString = true;
	contComm = true;
	lineNumber = 1;
}

void DLP::lab1(string filename) {
	
	std::ifstream inputFile(filename);
	if (inputFile.is_open()) {
		Token newToken;
		while (!inputFile.eof()) {
			nextToken = inputFile.get();


			switch (nextToken) {
			case '(':
				newToken.setType(leftParen);
				newToken.setVal(nextToken);
				newToken.setLine(lineNumber);
				tokenVct.push_back(newToken);
				break;

			case ')':
				newToken.setType(rightParen);
				newToken.setVal(nextToken);
				newToken.setLine(lineNumber);
				tokenVct.push_back(newToken);
				break;

			case ',':
				newToken.setType(comma);
				newToken.setVal(nextToken);
				newToken.setLine(lineNumber);
				tokenVct.push_back(newToken);
				break;

			case '.':
				newToken.setType(period);
				newToken.setVal(nextToken);
				newToken.setLine(lineNumber);
				tokenVct.push_back(newToken);
				break;

			case '?':
				newToken.setType(questionMark);
				newToken.setVal(nextToken);
				newToken.setLine(lineNumber);
				tokenVct.push_back(newToken);
				break;

			case ':':
				if (inputFile.peek() == '-') {
					tokenVal = nextToken;
					newToken.setType(colonDash);
					tokenVal += inputFile.get();
					newToken.setVal(tokenVal);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}
				else {
					newToken.setType(colon);
					newToken.setVal(nextToken);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					break;
				}

			case '*':
				newToken.setType(multiply);
				newToken.setVal(nextToken);
				newToken.setLine(lineNumber);
				tokenVct.push_back(newToken);
				break;
			case '+':
				newToken.setType(add);
				newToken.setVal(nextToken);
				newToken.setLine(lineNumber);
				tokenVct.push_back(newToken);
				break;

			case 'S':
				tokenVal = nextToken;
				while (isalpha(inputFile.peek())) {
					tokenVal += inputFile.get();
				}
				if (tokenVal == "Schemes") {
					newToken.setVal(tokenVal);
					newToken.setType(schemes);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}
				else {
					newToken.setVal(tokenVal);
					newToken.setType(id);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}

			case 'F':
				tokenVal = nextToken;
				while (isalpha(inputFile.peek())) {
					tokenVal += inputFile.get();
				}
				if (tokenVal == "Facts") {
					newToken.setVal(tokenVal);
					newToken.setType(facts);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}
				else {
					newToken.setVal(tokenVal);
					newToken.setType(id);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}

			case 'R':
				tokenVal = nextToken;
				while (isalpha(inputFile.peek())) {
					tokenVal += inputFile.get();
				}
				if (tokenVal == "Rules") {
					newToken.setVal(tokenVal);
					newToken.setType(rules);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}
				else {
					newToken.setVal(tokenVal);
					newToken.setType(id);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}

			case 'Q':
				tokenVal = nextToken;
				while (isalpha(inputFile.peek())) {
					tokenVal += inputFile.get();
				}
				if (tokenVal == "Queries") {
					newToken.setVal(tokenVal);
					newToken.setType(queries);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}
				else {
					newToken.setVal(tokenVal);
					newToken.setType(id);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}

				break;

			case '\'':
				tokenVal = nextToken;
				newToken.setLine(lineNumber);
				contString = true;

				currChar = inputFile.peek();
				if (inputFile.peek() == '\n')
					lineNumber++;
				tokenVal += inputFile.get();
				while (contString && !inputFile.eof()) {

					if (currChar == '\'' && inputFile.peek() != '\'') {
						contString = false;
					}
					else if (currChar == '\'' && inputFile.peek() == '\'') {
						tokenVal += inputFile.get();
						currChar = inputFile.peek();
						tokenVal += inputFile.get();
					}

					else {
						currChar = inputFile.peek();
						tokenVal += inputFile.get();
					}
					if (inputFile.peek() == inputFile.eof()) {
						contString = false;
					}
					if (currChar == '\n' && contString) {
						lineNumber++;
					}
				}

				if (inputFile.peek() == inputFile.eof() || inputFile.eof()) {
					newToken.setVal(tokenVal);
					newToken.setType(undefined);
					tokenVct.push_back(newToken);
					newToken.setType(eoFile);
					newToken.setVal("");
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}
				else {
					newToken.setVal(tokenVal);
					newToken.setType(stringType);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}


			case '#':
				tokenVal = nextToken;
				if (inputFile.peek() == '|') {
					newToken.setLine(lineNumber);
					tokenVal += inputFile.get();
					contComm = true;
					while (contComm && !inputFile.eof()) {

						if (currChar == '|' && inputFile.peek() == '#') {
							contComm = false;
						}

						else {
							currChar = inputFile.peek();
							tokenVal += inputFile.get();
						}
						if (inputFile.peek() == inputFile.eof()) {
							contComm = false;
						}
						if (currChar == '\n' && contComm) {
							lineNumber++;

						}
					}
					if (inputFile.eof() || inputFile.peek() == inputFile.eof()) {
						newToken.setVal(tokenVal);
						newToken.setType(undefined);
						tokenVct.push_back(newToken);
						newToken.setType(eoFile);
						newToken.setVal("");
						newToken.setLine(lineNumber);
						tokenVct.push_back(newToken);
						tokenVal = "";
						break;
					}
					else {
						tokenVal += inputFile.get();
						newToken.setVal(tokenVal);
						newToken.setType(comment);
						tokenVal = "";
						break;
					}

				}
				else {
					while (inputFile.peek() != '\n' && inputFile.peek() != inputFile.eof()) {
						tokenVal += inputFile.get();
					}
					newToken.setVal(tokenVal);
					newToken.setType(comment);
					newToken.setLine(lineNumber);

					tokenVal = "";
					break;
				}

			case '\n':
				lineNumber++;
				break;

			case ' ':
			case '\t':
				break;

			default:
				if (isalpha(nextToken)) {
					newToken.setType(id);
					newToken.setLine(lineNumber);
					tokenVal = nextToken;
					while (isalnum(inputFile.peek()) && !inputFile.eof()) {
						tokenVal += inputFile.get();
					}
					newToken.setVal(tokenVal);
					tokenVct.push_back(newToken);
					tokenVal = "";
					break;
				}
				else if (inputFile.eof()) {
					newToken.setType(eoFile);
					newToken.setVal("");
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
				}
				else {
					newToken.setType(undefined);
					newToken.setVal(nextToken);
					newToken.setLine(lineNumber);
					tokenVct.push_back(newToken);
					break;
				}
			}
		}

	}
}

void DLP::lab2() {
    goober = Parser();
	goober.setTokenVct(tokenVct);
	goober.parse();
}

vector<Predicate> DLP::getSchemesVct() {
    return goober.getSchemesVct();
}

vector<Predicate> DLP::getFactsVct() {
    return goober.getFactsVct();
}

vector<Rule> DLP::getRulesVct() {
    return goober.getRulesVct();
}

vector<Predicate> DLP::getQueriesVct(){
    return goober.getQueriesVct();
}
