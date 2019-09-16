
// cLBHView.cpp : CcLBHView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "cLBH.h"
#endif

#include "cLBHDoc.h"
#include "cLBHView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcLBHView

IMPLEMENT_DYNCREATE(CcLBHView, CView)

BEGIN_MESSAGE_MAP(CcLBHView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_REVERSE_IMG, &CcLBHView::OnReverseImg)
	ON_COMMAND(IDM_CONST_ADD, &CcLBHView::OnConstAdd)
	ON_COMMAND(IDM_FRAME_ADD, &CcLBHView::OnFrameAdd)
	ON_COMMAND(IDM_FRAME_MINUS, &CcLBHView::OnFrameMinus)
	ON_COMMAND(IDM_FRAME_MULTI, &CcLBHView::OnFrameMulti)
	ON_COMMAND(IDM_CONST_MINUS, &CcLBHView::OnConstMinus)
	ON_COMMAND(IDM_CONST_MULTI, &CcLBHView::OnConstMulti)
	ON_COMMAND(IDM_CONST_DIVISION, &CcLBHView::OnConstDivision)
	ON_COMMAND(IDM_ONBINARI, &CcLBHView::OnOnbinari)
	ON_COMMAND(IDM_HISTO_STRETCH, &CcLBHView::OnHistoStretch)
	ON_COMMAND(IDM_IMG_HISTO, &CcLBHView::OnImgHisto)
	ON_COMMAND(IDM_HISTO_EQUAL, &CcLBHView::OnHistoEqual)
	ON_COMMAND(IDM_HPF, &CcLBHView::OnHpf)
	ON_COMMAND(IDM_LPF, &CcLBHView::OnLpf)
	ON_COMMAND(IDM_SOBEL, &CcLBHView::OnSobel)
	ON_COMMAND(IDM_PREWITT, &CcLBHView::OnPrewitt)
	ON_COMMAND(IDM_LAPLACIAN, &CcLBHView::OnLaplacian)
	ON_COMMAND(IDM_MEDIAN, &CcLBHView::OnMedian)
	ON_COMMAND(IDM_LOG, &CcLBHView::OnLog)
	ON_COMMAND(IDM_HISTOSUM, &CcLBHView::OnHistosum)
	ON_COMMAND(IDM_BRIGHTCHANGE, &CcLBHView::OnBrightchange)
	ON_COMMAND(IDM_BANDREMV, &CcLBHView::OnBandremv)
	ON_COMMAND(IDM_BAND_PASS, &CcLBHView::OnBandPass)
	ON_COMMAND(IDM_LABELING, &CcLBHView::OnLabeling)
	ON_COMMAND(IDM_FRAME_COM, &CcLBHView::OnFrameCom)
	ON_COMMAND(IDM_MORPHOLOGY, &CcLBHView::OnMorphology)
END_MESSAGE_MAP()

// CcLBHView 생성/소멸

CcLBHView::CcLBHView()
	: i(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	height = width = 256;
	int rwsize = (((width)+31) / 32 * 4);  // 4바이트의 배수여야 함
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	BmInfo->bmiHeader.biBitCount = 8;
	BmInfo->bmiHeader.biClrImportant = 256;
	BmInfo->bmiHeader.biClrUsed = 256;
	BmInfo->bmiHeader.biCompression = 0;
	BmInfo->bmiHeader.biHeight = height;
	BmInfo->bmiHeader.biPlanes = 1;
	BmInfo->bmiHeader.biSize = 40;
	BmInfo->bmiHeader.biSizeImage = rwsize*height;
	BmInfo->bmiHeader.biWidth = width;
	BmInfo->bmiHeader.biXPelsPerMeter = 0;
	BmInfo->bmiHeader.biYPelsPerMeter = 0;
	for (int i = 0; i < 256; i++) // Palette number is 256
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbBlue = i;
		BmInfo->bmiColors[i].rgbReserved = 0;
	}

}

CcLBHView::~CcLBHView()
{
	free(BmInfo);
}

BOOL CcLBHView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CcLBHView 그리기

void CcLBHView::OnDraw(CDC* pDC)
{
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	for (int i = 0; i<height; i++)
		for (int j = 0; j<width; j++) m_RevImg[i][j] = pDoc->m_InImg[height - i - 1][j];
	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height,
		0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);

	for (i = 0; i<height; i++)
		for (int j = 0; j<width; j++) m_RevImg[i][j] = pDoc->m_OutImg[height - i - 1][j];
	SetDIBitsToDevice(pDC->GetSafeHdc(), 300, 0, width, height,
		0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);




	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CcLBHView 인쇄

BOOL CcLBHView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CcLBHView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CcLBHView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CcLBHView 진단

#ifdef _DEBUG
void CcLBHView::AssertValid() const
{
	CView::AssertValid();
}

void CcLBHView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcLBHDoc* CcLBHView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcLBHDoc)));
	return (CcLBHDoc*)m_pDocument;
}
#endif //_DEBUG


// CcLBHView 메시지 처리기


void CcLBHView::OnReverseImg()
{
	// TODO: Add your command handler code here
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (int i = 0; i<256; i++)
	{
		for (int j = 0; j<256; j++)
		{
			pDoc->m_OutImg[i][j] = 255 - pDoc->m_InImg[i][j];
		}
	}
	Invalidate(FALSE);
}





void CcLBHView::OnConstAdd()
{
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int tempVal = pDoc->m_InImg[i][j] + 60;
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}


void CcLBHView::OnFrameAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->TwoImgLoad();
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int tempVal = pDoc->m_InImg1[i][j] + pDoc->m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;

		}
		Invalidate(FALSE);
	}
}


void CcLBHView::OnFrameMinus()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->TwoImgLoad();
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int tempVal = pDoc->m_InImg1[i][j] - pDoc->m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;

		}
		Invalidate(FALSE);
	}

}


void CcLBHView::OnFrameMulti()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->TwoImgLoad();
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int tempVal = pDoc->m_InImg1[i][j] & pDoc->m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;

		}
		Invalidate(FALSE);
	}
}

void CcLBHView::OnFrameCom()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (int i = 0; i<256; i++)
	{
		for (int j = 0; j<256; j++) pDoc->m_OutImg[i][j] = 255 - pDoc->m_InImg[i][j];
	}

	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			pDoc->m_Face[i][j] = pDoc->m_InImg[i][j];
			pDoc->m_Back[i][j] = pDoc->m_OutImg[i][j];
		}
	}
	pDoc->TwoImgLoad(); // 레나원본과 얼굴 마스크를 논리곱 연산
	for (i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			int tempVal = pDoc->m_InImg1[i][j] & pDoc->m_Face[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg1[i][j] = (unsigned char)tempVal;
		}
	}
	for (i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			int tempVal = pDoc->m_InImg2[i][j] & pDoc->m_Back[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg2[i][j] = (unsigned char)tempVal;
		}
	}
	for (i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			int tempVal = pDoc->m_OutImg1[i][j] + pDoc->m_OutImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE); //화면 갱신
}
void CcLBHView::OnConstMinus()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int tempVal = pDoc->m_InImg[i][j] - 60;
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}


void CcLBHView::OnConstMulti()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int tempVal = (int)(pDoc->m_InImg[i][j] * 1.5);
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}


void CcLBHView::OnConstDivision()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int tempVal = (int)(pDoc->m_InImg[i][j] / 1.5);
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}

void CcLBHView::OnBandremv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i, j;
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)   pDoc->m_OutImg[i][j] = 0;
	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{
			pDoc->m_OutImg[i][j] = pDoc->m_InImg[i][j];
			if (pDoc->m_InImg[i][j] >= 128)
				if (pDoc->m_InImg[i][j] <= 192)
					pDoc->m_OutImg[i][j] = 0;
		}
	}
	Invalidate(FALSE);
}


void CcLBHView::OnBandPass()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i, j;
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)   pDoc->m_OutImg[i][j] = 0;
	for (i = 1; i < height; i++)
	{
		for (j = 1; j < width; j++)
		{
			pDoc->m_OutImg[i][j] = pDoc->m_InImg[i][j];
			if (pDoc->m_InImg[i][j] <= 128)
				pDoc->m_OutImg[i][j] = 0;
			if (pDoc->m_InImg[i][j] >= 192)
				pDoc->m_OutImg[i][j] = 0;
		}
	}
	Invalidate(FALSE);

}

void CcLBHView::OnOnbinari()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (pDoc->m_InImg[i][j] > 100) pDoc->m_OutImg[i][j] = 255;
			else pDoc->m_OutImg[i][j] = 0;
		}
	}
	Invalidate(FALSE);
}


void CcLBHView::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_HistoStretch(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnImgHisto()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_ImgHisto(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_HistoEqual(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnHpf()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_HPF(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnLpf()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_LPF(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Sobel(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnPrewitt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Prewitt(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnLaplacian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Laplacian(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnMedian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_median(256, 256);
	Invalidate(FALSE);
}



void CcLBHView::OnLog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_LOG(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnHistosum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_HistoSum(256, 256);
	Invalidate(FALSE);
}

void CcLBHView::OnBrightchange()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Brightchange(256, 256);
	Invalidate(FALSE);
}





void CcLBHView::OnLabeling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->grass_label(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnMorphology()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_AllocStructureElementBinary(4);
	pDoc->m_SetStructureElementBinary(0, 4, 0); // m_pSEBinary[0].row = 4, m_pSEBinary[0].col = 0
	pDoc->m_SetStructureElementBinary(1, 0, -1); // m_pSEBinary[1].row = 0, m_pSEBinary[1].col = -1
	pDoc->m_SetStructureElementBinary(2, 0, 0); // m_pSEBinary[2].row = 0, m_pSEBinary[2].col = 0
	pDoc->m_SetStructureElementBinary(3, 0, 1); // m_pSEBinary[3].row = 0, m_pSEBinary[3].col = 1
	pDoc->m_Morphology(256, 256);
	pDoc->m_FreeStructureElementBinary();

	Invalidate(FALSE);
}
