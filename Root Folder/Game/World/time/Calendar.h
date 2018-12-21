#pragma once
#include "../../Resource Management/languages/gametext.h"
#include "../../Resource Management/utils/binaryreader.h"
#include "../../Resource Management/utils/binarywriter.h"
#include "../../Render Engine/basics/window.h"
#include <iostream>



class Calendar
{
public:
	Calendar();
	Calendar(int _day, float _time);
	~Calendar();

	/* ������ʼ�� */
	Calendar init();

	/* ����-��ȡday��time */
	Calendar load(BinaryReader reader);

	/* ����״̬ */
	void update(float delta, Window *w);

	/* ����ʱ��:ÿ����ʱ��ƫ�Ƶ�ʱ���Ҳ�����ͣ�ڼ䣬����ʱ�� */
	void updateTime(float delta);

	/* P��ͣʱ�� */
	void checkPauseTime(Window *w);

	/* Z����ʱ�� X����ʱ�� */
	void checkTimeChange(float delta, Window *w);

	/* ��ӭ��Ϣ */
	void notifyWelcomeMessage();


	/* ʱ�䷶Χ[0,1),�ӽ�0����һ�쿪ʼ���ӽ�1����һ��Ľ��� */
	float getRawTime();

	/* �Ƿ���ҹ��ʱ�� */
	bool isNightTime();

	/* �жϵ�ǰʱ���Ƿ���NotifyTime֮�� */
	bool isAfterNotifyTime();

	/* ��õ�ǰСʱ�� */
	int getTimeHours();

	/* ��õ�ǰ������ */
	int getTimeMinutes();

	/* ��õ�ǰ�������Ľ���ֵ��������ÿ5min�ļ����ʾ */
	int getTimeMinutesNearest(int interval);

	/* ��õ�ǰ���� */
	int getYear();

	/* ��õ�ǰ���� */
	int getQuarter();

	/* ��õ�ǰ���� */
	int getDay();

	/* �浵-�洢day��time */
	void save(BinaryWriter writer);

	std::string formatTimeHours(float timeInHours);
	/* �����Զ����ַ�����ʽ���� */
	std::string formatTimeDays(float timeInDays);


private:
	// 683;Welcome Message Title;Welcome;
	std::string TITLE = GameText::getText(683);
	// 684;Welcome Message;Welcome to Equilinox! Click the flashing task tab and follow the first task to get started.;
	std::string MESSAGE = GameText::getText(684);
	/* 892-897;��\��\ʱ */
	std::string YEAR = GameText::getText(892);
	std::string YEARS = GameText::getText(893);
	std::string DAY = GameText::getText(894);
	std::string DAYS = GameText::getText(895);
	std::string HR = GameText::getText(896);
	std::string HRS = GameText::getText(897);

	float NOTIFY_TIME = 7.03 / 24;	// ��

	float DAY_LENGTH_SECONDS = 720;	// ÿ��=720s
	float CHEAT_DAY_SECONDS = 10;	// CHEATģʽ�£�ÿ��=10s
	float START_TIME = 7 / 24;		// ��ʼʱ��
	float HOURS_IN_DAY = 24;		// ÿ��=24h
	float HOUR_LENGTH = DAY_LENGTH_SECONDS / HOURS_IN_DAY;	// ÿСʱ=30s

	int QUARTERS = 1;				// ÿ��=1����
	int DAYS_PER_QUARTER = 10;		// 1����=10��

	int day;				// ����
	float time;				// �����ĳһ����ʱ��
	bool notified;			// �Ƿ��޸�ʱ��
	bool pauseTime = false;	// �Ƿ���ͣʱ��


};

