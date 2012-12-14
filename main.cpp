#include "imagery.h"

int main()
{
	Imagery *img = new Imagery();
	img->LoadFromFile("test.txt");
	// displaying

	img->DisplayImage();

	delete img;

	return 0;
}
