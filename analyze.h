#include<iostream>
#include"struct.h"
#include<stack>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<fstream>
using namespace std;

int realnum(string s,int n)
{ 
	int Numdot = 0;
	int i = n;
	while((s[i]>='0'&&s[i]<='9')||s[i]=='.')
	{
		i++;
		if(s[i]=='.')
			Numdot++;
		if(Numdot > 1) break;
	}
	return i;
}

bool is_legal(string s)
{
	int nsize = s.size();
	int Lnum = 0,Rnum = 0;
	char s1 = s[0];

	nsize = s.size();

	ifstream infile("result.txt",ios::in);
	if(infile.is_open())
	{
		int b = 0;
		string ans;
		infile >> ans;
	        for(int b = 0; b < nsize-2; b++)
	        {
        	        if(s[b]=='a'&& s[b+1]=='n'&& s[b+2]=='s')
			{
			//	cout<<b<<endl;
				if(b==0 || (b >0&&s[b-1]!='t'))
				{
                	        s.replace(b,3,ans);
				nsize = s.size();
				}
			}
		}
	}
//	cout<<s<<endl;

			
	int a = 0;
	for(a = 0;a <nsize;)
	{
		if(s[a]=='+'||s[a]=='-'||s[a]=='*'||s[a]=='/'||s[a]=='('||s[a]==')')
			a++;
		else if(s[a]=='s'||s[a]=='c'||s[a]=='t')
			a+=3;
		else if(s[a]=='p')
			a+=2;
		else if(s[a]>='0'&&s[a]<='9')
			a = realnum(s,a);
		else if(s[a]=='e'||s[a]=='l')
			a+=3;
	//	else if(s[a]=='s'&& a<nsize-1)
	//	{
	//		if(s[a+1]=='i')
	//			a+=3;
	//		else if(s[a+1]=='q')
	//			a+=4;
	//		else break;
	//	}
		else break;
	}
	if(a != nsize)
	{
		cout<<s.substr(0,a);
		fprintf(stdout,"\033[31m\033[1m");
		cout<<s[a];
		fprintf(stdout,"\033[0m");
		cout<<s.substr(a+1,nsize-a-1)<<endl;
		cout<<"error:出现未知的符号"<<endl;
		return false;
	}

	if(s1 == '+'||s1 == '*'||s1 == '/')
	{
		fprintf(stdout,"\033[31m\033[1m");
		cout<<s[0];
		fprintf(stdout,"\033[0m");
		string st = s.substr(1,nsize-1);
		cout<<st<<endl;
		cout<<"error:表达式以不合理的操作符开头"<<endl;
		return false;
	}
	for(int i = 0; i < nsize; )
	{ 
		if(s[i] == '(')
			Lnum++;
		else if(s[i] == ')')
			Rnum++;
		if(Lnum < Rnum)
		{
			cout<< s.substr(0,i);
			fprintf(stdout,"\033[31m\033[1m");
			cout<<s[i];
			fprintf(stdout,"\033[0m");
			cout<<s.substr(i+1,nsize-i-1)<<endl;;
			cout<<"error:左右括弧不匹配"<<endl;
			return false;
		}
		s1 = s[i];
		if(s1 == 'p'&& i < nsize-1 && s[i+1]!='i'&& i-1>=0 && s[i-1]!='x')
		{
			cout<< s.substr(0,i);
			fprintf(stdout,"\033[31m\033[1m");
			cout<<s.substr(i,2);
			fprintf(stdout,"\033[0m");
			cout<< s.substr(i+2,nsize-i-2)<<endl;
			cout<<"error:疑似常数pi输入错误"<<endl;
			return false;
		}
		if(i+3 < nsize && (s1 == 's'||s1 == 'c'|| s1 == 't'))
		{
			string temp = s.substr(i,3);
			//cout<<i<<endl;
			//cout<<temp<<endl;
			if(temp == "sin" || temp == "cos" ||temp == "tan")
			{
				if(s[i+3] == ')'||s[i+3] == '+'||s[i+3]=='*'||s[i+3]=='/')
				{
					cout<<s.substr(0,i+3);
					fprintf(stdout,"\033[31m\033[1m");
					cout<<s[i+3];
					fprintf(stdout,"\033[0m");
					cout<<s.substr(i+4,nsize-i-4)<<endl;
					cout<<"error:三角函数之后出现不合理的操作符"<<endl;
					return false;
				}
				if(i>=1 && ((s[i-1] >='0' && s[i-1] <='9')||s[i-1]=='i'))
				{
					cout<<s.substr(0,i-1);
					fprintf(stdout,"\033[31m\033[1m");
					cout<<s.substr(i-1,4);
					fprintf(stdout,"\033[0m");
					cout<<s.substr(i+3,nsize-i-3)<<endl;
					cout<<"error:三角函数之前出现实数，疑似缺少乘号"<<endl;
					return false;
				}
			}
			else
			{
				cout<<s.substr(0,i);
				fprintf(stdout,"\033[31m\033[1m");
				cout<<s.substr(i,3);
				fprintf(stdout,"\033[0m");
				cout<<s.substr(i+3,nsize-i-3)<<endl;
				cout <<"error:三角函数名疑似错误"<<endl;
				return false;
			}
			if(i+3 != nsize-1)
				i+=2;
		}
                else if(i+3 < nsize && (s1 == 'e'||s1 == 'l'))
                {
                        string temp = s.substr(i,3);
                        //cout<<i<<endl;
                        //cout<<temp<<endl;
                        if(temp == "exp")
                        {
                                if(s[i+3] == ')'||s[i+3] == '+'||s[i+3]=='*'||s[i+3]=='/')
                                {
                                        cout<<s.substr(0,i+3);
                                        fprintf(stdout,"\033[31m\033[1m");
                                        cout<<s[i+3];
                                        fprintf(stdout,"\033[0m");
                                        cout<<s.substr(i+4,nsize-i-4)<<endl;
                                        cout<<"error:exp之后出现不合理的操作符"<<endl;
                                        return false;
                                }
                                if(i>=1 && ((s[i-1] >='0' && s[i-1] <='9')||s[i-1]=='i'))
                                {
                                        cout<<s.substr(0,i-1);
                                        fprintf(stdout,"\033[31m\033[1m");
                                        cout<<s.substr(i-1,4);
                                        fprintf(stdout,"\033[0m");
                                        cout<<s.substr(i+3,nsize-i-3)<<endl;
                                        cout<<"error:exp之前出现实数，疑似缺少乘号"<<endl;
                                        return false;
                                }
                        }
                        else if(temp == "log")
                        {
                                if(s[i+3] == ')'||s[i+3] == '+'||s[i+3]=='*'||s[i+3]=='/')
                                {
                                        cout<<s.substr(0,i+3);
                                        fprintf(stdout,"\033[31m\033[1m");
                                        cout<<s[i+3];
                                        fprintf(stdout,"\033[0m");
                                        cout<<s.substr(i+4,nsize-i-4)<<endl;
                                        cout<<"error:log之后出现不合理的操作符"<<endl;
                                        return false;
                                }
                                if(i>=1 && ((s[i-1] >='0' && s[i-1] <='9')||s[i-1]=='i'))
                                {
                                        cout<<s.substr(0,i-1);
                                        fprintf(stdout,"\033[31m\033[1m");
                                        cout<<s.substr(i-1,4);
                                        fprintf(stdout,"\033[0m");
                                        cout<<s.substr(i+3,nsize-i-3)<<endl;
                                        cout<<"error:log之前出现实数，疑似缺少乘号"<<endl;
                                        return false;
                                }
                        }

                        else if(s1='e'&&temp !="exp")
                        {
                                cout<<s.substr(0,i);
                                fprintf(stdout,"\033[31m\033[1m");
                                cout<<s.substr(i,3);
                                fprintf(stdout,"\033[0m");
                                cout<<s.substr(i+3,nsize-i-3)<<endl;
                                cout <<"error:exp疑似错误"<<endl;
                                return false;
                        }
                        else if(s1='l'&&temp !="log")
                        {
                                cout<<s.substr(0,i);
                                fprintf(stdout,"\033[31m\033[1m");
                                cout<<s.substr(i,3);
                                fprintf(stdout,"\033[0m");
                                cout<<s.substr(i+3,nsize-i-3)<<endl;
                                cout <<"error:log疑似错误"<<endl;
                                return false;
                        }

                        if(i+3 != nsize-1)
                                i+=2;
                }
		else if(s1 == '(')
		{
			if(i>= 1 &&( (s[i-1]>='0' && s[i-1]<='9')||s[i-1]=='i'))
			{
				cout<<s.substr(0,i);
				fprintf(stdout,"\033[31m\033[1m");
				cout<<s[i];
				fprintf(stdout,"\033[0m");
				cout<<s.substr(i+1,nsize-i-1)<<endl;
				cout<<"error:左括弧之前出现实数,疑似缺少乘号"<<endl;
				return false;
			}
			if(i < nsize-1 && (s[i+1]==')'||s[i+1]=='+'||s[i+1]=='*'||s[i+1]=='/'))
			{
				cout<<s.substr(0,i+1);
				fprintf(stdout,"\033[31m\033[1m");
				cout<<s[i+1];
				fprintf(stdout,"\033[0m");
				cout<<s.substr(i+2,nsize-i-2)<<endl;
				cout<<"error:左括弧之后出现不合理的操作符"<<endl;
				return false;
			}
		}
		else if(s1 == ')' && i < nsize-1 )
		{
			if(s[i+1]=='('||s[i+1]=='s'||s[i+1]=='c'||s[i+1]=='t')
			{
				cout<<s.substr(0,i+1);
				fprintf(stdout,"\033[31m\033[1m");
				cout<<s[i+1];
				fprintf(stdout,"\033[0m");
				cout<<s.substr(i+2,nsize-i-2)<<endl;
				cout<<"error:右括弧之后出现不合理的操作符"<<endl;
				return false;
			}
			if((s[i+1]>='0'&&s[i+1]<='9')||s[i+1]=='p')
			{
                                cout<<s.substr(0,i);
                                fprintf(stdout,"\033[31m\033[1m");
                                cout<<s[i];
                                fprintf(stdout,"\033[0m");
                                cout<<s.substr(i+1,nsize-i-1)<<endl;
				cout<<"error:右括弧之后出现实数，疑似缺少乘号"<<endl;
				return false;
			}
		}
		else if((s1 == '+'||s1 == '-'||s1 == '*'||s1 == '/') && i < nsize-1)
		{
			if(s[i+1] == ')')
			{
                                cout<<s.substr(0,i+1);
                                fprintf(stdout,"\033[31m\033[1m");
                                cout<<s[i+1];
                                fprintf(stdout,"\033[0m");
                                cout<<s.substr(i+2,nsize-i-2)<<endl;
				cout<<"error:操作符之后出现右括弧"<<endl;
				return false;
			}
			else if(s[i+1] == '+'||s[i+1] =='-'||s[i+1] == '*'||s[i+1] == '/')
			{
                                cout<<s.substr(0,i+1);
                                fprintf(stdout,"\033[31m\033[1m");
                                cout<<s[i+1];
                                fprintf(stdout,"\033[0m");
                                cout<<s.substr(i+2,nsize-i-2)<<endl;
				cout<<"error:操作符之后出现操作符"<<endl;
				return false;
			}
		}
		else if(s1>='0'&&s1<='9')
		{
			i = realnum(s,i);
			if(i!= s.size() && s[i] == 'p')
			{
                                cout<<s.substr(0,i);
                                fprintf(stdout,"\033[31m\033[1m");
                                cout<<s.substr(i,2);
                                fprintf(stdout,"\033[0m");
                                cout<<s.substr(i+2,nsize-i-2)<<endl;
				cout<<"error:实数之后出现实数，疑似缺少乘号"<<endl;
				return false;
			}
			else if(i != s.size() && s[i] == '.')
			{
                                cout<<s.substr(0,i);
                                fprintf(stdout,"\033[31m\033[1m");
                                cout<<s[i];
                                fprintf(stdout,"\033[0m");
                                cout<<s.substr(i+1,nsize-i-1)<<endl;
				cout<<"不合法的小数点"<<endl;
			return false;
			}
			i--;
		}
		i++;
	}

	if(Lnum != Rnum)
	{
		cout<<"error:左右括弧不匹配"<<endl;
		return false;
	}
	if(s[nsize-1]!='i'&&s[nsize-1]!=')'&&!(s[nsize-1]>='0'&&s[nsize-1]<='9'))
	{
		cout<<"error:表达式结尾输入不合理"<<endl;
		return false;
	}

	return true;
}
int Parse(string s,Expression *expression)
{
	int nsize = s.size();
	if(s[0] == '-')
		s[0] = '_';

	for(int i = 0; i < nsize;i++)
	{
		if(s[i] =='-')
		{
			if(i-3>= 0)
			{
				string temp = s.substr(i-3,3);
				if(temp == "sin"||temp == "cos"||temp =="tan")
					s[i] = '_';
			}
			if(i>=1 && s[i-1] == '(')
				s[i] = '_';
		}
	}

        ifstream infile("result.txt",ios::in);
        if(infile.is_open())
        {
                int b = 0;
                string ans;
                infile >> ans;

                for(int b = 0; b < nsize-2; b++)
                {
                        if(s[b]=='a'&& s[b+1]=='n'&& s[b+2]=='s')
                        {
				if(b==0 ||(b>0 && s[b-1]!='t'))
				{
                                s.replace(b,3,ans);
                                nsize = s.size();
				}
                        }
                }
        }

	for(int i = 0; i < nsize-1; i++)
	{
		if(s[i] == 'p' && s[i+1] == 'i')
		{
			s = s.replace(i,2,"3.1415926535897");
			nsize = s.size();
		}
	}

//	cout<<s<<endl;

	int count = 0;
	int msize = s.size();
	for(int i = 0; i < msize; i++)
	{
		switch(s[i])
		{
		case '+':{
			expression[count].optype = BOP;
			expression[count].form.operation = ADD;};break;
		case '-':{
			expression[count].optype = BOP;
			expression[count].form.operation = PLUS;};break;
		case '*':{
			expression[count].optype = BOP;
			expression[count].form.operation = MUL;};break;
		case '/':{
			expression[count].optype = BOP;
			expression[count].form.operation = DIV;};break;
		case '_':{
			expression[count].optype = Min;
			expression[count].form.operation = MIN;};break;
		case '(':{
			expression[count].optype = Lbr;
			expression[count].form.operation = LBR;};break;
		case ')':{
			expression[count].optype = Rbr;
			expression[count].form.operation = RBR;};break;
		case 's':{
			expression[count].optype = TRI;
			expression[count].form.operation = SIN;
			i+=2;};break;
		case 'c':{
			expression[count].optype = TRI;
			expression[count].form.operation = COS;
			i+=2;};break;
		case 't':{
			expression[count].optype = TRI;
			expression[count].form.operation = TAN;
			i+=2;};break;
		case 'e':{
			expression[count].optype = TRI;
			expression[count].form.operation = EXP;
			i+=2;};break;
		case 'l':{
			expression[count].optype = TRI;
			expression[count].form.operation = LOG;
			i+=2;};break;
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8': case '9':{
			expression[count].optype = Num;
			int j = realnum(s,i);
			string number = s.substr(i,j-i);
			i = j-1;
//			cout<<number.c_str()<<endl;
			expression[count].form.num = strtod(number.c_str(),NULL);
//			cout<< expression[count].form.num<<endl;
		    expression[count].form.operation = NUM;};break;
		default:;
		}
		count++;
	}
	return count;

}


