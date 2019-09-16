
// cLBHView.cpp : CcLBHView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CcLBHView ����/�Ҹ�

CcLBHView::CcLBHView()
	: i(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	height = width = 256;
	int rwsize = (((width)+31) / 32 * 4);  // 4����Ʈ�� ������� ��
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CcLBHView �׸���

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




	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CcLBHView �μ�

BOOL CcLBHView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CcLBHView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CcLBHView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CcLBHView ����

#ifdef _DEBUG
void CcLBHView::AssertValid() const
{
	CView::AssertValid();
}

void CcLBHView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcLBHDoc* CcLBHView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcLBHDoc)));
	return (CcLBHDoc*)m_pDocument;
}
#endif //_DEBUG


// CcLBHView �޽��� ó����


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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	pDoc->TwoImgLoad(); // ���������� �� ����ũ�� ���� ����
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
	Invalidate(FALSE); //ȭ�� ����
}
void CcLBHView::OnConstMinus()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_HistoStretch(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnImgHisto()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_ImgHisto(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnHistoEqual()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_HistoEqual(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnHpf()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_HPF(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnLpf()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_LPF(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnSobel()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Sobel(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnPrewitt()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Prewitt(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnLaplacian()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Laplacian(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnMedian()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_median(256, 256);
	Invalidate(FALSE);
}



void CcLBHView::OnLog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_LOG(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnHistosum()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_HistoSum(256, 256);
	Invalidate(FALSE);
}

void CcLBHView::OnBrightchange()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Brightchange(256, 256);
	Invalidate(FALSE);
}





void CcLBHView::OnLabeling()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CcLBHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->grass_label(256, 256);
	Invalidate(FALSE);
}


void CcLBHView::OnMorphology()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
