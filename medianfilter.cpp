#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <math.h>
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

void _medianFilter(RGB* input, ImageData* &output, int w) {

	int W = output->width;
	int EW = output->width + w*2;

	int H = output->height;
	int EH = output->height + w*2;
	for (int row = w; row < EH-w; ++row)
	{
		for (int col = w; col < EW-w; ++col)
		{
			int window_size = 0;

			for(int i = 0; i < w*2 + 1;i++) {
				for(int j = 0; j < w*2 + 1;j++) {
					++window_size;
				}
			}
			RGB *window = new RGB[window_size];
			int k = 0;
			for(int i = row - w; i < row + w + 1; i++) {
				for(int j = col - w; j < col + w + 1; j++) {
					window[k++] = input[i*EW + j];
				}
			}

			// sort window
			int min_red;
			int min_green;
			int min_blue;
			for(int i = 0; i < (int)ceil(window_size/2); ++i) {
				min_red = i;
				min_green = i;
				min_blue = i;
				for(int j = i + 1; j < window_size; ++j) {
					if(window[j].red < window[min_red].red) {
						min_red = j;
					}
					if(window[j].green < window[min_green].green) {
						min_green = j;
					}
					if(window[j].blue < window[min_blue].blue) {
						min_blue = j;
					}
				}
				const int temp_red = window[i].red;
				window[i].red = window[min_red].red;
				window[min_red].red = temp_red;

				const int temp_green = window[i].green;
				window[i].green = window[min_green].green;
				window[min_green].green = temp_green;

				const int temp_blue = window[i].blue;
				window[i].blue = window[min_blue].blue;
				window[min_blue].blue = temp_blue;

			}
			output->m_img[(row - w)*W + (col - w)].red = window[(int)ceil(window_size/2)].red;
			output->m_img[(row - w)*W + (col - w)].green = window[(int)ceil(window_size/2)].green;
			output->m_img[(row - w)*W + (col - w)].blue = window[(int)ceil(window_size/2)].blue;
		}
	}
}

void medianFilter(ImageData* input, ImageData* &output, int w) {

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

	_medianFilter(extension, output , w);
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

	// cout << testcase << endl << endl;
	for (int i = 0; i < testcase; ++i)
	{
		extractInput(img, kernel);
		medianFilter(img, output, kernel);
		displayOutput(output);
		cout << endl;
	}

	return 0;
}