#include "Game.h"
#include <chrono>
#include <thread>
#include "SendQuestionResponse.h"
#include "JsonResponsePacketSerializer.h"
#include "Server.h"
#include "PlayerResult.h"
#include "SendResultsResponse.h"
#include "LeaveRoomResponse.h"

void cleanUp(locked<bool>& _running, GameManager& manager, Game* game)//The most hacky sulution ever
{
	{
		locked_container<bool> running = _running;//Makes sure that run game is done
	}
	manager.removeGame(*game);
}

void Game::runGame()
{
	{
		locked_container<bool> running = _running;
		((bool&)running) = true;
		_currentQuestionID = 0;
		sendNextQuestion();
	}
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
				(bool&)running = false;
				std::thread t(cleanUp, std::reference_wrapper<locked<bool>>(_running), std::reference_wrapper<GameManager>(_manager), this);//clean up
				t.join();
				break;
			}
			else
			{
				sendNextQuestion();
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(50));//Sleep for 500ms or 0.5s
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
	for (std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>::iterator itr = users.begin(); itr != users.end(); itr++)
	{
		StupidMeter sm = BRICK;
		unsigned int timeA = _timeForQuestion;
		LoggedUser& user = itr->first;
		GameData& data = itr->second;
		if (data.answered)
		{
			sm = _currentQuestion.getStuipedityRate(data.answerID);
			timeA = data.questionAnswer - _currentQuestion.getStartTime();
			//Reset data
			
			data.answered = false;
			data.answerID = -1;
			data.questionAnswer = time(NULL);
		}
		if (sm != GENIUS)
			data.wrongAnswerCount += 1;
		else
			data.currectAnswerCount += 1;
		{
			int totalQuestion = data.wrongAnswerCount + data.currectAnswerCount;
			data.averageAnswerTime = (data.currectAnswerCount * (totalQuestion - 1) + timeA) / totalQuestion;
		}
		_base.addQuestionStat(user.getUsername(), timeA, sm);

	}
}

void Game::finishGame()
{
	{
		std::vector<PlayerResult> results;
		std::map<std::string, unsigned int> poses;//To make effecincy from O(n*n) to be o(n) 
		locked_container<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> _users = m_players;//locks stuff
		std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>& users = _users;
		//Getting results
		for (auto user : users)
		{
			results.push_back({ user.first.get().getUsername(), user.second.currectAnswerCount, user.second.wrongAnswerCount, user.second.averageAnswerTime });
		}
		//Sorting results
		std::sort(results.begin(), results.end(), [](PlayerResult a, PlayerResult b)
		{
			return a.currectAnswers == b.currectAnswers ? a.averageTime > b.averageTime : a.currectAnswers > b.currectAnswers;
		});
		//Preparing for data sending
		for (unsigned int i = 0, size = results.size(); i < size; i++)
		{
			poses[results[i].username] = i;
		}
		//sending data
		for (auto user : users)
		{
			_base.addGame(user.first.get().getUsername(), poses[user.first.get().getUsername()] == 0);
			_base.addHighscore(user.first.get().getUsername(), user.second.currectAnswerCount);
			user.first.get().getClient().getPipeManager().write( JsonResponsePacketSerializer::getInstance()->serializeResponse(SendResultsResponse(poses[user.first.get().getUsername()], results)));
			locked_container<IRequestHandler*> _handler = user.first.get().getClient().getHandler();
			IRequestHandler*& handler = _handler;
			delete handler;
			handler = _factory.createMenuRequestHandler(user.first);
			user.first.get().getRoomData().game = 0;
		}
	}
}

void Game::sendNextQuestion()
{
	if (lastQuestion())
		throw std::exception("You already reached the last question");
	else
	{
		_currentQuestion = QuestionData(m_question[_currentQuestionID++]);
		buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(SendQuestionResponse(_currentQuestion.getQuestion(), _currentQuestion.getAnswers(), m_question.size() - _currentQuestionID - 1));
		//sending code ffs do this
		locked_container<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> _users = m_players;//locks stuff
		std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>& users = _users;
		for (auto user : users)
		{
			user.first.get().getClient().getPipeManager().write(buff);
		}
	}
}

void Game::sendHome()
{
	locked_container<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> _users = m_players;//locks stuff
	std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>& users = _users;
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(LeaveRoomResponse(1));
	for (auto user : users)
	{
		user.first.get().getClient().getPipeManager().write(buff);
		locked_container<IRequestHandler*> _handler = user.first.get().getClient().getHandler();
		IRequestHandler*& handler = _handler;
		delete handler;
		handler = _factory.createMenuRequestHandler(user.first);
		user.first.get().getRoomData().game = 0;
	}
}

Game::Game(std::vector<std::reference_wrapper<LoggedUser>> users, std::vector<Question> questions, IDatabase & database, size_t timeForQuestion, RequestHandlerFactory& fact, GameManager& mang, const unsigned int id) : _base(database), m_question(questions), _timeForQuestion(timeForQuestion), _currentQuestionID(-1), _factory(fact), _manager(mang), _id(id)
{
	locked_container<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> _users = m_players;//locks stuff
	std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>& usersMap = _users;
	for (auto user : users)
	{
		user.get().getRoomData().game = _id;
		usersMap[user] = {false, 0, time(NULL), 0, 0, 0};
	}
}

Game::~Game()
{
	stop();
	if(_tr.joinable())
		_tr.join();
}

bool Game::operator==(const Game & b) const
{
	return _id == b._id;
}

bool Game::operator==(const unsigned int & b) const
{
	return _id == b;
}

void Game::start()
{
	{
		locked_container<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> _users = m_players;//locks stuff
		std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>& users = _users;
		for (auto user : users)
		{
			user.first.get().getRoomData().id = 0;
			user.first.get().getRoomData().isAdmin = false;
		}
	}
	_tr = std::thread(&Game::runGame, this);//and cabamo game running	
}

void Game::submitAnswer(LoggedUser & user, unsigned int answer, time_t time)
{
	printf("%s submitted an answer\n", user.getUsername().c_str());
	locked_container<bool> running = _running;//This is used to synchronize stuff
	locked_container<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> _users = m_players;//locks stuff
	std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>& users = _users;
	GameData& data = users[std::reference_wrapper<LoggedUser>(user)];
	data.answered = true;
	data.answerID = answer;
	data.questionAnswer = time;
}

void Game::removePlayer(LoggedUser & user)
{
	locked_container<bool> running = _running;//This is used to synchronize stuff
	locked_container<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> _users = m_players;//locks stuff
	std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>& users = _users;
	users.erase(std::reference_wrapper<LoggedUser>(user));
}

void Game::stop()
{
	locked_container<bool> running = _running;//This is used to synchronize stuff
	if (!(bool&)running)
		return;
	((bool&)running) = false;
	sendHome();
}
