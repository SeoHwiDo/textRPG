#pragma once
#include<string>
#include <memory>
#include <map>
template<typename T>
class Item
{
protected:
	
	static std::map<int, std::shared_ptr<const T>> itemDB;
public:
	static void initDB();

	static std::shared_ptr<const T> GetItemData(int id)
	{
		auto it = itemDB.find(id);
		if (it != itemDB.end()) {
			return it->second;
		}
		return nullptr; // 찾지 못했을 경우
	}
};
template <typename T>
std::map<int, std::shared_ptr<const T>> Item<T>::itemDB;

