#pragma once
#include<iostream>
using namespace std;

enum Optype{Num,Lbr,Rbr,BOP,TRI,Min};
enum Operation{NUM,ADD,PLUS,MUL,DIV,LBR,RBR,SIN,COS,TAN,MIN,EXP,LOG};

union Form
{
	Operation operation;
	double num;
};

struct Expression
{
	Optype optype;
	Form form;
};
