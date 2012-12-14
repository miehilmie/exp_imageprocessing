#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "rgb.h"
using namespace std;



int main()
{
	fstream f;

	string s;
	f.open("test.txt", fstream::in | fstream::out);
	int row = 5, col = 5;
	RGB **element = new RGB*[row];
	for (int i = 0; i < row; ++i)
	{
		element[i] = new RGB[col];
	}
	for(int cur_row = 0; cur_row < row; ++cur_row) {

		// fetch from file
		getline(f, s);

		istringstream iss(s); // make line into stream string
		int n_count = 0, cur_col = 0;
		string l;

		while(iss >> l) {

			if(n_count%3 == 0) {
				// initiate 
				element[cur_row][cur_col].red = atoi(l.c_str());
			}else if(n_count%3 == 1) {
				element[cur_row][cur_col].green = atoi(l.c_str());
			}
			else { // n_count%3 == 2
				element[cur_row][cur_col].blue = atoi(l.c_str());
				++cur_col;
			}

			n_count++;
		}
	}

	// displaying
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cout << "Row #" << i << endl;
			cout << "Red   : " << element[i][j].red << endl
				 << "Green : " << element[i][j].green << endl
				 << "Blue  : " << element[i][j].blue <<  endl << endl;
		}
	}


	delete [] element;

	f.close();
	return 0;
}
