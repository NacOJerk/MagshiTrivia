#pragma once
#include <mutex>

using std::mutex;

template <class E> class locked
{
public:
	locked() : _obj(new E) {}

	locked(E* obj) : _obj(obj) {}

	locked(E* obj, E data) : locked(obj)
	{
		*_obj = data;
	}

	locked(const locked& othr)
	{
		*this = othr;
	}

	locked& operator=(const locked& othr)
	{
		lock.lock();
		if (&othr == this)
			return *this;
		_obj ? delete _obj : 1;
		_obj = new E(*othr._obj);
		lock.unlock();
	}

	~locked()
	{
		lock.lock();
		delete _obj;
		_obj = nullptr;
		lock.unlock();
	}

	operator E*()
	{
		lock.lock();
		return _obj;
	}

	void operator()()
	{
		lock.unlock();
	}



private:
	E* _obj;
	mutex lock;
};