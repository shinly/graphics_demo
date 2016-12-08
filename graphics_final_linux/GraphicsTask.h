#pragma once
class IGraphicsTask
{
public:
	IGraphicsTask(void);
	~IGraphicsTask(void);

	virtual void executeTask();
};

