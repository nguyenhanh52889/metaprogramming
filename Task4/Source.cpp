#include <iostream>
#include "Functor.h"





struct TestFunctor
{
	void operator()(int i, double d)
	{
		std::cout << i << " " << d;
	}
};





template<class TCallableEntity, typename...Params>
Functor<TCallableEntity, Loki::Typelist<Params&&...>> make_functor(const TCallableEntity& callable_entity,
	Params&&... given_params) {
	//Functor<TCallableEntity, P1, P2> cmd(callable_entity, p1, p2);
	//return Functor<TCallableEntity, Loki::TL::MakeTypelist<Params...>>(callable_entity, std::forward<Params>(given_params)...);
	return Functor<TCallableEntity, Loki::Typelist<Params&&...>>(callable_entity);

}

const int function(int, int) {};
int main()
{
	TestFunctor f;
	Functor<void, TYPELIST_2(int, double)> cmd(f);
	cmd(4, 4.5);
	auto a = make_functor(function, 1, 2.5);
	//int x = functor1.call();
	//CEWrapper<int> cmd(f);
	//cmd(1, 2);
	system("pause");
	return 0;
}