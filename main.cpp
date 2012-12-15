#include <iostream>
#include <vector>
#include <string>
#include <cstring>
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
struct ImageData
{
	int size; // test case
	vector<string> m_imgtype;			// all related to test case index
	vector<Dimension> m_imgdimension;   // all related to test case index
	vector<RGB**>  m_img;               // all related to test case index
	ImageData() {}
	ImageData(const ImageData& cpy) {
		size = cpy.size;
		m_imgtype = cpy.m_imgtype;
		m_imgdimension = cpy.m_imgdimension;
		m_img = cpy.m_img;
	}
	~ImageData() {
		// avoid memleak
		for (int i = 0; i < size; ++i)
		{
			for(int	j = 0; j < m_imgdimension[i].height; j++) {
				delete [] m_img[i][j];
			}
			delete [] m_img[i];
		}
	}
};

void extractInput(ImageData* &output) {
	cin >> output->size;

	for (int cur_tcase = 0; cur_tcase < output->size; ++cur_tcase)
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
		output->m_imgtype.push_back(imgtype);
		output->m_imgdimension.push_back(imgdimension);
		output->m_img.push_back(img);
	}
}

void displayOutput(ImageData* img) {
	// displaying
	cout << img->size << endl << endl;
	for (int tc = 0; tc < img->size; ++tc)
	{
		cout << img->m_imgtype[tc] << endl;
		cout << img->m_imgdimension[tc].width << endl << img->m_imgdimension[tc].height << endl;
		for (int i = 0; i < img->m_imgdimension[tc].height; ++i)
		{
			for (int j = 0; j < img->m_imgdimension[tc].width; ++j)
			{
				if(j != 0) cout << " ";
				cout << img->m_img[tc][i][j].red << " " << img->m_img[tc][i][j].green << " " << img->m_img[tc][i][j].blue;
			}
			cout << endl;
		}
	}
}

void meanFilter(ImageData* input, ImageData* &output) {
	ImageData* extension = new ImageData(*input);
	int EXT_VALUE = 2;

	for (int i = 0; i < input->size; ++i)
	{
		extension->m_imgdimension[i].width += EXT_VALUE*2;
		extension->m_imgdimension[i].height += EXT_VALUE*2;

		RGB** image = new RGB*[extension->m_imgdimension[i].height];
		for (int j = 0; j < input->m_imgdimension[i].height; ++j)
		{
			image[j] = new RGB[extension->m_imgdimension[i].width];
			memcpy(image[j] + EXT_VALUE, input->m_img[i][j], sizeof(input->m_img[i][j]));
			for (int v = 0; v < EXT_VALUE; ++v)
			{
				// left = v
				
				//right
			}
		}
		cout << image[0][0].red;


	}

}


/***
 * File : main.cpp
 * Description : You should run this using ./a.out < 'file' 
 * 'file' is where your input format file
**/
int main(int argv, char** argc) {
	ImageData* img = new ImageData();
	ImageData* output;

	extractInput(img);
	meanFilter(img, output);
	// displayOutput(img);

	delete img;
	return 0;
}