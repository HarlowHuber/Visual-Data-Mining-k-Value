
// vdatminDoc.h : interface of the CvdatminDoc class
//


#pragma once
extern bool is_first_wnd;

class CvdatminDoc : public CDocument
{
protected: // create from serialization only
	CvdatminDoc() noexcept;
	DECLARE_DYNCREATE(CvdatminDoc)

// Attributes
public:
	// Personnal datas ;)
	diskview_mfc_t* disk_obj;
	nvboolfunc_t* boolfunc;
	nvinput_t* input;
	LPCTSTR mytitle = L"vdatmin";


	// callback functions, used for the MFC events
	void (diskview_mfc_t::* mouse_ldwn)(int, int, unsigned int);
	void (diskview_mfc_t::* mouse_lup) (int, int, unsigned int);
	void (diskview_mfc_t::* mouse_rdwn)(int, int, unsigned int);
	void (diskview_mfc_t::* mouse_rup) (int, int, unsigned int);
	bool (diskview_mfc_t::* mouse_over) (int, int, unsigned int);

	// managing function for callbacks
	void reset_rcontrols(void) { mouse_rdwn = mouse_lup = NULL; }
	void reset_lcontrols(void) { mouse_ldwn = mouse_lup = NULL; }
	void reset_oncontrols(void) { mouse_over = NULL; }
	void reset_allcontrols(void) { reset_rcontrols(); reset_lcontrols(); reset_oncontrols(); }

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CvdatminDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
