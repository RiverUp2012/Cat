
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
	static bool queryLeonHP(int & hp);
	static bool setLeonHP(const int hp);
	static bool queryLeonMaxHP(int & maxHP);
	static bool setLeonMaxHP(const int maxHP);
	static bool addCurrentItemCount(const int addItemCount);
	static bool addCurrentGunBulletCount(const int addGunBulletCount);
};
