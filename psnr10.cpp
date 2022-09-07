#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void main(int argc, char* argv[])
{
	int w, h, f, b;
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	b = atoi(argv[3]);

	FILE *fin1 = NULL, *fin2 = NULL;
	unsigned char *org0;
	unsigned short *org1, *org2;
    int heightU = (int)(h * 1.25);
    int heightV = (int)(h * 1.5);
	int sizeY = (int)(w * h);
	int sizeYU = (int)(w * heightU);
    int sizeYUV = (int)(w * heightV);
	int place;
	double err = 0, mse = 0, psnrY = 0, psnrU = 0, psnrV = 0, apsnrY = 0, apsnrU = 0, apsnrV = 0;

	fin1 = fopen(argv[4], "rb");
	fin2 = fopen(argv[5], "rb");

	org0 = (unsigned char *)malloc(sizeof(unsigned char) * sizeYUV);
	org1 = (unsigned short *)malloc(sizeof(unsigned short) * sizeYUV);
	org2 = (unsigned short *)malloc(sizeof(unsigned short) * sizeYUV);

	if (b == 8)	fread(org0, sizeof(unsigned char), sizeYUV, fin1);
	else fread(org1, sizeof(unsigned short), sizeYUV, fin1);
	fread(org2, sizeof(unsigned short), sizeYUV, fin2);

	for (f = 0; feof(fin1) == 0 && feof(fin2) == 0; f++)
	{
		err = 0;
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				place = j * w + i;
				if (b == 8) err += (double)(((org0[place] << 2) - org2[place]) * ((org0[place] << 2) - org2[place]));
				else err += (double)((org1[place] - org2[place]) * (org1[place] - org2[place]));
			}
		}
		psnrY = 10 * log10(((255 << 2) * (255 << 2)) / (err / sizeY));
		apsnrY += psnrY;

        err = 0;
        for (int j = h; j < heightU; j++)
        {
            for (int i = 0; i < w; i++)
            {
                place = j * w + i;
                if (b == 8) err += (double)(((org0[place] << 2) - org2[place]) * ((org0[place] << 2) - org2[place]));
                else err += (double)((org1[place] - org2[place]) * (org1[place] - org2[place]));
            }
        }
        psnrU = 10 * log10(((255 << 2) * (255 << 2)) / (err / (sizeYU - sizeY)));
        apsnrU += psnrU;

        err = 0;
        for (int j = heightU; j < heightV; j++)
        {
            for (int i = 0; i < w; i++)
            {
                place = j * w + i;
                if (b == 8) err += (double)(((org0[place] << 2) - org2[place]) * ((org0[place] << 2) - org2[place]));
                else err += (double)((org1[place] - org2[place]) * (org1[place] - org2[place]));
            }
        }
        psnrV = 10 * log10(((255 << 2) * (255 << 2)) / (err / (sizeYUV - sizeYU)));
        apsnrV += psnrV;

        printf("Frame = %3d PSNR: %.4f %.4f %.4f\n", f, psnrY, psnrU, psnrV);


		if (b == 8)	fread(org0, sizeof(unsigned char), sizeYUV, fin1);
		else fread(org1, sizeof(unsigned short), sizeYUV, fin1);
		fread(org2, sizeof(unsigned short), sizeYUV, fin2);
	}

	printf("%10.4f %10.4f %10.4f\n", apsnrY / f, apsnrU / f, apsnrV / f);
}


