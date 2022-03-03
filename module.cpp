#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#include "expression.h"
#include "subexpression.h"
#include "symboltable.h"
#include "parse.h"

void parseAssignments( stringstream& in );

SymbolTable symbolTable;

int main()
{
Expression* expression;
char paren, comma;
string line;
ifstream fin("input.txt");
if (!fin.is_open())
perror("error while opening file");
while (getline(fin, line))
{
symbolTable.init();
if (!fin)
break;
stringstream in(line, ios_base::in);
in >> paren;
cout << line << " ";
expression = SubExpression::parse(in);
in >> comma;
parseAssignments( in );
double result = expression->evaluate();
cout << "Value = " << result << endl;
}
return 0;
}

void parseAssignments( stringstream& in )
{
char assignop, delimiter;
string variable;
double value;
do
{
variable = parseName(in);
in >> ws >> assignop >> value >> delimiter;
symbolTable.insert(variable, value);
} while (delimiter == ',');
}
