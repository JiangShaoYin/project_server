 /// @date    2018-07-09 23:47:17
 
#include "../include/DictProducer.h"

DictProducer::DictProducer(const string &dir)	//将文件输出至dir
	:_dir(dir) {
	get_file();
	}

void DictProducer::get_file() {
	Configuration config("../data/conf.txt");
		_files = config.getConfigMap();
#if 0
		auto iter = configMap.begin();
	while(iter != configMap.end()){
		_files.push_back(make_pair(iter->first, iter->second));
		++iter;
	}
#endif
}

void DictProducer::show_file() {
	for(auto& it : _files) {
		cout << it.second << endl;
	}
}

void DictProducer::build_dict() {
	for(auto &it : _files){
		string fileName = it.first;
		ifstream ifs(it.second);
		while(ifs){
			string word;
			ifs >> word;
			if(_dict.find(word)==_dict.end()) 
				_dict.insert(make_pair(word, 1));	
			else 
				++ _dict[word];
		}
		store_dict(fileName);
	}
}

void DictProducer::show_dict() {
	for(auto& it : _dict) {
		cout << it.first << " "
			 << it.second << endl;
	}
}

void DictProducer::store_dict(const string & fileName) {
	stringstream reFileName;
	reFileName << "dict_" << fileName; 
	cout << reFileName.str() << endl;
}

