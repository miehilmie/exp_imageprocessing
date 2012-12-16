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

	int neighbour;
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

/***
 * Fn: extractInput
 * Params: output - imagedata from file
                w - kernel value (specifically for meanfilter)
 */
void extractInput(ImageData* &output, int &w) {
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
		

		// get kernel value
		cin >> w;
		output = n;
}

void displayOutput(ImageData* img) {
	// displaying
	cout << img->type << endl;
	cout << img->width << endl << img->height << endl;
	for (int row = 0; row < img->height; ++row)
	{
		for (int col = 0; col < img->width; ++col)
		{
			if(col != 0) cout << " ";
			cout << img->m_img[row*img->width + col].red << " " 
				 << img->m_img[row*img->width + col].green << " "
				 << img->m_img[row*img->width + col].blue;
		}
		cout << endl;
	}
}

void displayOutput(ImageData* img, int kernel) {
	// displaying
	cout << img->type << endl;
	cout << img->width << endl << img->height << endl;
	for (int row = 0; row < img->height; ++row)
	{
		for (int col = 0; col < img->width; ++col)
		{
			if(col != 0) cout << " ";
			cout << img->m_img[row*img->width + col].red << " " 
				 << img->m_img[row*img->width + col].green << " "
				 << img->m_img[row*img->width + col].blue;
		}
		cout << endl;
	}
	cout << kernel << endl;
}

void _meanFilter(RGB* input, ImageData* &output, int w) {

	int W = output->width;
	int EW = output->width + w*2;

	int H = output->height;
	int EH = output->height + w*2;

	for (int row = 0; row < H; ++row)
	{
		for (int col = 0; col < W; ++col)
		{
			int sum_red = 0;
			int sum_blue = 0;
			int sum_green = 0;
			int count = 0;
			for(int sum_row = -w; sum_row <= w; ++sum_row) {
				for (int sum_col = -w; sum_col <= w; ++sum_col)
				{
					sum_red += input[EW*(row + w + sum_row) + (col + w + sum_col)].red;
					sum_green += input[EW*(row + w + sum_row) + (col + w + sum_col)].green;
					sum_blue += input[EW*(row + w + sum_row) + (col + w + sum_col)].blue;
					count++;
				}
			}
			output->m_img[row*W + col].red = sum_red/count;
			output->m_img[row*W + col].green = sum_green/count;
			output->m_img[row*W + col].blue = sum_blue/count;
		}
	}
}

void meanFilter(ImageData* input, ImageData* &output, int w) {

	int EXT_VALUE = w;

	int W = input->width;
	int NW = input->width + EXT_VALUE*2;
	int H = input->height;
	int NH = input->height + EXT_VALUE*2;

	RGB* extension = new RGB[(NW) * (NH)];

	// copy output from input
	output = new ImageData(*input);

	for (int i = 0; i < H; ++i)
	{
		memcpy(extension + NW * (i+EXT_VALUE) + EXT_VALUE , input->m_img + i * W, W *sizeof(RGB));

		// ---> OUT OF BOUND HANDLER = LEFT RIGHT
		for (int ext = 0; ext < EXT_VALUE; ++ext)
		{
			extension[NW * (i+EXT_VALUE) + ext] = input->m_img[i*W + (EXT_VALUE - 1 - ext)]; 
			extension[NW * (i+EXT_VALUE) + NW - 1 - ext] = input->m_img[i*W + W - 1 - (EXT_VALUE - 1 - ext)]; 
		}
	}

	// ---> OUT OF BOUND HANDLER = TOP BTM
	// reflection
	for (int ext = 0; ext < EXT_VALUE; ++ext)
	{
		memcpy(extension + ext * NW, extension + (EXT_VALUE*2 - 1 - ext) * NW, NW*sizeof(RGB));
		memcpy(extension + (NH - EXT_VALUE + ext) * NW, extension + (NH - EXT_VALUE - 1 - ext) * NW, NW*sizeof(RGB));
	}

	_meanFilter(extension, output , w);
}


/***
 * File : main.cpp
 * Description : You should run this using ./a.out < 'file' 
 * 'file' is your input format file
**/
int main(int argv, char** argc) {
	ImageData*img;
	ImageData* output;

	int testcase;
	int kernel;
	cin >> testcase;

	cout << testcase << endl << endl;
	for (int i = 0; i < testcase; ++i)
	{
		extractInput(img, kernel);
		meanFilter(img, output, kernel);
		displayOutput(output, kernel);
		cout << endl;
	}

	return 0;
}