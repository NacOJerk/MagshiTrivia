#include "GetStatsResponse.h"

GetStatsResponse::GetStatsResponse(float winRate, float successRate, float stuipidityRate, float averageTime) : _winRate(winRate), _successRate(successRate), _stuipidityRate(stuipidityRate), _averageTime(averageTime)
{
}

float GetStatsResponse::getWinRate() const
{
	return _winRate;
}

float GetStatsResponse::getSuccessRate() const
{
	return _successRate;
}

float GetStatsResponse::getStuipidityRate() const
{
	return _stuipidityRate;
}

float GetStatsResponse::getAverageTime() const
{
	return _averageTime;
}
