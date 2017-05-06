
#pragma once

#include "MajorInclude.h"

class Bank 
{
	struct BankItem 
    {
		std::string name;
		void* object;
	};

	std::vector<BankItem *> items;
public:
	Bank::Bank() { items.reserve(100); }
	Bank::~Bank() { items.clear(); }

	template<class T> 
	void pushItem(T * item, std::string name);
	template<class T> 
	T *	popItem(std::string _name);
};

template<typename T> 
void Bank::pushItem(T * item, std::string name) 
{
	BankItem * bank_item = new BankItem();
	bank_item->object = (void*)item;
	bank_item->name = name;
	items.push_back(bank_item);
}

template<typename T> T * Bank::popItem(std::string _name)
{
	for (unsigned i = 0; i < items.size(); i++) 
    {
		if (items[i]->name == _name) 
        {
			return(static_cast<T *>(items[i]->object));
		}
	}

	throw Error(GAME, std::string("Error finding asset ->" + _name).c_str());
}