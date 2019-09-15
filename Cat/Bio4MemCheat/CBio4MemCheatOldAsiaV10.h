
#pragma once

#include "IBio4MemCheat.h"

//
// @brief ¿œ∞Ê±æ ≈∑∞Ê v1.0
//
class CBio4MemCheatOldAsiaV10 : public IBio4MemCheat {
public:
	bool setup(void) override;
	void shutdown(void) override;
	bool queryLeonHP(int & hp) override;
	bool setLeonHP(const int hp) override;
	bool queryLeonMaxHP(int & maxHP) override;
	bool setLeonMaxHP(const int maxHP) override;
	bool addCurrentItemCount(const int addItemCount) override;
	bool addCurrentGunBulletCount(const int addItemCount) override;
private:
	wlProcess mBio4Process;
};
