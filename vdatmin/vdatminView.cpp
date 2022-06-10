
// vdatminView.cpp : implementation of the CvdatminView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "vdatmin.h"
#endif

#include "vdatminDoc.h"
#include "vdatminView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvdatminView

IMPLEMENT_DYNCREATE(CvdatminView, CView)

BEGIN_MESSAGE_MAP(CvdatminView, CView)
	// vdatmin additives
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND(SHOW_BBOX_MENU, OnBboxMenu)
	ON_UPDATE_COMMAND_UI(SHOW_BBOX_MENU, OnUpdateBboxMenu)
	ON_COMMAND(ID_VALBBOX, OnValbbox)
	ON_UPDATE_COMMAND_UI(ID_VALBBOX, OnUpdateValbbox)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BBOX, OnBbox)
	ON_UPDATE_COMMAND_UI(ID_BBOX, OnUpdateBbox)
	ON_COMMAND(ID_VALBBOX_BTN, OnValbboxBtn)
	ON_UPDATE_COMMAND_UI(ID_VALBBOX_BTN, OnUpdateValbboxBtn)
	ON_COMMAND(ID_BUSHSORT, OnBushsort)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_LITTLE_SORT, OnLittleSort)
	ON_COMMAND(ID_HANSELCHAIN, OnHanselchain)
	ON_UPDATE_COMMAND_UI(ID_BUSHSORT, OnUpdateBushsort)
	ON_COMMAND(IDC_SHOWBUSHMNU, OnShowbushmnu)
	ON_UPDATE_COMMAND_UI(IDC_SHOWBUSHMNU, OnUpdateShowbushmnu)
	ON_COMMAND(ID_VIEW_UNICOLORVALUEBOUNDINGBOX, OnViewUnicolorvalueboundingbox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_UNICOLORVALUEBOUNDINGBOX, OnUpdateViewUnicolorvalueboundingbox)
	ON_UPDATE_COMMAND_UI(ID_UNIVALBBOX, OnUpdateUnivalbbox)
	ON_COMMAND(ID_UNIVALBBOX, OnUnivalbbox)
	ON_COMMAND(ID_SHOWHANSEL, OnShowhansel)
	ON_UPDATE_COMMAND_UI(ID_SHOWHANSEL, OnUpdateShowhansel)
	ON_COMMAND(ID_VIEW_SHOWHANSELCHAIN, OnViewShowhanselchain)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWHANSELCHAIN, OnUpdateViewShowhanselchain)
	ON_COMMAND(ID_HANSELALIGN, OnHanselalign)
	ON_UPDATE_COMMAND_UI(ID_HANSELALIGN, OnUpdateHanselalign)
	ON_COMMAND(ID_VALMOVE, OnValmove)
	ON_UPDATE_COMMAND_UI(ID_VALMOVE, OnUpdateValmove)
	ON_COMMAND(ID_MOVEHCHAIN, OnMovehchain)
	ON_UPDATE_COMMAND_UI(ID_MOVEHCHAIN, OnUpdateMovehchain)
	ON_COMMAND(ID_CENTER_CHAINS, OnCenterChains)
	ON_UPDATE_COMMAND_UI(ID_CENTER_CHAINS, OnUpdateCenterChains)
	ON_COMMAND(ID_MonotonExpand, OnMonotonExpand)
	ON_UPDATE_COMMAND_UI(ID_MonotonExpand, OnUpdateMonotonExpand)
	//For the 3d view.
	ON_COMMAND(ID_3D, On3dView)
	ON_UPDATE_COMMAND_UI(ID_3D, OnUpdate3dView)

	//To plot the data in 3d.
	ON_COMMAND(ID_3DPLOT, On3dPlot)
	ON_UPDATE_COMMAND_UI(ID_3DPLOT, OnUpdate3dPlot)

	//To draw the data in the compressed version.
	ON_COMMAND(ID_COMPRESS, OnCompress)
	ON_UPDATE_COMMAND_UI(ID_COMPRESS, OnUpdateCompress)

	//Toggle drawing the first position indicator.
	ON_COMMAND(ID_FIRSTPOS, OnFirstPos)
	ON_UPDATE_COMMAND_UI(ID_FIRSTPOS, OnUpdateFirstPos)


	//Turn on and off monotonization.
	ON_COMMAND(ID_MONOT, OnMonot)
	ON_UPDATE_COMMAND_UI(ID_MONOT, OnUpdateMonot)


	//Turn on and off higlighting monotonization violations.
	ON_COMMAND(ID_MONOTVIOL, OnMonotViol)
	ON_UPDATE_COMMAND_UI(ID_MONOTVIOL, OnUpdateMonotViol)

	//Toggle convert fake to real data.
	ON_COMMAND(ID_CONVERT, OnConvert)
	ON_UPDATE_COMMAND_UI(ID_CONVERT, OnUpdateConvert)
	// end vdatmin additives

	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CvdatminView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CvdatminView construction/destruction

CvdatminView::CvdatminView() noexcept
{
	// TODO: add construction code here

}

CvdatminView::~CvdatminView()
{
}

BOOL CvdatminView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CvdatminView drawing

void CvdatminView::OnDraw(CDC* /*pDC*/)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	//pDoc->SetTitle(pDoc->mytitle);
	pDoc->disk_obj->on_draw(m_pCDC->GetSafeHdc());
}


// CvdatminView printing


void CvdatminView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CvdatminView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CvdatminView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CvdatminView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

// OnRButtonUp member function already defined or declared
//void CvdatminView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CvdatminView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CvdatminView diagnostics

#ifdef _DEBUG
void CvdatminView::AssertValid() const
{
	CView::AssertValid();
}

void CvdatminView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvdatminDoc* CvdatminView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvdatminDoc)));
	return (CvdatminDoc*)m_pDocument;
}
#endif //_DEBUG


// CvdatminView message handlers
int CvdatminView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_pCDC = new CClientDC(this);

	pDoc->disk_obj->init_view(m_pCDC->GetSafeHdc());
	pDoc->SetTitle(pDoc->mytitle); // fix code: title is never assigned ???

	tooltip.Create(this);
	tooltip.AddWindowTool(this, LPSTR_TEXTCALLBACK);
	return 0;
}



//********************************************************************************************
// OpenGL allready erase the background ... no need to d anything more
//********************************************************************************************

BOOL CvdatminView::OnEraseBkgnd(CDC* pDC) { return true; }

//********************************************************************************************
// Resize the window and the OpenGL view
//********************************************************************************************

void CvdatminView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->disk_obj->resize(m_pCDC->GetSafeHdc(), cx, cy);
	Invalidate(true);
}

//********************************************************************************************
// delete the objects that should be
//********************************************************************************************

void CvdatminView::OnDestroy()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->disk_obj->destroy();
	if (m_pCDC) delete(m_pCDC);
	CView::OnDestroy();
}


/*********************************************************************************************

	Toggles drawing the first position indicator.  A red box around the first disk element.
*********************************************************************************************/

void CvdatminView::OnFirstPos()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj)
	{
		pDoc->boolfunc->toggleFirstPos();
		pDoc->disk_obj->paint();
	}

}

void CvdatminView::OnUpdateFirstPos(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || !pDoc->boolfunc->isMy3d())
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);

		//So button stays pushed in when on.
		pCmdUI->SetCheck(pDoc->boolfunc->isShowFirstPos());
	}

}

//********************************************************************************************
// Toggles drawing in 3d compressed mode.
//********************************************************************************************

void CvdatminView::OnCompress()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj)
	{
		pDoc->boolfunc->toggleCompress();
		if (pDoc->boolfunc->is3dPlot())
			pDoc->boolfunc->toggle3dPlot();

		//Setup the compressed data for this function.
		pDoc->boolfunc->calc3dData();
		pDoc->disk_obj->paint();
	}

}

void CvdatminView::OnUpdateCompress(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || !pDoc->boolfunc->isMy3d())
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->boolfunc->isCompressed());
	}

}


//********************************************************************************************
// Toggles converting fake elements to real ones.
//********************************************************************************************

void CvdatminView::OnConvert()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj && !pDoc->boolfunc->isMy3d())
	{
		pDoc->boolfunc->toggleConvert();


		if (pDoc->boolfunc->isConvert())
		{
			pDoc->disk_obj->reset_mousedragging();
			pDoc->mouse_ldwn = &diskview_mfc_t::selectElement;
		}
		else
		{
			pDoc->reset_oncontrols();
			pDoc->reset_lcontrols();
			pDoc->disk_obj->reset_mousedragging();
		}

		pDoc->disk_obj->paint();
	}

}

void CvdatminView::OnUpdateConvert(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || !pDoc->boolfunc->get_is_hansel_sorted() || pDoc->boolfunc->isMy3d() || pDoc->boolfunc->isMonot())
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->boolfunc->isConvert());
	}

}





//********************************************************************************************
// Toggles expanding monotonization.
//********************************************************************************************

void CvdatminView::OnMonot()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj && !pDoc->boolfunc->isMy3d())
	{
		pDoc->boolfunc->toggleMonot();


		if (pDoc->boolfunc->isMonot())
		{
			pDoc->disk_obj->reset_mousedragging();
			pDoc->mouse_ldwn = &diskview_mfc_t::selectElement;


		}
		else
		{
			pDoc->reset_oncontrols();
			pDoc->reset_lcontrols();
			pDoc->disk_obj->reset_mousedragging();
		}




		pDoc->disk_obj->paint();
	}

}

void CvdatminView::OnUpdateMonot(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || !pDoc->boolfunc->get_is_hansel_sorted() || pDoc->boolfunc->isMy3d() || pDoc->boolfunc->isConvert())
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->boolfunc->isMonot());
	}

}


//********************************************************************************************
// Toggles highlighting monotonization violations.
//********************************************************************************************

void CvdatminView::OnMonotViol()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if (pDoc->disk_obj)
	{
		pDoc->boolfunc->toggleMonotViol();
		pDoc->disk_obj->paint();
	}

}

void CvdatminView::OnUpdateMonotViol(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || !pDoc->boolfunc->get_is_hansel_sorted())
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->boolfunc->isMonotViol());
	}


}




//********************************************************************************************
// 3d plot controling toolbar button
// Toggles whether the data should be plotted in 3d or the normal 2d version.
//********************************************************************************************

void CvdatminView::On3dPlot()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj)
	{
		pDoc->boolfunc->toggle3dPlot();
		if (pDoc->boolfunc->isCompressed())
			pDoc->boolfunc->toggleCompress();
		pDoc->disk_obj->paint();

	}

}

void CvdatminView::OnUpdate3dPlot(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || !pDoc->boolfunc->isMy3d())
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->boolfunc->is3dPlot());
	}

}

//********************************************************************************************
// 3d view control toolbar button.
// Toggles the 3d view for the data.
//  On draws the 'top' structure, off draws the normal boxes.
//********************************************************************************************

void CvdatminView::On3dView()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj)
	{
		pDoc->boolfunc->toggle3d();
		pDoc->disk_obj->paint();

		//Invalidate();
	}

}

void CvdatminView::OnUpdate3dView(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj)
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->boolfunc->isMy3d());
	}

}


//********************************************************************************************
// Bbox control
//********************************************************************************************

void CvdatminView::OnBboxMenu()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj)
	{
		pDoc->disk_obj->show_bbox(!pDoc->disk_obj->get_bbox());
		Invalidate();
	}

}

//********************************************************************************************
// Check the bbox menu (also used for the button) 
//********************************************************************************************

void CvdatminView::OnUpdateBboxMenu(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj)
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->disk_obj->get_bbox());
	}

}
//********************************************************************************************
// Val Bbox control button
//********************************************************************************************

void CvdatminView::OnValbbox()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj)
	{
		pDoc->disk_obj->show_valbbox(!pDoc->disk_obj->get_showvalbox());
		Invalidate();
	}

}

//********************************************************************************************
// check the val Bbox button or menu
//********************************************************************************************

void CvdatminView::OnUpdateValbbox(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj)
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->disk_obj->get_showvalbox());
	}

}

//For handling keydown presses.
void CvdatminView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->disk_obj->set_key(nChar);
	pDoc->disk_obj->paint();

}


//********************************************************************************************
// mouse event managing part (use the pointers of the CvdatminDoc object)
//********************************************************************************************

void CvdatminView::OnMouseMove(UINT nFlags, CPoint point)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->mouse_over)
		if ((pDoc->disk_obj->*pDoc->mouse_over)(point.x, point.y, nFlags)) Invalidate();
	pDoc->disk_obj->set_mousepos(point.x, point.y, nFlags);
	CView::OnMouseMove(nFlags, point);
}

//********************************************************************************************
// mouse event managing part (Ldown)
//********************************************************************************************

void CvdatminView::OnLButtonDown(UINT nFlags, CPoint point)
{

	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->mouse_ldwn)
	{
		(pDoc->disk_obj->*pDoc->mouse_ldwn)(point.x, point.y, nFlags);
		Invalidate();
	}

}

//********************************************************************************************
// mouse event managing part (Lup)
//*******************************************************************************************

void CvdatminView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->mouse_lup)
	{
		(pDoc->disk_obj->*pDoc->mouse_lup)(point.x, point.y, nFlags);
		Invalidate();
	}

	CView::OnLButtonUp(nFlags, point);
}

//********************************************************************************************
// mouse event managing part (rdwn)
//********************************************************************************************

void CvdatminView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->mouse_rdwn) (pDoc->disk_obj->*pDoc->mouse_rdwn)(point.x, point.y, nFlags);

	CView::OnRButtonDown(nFlags, point);
}

//********************************************************************************************
// mouse event managing part (rup)
//********************************************************************************************

void CvdatminView::OnRButtonUp(UINT nFlags, CPoint point)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->mouse_rup) (pDoc->disk_obj->*pDoc->mouse_rup)(point.x, point.y, nFlags);
	CView::OnRButtonUp(nFlags, point);
}

//********************************************************************************************
// Manage the caption showing up on the disk set
//********************************************************************************************

void CvdatminView::OnNeedText(NMHDR* pnmh, LRESULT* pResult)
{
	TOOLTIPTEXT* pttt = (TOOLTIPTEXT*)pnmh;
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	memset(pttt->szText, '\0', 80);
	char* c = (char*)pttt->szText;
	pDoc->disk_obj->get_caption(c, 80);
}


//********************************************************************************************
// Tooltip
//********************************************************************************************

BOOL CMyToolTipCtrl::AddWindowTool(CWnd* pWnd, LPCTSTR pszText)
{
	TOOLINFO ti;
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	ti.hwnd = pWnd->GetParent()->GetSafeHwnd();
	ti.uId = (UINT)pWnd->GetSafeHwnd();
	ti.hinst = AfxGetInstanceHandle();
	ti.lpszText = (LPTSTR)pszText;

	return (BOOL)SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti);
}

//********************************************************************************************
// Tooltip managing
//********************************************************************************************

BOOL CMyToolTipCtrl::AddRectTool(CWnd* pWnd, LPCTSTR pszText,
	LPCRECT lpRect, UINT nIDTool)
{
	TOOLINFO ti;
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_SUBCLASS;
	ti.hwnd = pWnd->GetSafeHwnd();
	ti.uId = nIDTool;
	ti.hinst = AfxGetInstanceHandle();
	ti.lpszText = (LPTSTR)pszText;
	::CopyRect(&ti.rect, lpRect);

	return (BOOL)SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti);
}

//********************************************************************************************
// bbox button action (use the menu action)
//********************************************************************************************

void CvdatminView::OnBbox()
{
	OnBboxMenu();
}

//********************************************************************************************
// update the bbox button (use the menu update)
//********************************************************************************************

void CvdatminView::OnUpdateBbox(CCmdUI* pCmdUI)
{
	OnUpdateBboxMenu(pCmdUI);
}

//********************************************************************************************
// val bbox action ...
//********************************************************************************************

void CvdatminView::OnValbboxBtn()
{
	OnValbbox();
}

//********************************************************************************************
// update valbbox button ...
//********************************************************************************************

void CvdatminView::OnUpdateValbboxBtn(CCmdUI* pCmdUI)
{
	OnUpdateValbbox(pCmdUI);
}

//********************************************************************************************
// Bush Sort, actually more a bush view function
//********************************************************************************************

void CvdatminView::OnBushsort()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc->disk_obj->get_showbush() || (pDoc->disk_obj->get_showbush() && pDoc->mouse_lup != &diskview_mfc_t::do_bush_sort))
	{
		pDoc->reset_lcontrols();
		pDoc->reset_oncontrols();
		pDoc->mouse_lup = &diskview_mfc_t::do_bush_sort;
		pDoc->disk_obj->show_bush();
	}
	else {
		pDoc->disk_obj->show_bush(false);
		pDoc->mouse_lup = NULL;
	}
	Invalidate();
}

//********************************************************************************************
// Set the appropriate cursor
//********************************************************************************************

BOOL CvdatminView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	/*
	CvdatminDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	*/
	SetCursor(LoadCursor(NULL, IDC_CROSS));
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

//********************************************************************************************
// Launch the action of a numbered sort (littlesort)
//********************************************************************************************

void CvdatminView::OnLittleSort()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->boolfunc->little_sort();
	Invalidate();
}

//********************************************************************************************
// Sort using Hansel Chain position
//********************************************************************************************

void CvdatminView::OnHanselchain()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->boolfunc->hansel_place();
	Invalidate();
}

//********************************************************************************************
// update the button of the bush sort
//********************************************************************************************

void CvdatminView::OnUpdateBushsort(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj)
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->disk_obj->get_showbush());
	}

}

//********************************************************************************************
// bush sort menu action (use the same as the button)
//********************************************************************************************

void CvdatminView::OnShowbushmnu()
{
	OnBushsort();
}

//********************************************************************************************
// Check the menu
//********************************************************************************************

void CvdatminView::OnUpdateShowbushmnu(CCmdUI* pCmdUI)
{
	OnUpdateBushsort(pCmdUI);
}

//********************************************************************************************
// Unicolor value bounding box button
//********************************************************************************************

void CvdatminView::OnViewUnicolorvalueboundingbox()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj) pDoc->disk_obj->show_univalbbox(!pDoc->disk_obj->get_univalbbox());
	Invalidate();
}

//********************************************************************************************
// update function of the uncolor bounding box function
//********************************************************************************************

void CvdatminView::OnUpdateViewUnicolorvalueboundingbox(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj)
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);

		pCmdUI->SetCheck(pDoc->disk_obj->get_univalbbox());
	}

}

//********************************************************************************************
// univalbbox update
//********************************************************************************************

void CvdatminView::OnUpdateUnivalbbox(CCmdUI* pCmdUI)
{
	OnUpdateViewUnicolorvalueboundingbox(pCmdUI);
}

//********************************************************************************************
// unival bbox command
//********************************************************************************************

void CvdatminView::OnUnivalbbox()
{
	OnViewUnicolorvalueboundingbox();
}

//********************************************************************************************
// Showhansel button action
//********************************************************************************************

void CvdatminView::OnShowhansel()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc->disk_obj->get_showhchain() || (pDoc->disk_obj->get_showhchain() && pDoc->mouse_lup != &diskview_mfc_t::do_show_hansel))
	{
		pDoc->reset_oncontrols();
		pDoc->reset_lcontrols();
		pDoc->mouse_lup = &diskview_mfc_t::do_show_hansel;
		pDoc->disk_obj->show_hchain();
	}
	else {
		pDoc->reset_oncontrols();
		pDoc->reset_lcontrols();
		pDoc->disk_obj->show_hchain(false);
		pDoc->mouse_lup = NULL;
	}
	Invalidate();
}

//********************************************************************************************
// Show hansel update function
//********************************************************************************************

void CvdatminView::OnUpdateShowhansel(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || !pDoc->boolfunc->get_is_hansel_sorted() || pDoc->boolfunc->isMy3d())
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->disk_obj->get_showhchain());
	}
}

//********************************************************************************************
// menu action
//********************************************************************************************

void CvdatminView::OnViewShowhanselchain()
{
	OnShowhansel();
}

//********************************************************************************************
// update function
//********************************************************************************************

void CvdatminView::OnUpdateViewShowhanselchain(CCmdUI* pCmdUI)
{
	OnUpdateShowhansel(pCmdUI);
}

//********************************************************************************************
// Hansel alignment
//********************************************************************************************

void CvdatminView::OnHanselalign()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj)
	{
		pDoc->disk_obj->set_hanselaligned(!pDoc->disk_obj->get_hanselaligned());
	}
	Invalidate();
}

//********************************************************************************************
// Hansel align update function
//********************************************************************************************

void CvdatminView::OnUpdateHanselalign(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj)
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->disk_obj->get_hanselaligned());
	}

}

//********************************************************************************************
// Value move function
//********************************************************************************************

void CvdatminView::OnValmove()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj)
	{
		if (pDoc->mouse_over == &diskview_mfc_t::do_move_one_over)
		{
			pDoc->reset_oncontrols();
			pDoc->reset_lcontrols();
			pDoc->disk_obj->reset_mousedragging();
		}
		else {
			pDoc->disk_obj->reset_mousedragging();
			pDoc->mouse_ldwn = &diskview_mfc_t::do_move_one_dn; 
			pDoc->mouse_lup = &diskview_mfc_t::do_move_one_up;
			pDoc->mouse_over = &diskview_mfc_t::do_move_one_over; 
		}
	}

}

//********************************************************************************************
// update function of the move button
//********************************************************************************************

void CvdatminView::OnUpdateValmove(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || pDoc->boolfunc->isMy3d())
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->mouse_over == &diskview_mfc_t::do_move_one_over); 
	}
}

//********************************************************************************************
// Move chain action
//********************************************************************************************

void CvdatminView::OnMovehchain()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->disk_obj)
	{
		if (pDoc->mouse_over == &diskview_mfc_t::do_move_hchain_over)
		{
			pDoc->reset_lcontrols();
			pDoc->reset_oncontrols();
		}
		else {
			pDoc->disk_obj->reset_mousedragging();
			pDoc->mouse_ldwn = &diskview_mfc_t::do_mode_hchain_dn; 
			pDoc->mouse_lup = &diskview_mfc_t::do_move_one_up;
			pDoc->mouse_over = &diskview_mfc_t::do_move_hchain_over;
		}
	}

}

//********************************************************************************************
// update function of the move chain button
//********************************************************************************************

void CvdatminView::OnUpdateMovehchain(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || !pDoc->boolfunc->get_is_hansel_sorted() || pDoc->boolfunc->isMy3d())
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pDoc->mouse_over == &diskview_mfc_t::do_move_hchain_over);
	}
}

void CvdatminView::OnCenterChains()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->boolfunc) pDoc->boolfunc->center_hchain_sort();
	Invalidate();
}

void CvdatminView::OnUpdateCenterChains(CCmdUI* pCmdUI)
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->disk_obj || !pDoc->boolfunc->get_is_hansel_sorted())
	{
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}

void CvdatminView::OnMonotonExpand()
{
	CvdatminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->boolfunc->mexpand();
	Invalidate();

}

void CvdatminView::OnUpdateMonotonExpand(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here

}
