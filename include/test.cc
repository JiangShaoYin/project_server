 /// @date    2018-07-09 21:48:05
 
#include <iostream>
#include <fstream>
using std::ifstream;
using std::cout;
using std::endl;
#include <string>
using std::string;
 
 
void test1() { 
 string word = "../data/dict.txt";
 ifstream ifs(word);
 if(!ifs)
	 cout << "file open error" << endl;
 string a;
 ifs >> a;
 cout << a;
} 
 
int main(){
	test1();
	return 0;
}
