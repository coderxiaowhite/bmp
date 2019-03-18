#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>

/*处理bmp图片*/
typedef struct
{
	BYTE b;
	BYTE g;
	BYTE r;
}RGB;

void main() {
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;

	FILE* info = fopen("金泫雅.bmp", "rb");
	FILE* oufo_1 = fopen("目标图片.bmp", "wb");
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, info);//调用位图文件头
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, info);//调用位图信息头
	/*建立二维结构数组储存位图信息*/
	fwrite(&fileHeader, sizeof(fileHeader), 1, oufo_1);
	fwrite(&infoHeader, sizeof(infoHeader), 1, oufo_1);
	
	RGB** buffer = (RGB * *)malloc(sizeof(RGB*) * infoHeader.biHeight);//the usage  of malloc

	for (LONG i = 0; i < infoHeader.biHeight; i++) {
		buffer[i] = (RGB*)malloc(sizeof(RGB) * infoHeader.biWidth);
		fread(buffer[i], sizeof(RGB)*infoHeader.biWidth,1, info);
	}

	/*储存*/

	if (infoHeader.biBitCount == 24)
	{/*if the bitMap is 24 bits*/
		int choose;
		scanf("%d", &choose);
		if (choose == 1) {
			for (LONG i = 0; i < infoHeader.biHeight; i++)
				for (LONG j = 0; j < infoHeader.biWidth; j++)
					buffer[i][j].r = buffer[i][j].g = buffer[i][j].b = (BYTE)((buffer[i][j].g + buffer[i][j].b + buffer[i][j].r) / 3);
		}
		else if (choose == 2) {
			/*无方向的锐化*/
			for (LONG i = 1; i < infoHeader.biHeight-1; i++)
				for (LONG j = 1; j < infoHeader.biWidth-1; j++)
				{
					buffer[i][j].g = (BYTE)(buffer[i - 1][j - 1].g + buffer[i - 1][j].g * 2 + buffer[i - 1][j + 1].g * 1 - (buffer[i + 1][j - 1].g + buffer[i + 1][j].g * 2 + buffer[i + 1][j + 1].g * 1));
					buffer[i][j].r = (BYTE)(buffer[i - 1][j - 1].r + buffer[i - 1][j].r * 2 + buffer[i - 1][j + 1].r * 1 - (buffer[i + 1][j - 1].r + buffer[i + 1][j].r * 2 + buffer[i + 1][j + 1].r * 1));
					buffer[i][j].b = (BYTE)(buffer[i - 1][j - 1].b + buffer[i - 1][j].b * 2 + buffer[i - 1][j + 1].b * 1 - (buffer[i + 1][j - 1].b + buffer[i + 1][j].b * 2 + buffer[i + 1][j + 1].b * 1));
				}
			for(LONG m=0;m<infoHeader.biWidth;m++)
			{
				buffer[0][m].b = buffer[0][m].g = buffer[0][m].r = (BYTE)0;
				buffer[infoHeader.biHeight - 1][m].b = buffer[infoHeader.biHeight - 1][m].g = buffer[infoHeader.biHeight - 1][m].r = (BYTE)0;
			}
			for (LONG m = 0; m < infoHeader.biHeight; m++)
			{
				buffer[m][0].b = buffer[m][0].g = buffer[m][0].r = (BYTE)0;
				buffer[m][infoHeader.biWidth - 1].b = buffer[m][infoHeader.biWidth - 1].g = buffer[m][infoHeader.biWidth - 1].r = (BYTE)0;
			}
		}
	for (LONG i = 0; i < infoHeader.biHeight; i++)
		fwrite(buffer[i], sizeof(RGB) * infoHeader.biWidth, 1, oufo_1);

		fclose(info);
		fclose(oufo_1);
		return 0;
	}
}