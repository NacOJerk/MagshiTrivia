#pragma once
#include <mutex>

using std::mutex;

template <class E> class locked_container;

template <class E> class locked
{
public:
	locked() : _obj(new E) {}

	locked(E* obj) : _obj(obj) {}

	locked(E* obj, E data) : locked(obj)
	{
		*_obj = data;
	}

	locked(E data) : locked(new E, data) {}

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

	operator locked_container<E>()
	{
		return locked_container<E>(*this);
	}

	void operator()()
	{
		lock.unlock();
	}



private:
	E* _obj;
	mutex lock;
};

template <class E> class locked_container
{
	locked<E>& _lock;
	E* pointer;

public:
	locked_container(locked<E>& lock) : _lock(lock)
	{
		pointer = _lock;
	}
	~locked_container()
	{
		pointer = nullptr;
		_lock();
	}

	operator E&()
	{
		return *pointer;
	}

};