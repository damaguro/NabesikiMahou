#include "PictTestText.h"

PictTestText::~PictTestText()
{
}

PictTestText* PictTestText::Instance()
{
	static PictTestText instance;
	return &instance;
}

void PictTestText::PictText(int x, int y, TCHAR* text)
{
	DrawString(x, y, text, f_color, f_edge_color);
}

void PictTestText::DefPictTestText(int x, int y, TCHAR* text)
{
	f_color = GetColor(255, 255, 255);
	f_edge_color = GetColor(0, 0, 0);
	DrawString(x, y, text, f_color, f_edge_color);
}


void PictTestText::SetTestFontColor(int f_R, int f_G, int f_B)
{
	f_color = GetColor(f_R, f_G, f_B);
}



void PictTestText::SetTestFontEdgeColor(int fe_R, int fe_G, int fe_B)
{
	f_edge_color = GetColor(fe_R, fe_G, fe_B);
}



void PictTestText::SetTestFontAndEdgeColor(int f_R, int f_G, int f_B, int fe_R, int fe_G, int fe_B)
{
	SetTestFontColor(f_R, f_G, f_B);
	SetTestFontEdgeColor(fe_R, fe_G, fe_B);
}


void PictTestText::OutPutIntText(int x, int y, int value)
{
	TCHAR dest[256];
	::_itoa_s(value, dest, 256 * sizeof(TCHAR), 10);
	PictText(x, y, dest);
}

void PictTestText::OutPutDoubleText(int x, int y, double value)
{
	TCHAR dest[256];
	_stprintf_s(dest, "%f", value);
	PictText(x, y, dest);
}


void PictTestText::DefOutPutIntText(int x, int y, int value)
{
	TCHAR dest[256];
	_stprintf_s(dest, "%d", value);
	DefPictTestText(x, y, dest);
}


void PictTestText::DefOutPutDoubleText(int x, int y, double value)
{
	TCHAR dest[256];
	_stprintf_s(dest, "%f", value);
	DefPictTestText(x, y, dest);
}
