
// cLBHDoc.cpp : CcLBHDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "cLBH.h"
#endif

#include "cLBHDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct
{
	int row, col;
}structureElementBinary, *pStructureElementBinary;
pStructureElementBinary m_pSEBinary;
// CcLBHDoc

IMPLEMENT_DYNCREATE(CcLBHDoc, CDocument)

BEGIN_MESSAGE_MAP(CcLBHDoc, CDocument)
END_MESSAGE_MAP()


// CcLBHDoc 생성/소멸

CcLBHDoc::CcLBHDoc()


{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
}

CcLBHDoc::~CcLBHDoc()
{
}

BOOL CcLBHDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CcLBHDoc serialization

void CcLBHDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar.Write(m_OutImg, 256 * 256); // 처리된 영상배열 m_OutImg를 파일로 저장 
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		CFile *infile = ar.GetFile(); // 입력할 화일의 포인트를 가져옴.
		if (infile->GetLength() != 256 * 256) // 화일 사이즈를 검사함
		{
		//	AfxMessageBox("파일 크기가 256x256사이즈가 아닙니다.");
			
			return;
		}
		ar.Read(m_InImg, infile->GetLength()); // 영상파일을 읽어 m_InImg배열에 저장 
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CcLBHDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CcLBHDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CcLBHDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CcLBHDoc 진단

#ifdef _DEBUG
void CcLBHDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CcLBHDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CcLBHDoc 명령


void CcLBHDoc::OnReverseImg()
{
	// TODO: Add your command handler code here
    
	UpdateAllViews(NULL);
}


void CcLBHDoc::TwoImgLoad()
{
	CFileDialog opendlg1(TRUE);
	CFile file;
	if (opendlg1.DoModal() == IDOK)
	{
		file.Open(opendlg1.GetFileName(), CFile::modeRead);
		file.Read(m_InImg1, sizeof(m_InImg1));
		file.Close();
	}
	CFileDialog opendlg2(TRUE);
	if (opendlg2.DoModal() == IDOK)
	{
		file.Open(opendlg2.GetFileName(), CFile::modeRead);
		file.Read(m_InImg2, sizeof(m_InImg2));
		file.Close();
	}

}


void CcLBHDoc::m_HistoStretch(int height, int width)
{
	int i, j;
	int lowvalue = 255, highvale = 0;

	for (i = 0; i < 255; i++)
	{
		for (j = 0; j < 255; j++) if (m_InImg[i][j] < lowvalue)lowvalue = m_InImg[i][j];
	}
	for (i = 0; i < 255; i++)
	{
		for (j = 0; j < 255; j++) if (m_InImg[i][j] > highvale)highvale = m_InImg[i][j];
	}
	float mult = 255.0f / (float)(highvale - lowvalue);

	for (i = 0; i < 255; i++)
	{
		for (j = 0; j < 255; j++)
			m_OutImg[i][j] = (unsigned char)((m_InImg[i][j] - lowvalue)*mult);
	}
}


void CcLBHDoc::m_ImgHisto(int height, int width)
{
	int i, j, vmax, vmin;
	for (i = 0; i<256; i++) m_HistoArr[i] = 0;
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			int gv = (int)m_InImg[i][j];
			m_HistoArr[gv]++;
		}
	}
	// 히스토그램 크기 정규화
	vmin = 1000000; vmax = 0;
	for (i = 0; i<256; i++)
	{
		if (m_HistoArr[i] <= vmin) vmin = m_HistoArr[i];
		if (m_HistoArr[i] >= vmax) vmax = m_HistoArr[i];
	}
	if (vmax == vmin) return;
	float vd = (float)(vmax - vmin);
	for (i = 0; i<256; i++)
	{
		m_HistoArr[i] = (int)(((float)m_HistoArr[i] - vmin)*255.0 / vd);
	}
	// 히스토그램의 출력
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++) m_OutImg[i][j] = 255;

	for (j = 0; j<width; j++)
	{
		for (i = 0; i<m_HistoArr[j]; i++)
			m_OutImg[255 - i][j] = 0;
	}
}


void CcLBHDoc::m_HistoEqual(int height, int width)
{
	int i, j;
	unsigned int *histogram = new unsigned int[256];
	unsigned int *sum_hist = new unsigned int[256];

	for (i = 0; i < 256; i++) histogram[i] = 0;

	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < width; j++) histogram[m_InImg[i][j]]++;
	}

	int sum = 0;
	float scale_factor = 255.0f / (float)(height*width);

	for (i = 0; i < 256; i++)
	{
		sum += histogram[i];
		sum_hist[i] = (int)((sum*scale_factor) + 0.5);
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < 256; j++) m_OutImg[i][j] = sum_hist[m_InImg[i][j]];
	}

	delete[]histogram; delete[] sum_hist;
}


void CcLBHDoc::m_HPF(int height, int width)
{
	int MaskBox[3][3] = { { -1,-1,-1 },{ -1,9,-1 },{ -1,-1,-1 } };
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int mr, mc;
	int newValue, i, j;
	//결과 이미지 0으로 초기화
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)    m_OutImg[i][j] = 0;
	for (i = 1; i<heightm1; i++)
	{
		for (j = 1; j<widthm1; j++)
		{
			newValue = 0; //0으로 초기화
			for (mr = 0; mr<3; mr++)
				for (mc = 0; mc<3; mc++)
					newValue += (MaskBox[mr][mc] * m_InImg[(i - 1) + mr][(j - 1) + mc]);
			newValue /= 9; //마스크의 합의 크기로 나누기:값의 범위를 0에서 255로 함		          	  
			m_OutImg[i][j] = (BYTE)newValue;//BYTE값으로 변환 
		}
	}

}


void CcLBHDoc::m_LPF(int height, int width)
{
	int MaskBox[3][3] = { { 1,1,1 },{ 1,1,1 },{ 1,1,1 } };
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int mr, mc;
	int newValue, i, j;
	//결과 이미지 0으로 초기화
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)    m_OutImg[i][j] = 0;
	for (i = 1; i<heightm1; i++)
	{
		for (j = 1; j<widthm1; j++)
		{
			newValue = 0; //0으로 초기화
			for (mr = 0; mr<3; mr++)
				for (mc = 0; mc<3; mc++)
					newValue += (MaskBox[mr][mc] * m_InImg[(i - 1) + mr][(j - 1) + mc]);
			newValue /= 9; //마스크의 합의 크기로 나누기:값의 범위를 0에서 255로 함	
			m_OutImg[i][j] = (BYTE)newValue;//BYTE값으로 변환 

		}
	}
}


void CcLBHDoc::m_Sobel(int height, int width)
{
	int MaskSobelX[3][3] = { { -1,0,1 },{ -2,0,2 },{ -1,0,1 } };
	int MaskSobelY[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int mr, mc;
	int newValue;
	int i, j;
	int *pImgSobelX, *pImgSobelY;
	int min, max, where;
	float constVal1, constVal2;
	//정수값을 갖는 이미지 동적 메모리 할당
	pImgSobelX = new int[height*width];
	pImgSobelY = new int[height*width];
	for (i = 0; i < height; i++) 	//결과 이미지 0으로 초기화
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = 0;
			where = i*width + j;
			pImgSobelX[where] = 0;
			pImgSobelY[where] = 0;
		}
	//X 방향 에지 강도 계산 
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = 0; //0으로 초기화
			for (mr = 0; mr < 3; mr++)
				for (mc = 0; mc < 3; mc++)
					newValue += (MaskSobelX[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
			pImgSobelX[i*width + j] = newValue;
		}
	}
	//Y 방향 에지 강도 계산 
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = 0; //0으로 초기화
			for (mr = 0; mr < 3; mr++)
				for (mc = 0; mc < 3; mc++)
					newValue += (MaskSobelY[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
			pImgSobelY[i*width + j] = newValue;
		}
	}
	//에지 강도 계산 절대값(X)+절대값(Y)후 pImgSobelX[]에 저장
	for (i = 1; i < heightm1; i++)
		for (j = 1; j < widthm1; j++)
		{
			where = i*width + j;
			constVal1 = pImgSobelX[where];
			constVal2 = pImgSobelY[where];
			if (constVal1 < 0)    constVal1 = -constVal1;
			if (constVal2 < 0)    constVal2 = -constVal2;
			pImgSobelX[where] = constVal1 + constVal2;
		}
	//디스플레이를 위해 0에서 255사이로 값의 범위를 매핑 위해 먼저 최대,최소값을 찾은후 이를 이용하여 매핑.
	min = (int)10e10;
	max = (int)-10e10;
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = pImgSobelX[i*width + j];
			if (newValue < min)   	min = newValue;
			if (newValue > max)	max = newValue;
		}
	}
	//변환시 상수값을 미리 계산 
	constVal1 = (float)(255.0 / (max - min));
	constVal2 = (float)(-255.0*min / (max - min));
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			//[min,max]사이의 값을 [0,255]값으로 변환 
			newValue = pImgSobelX[i*width + j];
			newValue = constVal1*newValue + constVal2;
			m_OutImg[i][j] = (BYTE)newValue;
		}
	}

	//동적 할당 메모리 해제
	delete[] pImgSobelX;
	delete[] pImgSobelY;
}



void CcLBHDoc::m_Prewitt(int height, int width)
{
	int MaskPrewittX[3][3] = { { -1,0,1 },{ -1,0,1 },{ -1,0,1 } };
	int MaskPrewittY[3][3] = { { 1,1,1 },{ 0,0,0 },{ -1,-1,-1 } };
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int mr, mc;
	int newValue;
	int i, j;
	int *pImgPrewittX, *pImgPrewittY;
	int min, max, where;
	float constVal1, constVal2;
	//정수값을 갖는 이미지 동적 메모리 할당
	pImgPrewittX = new int[height*width];
	pImgPrewittY = new int[height*width];
	for (i = 0; i < height; i++) 	//결과 이미지 0으로 초기화
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = 0;
			where = i*width + j;
			pImgPrewittX[where] = 0;
			pImgPrewittY[where] = 0;
		}
	//X 방향 에지 강도 계산 
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = 0; //0으로 초기화
			for (mr = 0; mr < 3; mr++)
				for (mc = 0; mc < 3; mc++)
					newValue += (MaskPrewittX[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
			pImgPrewittX[i*width + j] = newValue;
		}
	}
	//Y 방향 에지 강도 계산 
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = 0; //0으로 초기화
			for (mr = 0; mr < 3; mr++)
				for (mc = 0; mc < 3; mc++)
					newValue += (MaskPrewittY[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
			pImgPrewittY[i*width + j] = newValue;
		}
	}
	//에지 강도 계산 절대값(X)+절대값(Y)후 pImgSobelX[]에 저장
	for (i = 1; i < heightm1; i++)
		for (j = 1; j < widthm1; j++)
		{
			where = i*width + j;
			constVal1 = pImgPrewittX[where];
			constVal2 = pImgPrewittY[where];
			if (constVal1 < 0)    constVal1 = -constVal1;
			if (constVal2 < 0)    constVal2 = -constVal2;
			pImgPrewittX[where] = constVal1 + constVal2;
		}
	//디스플레이를 위해 0에서 255사이로 값의 범위를 매핑 먼저 최대,최소값을 찾은후 이를 이용하여 매핑.
	min = (int)10e10;
	max = (int)-10e10;
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = pImgPrewittX[i*width + j];
			if (newValue < min)   	min = newValue;
			if (newValue > max)	max = newValue;
		}
	}
	//변환시 상수값을 미리 계산 
	constVal1 = (float)(255.0 / (max - min));
	constVal2 = (float)(-255.0*min / (max - min));
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			//[min,max]사이의 값을 [0,255]값으로 변환 
			newValue = pImgPrewittX[i*width + j];
			newValue = constVal1*newValue + constVal2;
			m_OutImg[i][j] = (BYTE)newValue;
		}
	}

	//동적 할당 메모리 해제
	delete[] pImgPrewittX;
	delete[] pImgPrewittY;
}



void CcLBHDoc::m_Laplacian(int height, int width)
{
	int MaskBox[3][3] = { { -1,-1,-1 },{ -1,8,-1 },{ -1,-1,-1 } };
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int mr, mc;
	int newValue;
	int i, j;
	int *pTmpImg;
	int min, max;
	float constVal1, constVal2;
	//정수값을 갖는 이미지 동적 메모리 할당
	pTmpImg = new int[height*width];

	//결과 이미지 0으로 초기화
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = 0;
			pTmpImg[i*width + j] = 0;
		}
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = 0; //0으로 초기화
			for (mr = 0; mr < 3; mr++)
				for (mc = 0; mc < 3; mc++)
					newValue += (MaskBox[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
			//값을 양수로 변환 
			if (newValue < 0)
				newValue = -newValue;
			pTmpImg[i*width + j] = newValue;
		}
	}
	//디스플레이를 위해 0에서 255사이로 값의 범위를 매핑
	//이를 위해 먼저 최대,최소값을 찾은후 이를 이용하여 매핑한다.
	min = (int)10e10;
	max = (int)-10e10;
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = pTmpImg[i*width + j];
			if (newValue < min)
				min = newValue;
			if (newValue > max)
				max = newValue;
		}
	}
	constVal1 = (float)(255.0 / (max - min)); 	//변환시 상수값을 미리 계산 
	constVal2 = (float)(-255.0*min / (max - min));
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = pTmpImg[i*width + j]; //[min,max]사이의 값을 [0,255]값으로 변환 
			newValue = constVal1*newValue + constVal2;
			m_OutImg[i][j] = (BYTE)newValue;
		}
	}
	delete[] pTmpImg; //동적 할당 메모리 해제
	
}


void CcLBHDoc::m_median(int height, int width)
{
	int w, h;
	int TempArray[9] = { 0, };
	int i, j;
	int tmp = 0;
	for (h = 1; h < height - 1; h++)
		for (w = 1; w < width - 1; w++)
		{
			TempArray[0] = m_InImg[h - 1][w - 1];
			TempArray[1] = m_InImg[h - 1][w];
			TempArray[2] = m_InImg[h - 1][w + 1];
			TempArray[3] = m_InImg[h][w - 1];
			TempArray[4] = m_InImg[h][w];
			TempArray[5] = m_InImg[h][w + 1];
			TempArray[6] = m_InImg[h + 1][w - 1];
			TempArray[7] = m_InImg[h + 1][w];
			TempArray[8] = m_InImg[h + 1][w + 1];

			for (i = 0; i < 8; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (TempArray[j] > TempArray[j + 1])
					{
						tmp = TempArray[j];
						TempArray[j] = TempArray[j + 1];
						TempArray[j + 1] = tmp;
					}
				}
			}
			m_OutImg[h][w] = (BYTE)TempArray[4];
		}

}


void CcLBHDoc::m_LOG(int height, int width)
{
	int MaskBox[5][5] = { { 0,0,-1,0,0 },{ 0,-1,-2,-1,0 },{ -1,-2,16,-2,-1 },{ 0,-1,-2,-1,0 } ,{ 0,0,-1,0,0 } };
	int heightm1 = height - 2;
	int widthm1 = width - 2;
	int mr, mc;
	int newValue;
	int i, j;
	int *pTmpImg;
	int min, max;
	float constVal1, constVal2;
	//정수값을 갖는 이미지 동적 메모리 할당
	pTmpImg = new int[height*width];

	//결과 이미지 0으로 초기화
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = 0;
			pTmpImg[i*width + j] = 0;
		}
	for (i = 2; i < heightm1; i++)
	{
		for (j = 2; j < widthm1; j++)
		{
			newValue = 0; //0으로 초기화
			for (mr = 0; mr < 5; mr++)
				for (mc = 0; mc < 5; mc++)
					newValue += (MaskBox[mr][mc] * m_InImg[i + mr - 2][j + mc - 2]);
			//값을 양수로 변환 
			if (newValue < 0)
				newValue = -newValue;
			pTmpImg[i*width + j] = newValue;
		}
	}
	//디스플레이를 위해 0에서 255사이로 값의 범위를 매핑
	//이를 위해 먼저 최대,최소값을 찾은후 이를 이용하여 매핑한다.
	min = (int)10e10;
	max = (int)-10e10;
	for (i = 2; i < heightm1; i++)
	{
		for (j = 2; j < widthm1; j++)
		{
			newValue = pTmpImg[i*width + j];
			if (newValue < min)
				min = newValue;
			if (newValue > max)
				max = newValue;
		}
	}
	constVal1 = (float)(255.0 / (max - min)); 	//변환시 상수값을 미리 계산 
	constVal2 = (float)(-255.0*min / (max - min));
	for (i = 2; i < heightm1; i++)
	{
		for (j = 2; j < widthm1; j++)
		{
			newValue = pTmpImg[i*width + j]; //[min,max]사이의 값을 [0,255]값으로 변환 
			newValue = constVal1*newValue + constVal2;
			m_OutImg[i][j] = (BYTE)newValue;
		}
	}
	delete[] pTmpImg; //동적 할당 메모리 해제
}


void CcLBHDoc::m_HistoSum(int height, int width)
{
	int i, j, vmax, vmin;

	for (i = 0; i < 256; i++) m_HistoArr[i] = 0;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			int gv = (int)m_InImg[i][j];
			m_HistoArr[gv]++;
		}
	}
	int cumulative_histogram[256] = { 0, };
	int sum = 0;

	for (int i = 1; i < 256; i++)
	{
		sum += m_HistoArr[i];
		cumulative_histogram[i] = sum;
	}

	vmin = 1000000;
	vmax = 0;
	for (i = 0; i<256; i++)
	{
		if (cumulative_histogram[i] <= vmin) vmin = cumulative_histogram[i];
		if (cumulative_histogram[i] >= vmax) vmax = cumulative_histogram[i];
	}
	if (vmax == vmin) return;
	float vd = (float)(vmax - vmin);
	for (i = 0; i<256; i++)
	{
		cumulative_histogram[i] = (int)(((float)cumulative_histogram[i] - vmin)*255.0 / vd);
	}



	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++) m_OutImg[i][j] = 255;

	for (j = 0; j < width; j++)
	{
		for (i = 0; i < cumulative_histogram[j]; i++)
			m_OutImg[255 - i][j] = 0;
	}

}


void CcLBHDoc::m_Brightchange(int height, int width)
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)    m_OutImg[i][j] = 0;
	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{

			if (m_InImg[i][j] > 192)
				m_OutImg[i][j] = 192;
			else if (m_InImg[i][j] > 128)
				m_OutImg[i][j] = 128;
			else if (m_InImg[i][j] > 64)
				m_OutImg[i][j] = 64;
			else m_OutImg[i][j] = 0;
		}
	}
}

void CcLBHDoc::grass(short *coloring, int height, int width, int i, int j, int curColor)
{
	int k, l, index;
	for (k = i - 1; k <= i + 1; k++)
	{
		for (l = j - 1; l <= j + 1; l++)
		{
			// 영상의 경계를 벗어나면 라벨링하지 않음
			if (k<0 || k >= height || l<0 || l >= width) continue;
			index = k*width + l;
			// 아직 방문하지 않은 픽셀이고 값이 255라면 라벨링함
			if (m_InImg[k][l] == 255 && coloring[index] == 0)
			{
				coloring[index] = curColor;
				m_BlobPixelSum++;
				grass(coloring, height, width, k, l, curColor);
			}
		}
	}
}
void CcLBHDoc::grass_label(int height, int width)
{
	short *coloring = new short[height*width]; // 라벨링된 영상을 저장하기 위한 배열의 메모리 할당 
	int i, j, curColor = 0;
	for (i = 0; i<height*width; i++) coloring[i] = 0;
	// 영역의 면적을 Text정보로 출력  

	for (i = 0; i<height; i++) // 입력 영상의 라벨링 
	{
		for (j = 0; j<width; j++)
		{
			if (m_InImg[i][j] == 255 && coloring[i*width + j] == 0)
			{
				curColor++;
				m_BlobPixelSum = 0;
				grass(coloring, height, width, i, j, curColor);  // 재귀호출함수

			}
		}
	}
	float grayGap = 250.0f / (float)(curColor + 1);

	// 라벨링된 데이터를 m_OutImg배열을 이용하여 화면출력 
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			int value = (int)(coloring[i*width + j] * grayGap);
			if (value == 0) m_OutImg[i][j] = 255;
			else m_OutImg[i][j] = value;
		}
	}

	delete[]coloring; // 메모리 해제 
}





void CcLBHDoc::m_Morphology(int height, int width)
{
	int flagPassed;
	int r, c, i;
	int mx, my;
	float mean, sum;
	//먼저 입력 영상을 이치화함 ,영상의 평균을 구한후 평균보다 큰 값은 0, 평균보다 작은 값은 255로 지정
	sum = 0;
	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++)
			sum += m_InImg[r][c];
	mean = sum / (height*width);
	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++)
		{
			if (m_InImg[r][c] > mean) m_InImg[r][c] = 0;
			else m_InImg[r][c] = 255;
		}//결과 이미지를 BACKGROUND=255값으로 모두 초기화
	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++)
			m_OutImg[r][c] = 255;
	for (r = 0; r<height; r++)
		for (c = 0; c<width; c++)
		{
			flagPassed = 1;
			for (i = 1; i<m_pSEBinary[0].row; i++) // i=1,2,3 까지 진행
			{
				mx = c + m_pSEBinary[i].col; // 순서대로 -1, 0, 1
				my = r + m_pSEBinary[i].row; // 순서대로 0, 0, 0
											 //범위 검사
				if (mx >= 0 && mx<width && my >= 0 && my<height)
					if (m_InImg[my][mx] == 255)
						//하나라도 BACKGROUND=255값을 포함하면 제일 안쪽 for loop를 빠져나감.
					{
						flagPassed = 0;
						break;
					}
			}
			if (flagPassed) m_OutImg[r][c] = 0;
		}
}


void CcLBHDoc::m_AllocStructureElementBinary(int HowMany)
{
	m_pSEBinary = new structureElementBinary[HowMany];
}


void CcLBHDoc::m_SetStructureElementBinary(int which, int row, int col)
{
	m_pSEBinary[which].row = row;
	m_pSEBinary[which].col = col;
}


void CcLBHDoc::m_FreeStructureElementBinary()
{
	if (m_pSEBinary != NULL)
	{
		delete[] m_pSEBinary;
	}
}
