#ifndef GETINDEX
#define GETINDEX


struct EmptyType
{
};

template <
	typename T0 = EmptyType,
	typename T1 = EmptyType,
	typename T2 = EmptyType,
	typename T3 = EmptyType,
	typename T4 = EmptyType,
	typename T5 = EmptyType,
	typename T6 = EmptyType,
	typename T7 = EmptyType,
	typename T8 = EmptyType,
	typename T9 = EmptyType
> struct TypeList;



template <
	typename T0,
	typename T1,
	typename T2,
	typename T3,
	typename T4,
	typename T5,
	typename T6,
	typename T7,
	typename T8,
	typename T9
> struct TypeList
{
	typedef T0 head;
	typedef TypeList<T1, T2, T3, T4, T5, T6, T7, T8, T9> tail;

	enum
	{
		length = tail::length + 1
	};
};



template <> struct TypeList<
	EmptyType,
	EmptyType,
	EmptyType,
	EmptyType,
	EmptyType,
	EmptyType,
	EmptyType,
	EmptyType,
	EmptyType,
	EmptyType>
{
	enum
	{
		length = 0
	};
};

template <typename TypeList> struct TypeListLength
{
	enum
	{
		value = TypeList::length
	};
};

template <
	typename TypeList,
	unsigned int Index,
	unsigned int Step = 0,
	bool Stop = (Index == Step),
	bool OutOfRange = (TypeListLength<TypeList>::value == 0)
> struct TypeListGet
{


	typedef typename TypeListGet<typename TypeList::tail, Index, Step + 1>::type type;
};



template <
	typename TypeList,
	unsigned int Index,
	unsigned int Step,
	bool Stop
> struct TypeListGet<
TypeList,
Index,
Step,
Stop,
true>
{
};



template <
	typename TypeList,
	unsigned int Index,
	unsigned int Step,
	bool OutOfRange
> struct TypeListGet<
TypeList,
Index,
Step,
true,
OutOfRange>
{

	typedef typename TypeList::head type;
};



template <
	typename TypeList,
	unsigned int Index = 0,
	bool Stop = (Index == TypeListLength<TypeList>::value)
> struct TypeSwitch
{
	bool operator()(unsigned int i, char const * f)
	{
		if (i == Index)
		{
			//std::cout << typeid(TypeListGet<TypeList, Index>::type).name() << std::endl;
			//return f<typeid(TypeListGet<TypeList, Index>::type)>();
			if ((std::string)(typeid(TypeListGet<TypeList, Index>::type).name()) == f)
			{
				return true;
			}
			else
				return false;
		}
		else
		{
			TypeSwitch<TypeList, Index + 1> next;
			return next.operator()(i, f);
		}
	}
	int getIndexOf(char const * f)
	{
		for (unsigned int i = 0; i < TypeListLength<TypeList>::value; i++) {
			if (operator()(i, f))
			{
				return (int)i;
			}
		}
		return (int)(-1);
	}
};

/**
Handles the base case when the type cannot be found. This works because we
specialize over the value of the "Stop" variable.
*/

template <
	typename TypeList,
	unsigned int Index
> struct TypeSwitch<
TypeList,
Index,
true>
{
	bool operator()(unsigned int /* i */, char const * /* f */)
	{
		throw std::runtime_error("Index is out of range");
	}

	int getIndexOf(char const *)
	{
		throw std::runtime_error("Index is out of range");
	}
};




#endif