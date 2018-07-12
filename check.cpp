#include"function_declare.h"

bool checkColor(Mat * img, Point2i &center, double r_d,double proportion)
{
	double dx;
	double dy;
	double d;

	int channel = img->channels();
	if (channel != 3)
		return false;

	int x = center.x;
	int y = center.y;
	int r = (int)(r_d + 0.5);

	unsigned long time = 0;

	for (int i = (y - r) > 0 ? (y - r) : 0; ((i < y + r) && (i < img->rows)); i++)
	{
		for (int j = (x - r)>0 ? (x - r) : 0; ((j < x + r) && (j<img->cols)); j++)
		{
			dx = abs(x - j);
			dy = abs(y - i);
			d = sqrt(dx*dx + dy*dy);

			if (d < r_d) {
				unsigned char* srcData = img->ptr(i);

				
				if ((srcData[3 * j + 2] - srcData[3 * j] <= maxR_B)&(srcData[3 * j + 2] - srcData[3 * j] >= minR_B))
					if ((srcData[3 * j + 1] - srcData[3 * j] <= maxG_B)&(srcData[3 * j + 1] - srcData[3 * j] >= minG_B))
						if ((srcData[3 * j] >= minB)&(srcData[3 * j] <= maxB))
							if ((srcData[3 * j + 1] >= minG)&(srcData[3 * j + 2] <= maxG))
								if ((srcData[3 * j + 2] >= minR)&(srcData[3 * j + 2] <= maxR))
								{
									time++;
								}
			}

		}
	}

	if (time >= proportion*pi*r*r)
	{
		return true;
	}

	return false;
}