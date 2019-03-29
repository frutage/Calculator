#include<iostream>
#include<iomanip>
#include<string>
#include"struct.h"
#include"analyze.h"
#include"calculate.h"
#include<fstream>
#define MAX 100
using namespace std;

Expression expression[MAX];
Expression postfix[MAX];
string s1;
string s2;
string s3;
string s4;
string s5;

double save_result(double result)
{
	ofstream outfile("result.txt",ios::out);
	outfile << fixed << setprecision(8) << result;
	//cout << "" << endl;
	outfile.close();
} 
int main()
{
        int time = 0;
	s1=  "sinpi+cos-pi",s2 = "(1+2*78-sin(pi/2)";
        s3 = "1+3 2 *3",s4 = "-9*sin3";
        s5 = "2pi";


	cout<<"            welcome to calculator  "<<endl;
	cout<<"            print 'quit' to leave"<<endl;
	cout<<"      use 'ans' to save result in last turn"<<endl;
	cout<<"      print 'list' to see the last five exressions"<<endl;
        while(time < 100)
        {
	cout<<endl;
        cout<<"输入表达式：";
        string str;
        getline(cin,str);

        int nsize = str.size();
        for(int j = 0; j < nsize;)
        {
                if(str[j] == ' ')
                        str.erase(j,1);
                else    
                        j++;
		if(str[j]>='A'&&str[j]<='Z')
			str[j] = str[j]+'a'-'A';
                nsize = str.size();
        }
	//cout<<str<<endl;

        while(str!="quit"&& str!="list" && !is_legal(str))
        {
		cout<<endl;
                cout<<"输入表达式：";
                getline(cin,str);
		if(str=="quit") break;
		int msize = str.size();
		for(int j = 0; j < msize; )
		{
			if(str[j]==' ')
				str.erase(j,1);
			else
				j++;
			if(str[j]>='A'&&str[j]<='Z')
				str[j] = str[j]+'a'-'A';
			msize = str.size();
		}
	}
        if(str=="quit")
                 break;
	else if(str=="list")
	{
		cout<<s1<<endl;
		cout<<s2<<endl;
		cout<<s3<<endl;
		cout<<s4<<endl;
		cout<<s5<<endl;
	}
	else
	{
		s1 = s2;
		s2 = s3;
		s3 = s4;
		s4 = s5;
		s5 = str;
        	int count = Parse(str,expression);
        	int length = inFix2PostFix(expression,postfix,count);
        	double result = 0;
        	result = postcalculate(postfix,length);
		save_result(result);
        	cout<< "计算结果:"<< fixed<< setprecision(8)<< result<<endl;
        }
	}
        return 0;
}


