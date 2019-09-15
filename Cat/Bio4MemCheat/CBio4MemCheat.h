
#pragma once

//
// @brief 游戏版本枚举体
//
enum Bio4Ver {
	Bio4VerUnknown, // 未知版本
	Bio4VerOldAsiaV10, // 老版本 亚版 v1.0
	Bio4VerOldAsiaV11, // 老版本 亚版 v1.1
	Bio4VerOldEuropeV10, // 老版本 欧版 v1.0
	Bio4VerOldEuropeV11, // 老版本 欧版 v1.1
};

//
// @brief 生化危机 4 内存修改模块
//
class CBio4MemCheat {
public:
	//
	// @brief 启动模块
	//
	static bool setup(const Bio4Ver & ver);
	//
	// @brief 关闭模块
	//
	static void shutdown(void);
	static bool queryLeonHP(int & hp);
	static bool setLeonHP(const int hp);
	static bool queryLeonMaxHP(int & maxHP);
	static bool setLeonMaxHP(const int maxHP);
	static bool addCurrentItemCount(const int addItemCount);
	static bool addCurrentGunBulletCount(const int addGunBulletCount);
};
