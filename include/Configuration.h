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
			 :_filePath(filePath) {} 
		map<string, string>& getConfigMap();
	private:
		string _filePath;
		map<string,string> _configMap;
};//end of Configuration

map<string, string>& Configuration::getConfigMap() {
	ifstream ifs(_filePath); 
		string line;
	while(getline(ifs, line)) {
		istringstream iss(line);
			string fileName, filePath;
		iss >> fileName;
		iss >> filePath;
		_configMap.insert(make_pair(fileName, filePath));
	}
	return _configMap;
}


#endif
