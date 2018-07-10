 /// @date    2018-07-09 19:53:57
 
#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__
#include "Configuration.h"
#include <vector>
#include <iostream>

class DictProducer {
	public:
		DictProducer(const string &dir);
		void build_dict();
		void show_file();
		void show_dict();
	private:
		void store_dict(const string & fileName);
		void get_file();
	private:
		string _dir;
		map<string, string> _files;
		map<string,int> _dict;
};
#endif
