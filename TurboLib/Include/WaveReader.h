
#ifndef WAVEREADER_H
#define WAVEREADER_H

//---------------------------------------------------------------
// wave reader
// wave ��Ƶ���ݶ�ȡ��ؽӿ�
//---------------------------------------------------------------

//
// �� wave �ļ����� wave ��ȡ
//
extern T_OBJECT TWaveReaderCreateFromWaveFileW(
	const wchar_t * waveFileName);

//
// ���� wave ��ȡ
//
extern void TWaveReaderDestroy(
	T_OBJECT waveReader);

//
// ��ȡ wave pcm ����
//
extern void TWaveReaderGetPCMParam(
	T_OBJECT waveReader,
	int * pcmDataSize,
	unsigned short * channels,
	unsigned short * bitsPerSample,
	unsigned int * sampleRate);

//
// ��ȡ wave pcm ����
//
extern int TWaveReaderReadPCMData(
	T_OBJECT waveReader,
	void * buffer,
	const int bytesToRead);

#endif // WAVEREADER_H
