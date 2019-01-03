#pragma once

#include <chrono>
#include "glrequestqueue.h"
#include "glrequest.h"

class GlRequestProcessor
{
private:
	static float MAX_TIME_MILLIS;
	static GlRequestQueue requestQueue;

public:
	//������������
	static void sendRequest(GlRequest request){ requestQueue.addRequest(request); }

	//ִ�ж����е��������ִ��8����
	static void dealWithTopRequests()
	{
		float remainingTime = MAX_TIME_MILLIS * 1000000;
		auto time_now = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
		auto start = time_now.time_since_epoch().count();
		while (requestQueue.hasRequests())
		{
			requestQueue.acceptNextRequest().executeGlRequest();
			auto time_now = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
			auto end = time_now.time_since_epoch().count();
			long timeTaken = end - start;
			remainingTime -= timeTaken;
			start = end;
			if (remainingTime < 0)
				break;
		}
	}

	//�������е�����ִ����
	static void completeAllRequests()
	{
		while (requestQueue.hasRequests())
			requestQueue.acceptNextRequest().executeGlRequest();
	}
};