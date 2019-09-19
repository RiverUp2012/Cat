
#pragma once

#include "glNonCopyable.h"

//
// @brief ÎÄ¼þÀà
//
class glFile : public glNonCopyable {
public:
	glFile();
	virtual ~glFile();
public:
	bool openW(
		const wchar_t * fileName,
		const bool forRead,
		const bool forWrite);
	bool openA(
		const char * fileName,
		const bool forRead,
		const bool forWrite);
	void close(void);
	bool isAlready(void) const;
	bool isEndOfFile(bool & endOfFile);
	bool isForRead(void) const;
	bool isForWrite(void) const;
	bool seekToBegin(void);
	bool seekToEnd(void);
	bool seekTo(const long long int pos);
	bool seekOffset(const long long int offset);
	bool getPointer(long long int & pointer);
	bool getFileSize(long long int & fileSize);
	bool write(const void * data, const int bytesToWrite);
	bool read(void * data, const int bytesToRead);
	const unsigned char * getViewPointer(void) const;
private:
	void * mFileHandle;
	void * mMappingHandle;
	bool mForRead;
	bool mForWrite;
	unsigned char * mView;
};
