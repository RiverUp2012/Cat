
#pragma once

//
// @brief ��Ϸ�汾ö����
//
enum Bio4Ver {
	Bio4VerUnknown, // δ֪�汾
	Bio4VerOldAsiaV10, // �ϰ汾 �ǰ� v1.0
	Bio4VerOldAsiaV11, // �ϰ汾 �ǰ� v1.1
	Bio4VerOldEuropeV10, // �ϰ汾 ŷ�� v1.0
	Bio4VerOldEuropeV11, // �ϰ汾 ŷ�� v1.1
	Bio4VerHDV16, // �ռ������ v1.06
};

//
// @brief ����Σ�� 4 �ڴ��޸�ģ��
//
class CBio4MemCheat {
public:
	//
	// @brief ����ģ��
	//
	static bool setup(const Bio4Ver & ver);
	//
	// @brief �ر�ģ��
	//
	static void shutdown(void);
	//
	// @brief ��ѯ leon ����ֵ
	//
	static bool queryLeonHP(int & hp);
	//
	// @brief ���� leon ����ֵ
	//
	static bool setLeonHP(const int hp);
	//
	// @brief ��ѯ leon �������ֵ
	//
	static bool queryLeonMaxHP(int & maxHP);
	//
	// @brief ���� leon �������ֵ
	//
	static bool setLeonMaxHP(const int maxHP);
	//
	// @brief ���ӵ�ǰ�ֳֵ�������
	//
	static bool addCurrentItemCount(const int addItemCount);
	//
	// @brief ���ӵ�ǰ�ֳ�ǹе�ӵ�����
	//
	static bool addCurrentGunBulletCount(const int addGunBulletCount);
	//
	// @brief ��ѯ leon �����
	//
	static bool queryLeonPTAS(int & ptas);
	//
	// @brief ���� leon �����
	//
	static bool setLeonPTAS(const int ptas);
};
