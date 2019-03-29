#include<iostream>
#include"struct.h"
#include<math.h>
#include<stack>
#include<string>
using namespace std;

int precedence(Operation op1,Operation op2)
{
	if(op1==LBR)
		return -1;
	if(op1 == ADD || op1 == PLUS)
	{
		if(op2 == MUL || op2 == DIV || op2 == SIN ||op2 == COS ||op2 == TAN || op2 == MIN || op2 == EXP ||op2 == LOG)
			return -1;
		else
			return 0;
	}
	if(op1 == MUL || op1 == DIV)
	{
		if(op2 == ADD || op2 == PLUS)
			return 1;
		else if(op2 == SIN ||op2 ==  COS || op2 == TAN || op2 == MIN||op2==EXP||op2==LOG)
			return -1;
		else 
			return 0;
	}
	if(op1 == SIN || op1 == COS || op1 == TAN || op1 == MIN||op1==EXP||op1==LOG)
	{
		if(op2 == SIN || op2 == COS || op2 == TAN || op2 == MIN||op2==EXP||op2==LOG)
			return 0;
		else 
			return 1;
	}
}

int inFix2PostFix(Expression *infix,Expression *postfix,int count)
{
//	for(int t = 0; t < count; t++)
//		cout << infix[t].optype << " ";
//	cout<<endl;

	stack<Expression> st;
	int j = 0;
	for(int i = 0; i < count; i++)
	{
		Operation c = infix[i].form.operation;
		if( c == LBR)
			st.push(infix[i]);
		else if(c == RBR)
		{
			while(st.top().form.operation != LBR)
			{
				postfix[j] = st.top();
				j++;
				st.pop();
			}
			st.pop();
		}
		else if(c == NUM)
		{
			postfix[j] = infix[i];
			//cout<< j <<endl;
			j++;
		}
		else if(c == SIN||c == COS ||c == TAN || c == MIN||c==EXP||c==LOG)
			st.push(infix[i]);
		else 
		{
			while(st.empty()==false && precedence(st.top().form.operation,c)>= 0)
			{
				postfix[j] = st.top();
				j++;
				st.pop();
			}
			st.push(infix[i]);
		}
	}
	while(st.empty()==false)
	{
		postfix[j] = st.top();
		j++;
		st.pop();
	}

//	for(int t = 0; t < j; t++)
//		cout<< postfix[t].optype<<" ";
//	cout<< endl;
	return j;	
}
double postcalculate(Expression *postfix,int count)
{
	stack<double> sp;
	for(int i = 0; i < count; i++)
	{
		if(postfix[i].optype == Num)
		{
//			cout<<postfix[i].form.num<<endl;
			sp.push(postfix[i].form.num);
//			cout<<st.top()<<" ";
		}
		else if(postfix[i].optype == TRI || postfix[i].optype == Min)
		{
			double temp = sp.top();
			sp.pop();
			if(postfix[i].form.operation == SIN)
				temp = sin(temp);
			else if(postfix[i].form.operation == COS)
				temp = cos(temp);
			else if(postfix[i].form.operation == TAN)
				temp = tan(temp);
			else if(postfix[i].form.operation == MIN)
				temp = -temp;
			else if(postfix[i].form.operation == EXP)
				temp = exp(temp);
			else if(postfix[i].form.operation == LOG)
				temp = log(temp);
			sp.push(temp);
		}
		else if(postfix[i].optype == BOP)
		{
			double temp1 = sp.top();
			sp.pop();
			double temp2 = sp.top();
			//cout<<temp2<<","<<temp1<<endl;
			sp.pop();
			Operation m = postfix[i].form.operation;
			if(m == ADD)
				temp1 = temp2+temp1;
			else if(m == PLUS)
				temp1 = temp2-temp1;
			else if(m == MUL)
				temp1 = temp2*temp1;
			else if(m == DIV)
				temp1 = temp2/temp1;
			sp.push(temp1);
		}
	}
//	cout<<st.top()<<endl;
	return sp.top();

}
