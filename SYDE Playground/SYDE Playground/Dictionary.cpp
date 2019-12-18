#include "pch.h"
#include "Dictionary.h"

TestItem_A::TestItem_A()
{
	m_ItemName = "TestItem_A";
	m_CommandName = "#IM0001";
}

std::string TestItem_A::returnCommandStr()
{
	return m_CommandName;
}

std::string TestItem_A::info_test()
{
	return m_ItemName = ": A Test Item Move That Has No Effect When Used";
}

std::vector<MoveItem*> Dictionary::ItemsList = std::vector<MoveItem*>();

void Dictionary::InitDictionary()
{
	TestItem_A* _TestItemA = new TestItem_A(); 
	AddItem(_TestItemA);
}

MoveItem* Dictionary::find(std::string _commandCode)
{
	MoveItem* tmp;
	NULLITEM ___NULL = NULLITEM();
	tmp = &___NULL;
	bool found = false;
	for (int i = 0; i < ItemsList.size(); i++)
	{
		std::string comparison = ItemsList[i]->returnCommandStr();
		if (comparison == _commandCode)
		{
			tmp = ItemsList[i];
		}
	}
	return tmp;
}

std::string Dictionary::findInfo(std::string _commandCode)
{
	return find(_commandCode)->info_test();
}

void Dictionary::AddItem(MoveItem* _new)
{
	ItemsList.push_back(_new);
}

std::string NULLITEM::returnCommandStr()
{
	return "NULL";
}

std::string NULLITEM::info_test()
{
	return "NULL";
}
