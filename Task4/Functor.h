#pragma once

#include "C:\Users\nguyenhanh\Documents\Visual Studio 2013\Projects\GenScatterHierarchy\GenScatterHierarchy\loki\include\loki\Typelist.h"
#include "C:\Users\nguyenhanh\Documents\Visual Studio 2013\Projects\GenScatterHierarchy\GenScatterHierarchy\loki\include\loki\EmptyType.h"

class NullType {};
#define TYPELIST_1(x)           Loki::Typelist< x, NullType>
#define TYPELIST_2(x, y)        Loki::Typelist< x, TYPELIST_1(y)>
#define TYPELIST_3(x, y, z)     Loki::Typelist< x, TYPELIST_2(y,z)>




template <typename R, class TList>
class FunctorImpl;

template <typename R>
class FunctorImpl<R, NullType>
{
public:
	typedef R ResultType;
	virtual R operator()() = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};
template <typename R, typename P1>
class FunctorImpl<R, TYPELIST_1(P1)>
{
public:
	typedef R ResultType;
	virtual R operator()(P1) = 0;
	virtual FunctorImpl* Clone() const = 0;
	typedef typename P1 Parm1;
	virtual ~FunctorImpl() {}
};
template <typename R, typename P1, typename P2>
class FunctorImpl<R, TYPELIST_2(P1, P2)>
{
public:
	typedef R ResultType;
	virtual R operator()(P1, P2) = 0;
	virtual FunctorImpl* Clone() const = 0;
	typedef typename P1 Parm1;
	typedef typename P2 Parm2;
	virtual ~FunctorImpl() {};
};

template <class ParentFunctor, typename Fun>
class FunctorHandler
	: public ParentFunctor::Impl

{
public:
	typedef typename ParentFunctor::Impl Base;
	typedef typename Base::ResultType ResultType;
	typedef typename Base::Parm1 Parm1;
	typedef typename Base::Parm2 Parm2;
	typedef typename Base::ResultType ResultType;
	FunctorHandler(const Fun& fun) : fun_(fun) {}
	FunctorHandler* Clone() const
	{
		return new FunctorHandler(*this);
	}
	ResultType operator()()
	{
		return fun_();
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1)
	{
		return fun_(p1);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1,
		typename ParentFunctor::Parm2 p2)
	{
		return fun_(p1, p2);
	}
private:
	Fun fun_;
};

template <typename R, class TList>
//template <typename R, typename P1, typename P2>

class Functor
{
public:
	typedef TList ParmList;
	typedef typename Loki::TL::TypeAtNonStrict<TList, 0, Loki::EmptyType>::Result Parm1;
	typedef typename Loki::TL::TypeAtNonStrict<TList, 1, Loki::EmptyType>::Result Parm2;
	typedef FunctorImpl<R, TList> Impl;
	std::auto_ptr<Impl> spImpl_;

	Functor() : spImpl_(0) {};

	template <class Fun>
	Functor(const Fun& fun) : spImpl_(new FunctorHandler<Functor, Fun>(fun)) {};

	Functor(const Functor& rhs) : spImpl_(Impl::Clone(rhs.spImpl_.get())) {};
	Functor& operator=(const Functor&) {};
	explicit Functor(std::auto_ptr<Impl> spImpl) :spImpl_(spImpl) {};
	R operator()()
	{
		return (*spImpl_)();
	}
	R operator()(Parm1 p1)
	{
		return (*spImpl_)(p1);
	}
	R operator()(Parm1 p1, Parm2 p2)
	{
		return (*spImpl_)(p1, p2);
	}




private:
	// Handy type definition for the body type
	//typedef FunctorImpl<R, TList> Impl;
	//std::auto_ptr<Impl> spImpl_;
};