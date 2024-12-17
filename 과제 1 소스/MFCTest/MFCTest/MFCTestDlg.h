
// MFCTestDlg.h: 헤더 파일
//
#include <random>
#include <thread>

#pragma once


// CMFCTestDlg 대화 상자
class CMFCTestDlg : public CDialogEx
{
// 생성입니다.

public:
	CMFCTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

private:
	CImage m_image;
	int m_x1, m_y1, m_x2, m_y2;
	int m_radius;

	void UpdateDisplay();
	void DrawCircle(int x, int y, int radius, int color = 0x000000);
	void MoveCircleAction();
	void SaveImage(CString path);
	void DrawXMark(int x, int y);

	CEdit m_editX1, m_editY1, m_editX2, m_editY2;
	CString m_filePath;

public:
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();

};
