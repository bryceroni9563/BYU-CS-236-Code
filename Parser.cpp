#include "Parser.h"
#include "Token.h"



Parser::Parser(){
    numSchemes = 0;
    numFacts = 0;
    numRules = 0;
    numQueries = 0;
	index = 0;
    tokenVct = {};
    factsVct = {};
    schemesVct = {};
    rulesVct = {};
    queriesVct = {};
}

void Parser::setTokenVct(std::vector<Token> newVct){
    tokenVct = newVct;
    return;
}

void Parser::parse(){
    try{
        currToken = tokenVct[index];
	    match(schemes);
	    match(colon);
	    parseSchemes();
	    parseSchemeList();
	    match(facts);
	    match(colon);
	    parseFactList();
	    match(rules);
	    match(colon);
	    parseRuleList();
	    match(queries);
	    match(colon);
	    parseQueries();
	    parseQueryList();
        //printStuff();
    }
    catch(Token error){
        cout << "Failure!" << endl;
        cout << "  " << error.getToken() << endl;
    }
}

void Parser::match(string type){
	if (type == currToken.getType()) {
		index++;
		currToken = tokenVct[index];
		return;
	}
	else {
		throw currToken;
		return;
	}
}

void Parser::parseSchemes() {
    pred = Predicate(currToken.getVal());
    
	match(id);
    match(leftParen);
	if (currToken.getType() == id) {
		pred.addParameter(Parameter(currToken.getType(), currToken.getVal()));
        
	}
	match(id);
	if (currToken.getType() == comma) {
		parseIDList();
	}
	match(rightParen);
	schemesVct.push_back(pred);
	numSchemes++;
	return;
}

void Parser::parseSchemeList() {
	if (currToken.getType() == id) {
		parseSchemes();
	}
	if (currToken.getType() == id) {
		parseSchemeList();
	}
	return;
}

void Parser::parseFactList() {
    
	if (currToken.getType() == id) {
		parseFacts();
		if (currToken.getType() == id) {
			parseFactList();
		}
	}
    
	return;
}

void Parser::parseFacts() {
	pred = Predicate(currToken.getVal());
    match(id);
    match(leftParen);
	if (currToken.getType() == stringType) {
		pred.addParameter(Parameter(currToken.getType(), currToken.getVal()));
		domain.insert(currToken.getVal());
        match(stringType);
	}
	
	if (currToken.getType() == comma) {
		parseStrings();
	}
	match(rightParen);
	match(period);
	factsVct.push_back(pred);
	numFacts++;
	return;
}

void Parser::parseStrings() {
	match(comma);
	if (currToken.getType() == stringType) {
		pred.addParameter(Parameter(currToken.getType(), currToken.getVal()));
		domain.insert(currToken.getVal());
        match(stringType);
	}
	if (currToken.getType() == comma) {
		parseStrings();
	}
	return;
}

void Parser::parseRuleList() {

    pred = Predicate(currToken.getVal());
	if (currToken.getType() == id) {
        parseHeadPredicate();
        nextRule = Rule(pred);
    	match(colonDash);
		parseRules();
		if (currToken.getType() == period) {
			match(period);
		}
        if (currToken.getType() == id) {
            parseRuleList();
        }
	}
    
}

void Parser::parseRules() {
    rulePred = true;
	parsePredicate(rulePred);
	if (currToken.getType() == comma) {
		parsePredicateList(rulePred);
	}
	
	rulesVct.push_back(nextRule);
    numRules++;
	return;
}

void Parser::parseQueries() {
    rulePred = false;
	pred = Predicate(currToken.getVal());
	parsePredicate(rulePred);
	match(questionMark);
	queriesVct.push_back(pred);
    numQueries++;
    return;
}

void Parser::parseQueryList() {
    
	if (currToken.getType() == eoFile) {
        match(eoFile);
	}
	else {
		parseQueries();
		if (currToken.getType() == id) {
			parseQueryList();
		}
		
	}
    
    return;
}

void Parser::parseIDList() {
	match(comma);
	if (currToken.getType() == id) {
		pred.addParameter(Parameter(currToken.getType(), currToken.getVal()));
        match(id);
	}
	

	if (currToken.getType() == comma) {
		parseIDList();
	}
	return;
}

void Parser::parseHeadPredicate() {
	match(id);
	match(leftParen);
	if (currToken.getType() == id) {
		pred.addParameter(Parameter(currToken.getType(), currToken.getVal()));
        match(id);
	}
	
	if (currToken.getType() == comma) {
		parseIDList();
	}
	match(rightParen);
    return;
}

void Parser::parsePredicate(bool fromRule) {
	pred = Predicate(currToken.getVal());
	match(id);
	match(leftParen);
	parseParameter();
	if (currToken.getType() == comma) {
		parseParameterList();
	}
    
    if (fromRule){
        nextRule.addPredicate(pred);
    }
    match(rightParen);
    
    return;
}

void Parser::parsePredicateList(bool fromRule) {
	match(comma);
	parsePredicate(fromRule);
	if (currToken.getType() == comma) {
		parsePredicateList(fromRule);
	}
}

void Parser::parseParameter() {
	if (currToken.getType() == stringType || currToken.getType() == id) {
		pred.addParameter(Parameter(currToken.getType(), currToken.getVal()));
		match(currToken.getType());
	}
	if (currToken.getType() == leftParen) {
		parseExpression();
        pred.addParameter(Parameter(currToken.getType(), currExp));
        currExp = "";
	}
    return;
}

void Parser::parseParameterList() {
	match(comma);
	parseParameter();
	if (currToken.getType() == comma) {
		parseParameterList();
	}
    return;
}

void Parser::parseExpression() {
    currExp += currToken.getVal();
	match(leftParen);
	parseExpParameter();
	parseOperator();
	parseExpParameter();
    currExp += currToken.getVal();
	match(rightParen);
    return;
}

void Parser::parseExpParameter(){
    if (currToken.getType() == leftParen) {
        parseExpression();
    }
    else if (currToken.getType() == stringType || currToken.getType() == id) {
        currExp += currToken.getVal();
        match(currToken.getType());
    }
    return;
}

void Parser::parseOperator() {
	if (currToken.getType() == add) {
        currExp += currToken.getVal();
		match(add);
	}
    
	else if (currToken.getType() == multiply) {
        currExp += currToken.getVal();
		match(multiply);
	}
    else{
        match(add);
    }
}

int Parser::getNumSchemes() {
	return numSchemes;
}

int Parser::getNumFacts() {
	return numFacts;
}

int Parser::getNumRules() {
	return numRules;
}

int Parser::getNumQueries() {
	return numQueries;
}

int Parser::getDomainSize() {
    int numStrings = domain.size();
    return numStrings;
}

string Parser::printSchemes() {
	stringstream ss;
	for (int i = 0; i < (int)schemesVct.size(); i++) {
		ss << "  " << schemesVct[i].toString() << endl;
	}
	return ss.str();
}

string Parser::printFacts() {
	stringstream ss;
	for (int i = 0; i < (int)factsVct.size(); i++) {
		ss << "  " << factsVct[i].toString() << "." << endl;
	}

	return ss.str();
}

string Parser::printRules() {
	stringstream ss;
	for (int i = 0; i < (int)rulesVct.size(); i++) {
		ss << "  " << rulesVct[i].toString() << endl;
	}

	return ss.str();
}

string Parser::printQueries() {
	stringstream ss;
	for (int i = 0; i < (int)queriesVct.size(); i++) {
		if (i != ((int)queriesVct.size() - 1)){
            ss << "  " << queriesVct[i].toString() << "?" << endl;
        }
        else{
            ss << "  " << queriesVct[i].toString() << "?";
        }
	}

	return ss.str();
}

string Parser::printDomain() {
	stringstream ss;
	for (itr = domain.begin(); itr != domain.end(); itr++) {
		ss << "  " << *itr << endl;
	}

	return ss.str();
}

void Parser::printStuff(){
    cout << "Success!" << endl;
	cout << "Schemes(" << getNumSchemes() << "):" << endl;
	cout << printSchemes();
	cout << "Facts(" << getNumFacts() << "):" << endl;
	cout << printFacts();
	cout << "Rules(" << getNumRules() << "):" << endl;
	cout << printRules();
	cout << "Queries(" << getNumQueries() << "):" << endl;
	cout << printQueries() << endl;
    cout << "Domain(" << getDomainSize() << "):" << endl;
    cout << printDomain();
}

vector<Predicate> Parser::getSchemesVct() {
    return schemesVct;
}

vector<Predicate> Parser::getFactsVct() {
    return factsVct;
}

vector<Rule> Parser::getRulesVct() {
    return rulesVct;
}

vector<Predicate> Parser::getQueriesVct(){
    return queriesVct;
}







