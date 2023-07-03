
// vdatminDoc.cpp : implementation of the CvdatminDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "vdatmin.h"
#endif

#include "vdatminDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool is_first_wnd = true;

// CvdatminDoc

IMPLEMENT_DYNCREATE(CvdatminDoc, CDocument)
BEGIN_MESSAGE_MAP(CvdatminDoc, CDocument)
END_MESSAGE_MAP()


// CvdatminDoc construction/destruction

CvdatminDoc::CvdatminDoc() noexcept
{
	// TODO: add one-time construction code here
	inputcfg_t cfg;
	input = NULL;
	mytitle = NULL;

	mouse_ldwn = NULL;
	mouse_lup = NULL;
	mouse_rdwn = NULL;
	mouse_rup = NULL;
	mouse_over = NULL;


	if (!is_first_wnd)
	{

		if (cfg.DoModal() == IDOK)
		{
			input = cfg.the_input;
			char* c = _strdup(cfg.title);
			mytitle = (CA2CT)c; // FIX CODE -- THIS DOESN'T DO ANYTHING
			mytitle = L"Hardcoded title";
			free(c);
		}
		else
		{
			mytitle = L"Empty sample";
		}
	}
	else {
		mytitle = L"Empty sample";
		is_first_wnd = false;
	}
	// Create the several objects used from dll ...

	disk_obj = new diskview_mfc_t();
	if (!disk_obj)
	{
		::MessageBox(NULL, L"Can't create disk object", L"memory error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	if (!input)	boolfunc = new nvboolfunc_t(12);
	else boolfunc = new nvboolfunc_t(cfg.vector_size);

	if (!boolfunc)
	{
		::MessageBox(NULL, L"Can't create boolean function", L"memory error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	if (input)
	{
		boolfunc->set_input(input);
		delete input;
		boolfunc->little_sort();
	}

	disk_obj->show_valbbox(true);
	disk_obj->set_boolfunc(boolfunc);
	disk_obj->configure_boolfunc();

}

CvdatminDoc::~CvdatminDoc()
{
	if (mytitle)
		//free(mytitle); 
	if (disk_obj)
		free(disk_obj);
	if (boolfunc)
		free(boolfunc);
}

BOOL CvdatminDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CvdatminDoc serialization

void CvdatminDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CvdatminDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
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

// Support for Search Handlers
void CvdatminDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CvdatminDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CvdatminDoc diagnostics

#ifdef _DEBUG
void CvdatminDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CvdatminDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CvdatminDoc commands
