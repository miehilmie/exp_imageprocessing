#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define MAX_CHANNEL 3

struct RGB {
	int red;
	int green;
	int blue;
};
struct Dimension {
	int height;
	int width;
};

/***
 * File : main.cpp
 * Description : You should run this using ./a.out < 'file' 
 * 'file' is where your input format file
**/
int main(int argv, char** argc) {
	string s_temp;
	int m_testcase;
	vector<string> m_imgtype;			// all related to test case index
	vector<Dimension> m_imgdimension;   // all related to test case index
	vector<RGB**>  m_img;               // all related to test case index

	cin >> m_testcase;
	for (int cur_tcase = 0; cur_tcase < m_testcase; ++cur_tcase)
	{
		string imgtype;
		Dimension imgdimension;
		RGB** img;

		cin >> imgtype;
		cin >> imgdimension.width;
		cin >> imgdimension.height;

		img = new RGB*[imgdimension.height];

		for (int i = 0; i < imgdimension.height; ++i)
		{
			img[i] = new RGB[imgdimension.width];
		}

		for (int cur_row = 0; cur_row < imgdimension.height; ++cur_row)
		{
			for (int cur_col = 0; cur_col < imgdimension.width; ++cur_col)
			{
				RGB temp;
				for(int channel = 0; channel < MAX_CHANNEL; ++channel)
				{
					int input;
					cin >> input;
					if(channel%MAX_CHANNEL == 0)
					{
						temp.red = input;
					}
					else if(channel%MAX_CHANNEL == 1)
					{
						temp.green = input;
					}
					else
					{
						temp.blue = input;
					}
				}
				img[cur_row][cur_col] = temp;
			}
		}

		m_imgtype.push_back(imgtype);
		m_imgdimension.push_back(imgdimension);
		m_img.push_back(img);

	}
	cout << m_testcase << endl << endl;
	// displaying
	for (int tc = 0; tc < m_testcase; ++tc)
	{
		cout << m_imgtype[tc] << endl;
		cout << m_imgdimension[tc].width << endl << m_imgdimension[tc].height << endl;
		for (int i = 0; i < m_imgdimension[tc].height; ++i)
		{
			for (int j = 0; j < m_imgdimension[tc].width; ++j)
			{
				if(j != 0) cout << " ";
				cout << m_img[tc][i][j].red << " " << m_img[tc][i][j].green << " " << m_img[tc][i][j].blue;
			}
			cout << endl;
		}
	}


	// avoid memleak
	for (int i = 0; i < m_testcase; ++i)
	{
		for(int	j = 0; j < m_imgdimension[i].height; j++) {
			delete [] m_img[i][j];
		}
		delete [] m_img[i];
	}


	
	// getline(cin, line);
	// getline(cin, x);
	return 0;
}