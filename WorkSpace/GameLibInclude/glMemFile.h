
#pragma once

#include "glNonCopyable.h"

//
// @brief 内存文件类
//
class glMemFile : public glNonCopyable {
public:
	glMemFile();
	virtual ~glMemFile();
public:
	void open(const void * buffer, const int bufferSize, const bool autoDelete);
	void close(void);
	bool isAlready(void) const;
	bool isEndOfFile(bool & endOfFile);
	bool seekToBegin(void);
	bool seekToEnd(void);
	bool seekTo(const int pos);
	bool seekOffset(const int offset);
	bool getPointer(int & pointer);
	bool getFileSize(int & fileSize);
	bool write(const void * data, const int bytesToWrite);
	bool read(void * data, const int bytesToRead);
private:
	unsigned char * mBuffer;
	int mBufferSize;
	int mFilePointer;
	bool mAutoDelete;
};
