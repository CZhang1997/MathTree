// Churong Zhang

#include <iostream>

using namespace std;

#include "MathTree.h"

void main ()
	{
	char c = ' ';
	int num;
	int num2;
	int pre;
	char o;
	MathTree Tree;
	Token toke;

	try
		{
		// doing tree stuff
					cout << "Enter command, C, V, v, O(+, -, *, /, R, L), D, or X :" << endl;
					// Operator R - Root, Example: C3 OR1 C27 means root3 of 27, which is equal 3
					// Operator L - Log, Example: C5 OL1 C25 means Logbase5 of 25, which is equal 2

		while (c != 'X' && c != 'x')
		{
//			cout << "Enter command, C, V, v, O, D, or X :";
			cin >> c;
			switch (c)
			{
			case 'C':
			case 'c':
				cin >> num;
				toke.SetType(Token::ConstantToken);
				toke.SetValue(num);
				Tree.InsertOperand(toke);
				break;
			case 'V':
				toke.SetType(Token::VariableToken);
				cin >> num;
				toke.SetWhich(num);
				Tree.InsertOperand(toke);
				break;
			case 'v':
				cin >> num >> num2;
				toke.SetType(Token::VariableToken);
			
				toke.SetWhich(num);
				toke.SetValue(num2);
				break;
			case 'O':
			case 'o':
				cin >> o >> pre;
				switch (o)
				{
				case'+':
					
					toke.SetType(Token::OperatorPlusToken);
					toke.SetPrecedence((Operator::Precedence)pre);
					Tree.InsertBinaryOperator(toke);
					break;
				case'-':
					
					toke.SetType(Token::OperatorMinusToken);
					toke.SetPrecedence((Operator::Precedence)pre);
					Tree.InsertBinaryOperator(toke);
					break;
				case'*':
					
					toke.SetType(Token::OperatorAsteriskToken);
					toke.SetPrecedence((Operator::Precedence)pre);
					Tree.InsertBinaryOperator(toke);
					break;
				case'/':
					
					toke.SetType(Token::OperatorSlashToken);
					toke.SetPrecedence((Operator::Precedence)pre);
					Tree.InsertBinaryOperator(toke);
					break;
				case'R':

					toke.SetType(Token::OperatorRootToken);
					toke.SetPrecedence((Operator::Precedence)pre);
					Tree.InsertBinaryOperator(toke);
					break;
				case'L':

					toke.SetType(Token::OperatorLogToken);
					toke.SetPrecedence((Operator::Precedence)pre);
					Tree.InsertBinaryOperator(toke);
					break;
				}
				break;
			case 'D':
			case 'd':
				Tree.Delete();
				break;
			case'E':
			case 'e':
				cout << "Answer is " << Tree.Evaluate() << endl;
				break;
			case 'X':
			case 'x':
				cout << "Thank you for using MathTree." << endl;
				Tree.Delete();
				break;
			default:
				cout << "Error 888." << endl;
			}
		}

		}
	catch (Variable::Exception e)
		{
		if (e == Variable::VariableNotDefinedException)
				cout << "Variable has not been defined" << endl;
			else
				cout << "Internal Error 303" << endl;
		}
	catch (MathTree::ResultCode e)
		{
		switch (e)
			{
			case MathTree::ResultCode::DivideByZero:
				cout << "SORRY, YOU CANNOT DIVIDE BY ZERO" << endl;
				break;
			case MathTree::ResultCode::EvenRootNoNegative:
				cout << "SORRY, Even root only can take positive number" << endl;
				break;
			case MathTree::ResultCode::LogCannotLessThanZero:
				cout << "SORRY, Log only can take positive number" << endl;
				break;
			default:
								cout << "Internal Error 202" << endl;
			}
		}


	system("pause");
	}
