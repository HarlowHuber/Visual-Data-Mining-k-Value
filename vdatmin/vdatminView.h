
// vdatminView.h : interface of the CvdatminView class
//

#pragma once

class CMyToolTipCtrl : public CToolTipCtrl
{
public:
	BOOL AddWindowTool(CWnd* pWnd, LPCTSTR pszText);
	BOOL AddRectTool(CWnd* pWnd, LPCTSTR pszText,
		LPCRECT pRect, UINT nIDTool);
};

class CvdatminView : public CView
{
protected: // create from serialization only
	CvdatminView() noexcept;
	DECLARE_DYNCREATE(CvdatminView)

// Attributes
public:
	CvdatminDoc* GetDocument() const;
	CDC* m_pCDC;
	CMyToolTipCtrl tooltip;

	void OnNeedText(NMHDR* pnmh, LRESULT* pResult);
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CvdatminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	// vdamin additives
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnBboxMenu();
	afx_msg void OnUpdateBboxMenu(CCmdUI* pCmdUI);
	afx_msg void OnValbbox();
	afx_msg void OnUpdateValbbox(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBbox();
	afx_msg void OnUpdateBbox(CCmdUI* pCmdUI);
	afx_msg void OnValbboxBtn();
	afx_msg void OnUpdateValbboxBtn(CCmdUI* pCmdUI);
	afx_msg void OnBushsort();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLittleSort();
	afx_msg void OnHanselchain();
	afx_msg void OnUpdateBushsort(CCmdUI* pCmdUI);
	afx_msg void OnShowbushmnu();
	afx_msg void OnUpdateShowbushmnu(CCmdUI* pCmdUI);
	afx_msg void OnViewUnicolorvalueboundingbox();
	afx_msg void OnUpdateViewUnicolorvalueboundingbox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUnivalbbox(CCmdUI* pCmdUI);
	afx_msg void OnUnivalbbox();
	afx_msg void OnShowhansel();
	afx_msg void OnUpdateShowhansel(CCmdUI* pCmdUI);
	afx_msg void OnViewShowhanselchain();
	afx_msg void OnUpdateViewShowhanselchain(CCmdUI* pCmdUI);
	afx_msg void OnHanselalign();
	afx_msg void OnUpdateHanselalign(CCmdUI* pCmdUI);
	afx_msg void OnValmove();
	afx_msg void OnUpdateValmove(CCmdUI* pCmdUI);
	afx_msg void OnMovehchain();
	afx_msg void OnUpdateMovehchain(CCmdUI* pCmdUI);
	afx_msg void OnCenterChains();
	afx_msg void OnUpdateCenterChains(CCmdUI* pCmdUI);
	afx_msg void OnMonotonExpand();
	afx_msg void OnUpdateMonotonExpand(CCmdUI* pCmdUI);
	//Plot in 3d.
	afx_msg void On3dPlot();
	afx_msg void OnUpdate3dPlot(CCmdUI* pCmdUI);

	//3D view.
	afx_msg void On3dView();
	afx_msg void OnUpdate3dView(CCmdUI* pCmdUI);

	//Compress data.
	afx_msg void OnCompress();
	afx_msg void OnUpdateCompress(CCmdUI* pCmdUI);

	//Show first position indicator.
	afx_msg void OnFirstPos();
	afx_msg void OnUpdateFirstPos(CCmdUI* pCmdUI);

	//Key Handling.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	//Monotonization function.
	afx_msg void OnMonot();
	afx_msg void OnUpdateMonot(CCmdUI* pCmdUI);


	//Monotonization violations.
	afx_msg void OnMonotViol();
	afx_msg void OnUpdateMonotViol(CCmdUI* pCmdUI);

	//Convert fake to real data.
	afx_msg void OnConvert();
	afx_msg void OnUpdateConvert(CCmdUI* pCmdUI);
	// end vdatmin additives

	afx_msg void OnFilePrintPreview();
	//afx_msg void OnRButtonUp(UINT nFlags, CPoint point); // OnRButtonUp member function already defined or declared
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in vdatminView.cpp
inline CvdatminDoc* CvdatminView::GetDocument() const
   { return reinterpret_cast<CvdatminDoc*>(m_pDocument); }
#endif

