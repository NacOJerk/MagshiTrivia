#include "Game.h"
#include <chrono>
#include <thread>


void Game::runGame()
{
	sendNextQuestion();
	while (true)
	{
		locked_container<bool> running = _running;//lock the run code thingy
		if (!((bool)running))//check if should still be running
		{
			break;
		}
		byte roundOver = isRoundOver();
		if (roundOver)
		{
			testAnswers();
			if (lastQuestion() || roundOver == 2)
			{
				finishGame();
				(bool)running = false;
				break;
			}
			else
			{
				sendNextQuestion();
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));//Sleep for 500ms or 0.5s
		}
	}
}

bool Game::lastQuestion()
{
	return _currentQuestionID == m_question.size();
}

byte Game::isRoundOver()
{
	
	locked_container<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> _users = m_players;//locks stuff
	std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>& users = _users;
	if (users.size() <= 1)
		return 2;
	if (difftime(time(NULL), _currentQuestion.getStartTime()) >= _timeForQuestion)
		return 1;
	bool answered = true;
	for (auto user : users)
	{
		answered = std::get<1>(user).answered;
		if (!answered)
			break;
	}
	return answered ? 1 : 0;
}

void Game::testAnswers()
{
	locked_container<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> _users = m_players;//locks stuff
	std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>& users = _users;
	for (auto user : users)
	{
		StupidMeter sm = BRICK;
		unsigned int timeA = _timeForQuestion;
		if (std::get<1>(user).answered)
		{
			sm = _currentQuestion.getStuipedityRate(std::get<1>(user).answerID);
			timeA = std::get<1>(user).questionAnswer - _currentQuestion.getStartTime();
			//Reset data
			std::get<1>(user).answered = false;
			std::get<1>(user).answerID = -1;
			std::get<1>(user).questionAnswer = time(NULL);
		}
		if (sm != GENIUS)
			std::get<1>(user).wrongAnswerCount += 1;
		else
			std::get<1>(user).currectAnswerCount += 1;
		{
			int totalQuestion = std::get<1>(user).wrongAnswerCount + std::get<1>(user).currectAnswerCount;
			std::get<1>(user).averageAnswerTime = (std::get<1>(user).currectAnswerCount * (totalQuestion - 1) + timeA) / totalQuestion;
		}


	}
}

void Game::finishGame()
{
}

void Game::sendNextQuestion()
{
	if (lastQuestion())
		throw std::exception("You already reached the last question");
	_currentQuestion = QuestionData(m_question[_currentQuestionID++]);
	//sending code ffs do this
}
