
#ifndef COMPILECONFIG_H
#define COMPILECONFIG_H

//
// 是否使用 Direct3D 9
//
// 若关闭该宏，D3D 9 绘图设备接口依旧可用，但所有的调用必然失败
//
#define T_USE_D3D9

//
// 是否使用 DirectSound 8
//
// 若关闭该宏，DS 8 音频设备接口依旧可用，但所有的调用必然失败
//
#define T_USE_DS8

#endif // COMPILECONFIG_H
