#include "Potion.h"
// 00=체력 10=마나
//0=하급 1=중급 2=상급
void Potion::InitDB(){
	
	itemDB[00] = std::make_shared<PotionData>(PotionData{ HP, "하급 체력 포션", 0, 50 });
	itemDB[10] = std::make_shared<PotionData>(PotionData{ MP, "하급 마나 포션" , 0, 30});

	itemDB[01] = std::make_shared<PotionData>(PotionData{ HP, "중급 체력 포션", 1, 100 });
	itemDB[11] = std::make_shared<PotionData>(PotionData{ MP, "중급 마나 포션" , 1, 60 });

	itemDB[02] = std::make_shared<PotionData>(PotionData{ HP, "상급 체력 포션", 2, 200 });
	itemDB[12] = std::make_shared<PotionData>(PotionData{ MP, "상급 마나 포션" , 2, 120 });
}

