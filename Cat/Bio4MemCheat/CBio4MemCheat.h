
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
	Bio4VerHDV16, // 终极高清版 v1.06
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
	//
	// @brief 查询 leon 生命值
	//
	static bool queryLeonHP(int & hp);
	//
	// @brief 设置 leon 生命值
	//
	static bool setLeonHP(const int hp);
	//
	// @brief 查询 leon 最大生命值
	//
	static bool queryLeonMaxHP(int & maxHP);
	//
	// @brief 设置 leon 最大生命值
	//
	static bool setLeonMaxHP(const int maxHP);
	//
	// @brief 增加当前手持道具数量
	//
	static bool addCurrentItemCount(const int addItemCount);
	//
	// @brief 增加当前手持枪械子弹数量
	//
	static bool addCurrentGunBulletCount(const int addGunBulletCount);
	//
	// @brief 查询 leon 金币数
	//
	static bool queryLeonPTAS(int & ptas);
	//
	// @brief 设置 leon 金币数
	//
	static bool setLeonPTAS(const int ptas);
};
