
#include "../GameLibInclude/glMemFile.h"

glMemFile::glMemFile() {
	mBuffer = 0;
	mBufferSize = 0;
	mFilePointer = 0;
	mAutoDelete = false;
}

glMemFile::~glMemFile() {
	close();
}

void glMemFile::open(const void * buffer, const int bufferSize, const bool autoDelete) {
	close();
	mBuffer = (unsigned char *)buffer;
	mBufferSize = bufferSize;
	mFilePointer = 0;
	mAutoDelete = autoDelete;
}

void glMemFile::close(void) {
	if (mBuffer && mAutoDelete) {
		delete[] mBuffer;
	}
	mBuffer = 0;
	mBufferSize = 0;
	mFilePointer = 0;
}

bool glMemFile::isAlready(void) const {
	return mBuffer && mBufferSize > 0;
}

bool glMemFile::isEndOfFile(bool & endOfFile) {
	if (mBuffer) {
		endOfFile = mFilePointer >= mBufferSize ? true : false;
		return true;
	}
	return false;
}

bool glMemFile::seekToBegin(void) {
	mFilePointer = 0;
	return true;
}

bool glMemFile::seekToEnd(void) {
	if (mBuffer) {
		mFilePointer = mBufferSize;
		return true;
	}
	return false;
}

bool glMemFile::seekTo(const int pos) {
	if (mBuffer && pos >= 0 && pos <= mBufferSize) {
		mFilePointer = pos;
		return true;
	}
	return false;
}

bool glMemFile::seekOffset(const int offset) {
	if (mBuffer && mFilePointer + offset >= 0 && mFilePointer + offset <= mBufferSize) {
		mFilePointer += offset;
		return true;
	}
	return false;
}

bool glMemFile::getPointer(int & pointer) {
	if (mBuffer) {
		pointer = mFilePointer;
		return true;
	}
	return false;
}

bool glMemFile::getFileSize(int & fileSize) {
	if (mBuffer) {
		fileSize = mBufferSize;
		return true;
	}
	return false;
}

bool glMemFile::write(const void * data, const int bytesToWrite) {
	const unsigned char * dataTemp = (const unsigned char *)data;
	if (mBuffer && dataTemp && bytesToWrite > 0 && mFilePointer + bytesToWrite <= mBufferSize) {
		for (int i = 0; i < bytesToWrite; ++i) {
			mBuffer[i + mFilePointer] = dataTemp[i];
		}
		return true;
	}
	return false;
}

bool glMemFile::read(void * data, const int bytesToRead) {
	unsigned char * dataTemp = (unsigned char *)data;
	if (mBuffer && dataTemp && bytesToRead > 0 && mFilePointer + bytesToRead <= mBufferSize) {
		for (int i = 0; i < bytesToRead; ++i) {
			dataTemp[i] = mBuffer[i + mFilePointer];
		}
		return true;
	}
	return false;
}
