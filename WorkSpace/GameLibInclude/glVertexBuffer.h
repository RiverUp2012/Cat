
#pragma once

#include "glNonCopyable.h"

struct IDirect3DVertexBuffer9;

//
// @brief ∂•µ„ª∫≥Â«¯¿‡
//
class glVertexBuffer : public glNonCopyable {
public:
	glVertexBuffer();
	virtual ~glVertexBuffer();
public:
	bool create(const int size, const int fvf);
	void destroy(void);
	bool isAlready(void) const;
	void * lock(const int offset = 0, const int size = 0);
	bool unlock(void);
	IDirect3DVertexBuffer9 * getIDirect3DVertexBuffer9(void) const;
private:
	IDirect3DVertexBuffer9 * mD3DVB9;
};
