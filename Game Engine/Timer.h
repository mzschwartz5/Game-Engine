#ifndef TIME_H
#define TIME_H

class Timer {
public:
	Timer();
	void calcDeltaTime();    // not static, so can only be called by owner of the single instance of this class.
	static double deltaTime; // time between last frame and current frame
private:
	double m_lastFrameTimeStamp;
	static bool instantiated_;
};

#endif