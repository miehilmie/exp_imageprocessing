#ifndef IMAGERY_H
#define IMAGERY_H
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "rgb.h"
/***
* Class : Imagery
* Description : This class is used to store array image extracted from file
*/
class Imagery
{

	RGB** m_element;

	int m_rowsize;
	int m_colsize;

	int m_testcase;

	string m_imgtype;
	public:
	void LoadFromFile(string pathtofile) {
		fstream f;
		string s;
		f.open(pathtofile.c_str(), fstream::in | fstream::out);

		// get first line : image type
		string line;
		getline(f, line);
		m_testcase = atoi(line.c_str());

		// second line : empty
		getline(f, line);

		// third line : type
		getline(f, m_imgtype);

		// fourth line : column / width
		getline(f, line);
		m_colsize = atoi(line.c_str());

		// fifth line : row / height
		getline(f, line);
		m_rowsize = atoi(line.c_str());

		m_element = new RGB*[m_colsize];
		for (int i = 0; i < m_colsize; ++i)
		{
			m_element[i] = new RGB[m_colsize];
		}
		for(int cur_row = 0; cur_row < m_rowsize; ++cur_row) {

		// fetch from file
			getline(f, s);

			istringstream iss(s); // make line into stream string
			int col_count = 0, cur_col = 0;
			string l;

			while(iss >> l && cur_col < m_colsize) {

				if(col_count%3 == 0) {
					// initiate 
					m_element[cur_row][cur_col].red = atoi(l.c_str());
				}else if(col_count%3 == 1) {
					m_element[cur_row][cur_col].green = atoi(l.c_str());
				}
				else { // n_count%3 == 2
					m_element[cur_row][cur_col].blue = atoi(l.c_str());
					++cur_col;
				}

				col_count++;
			}
		}
		f.close();
	}

	void DisplayImage() {

		for (int i = 0; i < m_rowsize; ++i)
		{
			for (int j = 0; j < m_colsize; ++j)
			{
				cout << "Row #" << i << endl;
				cout << "Red   : " << m_element[i][j].red << endl
					 << "Green : " << m_element[i][j].green << endl
					 << "Blue  : " << m_element[i][j].blue <<  endl << endl;
			}
		}
	}

	~Imagery() {
		delete [] m_element;
	}
};

#endif