
#pragma once

#include "IBio4MemCheat.h"

//
// @brief ÖÕ¼«¸ßÇå°æ v1.06
//
class CBio4MemCheatHDV16 : public IBio4MemCheat {
public:
	CBio4MemCheatHDV16();
public:
	bool setup(void) override;
	void shutdown(void) override;
	bool queryLeonHP(int & hp) override;
	bool setLeonHP(const int hp) override;
	bool queryLeonMaxHP(int & maxHP) override;
	bool setLeonMaxHP(const int maxHP) override;
	bool addCurrentItemCount(const int addItemCount) override;
	bool addCurrentGunBulletCount(const int addItemCount) override;
	bool queryLeonPTAS(int & ptas) override;
	bool setLeonPTAS(const int ptas) override;
private:
	wlProcess mBio4Process;
	int mBio4ModuleBaseAddress;
};
