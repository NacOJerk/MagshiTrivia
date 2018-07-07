#pragma once
class GetStatsResponse
{
	 float _winRate;
	 float _successRate;
	 float _stuipidityRate;
	 float _averageTime;
public:
	GetStatsResponse(float winRate, float successRate, float stuipidityRate, float averageTime);
	float getWinRate() const;
	float getSuccessRate() const;
	float getStuipidityRate() const;
	float getAverageTime() const;
};

