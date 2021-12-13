#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

class FileHandler
{
	ifstream fd;
	string fname;
public:
	FileHandler(string filename) : fname(filename)
	{
		fd.open(filename.c_str());
		if (fd.is_open() == false)
		{
			cerr << "Could not open file " << filename << endl;
			exit(1);
		}
		fd.close();
	}
	int countLines()
	{
		fd.open(fname.c_str());
		string line;
		int counter = 0;
		for(;!fd.eof();counter++)
			getline(fd, line);
		fd.close();
		return counter-1;
	}
	string getLine(int n)
	{
		fd.open(fname.c_str());
		string line;
		int counter = 0;
		for(;!fd.eof();counter++)
			if (counter == n)
				break;
			else
				getline(fd, line);
		fd.close();
		return line;
	}
};

#endif /* FILEHANDLER_H_ */
