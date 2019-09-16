
// cLBHView.h : CcLBHView 클래스의 인터페이스
//

#pragma once


class CcLBHView : public CView
{
protected: // serialization에서만 만들어집니다.
	CcLBHView();
	DECLARE_DYNCREATE(CcLBHView)

// 특성입니다.
public:
	CcLBHDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CcLBHView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReverseImg();

	afx_msg void OnConstAdd();
	afx_msg void OnFrameAdd();
	afx_msg void OnFrameMinus();
	afx_msg void OnFrameMulti();
	afx_msg void OnConstMinus();
	afx_msg void OnConstMulti();
	afx_msg void OnConstDivision();
	afx_msg void OnOnbinari();
	afx_msg void OnHistoStretch();
	afx_msg void OnImgHisto();
	afx_msg void OnHistoEqual();
	afx_msg void OnHpf();
	afx_msg void OnLpf();
	afx_msg void OnSobel();
	afx_msg void OnPrewitt();
	afx_msg void OnLaplacian();
	afx_msg void OnMedian();
	afx_msg void OnLog();
	afx_msg void OnHistosum();
	afx_msg void OnBrightchange();
	BITMAPINFO *BmInfo;
	int height;
	int width;
	unsigned char m_RevImg[256][256];
	int i;
	int j;
	afx_msg void OnBandremv();
	afx_msg void OnBandPass();
	afx_msg void OnLabeling();
	afx_msg void OnFrameCom();
	afx_msg void OnMorphology();
};

#ifndef _DEBUG  // cLBHView.cpp의 디버그 버전
inline CcLBHDoc* CcLBHView::GetDocument() const
   { return reinterpret_cast<CcLBHDoc*>(m_pDocument); }
#endif

