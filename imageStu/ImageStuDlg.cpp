// ImageStuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageStu.h"
#include "ImageStuDlg.h"
#include "DlgShowArray.h"
#include "DlgTask.h"
#include <cmath>
#include <bitset>
#include <algorithm>
#include "ColorSpaceInfo.h"
#include<iostream>
#include<fstream>
#include"Tools.h"

using namespace std;
//#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define RINT(x)(x - floor(x) > 0.5?ceil(x):floor(x)) 
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg dialog

CImageStuDlg::CImageStuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageStuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageStuDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// ͼ���Ѵ򿪱��
	_flag = false;

}

void CImageStuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageStuDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageStuDlg, CDialog)
	//{{AFX_MSG_MAP(CImageStuDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_FILE_OPEN, OnFileOpen)
	ON_WM_DESTROY()
	ON_COMMAND(IDC_FILE_SHOW_ARRAY, OnFileShowArray)
	ON_COMMAND(IDC_FILE_SAVE, OnFileSave)
	ON_COMMAND(IDE_ALL_RED, OnAllRed)
	ON_COMMAND(IDE_RED_BLUE, OnRedBlue)
	ON_COMMAND(IDE_COLOR_GRAY, OnColorGray)
	ON_COMMAND(IDE_GRAY_BLACK, OnGrayBlack)
	ON_COMMAND(IDC_GRAY_RESOlV, OnGRAYRESOlV)
	ON_COMMAND(IDC_DIRECT_SCALING, OnDirectScaling)
	ON_COMMAND(IDC_SCALL_2, OnScall2)
	ON_COMMAND(IDC_SCALL_3, OnScall3)
	ON_COMMAND(IDC_TRANSLATION, OnTranslation)
	ON_COMMAND(IDC_HORIZONTAL, OnHorizontal)
	ON_COMMAND(IDC_VERTICAL, OnVertical)
	ON_COMMAND(IDC_TRANSPOSE, OnTranspose)
	ON_COMMAND(IDC_TAKE_BACK, OnTakeBack)
	ON_COMMAND(IDC_HADES_TRANS, OnHadesTrans)
	ON_COMMAND(IDC_LOG_TRANS, OnLogTrans)
	ON_COMMAND(IDC_PIECEWISE, OnPiecewise)
	ON_COMMAND(IDC_WEIPINGMIAN, OnWeipingmian)
	ON_COMMAND(IDC_JUNHENGHUA, OnJunhenghua)
	ON_COMMAND(IDC_JUN_ZHI_LV_BO, OnJunZhiLvBo)
	ON_COMMAND(IDC_JIA_QUAN_LV_BO, OnJiaQuanLvBo)
	ON_COMMAND(IDC_LIN_YU_YU_ZHI, OnLinYuYuZhi)
	ON_COMMAND(ID_2D_ZHONGZHI, On2dZhongzhi)
	ON_COMMAND(IDC_2D_ZHONGZHI_SHIZI, On2dZhongzhiShizi)
	ON_COMMAND(IDC_LAPLACE, OnLaplace)
	ON_COMMAND(IDC_SOBEL, OnSobel)
	ON_COMMAND(IDC_RGB_HSI, OnRgbHsi)
	ON_COMMAND(IDC_256GRAY_216COLOR, On256gray216color)
	ON_COMMAND(IDC_HSI_RGB, OnHsiRgb)
	ON_COMMAND(IDC_RGB_HSI_HAdd60, OnRGBHSIHAdd60)
	ON_COMMAND(IDC_RGB_HSI_SCut50, OnRGBHSISCut50)
	ON_COMMAND(IDC_RGB_HSI_ICut50, OnRGBHSIICut50)
	ON_COMMAND(IDC_EXPAND, OnExpand)
	ON_COMMAND(IDC_DILATION, OnDilation)
	ON_COMMAND(IDC_HUFFMAN, OnHuffman)
	ON_COMMAND(IDC_OPEN, OnOpen)
	ON_COMMAND(IDC_CLOSE, OnClose)
	ON_COMMAND(IDC_FILL, OnFill)
	ON_COMMAND(IDC_BOARD, OnBoard)
	ON_COMMAND(IDC_CONNECTED_AREA, OnConnectedArea)
	ON_COMMAND(IDC_THIN, OnThin)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_THRESHOLD, &CImageStuDlg::OnThreshold)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg message handlers

BOOL CImageStuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TO DO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageStuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageStuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	// ��ͼ
	CDC * pDC = GetDC();
	if (_flag == true) {

		// �Ѿ����ļ�
		SetDIBitsToDevice(
			pDC->m_hDC  // �豸������
			, 0 // �豸������λͼ�������ʼ�߼�x����
			, 0 // �豸������λͼ�������ʼ�߼�y����
			, _infoHeader.biWidth // DIB�Ŀ��
			, _infoHeader.biHeight // DIB�ĸ߶�
			, 0 // DIB��ʼ��ȡ������������ݵ�xλ��
			, 0 // DIB��ʼ��ȡ������������ݵ�yλ��
			, 0 // DIB�����ص�ˮƽ�к�, ��ӦlpBits�ڴ滺�����ĵ�һ������
			, _infoHeader.biHeight  // DIB������
			, _lpBuf  // ��������
			, _bitmapInfo //BITMAPINFO����
			, DIB_RGB_COLORS // ��ʾ����ɫ
		);

	}
	ReleaseDC(pDC);

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageStuDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
// ���ٶԻ���, ӳ��WM_DESTORY��Ϣ
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TO DO: Add your message handler code here

	if (_flag == true) {
		FreeData();
	}


}

/************************************************************************/
/*                           �˵�                                       */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"��"(IDC_FILE_OPEN)
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileOpen()
{
	// TO DO: Add your command handler code here

	LPCTSTR lpszFilter = LPCTSTR(_T("BMP Files(*.bmp)|*.bmp|�κ��ļ�|*.*|"));
	CFileDialog dlg(TRUE, lpszFilter, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		lpszFilter, NULL);
	// �ļ���
	CString fileName;
	CFile file;
	// ���ļ�
	if (dlg.DoModal() == IDOK) {

		// �ļ���
		fileName = dlg.GetPathName();
		if (file.Open(fileName, CFile::modeRead | CFile::shareDenyNone, NULL) == 0) {
			// ��ȡ�ļ�ʧ��
			AfxMessageBox(_T("�޷����ļ�"), MB_OK, MB_ICONERROR);
			return;
		}

		// ��ȡ�ļ�ͷ
		if (!ReadFileHeader(file)) {
			return;
		}

		// ��ȡ��Ϣͷ 
		if (!ReadInfoHeader(file)) {
			return;
		}

		// ��ǰ�������ļ��򿪣����ͷ���Ӧ������
		if (_flag == true) {
			FreeData();
			_flag = false;
		}

		// �����ɫ����ɫ����
		_numQuad = CalcQuadNum();
		// ��ȡ��ɫ������
		ReadQuad(file);

		// �ж�ͼ������
		_imageType = CalcImageType();

		// ����ͼ������
		ReadImageData(file);




		// ���䴦��������
		_processBuf = (BYTE *)HeapAlloc(GetProcessHeap(), 0, _infoHeader.biSizeImage);

		// ��Ȳ���4�ı�������
		DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
		if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;



		Invalidate();

		int width = _infoHeader.biWidth;
		int height = _infoHeader.biHeight;

		// ����ռ�
		_colorData = new CBaseColorInfo[width * height];
		_grayData = new int[width * height];

		// ����ͼ�����ͣ�����ת������Ӧ��ͼ������
		if (_imageType == COLOR_24_BIT) {
			// 24λ��ɫͼ��
			BMPConvertColor24();

		}
		else if (_imageType == COLOR_8_BIT) {
			// 256��ɫͼ��
			BMPConvertColor8();
		}
		else if (_imageType == GRAY_8_BIT) {
			// 256�Ҷ�ͼ��
			BMPConvertGray8();
			// ��8λ�Ҷ�����ת����24λ��ɫ
			Gray8ConvertColor24(_grayData, _colorData, width, height);
		}
		else {
			MessageBox(_T("�ݲ�֧�ָ�ͼ������"));
			// �ر�ͼ��
			file.Close();
			FreeData();
			return;
		}

		// ͼ���ȡ���
		file.Close();
		_flag = true;

	}

}


//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"��ʾ����ͼ��"
// ��ת�����24λ��ɫ�����ڶԻ�������ʾ
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileShowArray()
{
	// TO DO: Add your command handler code here

	if (_flag == FALSE) {
		MessageBox(_T("û�д�ͼ��"));
		return;
	}

	CDlgShowArray dlg;
	dlg.SetColorData(_colorData);
	dlg.SetWidth(_infoHeader.biWidth);
	dlg.SetHeight(_infoHeader.biHeight);
	dlg.DoModal();

}


//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"����"�˵�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileSave()
{
	// TO DO: Add your command handler code here
	if (!_flag) {
		MessageBox(_T("û��ͼƬ���޷�����"));
		return;
	}

	CFileDialog dlg(FALSE, _T("*.bmp"), NULL, NULL, _T("*.bmp|*.bmp||"));
	if (dlg.DoModal() == IDOK)
	{
		SaveAsBmp((char*)(LPCTSTR)dlg.GetPathName(), _lpBuf, _infoHeader.biWidth, _infoHeader.biHeight, _infoHeader.biBitCount,
			_quad);
	}

}


/************************************************************************/
/*                         ˽�к���                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// ��ȡ�ļ�ͷ
// ����:
//   file: CFile &, BMP�ļ�
// ����ֵ:
//   BOOL, TRUE: �ɹ�; FALSE: ʧ��
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadFileHeader(CFile &file) {

	// ��ȡ�ļ�ͷ
	file.Read(&_fileHeader, sizeof(_fileHeader));
	// �ж��Ƿ�ΪBMP�ļ�
	if (_fileHeader.bfType != 0x4d42) {
		// "BM"
		AfxMessageBox(_T("����BMP�ļ�"), MB_OK, MB_ICONERROR);
		return FALSE;
	}

	// �ж��ļ��Ƿ���(�ļ���С�Ƿ����ļ�ͷ����Ϣһ��)
	if (file.GetLength() != _fileHeader.bfSize) {
		AfxMessageBox(_T("�ļ�����"), MB_OK, MB_ICONERROR);
		return FALSE;
	}

	return TRUE;

}


//////////////////////////////////////////////////////////////////////////
// ��ȡ�ļ���Ϣͷ
// ����:
//   file: CFile &, �Ѿ��򿪵�BMP�ļ�
// ����ֵ:
//   BOOL, TRUE�ɹ�; ����ʧ��
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadInfoHeader(CFile &file) {

	// ��ȡ�ļ���Ϣͷ
	file.Read(&_infoHeader, sizeof(_infoHeader));

	// ��ͼƬ��ʽ�޶���8λͼ��
	// 	if( _infoHeader.biBitCount != 8 ){
	// 		AfxMessageBox( "����Ϊ8λ�Ҷ�ͼ", MB_OK, MB_ICONERROR );
	// 		return FALSE;
	// 	}

	return TRUE;

}


//////////////////////////////////////////////////////////////////////////
// �ͷ�����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::FreeData() {

	HeapFree(GetProcessHeap(), 0, _bitmapInfo);
	HeapFree(GetProcessHeap(), 0, _lpBuf);
	// ����������
	HeapFree(GetProcessHeap(), 0, _processBuf);
	// �Ҷ���ɫ����
	delete[] _grayData;
	// ��ɫ��ɫ����
	delete[] _colorData;



}

//////////////////////////////////////////////////////////////////////////
// �����ɫ����ɫ����
// ����: ��
// ����ֵ:
//   int, ��ɫ����ɫ����
//////////////////////////////////////////////////////////////////////////
int CImageStuDlg::CalcQuadNum() {

	// �����ɫ������
	int numQuad = 0;
	if (_infoHeader.biBitCount < 24) {
		// �൱��2��biBitCount�η�
		numQuad = (1 << _infoHeader.biBitCount);
	}

	return numQuad;

}

//////////////////////////////////////////////////////////////////////////
// ��ȡ��ɫ������
// ����:
//   file: CFile &, BMP�ļ�
// ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadQuad(CFile &file) {

	// Ϊͼ����Ϣpbi����ռ�
	_bitmapInfo = (BITMAPINFO *)HeapAlloc(
		GetProcessHeap(),
		0,
		sizeof(BITMAPINFOHEADER) + _numQuad * sizeof(RGBQUAD)
	);
	memcpy(_bitmapInfo, &_infoHeader, sizeof(_infoHeader));
	_quad = (RGBQUAD *)((BYTE *)_bitmapInfo + sizeof(BITMAPINFOHEADER));

	// ��ȡ��ɫ��
	if (_numQuad != 0) {
		file.Read(_quad, sizeof(RGBQUAD) * _numQuad);
	}

}

//////////////////////////////////////////////////////////////////////////
// �ж��Ƿ�Ϊ256ɫ�Ҷ�ͼ
// �ж����ݣ���ɫ����������ɫ�ĵ�RGB��������Ӧ�����
// BOOL: TRUEΪ256ɫ�Ҷ�ͼ
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::Is256Gray() {

	BOOL result = TRUE;
	for (int i = 0; i <= _numQuad - 1; i++) {
		RGBQUAD color = *(_quad + i);
		//TRACE( "%d: %d, %d, %d\n", i, color.rgbRed,  color.rgbGreen, color.rgbBlue );
		if (!(color.rgbRed == color.rgbGreen && color.rgbRed == color.rgbBlue)) {
			result = FALSE;
			break;
		}
	}

	return result;

}

//////////////////////////////////////////////////////////////////////////
// ����ͼ������
// ����:
//   file: CFile &, BMPͼ��
// ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadImageData(CFile &file) {

	// Ϊͼ����������ռ�
	_infoHeader.biSizeImage = _fileHeader.bfSize - _fileHeader.bfOffBits;
	_lpBuf = (BYTE *)HeapAlloc(GetProcessHeap(), 0, _infoHeader.biSizeImage);
	// ��ȡͼ������
	file.Read(_lpBuf, _infoHeader.biSizeImage);

}

//////////////////////////////////////////////////////////////////////////
// �ж�ͼ������
// ����: ��
// ����ֵ: IMAGE_TYPE, ͼ������, ����ö��IMAGE_TYPE�Ķ���
//////////////////////////////////////////////////////////////////////////
IMAGE_TYPE CImageStuDlg::CalcImageType() {

	IMAGE_TYPE type = COLOR_24_BIT;
	if (_infoHeader.biBitCount == IMAGE_TYPE_BIT_24) {
		// 24��ɫͼ��
		type = COLOR_24_BIT;
		//MessageBox( "24λͼ��" );
	}
	else if (_infoHeader.biBitCount == IMAGE_TYPE_BIT_1) {
		// ��ֵͼ��
		type = GRAY_1_BIT;
		//MessageBox( "1λͼ��" );
	}
	else if (_infoHeader.biBitCount == IMAGE_TYPE_BIT_8) {
		// 8λ
		if (Is256Gray()) {
			// 8λ�Ҷ�ͼ��
			type = GRAY_8_BIT;
			//MessageBox( "8λ�Ҷ�ͼ��" );
		}
		else {
			// 8λ��ɫͼ��
			type = COLOR_8_BIT;
			//MessageBox( "8λ��ɫͼ��" );
		}
	}

	return type;

}

//////////////////////////////////////////////////////////////////////////
// ��BMP����ת����24λ��ɫ����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor24() {

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����

	int i, j;

	for (i = 0; i <= height - 1; i++) {
		for (j = 0; j <= width - 1; j++) {

			// BMPͼƬ�����е�����
			DWORD index = i * 3 * width + 3 * j;
			if (dwBytes % 3 != 0) {
				index = i * dwBytes + 3 * j;
			}
			// ��ɫ�����е�����
			DWORD resultIndex = (height - 1 - i) * width + j;
			_colorData[resultIndex].SetRed(_lpBuf[index + 2]);
			_colorData[resultIndex].SetGreen(_lpBuf[index + 1]);
			_colorData[resultIndex].SetBlue(_lpBuf[index]);

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// ��8λ��ɫBMP����ת��24λ��ɫ����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor8() {

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����
	// 	if( _colorFlag == true ){
	// 		delete [] _colorData;
	// 	}
	// 	_colorData = new CBaseColorInfo[ width * height ];
	// 	_colorFlag = true;


	int i, j;
	// 	for( i = 0; i <= 100; i++ ){
	// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
	// 	}
	// 	TRACE( "\n" );
	for (i = 0; i <= height - 1; i++) {
		for (j = 0; j <= width - 1; j++) {

			// BMPͼƬ�����е�����
			DWORD index = i * dwBytes + j;

			// ��ɫ�����е�����
			DWORD resultIndex = (height - 1 - i) * width + j;
			// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
			// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
			// 					i, j, index, resultIndex, width, height );
			// 			}

			// 			int red = _lpBuf[ index ] + 2;
			// 			int green = _lpBuf[ index ] + 1;
			// 			int blue = _lpBuf[ index ] + 0;
			// 
			// 			if( resultIndex <= width * height - 1 ){
			// 			_colorData[ resultIndex ].SetRed( red );
			// 			_colorData[ resultIndex ].SetGreen( green );
			// 			_colorData[ resultIndex ].SetBlue( blue );
			// 			}

			_colorData[resultIndex].SetRed(_quad[_lpBuf[index]].rgbRed);
			_colorData[resultIndex].SetGreen(_quad[_lpBuf[index]].rgbGreen);
			_colorData[resultIndex].SetBlue(_quad[_lpBuf[index]].rgbBlue);

			// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
			// 				_colorData[ resultIndex ].GetGreen(), 
			// 				_colorData[ resultIndex ].GetBlue() );

			// 			if( i <= 10 && j <= 10 ){
			// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
			// 				_colorData[ resultIndex ].GetGreen(), 
			// 				_colorData[ resultIndex ].GetBlue() );
			/*			}*/

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// ��8λ�Ҷ�BMP����ת��8λ�Ҷ�����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertGray8() {

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����
	// 	if( _colorFlag == true ){
	// 		delete [] _colorData;
	// 	}
	// 	_grayData = new BYTE[ width * height ];
	// 	_grayFlag = true;


	int i, j;
	// 	for( i = 0; i <= 100; i++ ){
	// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
	// 	}
	// 	TRACE( "\n" );
	for (i = 0; i <= height - 1; i++) {
		for (j = 0; j <= width - 1; j++) {

			// BMPͼƬ�����е�����
			DWORD index = i * dwBytes + j;

			// ��ɫ�����е�����
			DWORD resultIndex = (height - 1 - i) * width + j;
			// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
			// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
			// 					i, j, index, resultIndex, width, height );
			// 			}

			// 			int red = _lpBuf[ index ] + 2;
			// 			int green = _lpBuf[ index ] + 1;
			// 			int blue = _lpBuf[ index ] + 0;
			// 
			// 			if( resultIndex <= width * height - 1 ){
			// 			_colorData[ resultIndex ].SetRed( red );
			// 			_colorData[ resultIndex ].SetGreen( green );
			// 			_colorData[ resultIndex ].SetBlue( blue );
			// 			}

			_grayData[resultIndex] = _lpBuf[index];


			// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
			// 				_colorData[ resultIndex ].GetGreen(), 
			// 				_colorData[ resultIndex ].GetBlue() );

			// 			if( i <= 10 && j <= 10 ){
			// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
			// 				_colorData[ resultIndex ].GetGreen(), 
			// 				_colorData[ resultIndex ].GetBlue() );
			/*			}*/

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// ��8λ�Ҷ�����ת����24λ��ɫ
// �Ҷ�ͼ��RGBֵ����ͬ
// ����:
//   grayData: BYTE *, �Ҷ�����
//   colorData: CBaseColorInfo *, 24λ��ɫ����
//   width: ͼƬ���
//   height: ͼƬ�߶�
//  ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::Gray8ConvertColor24(BYTE * grayData,
	CBaseColorInfo * colorData,
	int width,
	int height) {


	int length = width * height;
	for (int i = 0; i <= length - 1; i++) {
		colorData[i].SetRed(grayData[i]);
		colorData[i].SetGreen(grayData[i]);
		colorData[i].SetBlue(grayData[i]);
	}

}

// ��8λ�Ҷ�����ת����24λ��ɫ
void CImageStuDlg::Gray8ConvertColor24(int * grayData, CBaseColorInfo * colorData, int width, int height) {

	int length = width * height;
	for (int i = 0; i <= length - 1; i++) {
		colorData[i].SetRed(grayData[i]);
		colorData[i].SetGreen(grayData[i]);
		colorData[i].SetBlue(grayData[i]);
	}

}

//////////////////////////////////////////////////////////////////////////
// ��ʾͼ��(ͨ��ͼ������,��ɫͼ��)
// ����:
//   colorData: CBaseColorInfo, ��ɫ����
//   width: int, ͼ����
//   height: int, ͼ��߶�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray(CBaseColorInfo * colorData,
	int width,
	int height) {

	CDlgShowArray dlg;
	// ͼ������(24λ��ɫͼ��)
	dlg.SetColorData(colorData);
	// ͼ����
	dlg.SetWidth(width);
	// ͼ��߶�
	dlg.SetHeight(height);
	// ��ʾ�Ի���
	dlg.DoModal();

}




//////////////////////////////////////////////////////////////////////////
// ��ʾͼ��(ͨ��ͼ������, �Ҷ�ͼ��)
// ����:
//   colorData: CBaseColorInfo, �Ҷ�ͼ������
//   width: int, ͼ����
//   height: int, ͼ��߶�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray(int * grayData, int width, int height) {

	// ���Ҷ�ͼ��ת�ɲ�ɫͼ��
	CBaseColorInfo * colorData = new CBaseColorInfo[width * height];
	Gray8ConvertColor24(grayData, colorData, width, height);

	CDlgShowArray dlg;
	// ͼ������(24λ��ɫͼ��)
	dlg.SetColorData(colorData);
	// ͼ����
	dlg.SetWidth(width);
	// ͼ��߶�
	dlg.SetHeight(height);
	// ��ʾ�Ի���
	dlg.DoModal();

	// �ͷŲ�ɫͼ��
	delete[] colorData;

}


//////////////////////////////////////////////////////////////////////////
// ���ܣ�����BMPͼƬ
// ������
//   bmpName: char *, �ļ���(��·�����ļ���׺)
//   imgBuf: unsigned char *, ͼ������
//   width: int, ͼ����
//   height: int, ͼ��߶�
//   biBitCount: int, �������
//   pColorTable: RGBAUAD *, ��ɫ��
//////////////////////////////////////////////////////////////////////////
bool CImageStuDlg::SaveAsBmp(char * bmpName,
	unsigned char * imgBuf,
	int width,
	int height,
	int biBitCount,
	RGBQUAD * pColorTable
) {

	// ���λͼ����Ϊ�գ���û�����ݴ���
	if (!imgBuf) {
		return false;
	}

	// ��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024����ɫͼ����ɫ���СΪ0
	int colorTableSize = 0;
	if (biBitCount == 8) {
		colorTableSize = 1024; // �о���һ����ȷ
	}

	// �����洢ͼ������ÿ���ֽ���תΪ4�ı���
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	// �Զ����Ƶ�д�ķ�ʽ���ļ�
	FILE *fp = fopen(bmpName, "wb");
	if (!fp) {
		return false;
	}

	// ����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;// bmp����
	// bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfSize = sizeof(BITMAPFILEHEADER)
		+ sizeof(BITMAPINFOHEADER)
		+ colorTableSize
		+ lineByte * height; // ͼ�������ֽ���
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	// bfOffBits��ͼ���ļ�ǰ����������ռ�֮��
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize;
	// �ļ�ͷд���ļ�
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

	// ����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
	BITMAPINFOHEADER head;
	head.biSize = sizeof(BITMAPINFOHEADER); // λͼ��Ϣͷ�ṹ�Ĵ�С(40���ֽ�)
	head.biWidth = width;// ͼ���ȣ�������Ϊ��λ
	head.biHeight = height;// ͼ��߶ȣ�������Ϊ��λ
	head.biPlanes = 1;// ����Ϊ1
	head.biBitCount = biBitCount; // ������ȣ�ÿ�����ص�Ϊ��(bit��)
	head.biCompression = BI_RGB; // ͼ���Ƿ�ѹ����һ����δѹ����
	head.biSizeImage = lineByte * height; // ʵ�ʵ�λͼ����ռ�ݵ��ֽ���
	head.biXPelsPerMeter = 0; // Ŀ���豸��ˮƽ�ֱ���
	head.biYPelsPerMeter = 0; // Ŀ���豸�Ĵ�ֱ�ֱ���
	head.biClrUsed = 0; // ��ͼ��ʵ���õ�����ɫ��
	head.biClrImportant = 0; // ��ͼ����Ҫ����ɫ�����Ϊ0�������е���ɫ����Ҫ 

	// дλͼ��Ϣͷ���ڴ�
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	// ���ͼ��ʱ�Ҷ�ͼ������ɫ��д���ļ�
	if (biBitCount == 8) {
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	// дλͼ���ݽ��ļ�
	fwrite(imgBuf, height * lineByte, 1, fp);

	// �ر��ļ�
	fclose(fp);

	return true;

}


//ȫ��
void CImageStuDlg::OnAllRed()
{
	// TO DO: Add your command handler code here
	int width = 800;
	int height = 600;
	int size = width * height;
	CBaseColorInfo * newColor = new CBaseColorInfo[size];
	for (int i = 0; i < size; ++i)
	{
		newColor[i].SetRed(255);
	}
	ShowPicByArray(newColor, 800, 600);
	delete[] newColor;

}

//�������
void CImageStuDlg::OnRedBlue()
{

	// TO DO: Add your command handler code here
	int width = 800;
	int height = 600;
	int size = width * height;

	CBaseColorInfo * newColor = new CBaseColorInfo[size];

	int index;
	int k = 0;
	for (int i = 1; i <= width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			index = j * width + i - 1;
			if (j / 30 % 2 == k)
			{
				newColor[index].SetBlue(255);
			}
			else
				newColor[index].SetRed(255);

		}
		if (i % 40 == 0)
		{
			k = (k + 1) % 2;;
		}

	}
	ShowPicByArray(newColor, 800, 600);
	delete[] newColor;

}


//G = 0.299 * R + 0.587 * G + 0.114 * B;
//��ɫ-���Ҷ�
void CImageStuDlg::OnColorGray()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int gray;
	int index;

	CBaseColorInfo * img = new CBaseColorInfo[size];
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			index = y * width + x;
			CBaseColorInfo info = _colorData[index];
			gray = 0.299 * info.GetRed() + 0.587 * info.GetGreen() + 0.114 * info.GetBlue();

			img[index] = CBaseColorInfo(gray, gray, gray);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//�Ҷ�-���ڰ�
void CImageStuDlg::OnGrayBlack()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int gray;
	int index;

	CBaseColorInfo * img = new CBaseColorInfo[size];
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			index = y * width + x;
			CBaseColorInfo info = _colorData[index];
			gray = 0.299 * info.GetRed() + 0.587 * info.GetGreen() + 0.114 * info.GetBlue();
			if (gray > 100)
			{
				gray = 255;
			}
			else
				gray = 0;
			img[index] = CBaseColorInfo(gray, gray, gray);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;
}

//�Ҷȷֱ���
void CImageStuDlg::OnGRAYRESOlV()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int gray;
	int index;

	int level = 2;
	int graylevel[256];
	for (int i = 0; i < 256; i++)
	{
		graylevel[i] = i / (256 / level)*(256 / level);
	}
	CBaseColorInfo * img = new CBaseColorInfo[size];
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			index = y * width + x;
			CBaseColorInfo info = _colorData[index];
			gray = 0.299 * info.GetRed() + 0.587 * info.GetGreen() + 0.114 * info.GetBlue();
			gray = graylevel[gray];
			img[index] = CBaseColorInfo(gray, gray, gray);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//ֱ������
void CImageStuDlg::OnDirectScaling()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;

	double scallX = 0.9;
	double scallY = 0.9;

	int size = width * height;

	int newWidth = width * scallX;

	int newHeight = height * scallY;

	int newSize = newWidth * newHeight;

	int * newImg = new int[newSize];

	int index;
	int oldIndex;

	for (int x = 0; x < newWidth; x++)
	{
		for (int y = 0; y < newHeight; y++)
		{
			index = y * newWidth + x;

			oldIndex = (int)(y / scallY) * width + (int)(x / scallX);

			newImg[index] = _grayData[oldIndex];

		}
	}

	ShowPicByArray(newImg, newWidth, newHeight);
	delete[] newImg;


}

//����ڲ�ֵ
void CImageStuDlg::OnScall2()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;

	double scallX = 0.3;
	double scallY = 0.3;

	int newWidth = width * scallX;
	int newHeight = height * scallY;

	int newSize = newWidth * newHeight;
	int * newImg = new int[newSize];

	int index;
	int newIndex;

	for (int x = 0; x < newWidth; ++x)
	{
		for (int y = 0; y < newHeight; ++y)
		{
			newIndex = y * newWidth + x;
			double oldX = x / scallX;
			if (oldX - (int)oldX > 0.5)
			{
				oldX = (int)oldX + 1;
			}
			else
				oldX = (int)oldX;
			double oldY = y / scallY;
			if (oldY - (int)oldY > 0.5)
			{
				oldY = (int)oldY + 1;
			}
			else
				oldY = (int)oldY;
			index = oldY * width + oldX;
			newImg[newIndex] = _grayData[index];
		}
	}

	ShowPicByArray(newImg, newWidth, newHeight);
	delete[] newImg;

}

//˫���Բ�ֵ
void CImageStuDlg::OnScall3()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;

	double scallX = 1.3;
	double scallY = 1.3;

	int newWidth = width * scallX;
	int newHeight = height * scallY;

	int newSize = newWidth * newHeight;
	int * newImg = new int[newSize];

	int index;
	int newIndex;

	for (int x = 0; x < newWidth; ++x)
	{
		for (int y = 0; y < newHeight; ++y)
		{
			newIndex = y * newWidth + x;

			double oldX = x / scallX;
			double oldY = y / scallY;

			int AX = (int)oldX;
			int AY = (int)oldY;

			index = AY * width + AX;


			int gray = _grayData[index];

			int grayA = gray;

			int BX = AX + 1;
			int BY = AY;
			index = BY * width + BX;

			gray = _grayData[index];

			int grayB = gray;

			int grayE = (oldX - (int)oldX)*(grayB - grayA) + grayA;

			int CX = AX;
			int CY = AY + 1;

			index = CY * width + CX;
			gray = _grayData[index];

			int grayC = gray;

			int DX = AX + 1;
			int DY = AY + 1;
			index = DY * width + DX;
			gray = _grayData[index];

			int grayD = gray;

			int grayF = (oldX - (int)oldX)*(grayD - grayC) + grayC;

			gray = (oldY - (int)oldY) *(grayF - grayE) + grayE;

			newImg[newIndex] = gray;
		}
	}

	ShowPicByArray(newImg, newWidth, newHeight);
	delete[] newImg;

}

//ƽ��
void CImageStuDlg::OnTranslation()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo * img = new CBaseColorInfo[size];

	int transX = 100;
	int transY = 10;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			int oldX = x - transX;
			int oldY = y - transY;

			if (oldX >= 0 && oldY >= 0)
			{
				int oldIndex = oldY * width + oldX;
				img[index] = _colorData[oldIndex];
			}
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//ˮƽ����
void CImageStuDlg::OnHorizontal()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo * img = new CBaseColorInfo[size];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			int oldX = width - x;
			int oldY = y;

			int oldIndex = oldY * width + oldX;
			img[index] = _colorData[oldIndex];

		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//��ֱ����
void CImageStuDlg::OnVertical()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo * img = new CBaseColorInfo[size];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			int oldX = x;
			int oldY = height - 1 - y;

			int oldIndex = oldY * width + oldX;
			img[index] = _colorData[oldIndex];

		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//ת��
void CImageStuDlg::OnTranspose()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo * img = new CBaseColorInfo[size];

	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			int index = y * height + x;
			int oldX = y;
			int oldY = x;

			int oldIndex = oldY * width + oldX;
			img[index] = _colorData[oldIndex];

		}
	}

	ShowPicByArray(img, height, width);
	delete[] img;
}

//ȡ��
void CImageStuDlg::OnTakeBack()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo * img = new CBaseColorInfo[size];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			int gray = 255 - _grayData[index];
			img[index] = CBaseColorInfo(gray, gray, gray);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;
}

//ڤ�α任
void CImageStuDlg::OnHadesTrans()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo * img = new CBaseColorInfo[size];

	double c = 0.9;
	double r = 1.1;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			int gray = _grayData[index];
			gray = c * pow(gray, r);
			if (gray > 255)
			{
				gray = 255;
			}
			if (gray < 0)
			{
				gray = 0;
			}
			img[index] = CBaseColorInfo(gray, gray, gray);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//�����任
void CImageStuDlg::OnLogTrans()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo * img = new CBaseColorInfo[size];

	double c = 30;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			int gray = _grayData[index];
			gray = c * log(1.0 + gray);

			img[index] = CBaseColorInfo(gray, gray, gray);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;
}

//�ֶκ���
void CImageStuDlg::OnPiecewise()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo * img = new CBaseColorInfo[size];

	double c = 30;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			int gray = _grayData[index];
			if (gray > 50 && gray < 100)
			{
				gray = 75;
			}
			img[index] = CBaseColorInfo(gray, gray, gray);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//λƽ��
void CImageStuDlg::OnWeipingmian()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int k = 4;

	CBaseColorInfo * img = new CBaseColorInfo[size];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			int gray = _grayData[index];

			std::bitset<8>a(gray);
			gray = (int)(a[k]);
			if (gray == 1)
			{
				gray = 255;
			}
			img[index] = CBaseColorInfo(gray, gray, gray);
		}
	}


	ShowPicByArray(img, width, height);
	delete[] img;

}

//���⻯
void CImageStuDlg::OnJunhenghua()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int count[256] = { 0 };
	double count2[256] = { 0 };
	double count3[256] = { 0 };
	int rule[256] = { 0 };

	CBaseColorInfo * img = new CBaseColorInfo[size];

	for (int i = 0; i < size; i++)//�����ۼ�ֵ
	{
		int gray = _grayData[i];
		count[gray]++;
	}

	for (int i = 0; i < 255; i++)//��һ��
	{
		count2[i] = (double)count[i] / size;
	}

	count3[0] = count2[0];

	for (int i = 1; i < 255; i++)//�����һ�����ۼ�ֵ
	{
		count3[i] = count2[i] + count3[i - 1];
	}

	for (int i = 0; i < 255; i++)
	{
		rule[i] = count3[i] * 255;
	}
	for (int i = 0; i < size; i++)
	{
		int gray = rule[_grayData[i]];
		img[i] = CBaseColorInfo(gray, gray, gray);
	}
	ShowPicByArray(img, width, height);
	delete[] img;

}

//��ֵ�˲����ټ���
void CImageStuDlg::OnJunZhiLvBo()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int window_size = 35;

	int x, y, z;
	CBaseColorInfo * img = new CBaseColorInfo[size];
	int * temp = new int[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = 0;
	}

	for (x = window_size / 2; x < width - window_size / 2; x++)
	{
		for (y = window_size / 2; y < height - window_size / 2; y++)
		{
			int sum = 0;
			for (z = x - window_size / 2; z <= x + window_size / 2; z++)
			{
				int index = y * width + z;
				sum += _grayData[index];
			}
			int indexTemp = y * width + x;
			temp[indexTemp] = (double)sum / window_size + 0.5;

		}
	}

	for (x = window_size / 2; x < width - window_size / 2; x++)
	{
		for (y = window_size / 2; y < height - window_size / 2; y++)
		{
			int sum = 0;
			for (z = y - window_size / 2; z <= y + window_size / 2; z++)
			{
				int index = z * width + x;
				sum += temp[index];
			}
			int indexImg = y * width + x;
			int gray = (double)sum / window_size + 0.5;
			img[indexImg] = CBaseColorInfo(gray, gray, gray);

		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;
}

//��Ȩ�˲�
void CImageStuDlg::OnJiaQuanLvBo()
{

	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int window_size = 15;

	int *model = new int[window_size];
	model[0] = 1;
	for (int i = 1; i <= window_size / 2; i++)
	{
		model[i] = model[i - 1] * 2;
	}

	for (int i = window_size / 2 + 1; i < window_size; i++)
	{
		model[i] = model[i - 1] / 2;
	}

	int sumq = 0;
	for (int i = 0; i < window_size; i++)
	{
		sumq += model[i];
	}

	int x, y, z;
	CBaseColorInfo * img = new CBaseColorInfo[size];
	int * temp = new int[size];

	for (int i = 0; i < size; i++)
	{
		temp[i] = 0;
	}

	for (x = window_size / 2; x < width - window_size / 2; x++)
	{
		for (y = window_size / 2; y < height - window_size / 2; y++)
		{
			int sum = 0;
			int k = 0;

			for (z = x - window_size / 2; z <= x + window_size / 2; z++)
			{
				int index = y * width + z;
				sum += _grayData[index] * model[k];
				k++;
			}
			int indexTemp = y * width + x;
			temp[indexTemp] = (double)sum / sumq + 0.5;

		}
	}

	for (x = window_size / 2; x < width - window_size / 2; x++)
	{
		for (y = window_size / 2; y < height - window_size / 2; y++)
		{
			int sum = 0;
			int k = 0;
			for (z = y - window_size / 2; z <= y + window_size / 2; z++)
			{
				int index = z * width + x;
				sum += temp[index] * model[k];
				k++;
			}
			int indexImg = y * width + x;
			int gray = (double)sum / sumq + 0.5;
			img[indexImg] = CBaseColorInfo(gray, gray, gray);

		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;
}

//������ֵ
void CImageStuDlg::OnLinYuYuZhi()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int window_size = 35;

	int x, y, z;

	double max = 0;
	CBaseColorInfo * img = new CBaseColorInfo[size];
	int * temp = new int[size];

	for (int i = 0; i < size; i++)
	{
		temp[i] = 0;
	}

	for (x = window_size / 2; x < width - window_size / 2; x++)
	{
		for (y = window_size / 2; y < height - window_size / 2; y++)
		{
			int sum = 0;
			for (z = x - window_size / 2; z <= x + window_size / 2; z++)
			{
				int index = y * width + z;
				sum += _grayData[index];
			}
			int indexTemp = y * width + x;
			temp[indexTemp] = (double)sum / window_size + 0.5;

		}
	}

	for (x = window_size / 2; x < width - window_size / 2; x++)
	{
		for (y = window_size / 2; y < height - window_size / 2; y++)
		{
			int sum = 0;
			for (z = y - window_size / 2; z <= y + window_size / 2; z++)
			{
				int index = z * width + x;
				sum += temp[index];
			}
			int indexImg = y * width + x;
			int gray = (double)sum / window_size + 0.5;
			if (gray > max)
			{
				max = gray;
			}
			img[indexImg] = CBaseColorInfo(gray, gray, gray);

		}
	}

	max = max * 0.4;
	for (int i = 0; i < size; i++)
	{
		if (img[i].GetBlue() > max)
		{
			int gray = _grayData[i];
			img[i] = CBaseColorInfo(gray, gray, gray);
		}
		else
		{
			img[i] = CBaseColorInfo(0, 0, 0);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;
}

//2D��ֵ�˲�
void CImageStuDlg::On2dZhongzhi()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int model = 5;

	CBaseColorInfo * img = new CBaseColorInfo[size];


	int* temp = new int[model * model];

	for (int x = model / 2; x < width - model / 2; x++)
	{
		for (int y = model / 2; y < height - model / 2; y++)
		{
			int k = 0;
			for (int i = x - model / 2; i <= x + model / 2; i++)
			{
				for (int j = y - model / 2; j <= y + model / 2; j++)
				{
					temp[k] = _grayData[j * width + i];
					k++;
				}
			}
			std::stable_sort(temp, temp + model * model);
			int gray = temp[model*model / 2];
			img[y * width + x] = CBaseColorInfo(gray, gray, gray);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;
	delete[] temp;
}

//2D��ֵ�˲���ʮ�֣�
void CImageStuDlg::On2dZhongzhiShizi()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int model = 5;

	CBaseColorInfo * img = new CBaseColorInfo[size];


	int* temp = new int[model + model - 1];

	for (int x = model / 2; x < width - model / 2; x++)
	{
		for (int y = model / 2; y < height - model / 2; y++)
		{
			int k = 0;
			for (int j = y - model / 2; j <= y + model / 2 && j != y; j++)
			{
				temp[k] = _grayData[j * width + x];
				k++;
			}
			for (int i = x - model / 2; i <= x + model / 2; i++)
			{
				temp[k] = _grayData[y * width + i];
				k++;
			}
			std::stable_sort(temp, temp + model + model - 1);
			int gray = temp[(model + model - 1) / 2];
			img[y * width + x] = CBaseColorInfo(gray, gray, gray);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;
	delete[] temp;

}

//������˹����
void CImageStuDlg::OnLaplace()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int model = 3;

	CBaseColorInfo * img = new CBaseColorInfo[size];
	int * temp1 = new int[size];
	int * temp2 = new int[size];


	for (int x = 1; x < width - 1; x++)
	{
		for (int y = 1; y < height - 1; y++)
		{
			int index = y * width + x;
			int gray = _grayData[index + width + 1] - _grayData[index];
			if (gray < 0)
			{
				gray *= (-1);
			}
			temp1[index] = gray;

		}
	}
	for (int x = 1; x < width - 1; x++)
	{
		for (int y = 1; y < height - 1; y++)
		{
			int index = y * width + x;
			int gray = _grayData[index + width] - _grayData[index + 1];
			if (gray < 0)
			{
				gray *= (-1);
			}
			temp2[index] = gray;

		}
	}
	for (int i = 0; i < size; i++)
	{
		int gray = temp2[i] + temp1[i];
		if (gray > 255)
		{
			gray = 255;
		}
		img[i] = CBaseColorInfo(gray, gray, gray);
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//Sobel ����
void CImageStuDlg::OnSobel()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int model = 3;

	CBaseColorInfo * img = new CBaseColorInfo[size];
	int * temp1 = new int[size];
	int * temp2 = new int[size];

	for (int x = 1; x < width - 1; x++)
	{
		for (int y = 1; y < height - 1; y++)
		{
			int index = y * width + x;
			int gray = -_grayData[index - width - 1]
				+ _grayData[index - width + 1]
				- _grayData[index - 1] * 2
				+ _grayData[index + 1] * 2
				- _grayData[index + width - 1]
				+ _grayData[index + width + 1];

			if (gray < 0)
			{
				gray *= (-1);
			}
			temp1[index] = gray;
		}
	}
	for (int x = 1; x < width - 1; x++)
	{
		for (int y = 1; y < height - 1; y++)
		{
			int index = y * width + x;
			int gray = _grayData[index - width - 1]
				+ _grayData[index - width] * 2
				+ _grayData[index - width + 1]
				- _grayData[index + width - 1]
				- _grayData[index + width] * 2
				- _grayData[index + width + 1];
			if (gray < 0)
			{
				gray *= (-1);
			}
			temp2[index] = gray;
		}
	}
	for (int i = 0; i < size; i++)
	{
		int gray = temp2[i] + temp1[i];
		if (gray > 255)
		{
			gray = 255;
		}
		img[i] = CBaseColorInfo(gray, gray, gray);
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//RGB->HSI
void CImageStuDlg::OnRgbHsi()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];
	double r, g, b;
	double h, s, i;


	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{

			int index = y * width + x;
			r = _colorData[index].GetRed();
			g = _colorData[index].GetGreen();
			b = _colorData[index].GetBlue();

			int red = r;
			int green = g;
			int blue = b;

			i = (red + green + blue) / 3.0;
			int sum = red + green + blue;
			//��һ��
			r = r * 1.0 / 255.0;
			g = g * 1.0 / 255.0;
			b = b * 1.0 / 255.0;

			if (sum != 0 && !(red == blue && red == green && blue == green))
			{
				int minv = red;
				if (minv > blue)
				{
					minv = blue;
				}
				if (minv > green)
				{
					minv = green;
				}

				//���Ͷ�
				s = 1 - minv * 3.0 / sum;
			}
			else
				s = 0;
			if (red == blue && red == green && green == blue)
			{
				h = 0;
			}
			else
			{
				double calc;
				double son = 0.5 * ((r - g) + (r - b));
				double mother = sqrt((r - g) * (r - g) + (r - b) * (g - b));
				if (fabs(mother) == 0)
				{
					calc = 0;
				}
				else
					calc = son / mother;
				if (blue <= green)
				{
					h = acos(calc);
				}
				else
					h = 2 * PI - acos(calc);
			}


			/*	CColorSpaceInfo info;
			info.SetPara1(h);
			info.SetPara2(s);
			info.SetPara3(i);*/

			red = h * 255.0 / (2 * PI);
			green = s * 255.0;
			blue = i;

			img[index] = CBaseColorInfo(red, green, blue);




		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;
}

//256�Ҷ�->216��ɫ
void CImageStuDlg::On256gray216color()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int level = 6;
	int step = 51;

	CBaseColorInfo* img = new CBaseColorInfo[size];

	CBaseColorInfo color[256];

	for (int i = 0; i < level; i++)
	{
		for (int j = 0; j < level; j++)
		{
			for (int k = 0; k < level; k++)
			{
				color[i * 6 * 6 + j * 6 + k] = CBaseColorInfo(step * i, step * j, step * k);
			}
		}
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{

			int index = y * width + x;
			int gray = _grayData[index];
			if (gray > 215)
			{
				img[index] = CBaseColorInfo(255, 255, 255);
			}
			else
				img[index] = color[gray];
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//HSI->RGB
void CImageStuDlg::OnHsiRgb()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];
	CBaseColorInfo* img_rgb = new CBaseColorInfo[size];
	double r, g, b;
	double h, s, i;


	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{

			int index = y * width + x;
			r = _colorData[index].GetRed();
			g = _colorData[index].GetGreen();
			b = _colorData[index].GetBlue();

			int red = r;
			int green = g;
			int blue = b;

			i = (red + green + blue) / 3.0;
			int sum = red + green + blue;
			//��һ��
			r = r * 1.0 / 255.0;
			g = g * 1.0 / 255.0;
			b = b * 1.0 / 255.0;

			if (sum != 0 && !(red == blue && red == green && blue == green))
			{
				int minv = red;
				if (minv > blue)
				{
					minv = blue;
				}
				if (minv > green)
				{
					minv = green;
				}

				//���Ͷ�
				s = 1 - minv * 3.0 / sum;
			}
			else
				s = 0;
			if (red == blue && red == green && green == blue)
			{
				h = 0;
			}
			else
			{
				double calc;
				double son = 0.5 * ((r - g) + (r - b));
				double mother = sqrt((r - g) * (r - g) + (r - b) * (g - b));
				if (fabs(mother) == 0)
				{
					calc = 0;
				}
				else
					calc = son / mother;
				if (blue <= green)
				{
					h = acos(calc);
				}
				else
					h = 2 * PI - acos(calc);
			}
			red = h * 255.0 / (2 * PI);
			green = s * 255.0;
			blue = i;

			img[index] = CBaseColorInfo(red, green, blue);
		}
	}

	//HSI->RGB
	for (int j = 0; j < size; j++)
	{

		CBaseColorInfo tmp = img[j];
		double p1 = tmp.GetRed();
		double p2 = tmp.GetGreen();
		double p3 = tmp.GetBlue();

		double hh = p1 * (2 * PI) / 255.0;
		double ss = p2 / 255.0;
		double ii = p3 / 255.0;


		double rr, gg, bb;
		if (fabs(ii) < 0)
		{
			rr = 0;
			gg = 0;
			bb = 0;
		}
		else if (fabs(ss) < 0)
		{
			rr = gg = bb = ii;
		}
		else
		{
			if (hh - 2 * PI / 3 < 0)
			{
				bb = ii * (1.0 - ss);
				rr = ii * (1.0 + ss * cos(hh) / cos(PI / 3.0 - hh));
				gg = 3.0 * ii - (bb + rr);
			}
			else if (hh - 4.0 * PI / 3.0 < 0)
			{
				rr = ii * (1.0 - ss);
				gg = ii * (1.0 + (ss * cos(hh - 2.0 * PI / 3.0) / cos(PI - hh)));
				bb = 3.0 * ii - (rr + gg);
			}
			else if (hh - 2.0 * PI < 0)
			{
				gg = ii * (1.0 - ss);
				bb = ii * (1.0 + ss * cos(hh - 4.0 * PI / 3.0) / cos(5.0 * PI / 3.0 - hh));
				rr = 3.0 * ii - (gg + bb);
			}
			else
			{

			}
		}
		img_rgb[j] = CBaseColorInfo(rr*255.0, gg*255.0, bb*255.0);
	}

	ShowPicByArray(img_rgb, width, height);
	delete[] img;
	delete[] img_rgb;

}

//RGB->HSI->H��60��
void CImageStuDlg::OnRGBHSIHAdd60()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];
	CBaseColorInfo* img_rgb = new CBaseColorInfo[size];
	double r, g, b;
	double h, s, i;


	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{

			int index = y * width + x;
			r = _colorData[index].GetRed();
			g = _colorData[index].GetGreen();
			b = _colorData[index].GetBlue();

			int red = r;
			int green = g;
			int blue = b;

			i = (red + green + blue) / 3.0;
			int sum = red + green + blue;
			//��һ��
			r = r * 1.0 / 255.0;
			g = g * 1.0 / 255.0;
			b = b * 1.0 / 255.0;

			if (sum != 0 && !(red == blue && red == green && blue == green))
			{
				int minv = red;
				if (minv > blue)
				{
					minv = blue;
				}
				if (minv > green)
				{
					minv = green;
				}

				//���Ͷ�
				s = 1 - minv * 3.0 / sum;
			}
			else
				s = 0;
			if (red == blue && red == green && green == blue)
			{
				h = 0;
			}
			else
			{
				double calc;
				double son = 0.5 * ((r - g) + (r - b));
				double mother = sqrt((r - g) * (r - g) + (r - b) * (g - b));
				if (fabs(mother) == 0)
				{
					calc = 0;
				}
				else
					calc = son / mother;
				if (blue <= green)
				{
					h = acos(calc);
				}
				else
					h = 2 * PI - acos(calc);
			}
			red = h * 255.0 / (2 * PI);
			green = s * 255.0;
			blue = i;

			img[index] = CBaseColorInfo(red, green, blue);
		}
	}

	//HSI->RGB
	for (int j = 0; j < size; j++)
	{

		CBaseColorInfo tmp = img[j];
		double p1 = tmp.GetRed();
		double p2 = tmp.GetGreen();
		double p3 = tmp.GetBlue();

		double hh = p1 * (2 * PI) / 255.0;

		//H����60��
		hh += PI / 3.0;
		double ss = p2 / 255.0;
		double ii = p3 / 255.0;


		double rr = 0, gg = 0, bb = 0;
		if (fabs(ii) < 0)
		{
			rr = 0;
			gg = 0;
			bb = 0;
		}
		else if (fabs(ss) < 0)
		{
			rr = gg = bb = ii;
		}
		else
		{
			if (hh - 2 * PI / 3 < 0)
			{
				bb = ii * (1.0 - ss);
				rr = ii * (1.0 + ss * cos(hh) / cos(PI / 3.0 - hh));
				gg = 3.0 * ii - (bb + rr);
			}
			else if (hh - 4.0 * PI / 3.0 < 0)
			{
				rr = ii * (1.0 - ss);
				gg = ii * (1.0 + (ss * cos(hh - 2.0 * PI / 3.0) / cos(PI - hh)));
				bb = 3.0 * ii - (rr + gg);
			}
			else if (hh - 2.0 * PI < 0)
			{
				gg = ii * (1.0 - ss);
				bb = ii * (1.0 + ss * cos(hh - 4.0 * PI / 3.0) / cos(5.0 * PI / 3.0 - hh));
				rr = 3.0 * ii - (gg + bb);
			}
			else
			{

			}
		}
		img_rgb[j] = CBaseColorInfo(rr*255.0, gg*255.0, bb*255.0);
	}

	ShowPicByArray(img_rgb, width, height);
	delete[] img;
	delete[] img_rgb;
}

//RGB->HSI->S��50%
void CImageStuDlg::OnRGBHSISCut50()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];
	CBaseColorInfo* img_rgb = new CBaseColorInfo[size];
	double r, g, b;
	double h, s, i;


	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{

			int index = y * width + x;
			r = _colorData[index].GetRed();
			g = _colorData[index].GetGreen();
			b = _colorData[index].GetBlue();

			int red = r;
			int green = g;
			int blue = b;

			i = (red + green + blue) / 3.0;
			int sum = red + green + blue;
			//��һ��
			r = r * 1.0 / 255.0;
			g = g * 1.0 / 255.0;
			b = b * 1.0 / 255.0;

			if (sum != 0 && !(red == blue && red == green && blue == green))
			{
				int minv = red;
				if (minv > blue)
				{
					minv = blue;
				}
				if (minv > green)
				{
					minv = green;
				}

				//���Ͷ�
				s = 1 - minv * 3.0 / sum;
			}
			else
				s = 0;
			if (red == blue && red == green && green == blue)
			{
				h = 0;
			}
			else
			{
				double calc;
				double son = 0.5 * ((r - g) + (r - b));
				double mother = sqrt((r - g) * (r - g) + (r - b) * (g - b));
				if (fabs(mother) == 0)
				{
					calc = 0;
				}
				else
					calc = son / mother;
				if (blue <= green)
				{
					h = acos(calc);
				}
				else
					h = 2 * PI - acos(calc);
			}
			red = h * 255.0 / (2 * PI);
			green = s * 255.0;
			blue = i;

			img[index] = CBaseColorInfo(red, green, blue);
		}
	}

	//HSI->RGB
	for (int j = 0; j < size; j++)
	{

		CBaseColorInfo tmp = img[j];
		double p1 = tmp.GetRed();
		double p2 = tmp.GetGreen();
		double p3 = tmp.GetBlue();

		double hh = p1 * (2 * PI) / 255.0;
		double ss = p2 / 255.0;

		//S����50%
		ss /= 2.0;
		double ii = p3 / 255.0;


		double rr, gg, bb;
		if (fabs(ii) < 0)
		{
			rr = 0;
			gg = 0;
			bb = 0;
		}
		else if (fabs(ss) < 0)
		{
			rr = gg = bb = ii;
		}
		else
		{
			if (hh - 2 * PI / 3 < 0)
			{
				bb = ii * (1.0 - ss);
				rr = ii * (1.0 + ss * cos(hh) / cos(PI / 3.0 - hh));
				gg = 3.0 * ii - (bb + rr);
			}
			else if (hh - 4.0 * PI / 3.0 < 0)
			{
				rr = ii * (1.0 - ss);
				gg = ii * (1.0 + (ss * cos(hh - 2.0 * PI / 3.0) / cos(PI - hh)));
				bb = 3.0 * ii - (rr + gg);
			}
			else if (hh - 2.0 * PI < 0)
			{
				gg = ii * (1.0 - ss);
				bb = ii * (1.0 + ss * cos(hh - 4.0 * PI / 3.0) / cos(5.0 * PI / 3.0 - hh));
				rr = 3.0 * ii - (gg + bb);
			}
			else
			{

			}
		}
		img_rgb[j] = CBaseColorInfo(rr*255.0, gg*255.0, bb*255.0);
	}

	ShowPicByArray(img_rgb, width, height);
	delete[] img;
	delete[] img_rgb;
}

//RGB->HSI->I��50%
void CImageStuDlg::OnRGBHSIICut50()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];
	CBaseColorInfo* img_rgb = new CBaseColorInfo[size];
	double r, g, b;
	double h, s, i;


	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{

			int index = y * width + x;
			r = _colorData[index].GetRed();
			g = _colorData[index].GetGreen();
			b = _colorData[index].GetBlue();

			int red = r;
			int green = g;
			int blue = b;

			i = (red + green + blue) / 3.0;
			int sum = red + green + blue;
			//��һ��
			r = r * 1.0 / 255.0;
			g = g * 1.0 / 255.0;
			b = b * 1.0 / 255.0;

			if (sum != 0 && !(red == blue && red == green && blue == green))
			{
				int minv = red;
				if (minv > blue)
				{
					minv = blue;
				}
				if (minv > green)
				{
					minv = green;
				}

				//���Ͷ�
				s = 1 - minv * 3.0 / sum;
			}
			else
				s = 0;
			if (red == blue && red == green && green == blue)
			{
				h = 0;
			}
			else
			{
				double calc;
				double son = 0.5 * ((r - g) + (r - b));
				double mother = sqrt((r - g) * (r - g) + (r - b) * (g - b));
				if (fabs(mother) == 0)
				{
					calc = 0;
				}
				else
					calc = son / mother;
				if (blue <= green)
				{
					h = acos(calc);
				}
				else
					h = 2 * PI - acos(calc);
			}
			red = h * 255.0 / (2 * PI);
			green = s * 255.0;
			blue = i;

			img[index] = CBaseColorInfo(red, green, blue);
		}
	}

	//HSI->RGB
	for (int j = 0; j < size; j++)
	{

		CBaseColorInfo tmp = img[j];
		double p1 = tmp.GetRed();
		double p2 = tmp.GetGreen();
		double p3 = tmp.GetBlue();

		double hh = p1 * (2 * PI) / 255.0;
		double ss = p2 / 255.0;
		double ii = p3 / 255.0;
		//I����50%
		ii /= 2.0;


		double rr, gg, bb;
		if (fabs(ii) < 0)
		{
			rr = 0;
			gg = 0;
			bb = 0;
		}
		else if (fabs(ss) < 0)
		{
			rr = gg = bb = ii;
		}
		else
		{
			if (hh - 2 * PI / 3 < 0)
			{
				bb = ii * (1.0 - ss);
				rr = ii * (1.0 + ss * cos(hh) / cos(PI / 3.0 - hh));
				gg = 3.0 * ii - (bb + rr);
			}
			else if (hh - 4.0 * PI / 3.0 < 0)
			{
				rr = ii * (1.0 - ss);
				gg = ii * (1.0 + (ss * cos(hh - 2.0 * PI / 3.0) / cos(PI - hh)));
				bb = 3.0 * ii - (rr + gg);
			}
			else if (hh - 2.0 * PI < 0)
			{
				gg = ii * (1.0 - ss);
				bb = ii * (1.0 + ss * cos(hh - 4.0 * PI / 3.0) / cos(5.0 * PI / 3.0 - hh));
				rr = 3.0 * ii - (gg + bb);
			}
			else
			{

			}
		}
		img_rgb[j] = CBaseColorInfo(rr*255.0, gg*255.0, bb*255.0);
	}

	ShowPicByArray(img_rgb, width, height);
	delete[] img;
	delete[] img_rgb;
}

//ͼ������
void CImageStuDlg::OnExpand()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];

	int step = 1;
	int color = 100;

	for (int x = step; x < width - step; x++)
	{
		for (int y = step; y < height - step; y++)
		{
			int index = y * width + x;
			int flag = 0;
			if (_grayData[index] <= color || _grayData[index - 1] <= color || _grayData[index - width] <= color)
			{
				flag = 1;
			}
			if (flag == 1)
			{
				img[index] = CBaseColorInfo(0, 0, 0);
			}
			else
				img[index] = CBaseColorInfo(255, 255, 255);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//ͼ��ʴ
void CImageStuDlg::OnDilation()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];

	int step = 1;
	int color = 100;

	for (int x = step; x < width - step; x++)
	{
		for (int y = step; y < height - step; y++)
		{
			int index = y * width + x;
			int flag = 0;
			if (_grayData[index] <= color && _grayData[index - 1] <= color && _grayData[index - width] <= color)
			{
				flag = 1;
			}
			if (flag == 1)
			{
				img[index] = CBaseColorInfo(0, 0, 0);
			}
			else
				img[index] = CBaseColorInfo(255, 255, 255);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;


}

//������,�ȸ�ʴ������
void CImageStuDlg::OnOpen()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];
	int* img1 = new int[size];
	int step = 1;
	int x;
	int y;
	int color = 128;
	for (x = step; x < width - step; x++)
	{
		for (y = step; y < height - step; y++)
		{
			int index = y * width + x;
			int flag = 0;
			if (_grayData[index] >= color && _grayData[index - 1] >= color && _grayData[index - width] >= color)
			{
				flag = 1;
			}
			if (flag == 1)
			{
				img1[index] = 255;
			}
			else
				img1[index] = 0;
		}
	}

	for (x = step; x < width - step; x++)
	{
		for (y = step; y < height - step; y++)
		{
			int index = y * width + x;
			int flag = 0;
			if (img1[index] >= color || img1[index - 1] >= color || img1[index - width] >= color)
			{
				flag = 1;
			}
			if (flag == 1)
			{
				img[index] = CBaseColorInfo(255, 255, 255);
			}
			else
				img[index] = CBaseColorInfo(0, 0, 0);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//ͼ��ղ������������ٸ�ʴ
void CImageStuDlg::OnClose()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];
	int* img1 = new int[size];
	int step = 1;
	int x;
	int y;
	int color = 128;
	for (x = step; x < width - step; x++)
	{
		for (y = step; y < height - step; y++)
		{
			int index = y * width + x;
			int flag = 0;
			if (_grayData[index] >= color || _grayData[index - 1] >= color || _grayData[index - width] >= color)
			{
				flag = 1;
			}
			if (flag == 1)
			{
				img1[index] = 255;
			}
			else
				img1[index] = 0;
		}
	}

	for (x = step; x < width - step; x++)
	{
		for (y = step; y < height - step; y++)
		{
			int index = y * width + x;
			int flag = 0;
			if (img1[index] >= color && img1[index - 1] >= color && img1[index - width] >= color)
			{
				flag = 1;
			}
			if (flag == 1)
			{
				img[index] = CBaseColorInfo(255, 255, 255);
			}
			else
				img[index] = CBaseColorInfo(0, 0, 0);
		}
	}

	ShowPicByArray(img, width, height);
	delete[] img;

}

//ͼ�����
void CImageStuDlg::OnFill()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int pointX = 132, pointY = 128;
	int point = pointY * width + pointX;

	int* img = new int[size]; //��ֵ��ͼ��0��255
	int* imgA = new int[size];//ԭͼ��0��1
	int* imgB = new int[size];//ԭͼ�񲹼�
	int* imgX = new int[size];//����ͼ��
	int i;
	int countX1 = 1, countX2 = 0; //�ж�����imgX�����Ƿ�һ��

	CBaseColorInfo* finalImg = new CBaseColorInfo[size];
	for (i = 0; i < size; i++)
	{
		if (_grayData[i] < 128)
		{
			img[i] = 0;
		}
		else
			img[i] = 255;
	}

	int gray = img[point];//����Aͼ,Bͼ

	for (i = 0; i < size; i++)
	{
		if (img[i] == gray)
		{
			imgA[i] = 1;
			imgB[i] = 0;
		}
		else
		{
			imgA[i] = 0;
			imgB[i] = 1;
		}
		imgX[i] = 1;
	}

	imgX[point] = 0;

	while (countX1 != countX2)
	{
		countX1 = CountX(size, imgX);
		imgX = Expland(width, height, imgX);//����Xͼ		
		imgX = Mixed(size, imgX, imgB);//��Bͼ������
		countX2 = CountX(size, imgX);
	}

	for (i = 0; i < size; i++)
	{
		if (imgA[i] == 1 && imgX[i] == 0)
		{
			imgA[i] = 0;
		}
		if (imgA[i] == 1)
		{

			finalImg[i] = CBaseColorInfo(gray, gray, gray);

		}
		else
			if (gray == 255)
				finalImg[i] = CBaseColorInfo(0, 0, 0);
			else
				finalImg[i] = CBaseColorInfo(255, 255, 255);
	}


	ShowPicByArray(finalImg, width, height);
	delete[] finalImg;
	delete[] img;
	delete[] imgA;
	delete[] imgB;
	delete[] imgX;

}

//��߽�
void CImageStuDlg::OnBoard()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];

	int step = 1;
	int color = 1;

	int* imgA = new int[size];
	int* imgAB = new int[size];
	int i;
	for (i = 0; i < size; i++)
	{
		if (_grayData[i] < 128)
		{
			imgA[i] = 1;
		}
		else
			imgA[i] = 0;
	}



	for (int x = step; x < width - step; x++)
	{
		for (int y = step; y < height - step; y++)
		{
			int index = y * width + x;
			if (imgA[index] == color
				&& imgA[index - 1] == color
				&& imgA[index + 1] == color
				&& imgA[index - width] == color
				&& imgA[index + width] == color
				&& imgA[index + width - 1] == color
				&& imgA[index + width + 1] == color
				&& imgA[index - width + 1] == color
				&& imgA[index - width - 1] == color)
			{
				imgAB[index] = 1;
			}
			else
				imgAB[index] = 0;
		}
	}

	for (i = 0; i < size; i++)
	{
		imgA[i] -= imgAB[i];
		if (imgA[i] == 1)
		{
			img[i] = CBaseColorInfo(255, 255, 255);
		}
		else

			img[i] = CBaseColorInfo(0, 0, 0);
	}
	ShowPicByArray(img, width, height);
	delete[] img;
	delete[] imgA;
	delete[] imgAB;
}

//����ͨ����
void CImageStuDlg::OnConnectedArea()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int i = 0;
	int x = 0, y = 0;
	CBaseColorInfo* img = new CBaseColorInfo[size];

	int * imgA = new int[size];
	int * imgL = new int[size];

	int * tempA = new int[size];
	int * tempB = new int[size];
	int * tempC = new int[size];

	int p = -1;

	int lable = 0;
	int allDone = 0;
	int done = 0;
	for (i = 0; i < size; i++) //��ֵ���Լ������ʼ��
	{
		if (_grayData[i] < 200)
		{
			imgA[i] = 0;
		}
		else
			imgA[i] = 1;

		imgL[i] = 0;
	}

	CorrImgA(width, height, imgA);
	for (i = 0; i < size; i++)//������ʼ��
	{
		if (imgA[i] == 1 && imgL[i] == 0)
		{
			p = i;
			break;
		}
	}
	while (p != -1)
	{
		for (i = 0; i < size; i++)//������ʼ��
		{
			p = -1;
			if (imgA[i] == 1 && imgL[i] == 0)
			{
				p = i;
				break;
			}
		}
		if (p != -1) {

			for (i = 0; i < size; i++)
			{
				tempA[i] = 0;
				tempB[i] = 0;
			}

			tempA[p] = 1;

			done = 0;
			while (done == 0)
			{
				for (i = 0; i < size; i++)
				{
					tempC[i] = tempB[i];
				}
				ExplandTempA(width, height, tempA);//����tempA
				MixTempA(size, imgA, tempA, tempB);//��tempA��imgA�����õ�TempB
				if (!CompareAB(size, tempB, tempC))//�Ա�TempA��TempB
				{
					for (i = 0; i < size; i++)
					{
						tempA[i] = tempB[i];
						done = 0;
					}
				}
				else
					done = 1;
			}

			++lable;
			for (i = 0; i < size; i++)//����ͼ��tempA����tempA��Ϊ1�ĵ���ͼ��L����Ϊ����label��ֵ
			{
				if (tempA[i] == 1)
				{
					imgL[i] = lable;
				}
			}
		}
	}

	for (i = 0; i < size; i++)
	{
		img[i] = CBaseColorInfo(imgL[i] * 80 % 255, imgL[i] * 20 % 255, imgL[i] * 30 % 255);
	}
	ShowPicByArray(img, width, height);
	delete[] img;
	delete[]imgA;
	delete[] imgL;
	delete[] tempA;
	delete[] tempB;

}

//ϸ��
void CImageStuDlg::OnThin()
{

	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	// ϸ����
	int ERASE_TABLE[256] = {
		0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,1,
			1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0, 1,1,0,1,1,1,0,1,
			0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
			0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0, 1,1,0,1,1,1,0,0,
			1,1,0,0,1,1,1,0, 1,1,0,0,1,0,0,0
	};

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	CBaseColorInfo* img = new CBaseColorInfo[size];

	int* imgA = new int[size];
	int i;
	for (i = 0; i < size; i++)
	{
		if (_grayData[i] < 200)
		{
			imgA[i] = 1;//��ɫ
		}
		else
		{
			imgA[i] = 0;//��ɫ
		}
	}

	int x, y;
	bool finish = false;
	while (!finish)
	{
		finish = true;
		for (y = 1; y < height - 1; y++)
		{
			for (x = 1; x < width - 1; x++)
			{
				int index = y * width + x;


				if (imgA[index] == 0)
				{

					int w = imgA[index - 1];
					int e = imgA[index + 1];
					if (w == 1 || e == 1)
					{
						int num = 0;
						num += imgA[index - width - 1]
							+ 2 * imgA[index - width]
							+ 4 * imgA[index - width + 1]
							+ 8 * imgA[index - 1]
							+ 16 * imgA[index + 1]
							+ 32 * imgA[index + width - 1]
							+ 64 * imgA[index + width]
							+ 128 * imgA[index + width + 1];
						if (ERASE_TABLE[num] == 1)
						{
							imgA[index] = 1;
							finish = false;
						}
					}
				}
			}
		}

		for (x = 1; x < width - 1; x++)
		{
			for (y = 1; y < height - 1; y++)
			{
				int index = y * width + x;


				if (imgA[index] == 0)
				{
					int num = 0;
					int n = imgA[index - width];
					int s = imgA[index + width];
					if (n == 1 || s == 1)
					{
						num += imgA[index - width - 1]
							+ 2 * imgA[index - width]
							+ 4 * imgA[index - width + 1]
							+ 8 * imgA[index - 1]
							+ 16 * imgA[index + 1]
							+ 32 * imgA[index + width - 1]
							+ 64 * imgA[index + width]
							+ 128 * imgA[index + width + 1];
						if (ERASE_TABLE[num] == 1)
						{
							imgA[index] = 1;
							finish = false;

						}
					}
				}
			}
		}

	}
	for (i = 0; i < size; i++)
	{
		img[i] = CBaseColorInfo(imgA[i] * 255, imgA[i] * 255, imgA[i] * 255);
	}

	ShowPicByArray(img, width, height);
	delete[] img;
	delete[] imgA;

}

//����������
void CImageStuDlg::OnHuffman()
{
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int i;
	HuffmanTree ht;
	HuffmanCode hc;
	int w[256] = { 0 };

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			int gray = _grayData[index];
			w[gray]++;
		}
	}

	HuffmanCoding(ht, hc, w, 256);


	std::ofstream SaveFile("a.txt");

	for (i = 1; i <= 256; i++)
	{
		if (w[i - 1] > 0)
			SaveFile << "�Ҷ�" << i - 1 << "����Ϊ:" << hc[i] << "����Ϊ:" << ht[i].weight << endl;
	}
	SaveFile << "TOP100Code��";
	for (i = 0; i < 100; i++)
	{
		SaveFile << hc[_grayData[i] + 1];
	}
	SaveFile.close();

	free(ht);
	for (i = 1; i <= 5; i++)
		free(hc[i]);

}

//��ֵ����
void CImageStuDlg::OnThreshold()
{
	// TO DO: �ڴ���������������
	if (_flag == 0)
	{
		MessageBox(_T("û��ͼ���룡����"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	double T0 = 0, T1 = 0;
	double MinGray = 255, MaxGray = 0;
	double sumA = 0, sumB = 0;
	int countA = 0, countB = 0;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	for (int i = 0; i < size; i++)
	{
		int gray = _grayData[i];
		if (gray < MinGray)
		{
			MinGray = gray;
		}
		if (gray > MaxGray)
		{
			MaxGray = gray;
		}
	}

	T0 = (MaxGray + MinGray) / 2.0;

	while (true)
	{
		sumA = 0;
		sumB = 0;
		countA = 0;
		countB = 0;
		for (int i = 0; i < size; i++)
		{
			int gray = _grayData[i];
			if (gray <= T0)
			{
				sumA += gray;
				countA++;
			}
			else
			{
				sumB += gray;
				countB++;
			}
		}

		double H1 = sumA / countA;
		double H2 = sumB / countB;
		T1 = (H1 + H2) / 2.0;
		if (fabs(T0 - T1) > 0.1)
		{
			T0 = T1;
		}
		else
			break;

	}
	CString strMsg = "";
	strMsg.Format(_T("��ֵΪ��%lf"), T0);
	MessageBox(strMsg);

	for (int i = 0; i < size; i++)
	{
		int gray = _grayData[i];
		if (gray <= T0)
		{
			img[i] = CBaseColorInfo(0, 0, 0);
		}
		else
		{
			img[i] = CBaseColorInfo(255, 255, 255);
		}
	}
	ShowPicByArray(img, width, height);
	delete[] img;
}
