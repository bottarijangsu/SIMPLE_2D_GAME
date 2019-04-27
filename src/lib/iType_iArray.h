#pragma once

struct xArray
{
	void* data;
	xArray* prev;
};

typedef void (*ARRAY_METHOD)(void*);

class iArray
{
public:
	iArray(ARRAY_METHOD method);
	virtual ~iArray();

public:
	void addObject(void* data);
	void addObjectAtIndex(int index, void* data);

	void* getObjectAtIndex(int index);

	void removeObjectAtIndex(int index);
	void removeAllObject();

	void removeObject(void* data);

public:
	xArray* node;
	int count;
	ARRAY_METHOD method;
};



