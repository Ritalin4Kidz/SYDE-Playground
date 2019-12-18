#pragma once
#include <string>
#include <vector>
class MoveItem {
public:

	MoveItem() {}
	~MoveItem() {}

	virtual std::string returnCommandStr() = 0;
	virtual std::string info_test() = 0;

};

class NULLITEM : public MoveItem {
public:
	NULLITEM() {}
	virtual ~NULLITEM() {}

	virtual std::string returnCommandStr() override;
	virtual std::string info_test() override;

private:
	std::string m_ItemName = "";
	std::string m_CommandName = "";
};


class TestItem_A : public MoveItem {
public:
	TestItem_A();
	virtual ~TestItem_A() {}

	virtual std::string returnCommandStr() override;
	virtual std::string info_test() override;
private:
	std::string m_ItemName = "";
	std::string m_CommandName = "";
};

class Dictionary {
public:
	static void InitDictionary();
	static MoveItem* find(std::string _commandCode);
	static std::vector<MoveItem*> ItemsList;
	static std::string findInfo(std::string _commandCode);
	static void AddItem(MoveItem* _new);
};