
#ifndef WAVEREADER_H
#define WAVEREADER_H

//---------------------------------------------------------------
// wave reader
// wave 音频数据读取相关接口
//---------------------------------------------------------------

//
// 从 wave 文件创建 wave 读取
//
extern T_OBJECT TWaveReaderCreateFromWaveFileW(
	const wchar_t * waveFileName);

//
// 销毁 wave 读取
//
extern void TWaveReaderDestroy(
	T_OBJECT waveReader);

//
// 获取 wave pcm 参数
//
extern void TWaveReaderGetPCMParam(
	T_OBJECT waveReader,
	int * pcmDataSize,
	unsigned short * channels,
	unsigned short * bitsPerSample,
	unsigned int * sampleRate);

//
// 读取 wave pcm 数据
//
extern int TWaveReaderReadPCMData(
	T_OBJECT waveReader,
	void * buffer,
	const int bytesToRead);

#endif // WAVEREADER_H
