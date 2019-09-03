
#include "stdafx.h"
#include "resource.h"
#include "CMainDlg.h"
#include "RemoteControl/CRemoteControlServer.h"
#include "RemoteControl/CRemoteControlClient.h"
#include "ProcessCleanup/CProcessCleanup.h"
#include "ProcessCleanup/CProcessCleanupConfigFile.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

CMainDlg::CMainDlg(CWnd* pParent) : CDialogEx(IDD_DLG_MAIN, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CMainDlg::OnInitDialog()
{
	wchar_t appPath[520] = { 0 };
	wchar_t imageFileName[520] = { 0 };
	wchar_t configFileName[520] = { 0 };
	wchar_t processExeFileName[520] = { 0 };

	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	TDirectoryGetAppW(appPath, _countof(appPath));

	// 绘制猫猫背景

	//adjustWindowPosToDesktopBottomRight();
	//SetWindowPos(0, 0, 0, 328, 401, SWP_NOREPOSITION); // 令窗口大小等于背景图像大小，姑且先硬编码一下，以后优化
	GetClientRect(&mClientRect);

	mDC = GetDC();
	if (mDC)
	{
		mMemDC.CreateCompatibleDC(mDC);
		mMemBmp.CreateBitmap(mClientRect.Width(), mClientRect.Height(), 1, 32, 0);
		mMemDC.SelectObject(&mMemBmp);

		mGraphics = Gdiplus::Graphics::FromHDC(mMemDC.GetSafeHdc());
		if (mGraphics)
		{
			swprintf_s(imageFileName, L"%sCat\\Image\\Cat.png", appPath);
			mImgBk = Gdiplus::Image::FromFile(imageFileName);
			if (mImgBk)
			{
				mGraphics->DrawImage(mImgBk, 0, 0, mImgBk->GetWidth(), mImgBk->GetHeight());
			}
		}
	}

	onDraw();

	// 从配置文件加载要清理的进程列表

	swprintf_s(configFileName, L"%sCat\\Config\\ProcessCleanup.ini", appPath);
	CProcessCleanupConfigFile::loadW(configFileName);

	// 将要清理的进程告诉进程清理模块

	if (CProcessCleanupConfigFile::firstProcessExeFileNameW(
		processExeFileName,
		_countof(processExeFileName)))
	{
		do 
		{
			CProcessCleanup::addProcessExeFileNameW(processExeFileName);

		} while (CProcessCleanupConfigFile::nextProcessExeFileNameW(
			processExeFileName,
			_countof(processExeFileName)));
	}

	// 启动进程清理模块

	CProcessCleanup::startup(0);

	// 测试配置保存功能

	CProcessCleanupConfigFile::saveW(L"D:\\config.ini");

	return TRUE;
}

LRESULT CMainDlg::OnNcHitTest(CPoint point)
{
	return HTCAPTION;
}

void CMainDlg::onDraw(void)
{
	POINT ptDest = { 0 };
	POINT ptSrc = { 0 };
	SIZE sizeDest = { mClientRect.Width(), mClientRect.Height() };
	BLENDFUNCTION blendFunc = { 0 };

	if (mDC && mGraphics && mImgBk)
	{
		blendFunc.AlphaFormat = AC_SRC_ALPHA;
		blendFunc.BlendFlags = 0;
		blendFunc.BlendOp = AC_SRC_OVER;
		blendFunc.SourceConstantAlpha = 255;

		::UpdateLayeredWindow(
			GetSafeHwnd(),
			mDC->GetSafeHdc(),
			&ptDest,
			&sizeDest,
			mGraphics->GetHDC(),
			&ptSrc,
			0,
			&blendFunc,
			ULW_ALPHA);
	}
}

void CMainDlg::adjustWindowPosToDesktopBottomRight(void)
{
	CRect clientRect;
	int appBarEdge = 0;
	int appBarWidth = 0;
	int appBarHeight = 0;
	int desktopWidth = 0;
	int desktopHeight = 0;
	int wndX = 0;
	int wndY = 0;

	GetClientRect(&clientRect);

	if (TOSInfoGetAppBarEdge(&appBarEdge) &&
		TOSInfoGetAppBarRect(0, 0, &appBarWidth, &appBarHeight) &&
		TOSInfoGetDesktopSize(&desktopWidth, &desktopHeight))
	{
		if (T_APPBAR_EDGE_LEFT == appBarEdge || T_APPBAR_EDGE_TOP == appBarEdge)
		{
			wndX = desktopWidth - clientRect.Width();
			wndY = desktopHeight - clientRect.Height();
		}
		else if (T_APPBAR_EDGE_RIGHT == appBarEdge)
		{
			wndX = desktopWidth - clientRect.Width() - appBarWidth;
			wndY = desktopHeight - clientRect.Height();
		}
		else if (T_APPBAR_EDGE_BOTTOM == appBarEdge)
		{
			wndX = desktopWidth - clientRect.Width();
			wndY = desktopHeight - clientRect.Height() - appBarHeight;
		}

		MoveWindow(
			wndX,
			wndY,
			clientRect.Width(),
			clientRect.Height());
	}
}
