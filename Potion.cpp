#include "Potion.h"
std::map<int, std::shared_ptr<PotionData>> potionDB;//정적 멤버변수는 반드시 cpp에서 한번 정의해서 메모리 할당해주어야함
void Potion::InitDB(){
	//10=체력
	//20=마나
	//1=하급
	//2=중급
	//3=상급
	potionDB[11] = std::make_shared<PotionData>(PotionData{ HP, "하급 체력 포션", 1, 50 });
	potionDB[21] = std::make_shared<PotionData>(PotionData{ MP, "하급 마나 포션" , 1, 30});

	potionDB[12] = std::make_shared<PotionData>(PotionData{ HP, "중급 체력 포션", 2, 100 });
	potionDB[22] = std::make_shared<PotionData>(PotionData{ MP, "중급 마나 포션" , 2, 60 });

	potionDB[13] = std::make_shared<PotionData>(PotionData{ HP, "상급 체력 포션", 1, 200 });
	potionDB[23] = std::make_shared<PotionData>(PotionData{ MP, "상급 마나 포션" , 1, 120 });
}

std::shared_ptr<PotionData> Potion::GetPotionData(int id)
{
	return potionDB[id];
}
