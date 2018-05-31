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

	// 图像已打开标记
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

	// 绘图
	CDC * pDC = GetDC();
	if (_flag == true) {

		// 已经打开文件
		SetDIBitsToDevice(
			pDC->m_hDC  // 设备描述表
			, 0 // 设备描述表位图输出的起始逻辑x坐标
			, 0 // 设备描述表位图输出的起始逻辑y坐标
			, _infoHeader.biWidth // DIB的宽度
			, _infoHeader.biHeight // DIB的高度
			, 0 // DIB开始读取输出的像素数据的x位置
			, 0 // DIB开始读取输出的像素数据的y位置
			, 0 // DIB中像素的水平行号, 对应lpBits内存缓冲区的第一行数据
			, _infoHeader.biHeight  // DIB的行数
			, _lpBuf  // 像素数据
			, _bitmapInfo //BITMAPINFO数据
			, DIB_RGB_COLORS // 显示的颜色
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
// 销毁对话框, 映射WM_DESTORY消息
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
/*                           菜单                                       */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// "文件"-->"打开"(IDC_FILE_OPEN)
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileOpen()
{
	// TO DO: Add your command handler code here

	LPCTSTR lpszFilter = LPCTSTR(_T("BMP Files(*.bmp)|*.bmp|任何文件|*.*|"));
	CFileDialog dlg(TRUE, lpszFilter, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		lpszFilter, NULL);
	// 文件名
	CString fileName;
	CFile file;
	// 打开文件
	if (dlg.DoModal() == IDOK) {

		// 文件名
		fileName = dlg.GetPathName();
		if (file.Open(fileName, CFile::modeRead | CFile::shareDenyNone, NULL) == 0) {
			// 读取文件失败
			AfxMessageBox(_T("无法打开文件"), MB_OK, MB_ICONERROR);
			return;
		}

		// 读取文件头
		if (!ReadFileHeader(file)) {
			return;
		}

		// 读取信息头 
		if (!ReadInfoHeader(file)) {
			return;
		}

		// 若前面已有文件打开，则释放相应的数据
		if (_flag == true) {
			FreeData();
			_flag = false;
		}

		// 计算调色板颜色数量
		_numQuad = CalcQuadNum();
		// 读取调色板数据
		ReadQuad(file);

		// 判断图像类型
		_imageType = CalcImageType();

		// 读入图像数据
		ReadImageData(file);




		// 分配处理后的数据
		_processBuf = (BYTE *)HeapAlloc(GetProcessHeap(), 0, _infoHeader.biSizeImage);

		// 宽度不是4的倍数则补齐
		DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
		if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;



		Invalidate();

		int width = _infoHeader.biWidth;
		int height = _infoHeader.biHeight;

		// 分配空间
		_colorData = new CBaseColorInfo[width * height];
		_grayData = new int[width * height];

		// 根据图像类型，将其转换成相应的图像数据
		if (_imageType == COLOR_24_BIT) {
			// 24位颜色图像
			BMPConvertColor24();

		}
		else if (_imageType == COLOR_8_BIT) {
			// 256彩色图像
			BMPConvertColor8();
		}
		else if (_imageType == GRAY_8_BIT) {
			// 256灰度图像
			BMPConvertGray8();
			// 将8位灰度数据转成用24位颜色
			Gray8ConvertColor24(_grayData, _colorData, width, height);
		}
		else {
			MessageBox(_T("暂不支持该图像类型"));
			// 关闭图像
			file.Close();
			FreeData();
			return;
		}

		// 图像读取完毕
		file.Close();
		_flag = true;

	}

}


//////////////////////////////////////////////////////////////////////////
// "文件"-->"显示数组图像"
// 将转换后的24位彩色数据在对话框中显示
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileShowArray()
{
	// TO DO: Add your command handler code here

	if (_flag == FALSE) {
		MessageBox(_T("没有打开图像"));
		return;
	}

	CDlgShowArray dlg;
	dlg.SetColorData(_colorData);
	dlg.SetWidth(_infoHeader.biWidth);
	dlg.SetHeight(_infoHeader.biHeight);
	dlg.DoModal();

}


//////////////////////////////////////////////////////////////////////////
// "文件"-->"保存"菜单
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileSave()
{
	// TO DO: Add your command handler code here
	if (!_flag) {
		MessageBox(_T("没有图片，无法保存"));
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
/*                         私有函数                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// 读取文件头
// 参数:
//   file: CFile &, BMP文件
// 返回值:
//   BOOL, TRUE: 成功; FALSE: 失败
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadFileHeader(CFile &file) {

	// 读取文件头
	file.Read(&_fileHeader, sizeof(_fileHeader));
	// 判断是否为BMP文件
	if (_fileHeader.bfType != 0x4d42) {
		// "BM"
		AfxMessageBox(_T("不是BMP文件"), MB_OK, MB_ICONERROR);
		return FALSE;
	}

	// 判断文件是否损坏(文件大小是否与文件头的信息一致)
	if (file.GetLength() != _fileHeader.bfSize) {
		AfxMessageBox(_T("文件已损坏"), MB_OK, MB_ICONERROR);
		return FALSE;
	}

	return TRUE;

}


//////////////////////////////////////////////////////////////////////////
// 读取文件信息头
// 参数:
//   file: CFile &, 已经打开的BMP文件
// 返回值:
//   BOOL, TRUE成功; 其它失败
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadInfoHeader(CFile &file) {

	// 读取文件信息头
	file.Read(&_infoHeader, sizeof(_infoHeader));

	// 将图片格式限定在8位图像
	// 	if( _infoHeader.biBitCount != 8 ){
	// 		AfxMessageBox( "必须为8位灰度图", MB_OK, MB_ICONERROR );
	// 		return FALSE;
	// 	}

	return TRUE;

}


//////////////////////////////////////////////////////////////////////////
// 释放数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::FreeData() {

	HeapFree(GetProcessHeap(), 0, _bitmapInfo);
	HeapFree(GetProcessHeap(), 0, _lpBuf);
	// 处理后的数据
	HeapFree(GetProcessHeap(), 0, _processBuf);
	// 灰度颜色数据
	delete[] _grayData;
	// 彩色颜色数据
	delete[] _colorData;



}

//////////////////////////////////////////////////////////////////////////
// 计算调色板颜色数量
// 参数: 无
// 返回值:
//   int, 调色板颜色数量
//////////////////////////////////////////////////////////////////////////
int CImageStuDlg::CalcQuadNum() {

	// 计算调色板数据
	int numQuad = 0;
	if (_infoHeader.biBitCount < 24) {
		// 相当于2的biBitCount次方
		numQuad = (1 << _infoHeader.biBitCount);
	}

	return numQuad;

}

//////////////////////////////////////////////////////////////////////////
// 读取调色板数据
// 参数:
//   file: CFile &, BMP文件
// 返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadQuad(CFile &file) {

	// 为图像信息pbi申请空间
	_bitmapInfo = (BITMAPINFO *)HeapAlloc(
		GetProcessHeap(),
		0,
		sizeof(BITMAPINFOHEADER) + _numQuad * sizeof(RGBQUAD)
	);
	memcpy(_bitmapInfo, &_infoHeader, sizeof(_infoHeader));
	_quad = (RGBQUAD *)((BYTE *)_bitmapInfo + sizeof(BITMAPINFOHEADER));

	// 读取调色板
	if (_numQuad != 0) {
		file.Read(_quad, sizeof(RGBQUAD) * _numQuad);
	}

}

//////////////////////////////////////////////////////////////////////////
// 判断是否为256色灰度图
// 判断依据，调色板中所有颜色的的RGB三个分量应该相等
// BOOL: TRUE为256色灰度图
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
// 读入图像数据
// 参数:
//   file: CFile &, BMP图像
// 返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadImageData(CFile &file) {

	// 为图像数据申请空间
	_infoHeader.biSizeImage = _fileHeader.bfSize - _fileHeader.bfOffBits;
	_lpBuf = (BYTE *)HeapAlloc(GetProcessHeap(), 0, _infoHeader.biSizeImage);
	// 读取图像数据
	file.Read(_lpBuf, _infoHeader.biSizeImage);

}

//////////////////////////////////////////////////////////////////////////
// 判断图像类型
// 参数: 无
// 返回值: IMAGE_TYPE, 图像类型, 参数枚举IMAGE_TYPE的定义
//////////////////////////////////////////////////////////////////////////
IMAGE_TYPE CImageStuDlg::CalcImageType() {

	IMAGE_TYPE type = COLOR_24_BIT;
	if (_infoHeader.biBitCount == IMAGE_TYPE_BIT_24) {
		// 24彩色图像
		type = COLOR_24_BIT;
		//MessageBox( "24位图像" );
	}
	else if (_infoHeader.biBitCount == IMAGE_TYPE_BIT_1) {
		// 二值图像　
		type = GRAY_1_BIT;
		//MessageBox( "1位图像" );
	}
	else if (_infoHeader.biBitCount == IMAGE_TYPE_BIT_8) {
		// 8位
		if (Is256Gray()) {
			// 8位灰度图像
			type = GRAY_8_BIT;
			//MessageBox( "8位灰度图像" );
		}
		else {
			// 8位彩色图像
			type = COLOR_8_BIT;
			//MessageBox( "8位彩色图像" );
		}
	}

	return type;

}

//////////////////////////////////////////////////////////////////////////
// 将BMP数据转换成24位颜色数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor24() {

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据

	int i, j;

	for (i = 0; i <= height - 1; i++) {
		for (j = 0; j <= width - 1; j++) {

			// BMP图片数据中的坐标
			DWORD index = i * 3 * width + 3 * j;
			if (dwBytes % 3 != 0) {
				index = i * dwBytes + 3 * j;
			}
			// 颜色数组中的坐标
			DWORD resultIndex = (height - 1 - i) * width + j;
			_colorData[resultIndex].SetRed(_lpBuf[index + 2]);
			_colorData[resultIndex].SetGreen(_lpBuf[index + 1]);
			_colorData[resultIndex].SetBlue(_lpBuf[index]);

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// 将8位彩色BMP数据转成24位颜色数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor8() {

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据
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

			// BMP图片数据中的坐标
			DWORD index = i * dwBytes + j;

			// 颜色数组中的坐标
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
// 将8位灰度BMP数据转成8位灰度数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertGray8() {

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据
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

			// BMP图片数据中的坐标
			DWORD index = i * dwBytes + j;

			// 颜色数组中的坐标
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
// 将8位灰度数据转成用24位颜色
// 灰度图的RGB值均相同
// 参数:
//   grayData: BYTE *, 灰度数据
//   colorData: CBaseColorInfo *, 24位颜色数据
//   width: 图片宽度
//   height: 图片高度
//  返回值: 无
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

// 将8位灰度数据转成用24位颜色
void CImageStuDlg::Gray8ConvertColor24(int * grayData, CBaseColorInfo * colorData, int width, int height) {

	int length = width * height;
	for (int i = 0; i <= length - 1; i++) {
		colorData[i].SetRed(grayData[i]);
		colorData[i].SetGreen(grayData[i]);
		colorData[i].SetBlue(grayData[i]);
	}

}

//////////////////////////////////////////////////////////////////////////
// 显示图像(通过图像数组,彩色图像)
// 参数:
//   colorData: CBaseColorInfo, 颜色数据
//   width: int, 图像宽度
//   height: int, 图像高度
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray(CBaseColorInfo * colorData,
	int width,
	int height) {

	CDlgShowArray dlg;
	// 图像数据(24位彩色图像)
	dlg.SetColorData(colorData);
	// 图像宽度
	dlg.SetWidth(width);
	// 图像高度
	dlg.SetHeight(height);
	// 显示对话框
	dlg.DoModal();

}




//////////////////////////////////////////////////////////////////////////
// 显示图像(通过图像数组, 灰度图像)
// 参数:
//   colorData: CBaseColorInfo, 灰度图像数据
//   width: int, 图像宽度
//   height: int, 图像高度
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray(int * grayData, int width, int height) {

	// 将灰度图像转成彩色图像
	CBaseColorInfo * colorData = new CBaseColorInfo[width * height];
	Gray8ConvertColor24(grayData, colorData, width, height);

	CDlgShowArray dlg;
	// 图像数据(24位彩色图像)
	dlg.SetColorData(colorData);
	// 图像宽度
	dlg.SetWidth(width);
	// 图像高度
	dlg.SetHeight(height);
	// 显示对话框
	dlg.DoModal();

	// 释放彩色图像
	delete[] colorData;

}


//////////////////////////////////////////////////////////////////////////
// 功能：保存BMP图片
// 参数：
//   bmpName: char *, 文件名(含路径、文件后缀)
//   imgBuf: unsigned char *, 图像数据
//   width: int, 图像宽度
//   height: int, 图像高度
//   biBitCount: int, 像素深度
//   pColorTable: RGBAUAD *, 颜色表
//////////////////////////////////////////////////////////////////////////
bool CImageStuDlg::SaveAsBmp(char * bmpName,
	unsigned char * imgBuf,
	int width,
	int height,
	int biBitCount,
	RGBQUAD * pColorTable
) {

	// 如果位图数据为空，则没有数据传入
	if (!imgBuf) {
		return false;
	}

	// 颜色表大小，以字节为单位，灰度图像颜色表为1024，彩色图像颜色表大小为0
	int colorTableSize = 0;
	if (biBitCount == 8) {
		colorTableSize = 1024; // 感觉不一定正确
	}

	// 将带存储图像数据每行字节数转为4的倍数
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	// 以二进制的写的方式打开文件
	FILE *fp = fopen(bmpName, "wb");
	if (!fp) {
		return false;
	}

	// 申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;// bmp类型
	// bfSize是图像文件4个组成部分之和
	fileHead.bfSize = sizeof(BITMAPFILEHEADER)
		+ sizeof(BITMAPINFOHEADER)
		+ colorTableSize
		+ lineByte * height; // 图像数据字节数
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	// bfOffBits是图像文件前三部分所需空间之和
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize;
	// 文件头写入文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

	// 申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head;
	head.biSize = sizeof(BITMAPINFOHEADER); // 位图信息头结构的大小(40个字节)
	head.biWidth = width;// 图像宽度，以像素为单位
	head.biHeight = height;// 图像高度，以像素为单位
	head.biPlanes = 1;// 必须为1
	head.biBitCount = biBitCount; // 像素深度，每个像素的为数(bit数)
	head.biCompression = BI_RGB; // 图像是否压缩，一般是未压缩的
	head.biSizeImage = lineByte * height; // 实际的位图数据占据的字节数
	head.biXPelsPerMeter = 0; // 目标设备的水平分辨率
	head.biYPelsPerMeter = 0; // 目标设备的垂直分辨率
	head.biClrUsed = 0; // 本图像实际用到的颜色数
	head.biClrImportant = 0; // 本图像重要的颜色，如果为0，则所有的颜色均重要 

	// 写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	// 如果图像时灰度图像，有颜色表，写入文件
	if (biBitCount == 8) {
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	// 写位图数据进文件
	fwrite(imgBuf, height * lineByte, 1, fp);

	// 关闭文件
	fclose(fp);

	return true;

}


//全红
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

//红蓝相间
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
//彩色-》灰度
void CImageStuDlg::OnColorGray()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//灰度-》黑白
void CImageStuDlg::OnGrayBlack()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//灰度分辨率
void CImageStuDlg::OnGRAYRESOlV()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//直接缩放
void CImageStuDlg::OnDirectScaling()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//最近邻插值
void CImageStuDlg::OnScall2()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//双线性插值
void CImageStuDlg::OnScall3()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//平移
void CImageStuDlg::OnTranslation()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//水平镜像
void CImageStuDlg::OnHorizontal()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//垂直镜像
void CImageStuDlg::OnVertical()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//转置
void CImageStuDlg::OnTranspose()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//取反
void CImageStuDlg::OnTakeBack()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//冥次变换
void CImageStuDlg::OnHadesTrans()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//对数变换
void CImageStuDlg::OnLogTrans()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//分段函数
void CImageStuDlg::OnPiecewise()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//位平面
void CImageStuDlg::OnWeipingmian()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//均衡化
void CImageStuDlg::OnJunhenghua()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

	for (int i = 0; i < size; i++)//计算累计值
	{
		int gray = _grayData[i];
		count[gray]++;
	}

	for (int i = 0; i < 255; i++)//归一化
	{
		count2[i] = (double)count[i] / size;
	}

	count3[0] = count2[0];

	for (int i = 1; i < 255; i++)//计算归一化后累计值
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

//均值滤波快速计算
void CImageStuDlg::OnJunZhiLvBo()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//加权滤波
void CImageStuDlg::OnJiaQuanLvBo()
{

	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//邻域阈值
void CImageStuDlg::OnLinYuYuZhi()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//2D中值滤波
void CImageStuDlg::On2dZhongzhi()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//2D中值滤波（十字）
void CImageStuDlg::On2dZhongzhiShizi()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//拉普拉斯算子
void CImageStuDlg::OnLaplace()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//Sobel 算子
void CImageStuDlg::OnSobel()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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
		MessageBox(_T("没有图像导入！！！"));
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
			//归一化
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

				//饱和度
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

//256灰度->216彩色
void CImageStuDlg::On256gray216color()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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
		MessageBox(_T("没有图像导入！！！"));
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
			//归一化
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

				//饱和度
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

//RGB->HSI->H加60°
void CImageStuDlg::OnRGBHSIHAdd60()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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
			//归一化
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

				//饱和度
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

		//H增加60度
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

//RGB->HSI->S减50%
void CImageStuDlg::OnRGBHSISCut50()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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
			//归一化
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

				//饱和度
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

		//S减少50%
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

//RGB->HSI->I减50%
void CImageStuDlg::OnRGBHSIICut50()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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
			//归一化
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

				//饱和度
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
		//I降低50%
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

//图像膨胀
void CImageStuDlg::OnExpand()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//图像腐蚀
void CImageStuDlg::OnDilation()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//开操作,先腐蚀再膨胀
void CImageStuDlg::OnOpen()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//图像闭操作，先膨胀再腐蚀
void CImageStuDlg::OnClose()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//图像填充
void CImageStuDlg::OnFill()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;

	int pointX = 132, pointY = 128;
	int point = pointY * width + pointX;

	int* img = new int[size]; //二值化图像0，255
	int* imgA = new int[size];//原图像0，1
	int* imgB = new int[size];//原图像补集
	int* imgX = new int[size];//膨胀图像
	int i;
	int countX1 = 1, countX2 = 0; //判断两次imgX点数是否一样

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

	int gray = img[point];//生成A图,B图

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
		imgX = Expland(width, height, imgX);//膨胀X图		
		imgX = Mixed(size, imgX, imgB);//和B图做交集
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

//求边界
void CImageStuDlg::OnBoard()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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

//求连通区域
void CImageStuDlg::OnConnectedArea()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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
	for (i = 0; i < size; i++) //二值化以及矩阵初始化
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
	for (i = 0; i < size; i++)//查找起始点
	{
		if (imgA[i] == 1 && imgL[i] == 0)
		{
			p = i;
			break;
		}
	}
	while (p != -1)
	{
		for (i = 0; i < size; i++)//查找起始点
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
				ExplandTempA(width, height, tempA);//膨胀tempA
				MixTempA(size, imgA, tempA, tempB);//将tempA和imgA交集得到TempB
				if (!CompareAB(size, tempB, tempC))//对比TempA和TempB
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
			for (i = 0; i < size; i++)//遍历图像tempA，将tempA中为1的点在图像L中设为变量label的值
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

//细化
void CImageStuDlg::OnThin()
{

	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
		return;
	}

	// 细化表
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
			imgA[i] = 1;//黑色
		}
		else
		{
			imgA[i] = 0;//白色
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

//哈夫曼编码
void CImageStuDlg::OnHuffman()
{
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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
			SaveFile << "灰度" << i - 1 << "编码为:" << hc[i] << "数量为:" << ht[i].weight << endl;
	}
	SaveFile << "TOP100Code：";
	for (i = 0; i < 100; i++)
	{
		SaveFile << hc[_grayData[i] + 1];
	}
	SaveFile.close();

	free(ht);
	for (i = 1; i <= 5; i++)
		free(hc[i]);

}

//阈值计算
void CImageStuDlg::OnThreshold()
{
	// TO DO: 在此添加命令处理程序代码
	if (_flag == 0)
	{
		MessageBox(_T("没有图像导入！！！"));
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
	strMsg.Format(_T("阈值为：%lf"), T0);
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
