 /// @date    2018-07-09 18:55:19
 
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
using std::string;
using std::map;
using namespace std;

class Configuration {
	public:
		Configuration(const string & filePath) 
			 :_filePath(filePath) {
			 cout << "Configuration(filePath): " << _filePath << endl;
			 } 
		map<string, string>& getConfigMap();
	private:
		string _filePath;
		map<string,string> _configMap;
};//end of Configuration
#endif
