#include <iostream>
#include <string>

#include "Analysis.h"

using namespace std;
using namespace analysis;
void testCase1(){
	// test Token and Variable Class
	Token token_a("a");
	Token token_aa("a");
	Token token_b("b");
	Token token_bb("b");
	Token token_c("c");
	Token token_cc("c");
	Variable variable_a("[[a]]");
	Variable variable_b("[[b]]");
	Variable variable_c("[[c]]");
	cout << "========================" << "\n";
	cout << "testCase1" << "\n";
	cout << "Token and Variable Class" << "\n";
	cout << "========================" << "\n";
	cout << "Token Numbers:       "<< Token::Tokens.size() << "\n";
	for ( Token i : Token::Tokens){
		cout << i.toString() << "\n";
	}
	cout << "Variable Numbers:    "<< Variable::Variables.size() << "\n";
	for ( Variable i : Variable::Variables){
		cout << i.toString() << "\n";
	}

	cout << "\n";
	clear();
}

void testCase2(){
	// test ConsBinomial
	Token* token_a = new Token("a");
	Token* token_b = new Token("b");
	Token* token_c = new Token("c");
	Variable* variable_a = new Variable("[[a]]");
	Variable* variable_b = new Variable("[[b]]");
	

	ConsBinomial* cons1 = new ConsBinomial(token_a, variable_a, OperatorCode::in);
	ConsBinomial* cons2 = new ConsBinomial(token_b, variable_a, OperatorCode::in);
	ConsBinomial* cons3 = new ConsBinomial(variable_a, variable_b, OperatorCode::subseteq);

	run();

	cout << "========================" << "\n";
	cout << "testCase2" << "\n";
	cout << "ConsBinomial" << "\n";
	cout << "========================" << "\n";
	cout << cons1->toString() << "\n";
	cout << cons3->toString() << "\n";
	cout << "\n";
	cout << variable_a->toStringTokens() << "\n";
	cout << variable_b->toStringTokens() << "\n";
	
	cout << "\n";
	clear();
}

void testCase3(){
	// test ConsIf
	Token* token_a = new Token("a");
	Token* token_b = new Token("b");
	Token* token_c = new Token("c");
	Variable* variable_a = new Variable("[[a]]");

	// if a ∈ [[a]] then b ∈ [[a]]
	ConsBinomial* cons1 = new ConsBinomial(token_a, variable_a, OperatorCode::in);
	ConsBinomial* thenCons1 = new ConsBinomial(token_b, variable_a, OperatorCode::in, false);
	ConsIf* consIf1 = new ConsIf(token_a, variable_a, OperatorCode::in, thenCons1);

	run();

	cout << "========================" << "\n";
	cout << "testCase3" << "\n";
	cout << "ConsIf" << "\n";
	cout << "========================" << "\n";
	cout << cons1->toString() << "\n";
	cout << consIf1->toString() << "\n";
	cout << "\n";
	cout << variable_a->toStringTokens();
	cout << "\n";

	cout << "\n";
	clear();
}

void testCase4(){
	// test ConsIf
	Token* token_a = new Token("a");
	Token* token_b = new Token("b");
	Token* token_c = new Token("c");
	Token* token_d = new Token("d");
	Variable* variable_a = new Variable("[[a]]");
	Variable* variable_b = new Variable("[[b]]");
	Variable* variable_c = new Variable("[[c]]");

	// a ∈ [[a]]
	// b ∈ [[a]]
	// c ∈ [[a]]
	ConsBinomial* cons1 = new ConsBinomial(token_a, variable_a, OperatorCode::in);
	ConsBinomial* cons2 = new ConsBinomial(token_b, variable_a, OperatorCode::in);
	ConsBinomial* cons3 = new ConsBinomial(token_c, variable_a, OperatorCode::in);

	// a ∈ [[b]]
	// c ∈ [[b]]
	ConsBinomial* cons4 = new ConsBinomial(token_a, variable_b, OperatorCode::in);
	ConsBinomial* cons5 = new ConsBinomial(token_c, variable_b, OperatorCode::in);

	// d ∈ [[c]]
	ConsBinomial* cons6 = new ConsBinomial(token_d, variable_c, OperatorCode::in);

	// if [[b]] ⊆ [[a]] then [[c]] ⊆ [[a]]
	ConsBinomial* thenCons1 = new ConsBinomial(variable_c, variable_a, OperatorCode::subseteq, false);
	ConsIf* consIf1 = new ConsIf(variable_b, variable_a, OperatorCode::subseteq, thenCons1);

	run();

	cout << "========================" << "\n";
	cout << "testCase4" << "\n";
	cout << "ConsIf" << "\n";
	cout << "========================" << "\n";
	cout << cons1->toString() << "\n";
	cout << cons2->toString() << "\n";
	cout << cons3->toString() << "\n";
	cout << cons4->toString() << "\n";
	cout << cons5->toString() << "\n";
	cout << cons6->toString() << "\n";
	cout << consIf1->toString() << "\n";
	cout << "\n";
	cout << variable_a->toStringTokens() << "\n";
	cout << variable_b->toStringTokens() << "\n";
	cout << variable_c->toStringTokens() << "\n";
	cout << "\n";

	clear();
}

int main(){
	testCase1();
	testCase2();
	testCase3();
	testCase4();
	return 0;
}
