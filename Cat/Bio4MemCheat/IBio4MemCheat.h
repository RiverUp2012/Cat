
#pragma once

//
// @brief 作弊器接口类
//
class IBio4MemCheat {
public:
	//
	// @brief 启动作弊器
	//
	virtual bool setup(void) = 0;
	//
	// @brief 关闭作弊器
	//
	virtual void shutdown(void) = 0;
	//
	// @brief 查询 leon 生命值
	//
	virtual bool queryLeonHP(int & hp) = 0;
	//
	// @brief 设置 leon 生命值
	//
	virtual bool setLeonHP(const int hp) = 0;
	//
	// @brief 查询 leon 最大生命值
	//
	virtual bool queryLeonMaxHP(int & maxHP) = 0;
	//
	// @brief 设置 leon 最大生命值
	//
	virtual bool setLeonMaxHP(const int maxHP) = 0;
	//
	// @brief 增加当前装备数量
	//
	virtual bool addCurrentItemCount(const int addItemCount) = 0;
};
