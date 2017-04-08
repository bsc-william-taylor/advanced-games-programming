/**
 * 
 * Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
 *  
 * This software is provided 'as-is', without any 
 * express or implied warranty. In no event will 
 * the authors be held liable for any damages 
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose, 
 * including commercial applications, and to alter it and redistribute 
 * it freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; 
 *    you must not claim that you wrote the original software. 
 *    If you use this software in a product, an acknowledgment 
 *    in the product documentation would be appreciated but 
 *    is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, 
 *    and must not be misrepresented as being the original software.
 *  
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once

#include "CommonHeader.h"

// A simple class which allows shares assets betweens scees
class Bank 
{
private:
	// a struct which represents each item in the container
	struct BankItem {
		std::string name;
		void* object;
	};
private:
	// a list of items that will be shared between scenes
	std::vector<BankItem *> items;
public:
	// constructor & deconstructor
	Bank::Bank() { items.reserve(100); }
	Bank::~Bank() { items.clear(); }
public:
	// This function adds an item to the list which can the be aquired by name
	template<class T> 
	void push_item(T * item, std::string _name);
	// This function returns an item by name
	template<class T> 
	T *	pop_item(std::string _name);
};

// Template function definition
template<class T> void Bank::push_item(T * item, std::string _name) {
	// create a new bank item
	BankItem * bank_item = new BankItem();
	bank_item->object = (void*)item;
	bank_item->name = _name;
	// push it into the vector
	items.push_back(bank_item);
}

template<class T> T * Bank::pop_item(std::string _name) {
	// iterate through the vector looking for the asset with the name
	for (unsigned i = 0; i < items.size(); i++) {
		// if we find the asset
		if (items[i]->name == _name) {
			// return it to the user casted to its real type
			return(static_cast<T *>(items[i]->object));
		}
	}

	// throw an exception telling the user that the asset cannot be find
	throw Error(GAME, std::string("Error finding asset ->" + _name).c_str());

	// return NULL to also idicate failure
	return NULL;
}