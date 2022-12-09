#include <stdio.h>
#include "pbPlots.h"
#include "supportLib.h"

int main(){
	double xs [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
	double ys [] = {0, 80, 46, 123, 88, 165, 130, 207, 172, 249, 214, 255, 255, 255, 225, 217, 188, 179, 151, 141, 113, 105, 75, 68, 37, 31, 0};

	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	DrawScatterPlot(canvasReference, 600, 400, xs, 29, ys, 29);

	size_t length;
	double *pngdata = ConvertToPNG(&length, canvasReference->image);
	WriteToFile(pngdata, length, "example1.png");
	DeleteImage(canvasReference->image);

	return 0;
}