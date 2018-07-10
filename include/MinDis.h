 /// @date    2018-07-09 14:31:48
 
#ifndef __MINDIS_H__
#define __MINDIS_H__
#include <string>
#include <algorithm>
#include <iostream>
using std::string;
using std::min;
using std::cout;
using std::endl;
int Min(int a, int b, int c) {
	return min(a, b) < c ? min(a,b) :c;
}

class MinDis {
	public:
		MinDis(string str1, string str2):_str1(str1),
										 _str2(str2) {}
		int dis();
	private:
		string _str1;
		string _str2;
};


int MinDis::dis() {
	int const len1 = _str1.size();
	int const len2 = _str2.size();
	int d[33][33]={};
	for(int i = 0; i<=len1; ++i)
		d[i][0] = i;
	for(int j = 0; j<=len1; ++j)
		d[0][j] = j;
	for(int i=1; i<=len1; ++i)
		for(int j=1; j<=len2; ++j){
			int insertion = d[i][j-1] + 1;//在word1后加上word2的最后一个字符，d[i][j-1]==d[i+1][j]
			int desertion = d[i-1][j] + 1;
			int cross = _str1.c_str()[i-1]==_str2.c_str()[j-1] ? d[i-1][j-1] : d[i-1][j-1]+1;
			d[i][j] = Min(insertion, desertion, cross);
		}
	return d[len1][len2];
}
#endif
