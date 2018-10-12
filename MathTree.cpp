// Churong Zhang


#include <stdlib.h>
#include <math.h>
#include "MathTree.h"

MathTree::Node::Node (const Token & T): Toke (T)
	{
	}

MathTree::MathTree ()
	{
	}

MathTree::~MathTree ()
	{
	Delete ();
	}
MathTree::Node::~Node() 
{
	cout << Toke.GetType() << " is Deleted" << endl;

}
void MathTree::Delete ()
	{
	if (pRoot)
	{
		WCS_Pointer <Node>		Ptr(GetLeftMostOperator(pRoot));	// Ptr could end up as NULL if tree is only a constant or variable

		while (Ptr)
			if (!(*Ptr).LeftSideDone)
			{
				(*Ptr).pLeft.SetToNull();

//				(*Ptr).Toke.SetValue((*(*Ptr).pLeft).Toke.GetValue());
				(*Ptr).LeftSideDone = true;
				Ptr = GetLeftMostOperator((*Ptr).pRight);
			}
			else
			{
				(*Ptr).pRight.SetToNull();
				
				Ptr = (*Ptr).pParent;
			}
		pRoot.SetToNull();
		pLastOperator.SetToNull();
	}

	//	Left as an exercise for the student
	}

Variable::ValueType MathTree::Evaluate ()
	{

	if (pRoot)
			{
			WCS_Pointer <Node>		Ptr (GetLeftMostOperator (pRoot));	// Ptr could end up as NULL if tree is only a constant or variable

			while (Ptr)
				if (!(*Ptr).LeftSideDone)
				{
					if ((*Ptr).Toke.GetType() == Token::VariableToken)
					{
						if (!(*Ptr).Toke.isDefined())
						{
							throw Variable::Exception::VariableNotDefinedException;
						}
					}
					else
					{
						(*Ptr).Toke.SetValue((*(*Ptr).pLeft).Toke.GetValue());
						(*Ptr).LeftSideDone = true;
						Ptr = GetLeftMostOperator((*Ptr).pRight);
					}
				}
					else
						{
						if ((*(*Ptr).pRight).Toke.GetType() == Token::VariableToken)
						{
							if (!(*(*Ptr).pRight).Toke.isDefined())
							{
								throw Variable::Exception::VariableNotDefinedException;
							}
						}
						switch ((*Ptr).Toke.GetType ())
							{
							case Token::OperatorPlusToken:
											(*Ptr).Toke.SetValue ((*Ptr).Toke.GetValue () + (*(*Ptr).pRight).Toke.GetValue ());
											break;
							case Token::OperatorMinusToken:
											//	Left as exercise for student
								(*Ptr).Toke.SetValue((*Ptr).Toke.GetValue() - (*(*Ptr).pRight).Toke.GetValue());
								break;
							case Token::OperatorAsteriskToken:
											//	Left as exercise for student
								(*Ptr).Toke.SetValue((*Ptr).Toke.GetValue() * (*(*Ptr).pRight).Toke.GetValue());
								break;
							case Token::OperatorSlashToken:
											//	Left as exercise for student
								if ((*(*Ptr).pRight).Toke.GetValue() == 0)
								{
									throw DivideByZero;
								}
								else
									(*Ptr).Toke.SetValue((*Ptr).Toke.GetValue() / (*(*Ptr).pRight).Toke.GetValue());
								break;
							case Token::OperatorRootToken:
								//	Left as exercise for student
								if ((*(*Ptr).pRight).Toke.GetValue() < 0)
								{
									if ((*Ptr).Toke.GetValue() % 2 == 0)
										throw EvenRootNoNegative;
									else
									{
										(*Ptr).Toke.SetValue( - pow( abs((*(*Ptr).pRight).Toke.GetValue()), 1.0 / (*Ptr).Toke.GetValue()));
									}
								}
								else
									(*Ptr).Toke.SetValue(pow((*(*Ptr).pRight).Toke.GetValue(), 1.0 / (*Ptr).Toke.GetValue()));
								break;
							case Token::OperatorLogToken:
								//	Left as exercise for student
								
								if ((*(*Ptr).pRight).Toke.GetValue() <= 0)
									throw LogCannotLessThanZero;
								(*Ptr).Toke.SetValue(log10((*(*Ptr).pRight).Toke.GetValue())/log10((*Ptr).Toke.GetValue()));
								break;
							default:
								cout << "Internal error 101" << endl;
								exit (0);
							}
						Ptr	= (*Ptr).pParent;
						}
			return (*pRoot).Toke.GetValue ();
			}
		else
			return 0;
	}

WCS_Pointer <MathTree::Node> & MathTree::GetLeftMostOperator (const WCS_Pointer <Node> & pStart)
	{
	WCS_Pointer <Node> Ptr (pStart);

	while ((*Ptr).pLeft)
		{
		(*Ptr).LeftSideDone		= false;
		Ptr						= (*Ptr).pLeft;
		}
	return (*Ptr).pParent;		// if tree only has a constant or variable, we will return NULL
	}




/*		original way we did this in class
MathTree::ResultCode MathTree::InsertBinaryOperator (const Token & T)
	{
	WCS_Pointer <Node>	pNewOperator	(new Node (T));

	if (!pLastOperator)
			{
			(*pRoot).pParent		= pNewOperator;
			(*pNewOperator).pLeft	= pRoot;
			pRoot					= pNewOperator;
			}
		else
			{
			if ((*pLastOperator).Toke.GetPrecedence () < (*pNewOperator).Toke.GetPrecedence ())
					{
					(*pNewOperator).pLeft				= (*pLastOperator).pRight;
					(*(*pNewOperator).pLeft).pParent	= pNewOperator;
					(*pLastOperator).pRight				= pNewOperator;
					(*pNewOperator).pParent				= pLastOperator;
					}
				else
					{	// need to go back up the tree to see where to add the new operator
					while (pLastOperator.Exists () && ((*pLastOperator).Toke.GetPrecedence () >= (*pNewOperator).Toke.GetPrecedence ()))
						pLastOperator = (*pLastOperator).pParent;
					if (pLastOperator.DoesNotExist ())		// we backed all the way out of the tree
							{
							(*pNewOperator).pLeft	= pRoot;
							(*pRoot).pParent		= pNewOperator;
							pRoot					= pNewOperator;
							}
						else
							{
							(*pNewOperator).pLeft				= (*pLastOperator).pRight;
							(*pNewOperator).pParent				= pLastOperator;
							(*(*pLastOperator).pRight).pParent	= pNewOperator;
							(*pLastOperator).pRight				= pNewOperator;
							}
					}
			}
	pLastOperator	= pNewOperator;
	return OK;
	}
*/

			// rewritten to shorten the code
MathTree::ResultCode MathTree::InsertBinaryOperator (const Token & T)
	{
	WCS_Pointer <Node>	pNewOperator	(new Node (T));

	while (pLastOperator && ((*pLastOperator).Toke.GetPrecedence () >= (*pNewOperator).Toke.GetPrecedence ()))
		pLastOperator = (*pLastOperator).pParent;
	if (!pLastOperator)		// we backed all the way out of the tree
			{
			(*pNewOperator).pLeft	= pRoot;
			(*pRoot).pParent		= pNewOperator;
			pRoot					= pNewOperator;
			}
		else
			{		// we are adding a new operator into the middle of the tree
			(*pNewOperator).pLeft				= (*pLastOperator).pRight;
			(*pNewOperator).pParent				= pLastOperator;
			(*(*pLastOperator).pRight).pParent	= pNewOperator;
			(*pLastOperator).pRight				= pNewOperator;
			}
	pLastOperator	= pNewOperator;
	return OK;
	}

MathTree::ResultCode MathTree::InsertOperand (const Token & T)
	{
	WCS_Pointer <Node>	pTemp (new Node (T));

	if (!pRoot)
			pRoot = pTemp;
		else
			{
			(*pLastOperator).pRight		= pTemp;
			(*pTemp).pParent			= pLastOperator;
			}
	return OK;
	}

MathTree::ResultCode MathTree::InsertUnaryOperator (const Token & T)
	{
	Token Temp (Token::ConstantToken, 0);

	InsertOperand (Temp);
	return InsertBinaryOperator (T);
	}
