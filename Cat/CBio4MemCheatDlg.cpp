
#include "stdafx.h"
#include "CBio4MemCheatDlg.h"
#include "Common/CMFCHelper.h"
#include "Bio4MemCheat/CBio4MemCheat.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(CBio4MemCheatDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_HOW_TO, &CBio4MemCheatDlg::OnBnClickedBtnHowTo)
	ON_BN_CLICKED(IDC_BTN_SETUP, &CBio4MemCheatDlg::OnBnClickedBtnSetup)
	ON_BN_CLICKED(IDC_BTN_SHUTDOWN, &CBio4MemCheatDlg::OnBnClickedBtnShutdown)
	ON_BN_CLICKED(IDC_BTN_ADD_CURRENT_ITEM_COUNT, &CBio4MemCheatDlg::OnBnClickedBtnAddCurrentItemCount)
	ON_BN_CLICKED(IDC_BTN_ADD_HP, &CBio4MemCheatDlg::OnBnClickedBtnAddHp)
	ON_BN_CLICKED(IDC_BTN_ADD_CURRENT_GUN_BULLET, &CBio4MemCheatDlg::OnBnClickedBtnAddCurrentGunBullet)
	ON_BN_CLICKED(IDC_BTN_ADD_PTAS, &CBio4MemCheatDlg::OnBnClickedBtnAddPtas)
END_MESSAGE_MAP()

CBio4MemCheatDlg::CBio4MemCheatDlg(CWnd* pParent)
	: CDialogEx(IDD_DLG_BIO4_MEM_CHEAT, pParent) {

}

CBio4MemCheatDlg::~CBio4MemCheatDlg() {

}

BOOL CBio4MemCheatDlg::OnInitDialog(void) {
	CDialogEx::OnInitDialog();

	if (CMFCHelper::attachDialogControl(this, &mCBBio4Ver, IDC_CB_BIO4_VERSION)) {
		mCBBio4Ver.InsertString(-1, _TEXT("�ϰ汾 ŷ�� v1.0"));
		mCBBio4Ver.InsertString(-1, _TEXT("�ϰ汾 ŷ�� v1.1"));
		mCBBio4Ver.InsertString(-1, _TEXT("�ϰ汾 �ǰ� v1.0"));
		mCBBio4Ver.InsertString(-1, _TEXT("�ϰ汾 �ǰ� v1.1"));
		mCBBio4Ver.SetCurSel(0);
	}

	return TRUE;
}

void CBio4MemCheatDlg::OnBnClickedBtnHowTo() {
	MessageBoxW(
		L"�Դ���ģʽ������Ϸ���ڴ��ڶ����˵����У����ε����Help����Version�����ڵ����ĶԻ����У������ \r\n"
		L"\r\n"
		L"��ʾ��biohazard 4 Ver1.0.0��Ϊ�ǰ� v1.0 \r\n"
		L"��ʾ��biohazard 4 Ver1.1.0��Ϊ�ǰ� v1.1 \r\n"
		L"��ʾ��resident evil 4 Ver1.0.0��Ϊŷ�� v1.0 \r\n"
		L"��ʾ��resident evil 4 Ver1.1.0��Ϊŷ�� v1.1 \r\n",
		L"���ѡ����Ϸ�汾");
}

void CBio4MemCheatDlg::OnBnClickedBtnSetup() {
	Bio4Ver ver = Bio4VerUnknown;
	const int curSel = mCBBio4Ver.GetCurSel();
	if (0 == curSel) ver = Bio4VerOldAsiaV10;
	else if (1 == curSel) ver = Bio4VerOldAsiaV11;
	else if (2 == curSel) ver = Bio4VerOldEuropeV10;
	else if (3 == curSel) ver = Bio4VerOldEuropeV11;
	if (Bio4VerUnknown != ver) {
		CBio4MemCheat::setup(ver);
	}
}

void CBio4MemCheatDlg::OnBnClickedBtnShutdown() {
	CBio4MemCheat::shutdown();
}

void CBio4MemCheatDlg::OnBnClickedBtnAddCurrentItemCount() {
	CBio4MemCheat::addCurrentItemCount(8);
}

void CBio4MemCheatDlg::OnBnClickedBtnAddHp() {
	int maxHP = 0;
	if (CBio4MemCheat::queryLeonMaxHP(maxHP)) {
		CBio4MemCheat::setLeonHP(maxHP);
	}
}

void CBio4MemCheatDlg::OnBnClickedBtnAddCurrentGunBullet() {
	CBio4MemCheat::addCurrentGunBulletCount(12);
}

void CBio4MemCheatDlg::OnBnClickedBtnAddPtas() {
	int ptas = 0;
	if (CBio4MemCheat::queryLeonPTAS(ptas)) {
		CBio4MemCheat::setLeonPTAS(ptas + 10000);
	}
}
