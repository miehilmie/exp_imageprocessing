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
struct ImageData
{
	string type;
	int width; 
	int height;
	RGB*  m_img;
	ImageData() {}
	ImageData(const ImageData& cpy) {
		type = cpy.type;
		width = cpy.width;
		height = cpy.height;
		m_img = cpy.m_img;
	}
	~ImageData() {
		// avoid memleak
		delete [] m_img;
	}
};

void extractInput(vector<ImageData*> &output) {
	int size;
	cin >> size;

	for (int cur_tcase = 0; cur_tcase < size; ++cur_tcase)
	{
		string imgtype;
		int width;
		int height;
		RGB* img;

		cin >> imgtype;
		cin >> width;
		cin >> height;

		img = new RGB[height * width];

		for (int c = 0; c < height * width; ++c)
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
			img[c] = temp;
		}
		ImageData* n = new ImageData();
		n->type = imgtype;
		n->height = height;
		n->width = width;
		n->m_img = img;
		output.push_back(n);
	}
}

void displayOutput(vector<ImageData*> img) {
	// displaying
	cout << img.size() << endl << endl;
	for (int tc = 0; tc < img.size(); ++tc)
	{
		cout << img[tc]->type << endl;
		cout << img[tc]->width << endl << img[tc]->height << endl;
		for (int row = 0; row < img[tc]->height; ++row)
		{
			for (int col = 0; col < img[tc]->width; ++col)
			{
				if(col != 0) cout << " ";
				cout << img[tc]->m_img[row*img[tc]->width + col].red << " " 
					 << img[tc]->m_img[row*img[tc]->width + col].green << " "
					 << img[tc]->m_img[row*img[tc]->width + col].blue;
			}
			cout << endl;
		}
	}
}

void meanFilter(ImageData* input, ImageData* &output) {

	int EXT_VALUE = 2;

	int W = input->width;
	int NW = input->width + EXT_VALUE*2;
	int H = input->height;
	int NH = input->height + EXT_VALUE*2;

	RGB* extension = new RGB[(NW) * (NH)];
	
	for (int i = 0; i < H; ++i)
	{
		memcpy(extension + NW * (i+EXT_VALUE) + EXT_VALUE , input->m_img + i * W, W *sizeof(RGB));
	}

	for (int row = 0; row < NH; ++row)
	{
		for (int col = 0; col < NW; ++col)
		{
			if(col != 0) cout << " ";
			cout << extension[row*NW + col].red << " " 
				 << extension[row*NW + col].green << " "
				 << extension[row*NW + col].blue;
		}
		cout << endl;
	}
}


/***
 * File : main.cpp
 * Description : You should run this using ./a.out < 'file' 
 * 'file' is where your input format file
**/
int main(int argv, char** argc) {
	vector<ImageData*> img;
	ImageData* output;

	extractInput(img);
	 meanFilter(img[0], output);
	//displayOutput(img);

	return 0;
}