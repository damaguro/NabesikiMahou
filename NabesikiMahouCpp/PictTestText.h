#pragma once
#include "DxLib.h"

#define PictTestTextIns PictTestText::Instance()

class PictTestText
{
public:
	~PictTestText();
	void PictText(int x, int y, TCHAR* text);
	static PictTestText* Instance();
private:
	PictTestText(){}
	PictTestText(const PictTestText &);
	PictTestText& operator=(const PictTestText &);
	unsigned int f_color, f_edge_color;
public:
	void DefPictTestText(int x, int y, TCHAR* text);
	void SetTestFontColor(int f_R, int f_G, int f_B);
	void SetTestFontEdgeColor(int fe_R, int fe_G, int fe_B);
	void SetTestFontAndEdgeColor(int f_R, int f_G, int f_B, int fe_R, int fe_G, int fe_B);
	void OutPutIntText(int x, int y, int value);
	void OutPutDoubleText(int x, int y, double value);
	void DefOutPutIntText(int x, int y, int value);
	void DefOutPutDoubleText(int x, int y, double value);
};