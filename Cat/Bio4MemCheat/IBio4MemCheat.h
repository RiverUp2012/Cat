
#pragma once

//
// @brief �������ӿ���
//
class IBio4MemCheat {
public:
	//
	// @brief ����������
	//
	virtual bool setup(void) = 0;
	//
	// @brief �ر�������
	//
	virtual void shutdown(void) = 0;
	//
	// @brief ��ѯ leon ����ֵ
	//
	virtual bool queryLeonHP(int & hp) = 0;
	//
	// @brief ���� leon ����ֵ
	//
	virtual bool setLeonHP(const int hp) = 0;
	//
	// @brief ��ѯ leon �������ֵ
	//
	virtual bool queryLeonMaxHP(int & maxHP) = 0;
	//
	// @brief ���� leon �������ֵ
	//
	virtual bool setLeonMaxHP(const int maxHP) = 0;
	//
	// @brief ���ӵ�ǰװ������
	//
	virtual bool addCurrentItemCount(const int addItemCount) = 0;
	//
	// @brief ���ӵ�ǰ�������ӵ�����
	//
	virtual bool addCurrentGunBulletCount(const int addGunBulletCount) = 0;
	//
	// @brief ��ѯ leon ��Ǯ
	//
	virtual bool queryLeonPTAS(int & ptas) = 0;
	//
	// @brief ���� leon ��Ǯ
	//
	virtual bool setLeonPTAS(const int ptas) = 0;
};
