
// cLBHDoc.h : CcLBHDoc 클래스의 인터페이스
//


#pragma once


class CcLBHDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CcLBHDoc();
	DECLARE_DYNCREATE(CcLBHDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CcLBHDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	
	unsigned char m_OutImg[256][256];
	unsigned char m_InImg[256][256];
	unsigned char m_Face[256][256];
	unsigned char m_Back[256][256];
	unsigned char m_InImg1[256][256];
	unsigned char m_InImg2[256][256];
	unsigned char m_OutImg1[256][256];
	unsigned char m_OutImg2[256][256];
	void OnReverseImg();
	void TwoImgLoad();
	void m_HistoStretch(int height, int width);
	void m_ImgHisto(int height, int width);
	unsigned char m_HistoArr[256];
	void m_HistoEqual(int height, int width);
	void m_HPF(int height, int width);
	void m_LPF(int height, int width);
	void m_Sobel(int height, int width);
	void m_Prewitt(int height, int width);
	void m_Laplacian(int height, int width);
	void m_median(int height, int width);
	void m_LOG(int height, int width);
	void m_HistoSum(int height, int width);
	void m_Brightchange(int height, int width);
	void grass_label(int height, int width);
	void grass(short *coloring, int height, int width, int i, int j, int curColor);
	int m_BlobPixelSum;

	void m_Morphology(int height, int width);
	void m_AllocStructureElementBinary(int HowMany);
	void m_SetStructureElementBinary(int which, int row, int col);
	void m_FreeStructureElementBinary();
};
