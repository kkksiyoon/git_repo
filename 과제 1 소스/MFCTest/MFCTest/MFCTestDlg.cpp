
// MFCTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCTest.h"
#include "MFCTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTestDlg 대화 상자



CMFCTestDlg::CMFCTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_X1, m_editX1);
	DDX_Control(pDX, IDC_EDIT_Y1, m_editY1);
	DDX_Control(pDX, IDC_EDIT_X2, m_editX2);
	DDX_Control(pDX, IDC_EDIT_Y2, m_editY2);
}

BEGIN_MESSAGE_MAP(CMFCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFCTestDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMFCTestDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMFCTestDlg::OnBnClickedBtnOpen)

END_MESSAGE_MAP()


// CMFCTestDlg 메시지 처리기

BOOL CMFCTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_x1 = m_y1 = m_x2 = m_y2 = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCTestDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 10, 10);
}

void CMFCTestDlg::DrawCircle(int x, int y, int radius, int color)
{
	if (m_image.IsNull()) {
		m_image.Create(500, 500, 24); 
	}

	HDC hdc = m_image.GetDC();
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	// 원 그리기
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	m_image.ReleaseDC();

	UpdateDisplay();
}

void CMFCTestDlg::MoveCircleAction()
{
	CreateDirectory(_T("image"), NULL);

	int dx = (m_x2 - m_x1) / 10;
	int dy = (m_y2 - m_y1) / 10;
	int currentX = m_x1, currentY = m_y1;

	for (int i = 0; i <= 10; i++)
	{
		DrawCircle(currentX, currentY, m_radius, RGB(0, 0, 255));

		CString filePath;
		filePath.Format(_T("image\\circle_%d.bmp"), i);
		SaveImage(filePath);

		currentX += dx;
		currentY += dy;
		Sleep(100);
	}
}

void CMFCTestDlg::SaveImage(CString path)
{
	m_image.Save(path);
}


void CMFCTestDlg::OnBnClickedBtnDraw()
{
	CString strX1, strY1;
	m_editX1.GetWindowText(strX1);
	m_editY1.GetWindowText(strY1);

	m_x1 = _ttoi(strX1);
	m_y1 = _ttoi(strY1);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(20, 50);

	m_radius = dis(gen);

	if (!m_image.IsNull()) {
		m_image.Destroy();
	}
	m_image.Create(500, 500, 24);

	DrawCircle(m_x1, m_y1, m_radius, RGB(0, 255, 0));
}

void CMFCTestDlg::OnBnClickedBtnAction()
{
	CString strX2, strY2;
	m_editX2.GetWindowText(strX2);
	m_editY2.GetWindowText(strY2);

	m_x2 = _ttoi(strX2);
	m_y2 = _ttoi(strY2);

	std::thread t(&CMFCTestDlg::MoveCircleAction, this);
	t.detach();
}

void CMFCTestDlg::OnBnClickedBtnOpen()
{
	CFileDialog dlg(TRUE, L"bmp", nullptr, OFN_FILEMUSTEXIST, L"Image Files (*.bmp;*.jpg)|*.bmp;*.jpg||");
	if (dlg.DoModal() == IDOK)
	{
		m_filePath = dlg.GetPathName();

		if (!m_image.IsNull()) 
		{
			m_image.Destroy();
		}
		if (m_image.Load(m_filePath) != S_OK)
		{
			AfxMessageBox(L"이미지 파일을 로드하는 데 실패했습니다.");
			return;
		}

		UpdateDisplay();

		DrawXMark(m_x1, m_y1);
	}
}

void CMFCTestDlg::DrawXMark(int x, int y)
{
	HDC hdc = m_image.GetDC();
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, x - 10, y - 10, nullptr);
	LineTo(hdc, x + 10, y + 10);
	MoveToEx(hdc, x + 10, y - 10, nullptr);
	LineTo(hdc, x - 10, y + 10);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	m_image.ReleaseDC();
	UpdateDisplay();
}
