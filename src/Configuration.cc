 /// @date    2018-07-10 10:52:13
#include "Configuration.h" 

map<string, string>& Configuration::getConfigMap() {
	ifstream ifs(_filePath); 
	if(!ifs)
		cout << "ifs error" << endl;
	string line;
	while(getline(ifs, line)) {
		istringstream iss(line);
			string fileName, filePath;
		iss >> fileName;//	cout << fileName << endl;
		iss >> filePath;
		_configMap.insert(make_pair(fileName, filePath));
	}
	return _configMap;
}


