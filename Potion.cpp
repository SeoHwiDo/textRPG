#include "Potion.h"
// 00=체력 10=마나
//1=하급 2=중급 3=상급
void Potion::InitDB(){
	
	itemDB[11] = std::make_shared<PotionData>(PotionData{ HP, "하급 체력 포션", 1, 50 });
	itemDB[21] = std::make_shared<PotionData>(PotionData{ MP, "하급 마나 포션" , 1, 30});

	itemDB[12] = std::make_shared<PotionData>(PotionData{ HP, "중급 체력 포션", 2, 100 });
	itemDB[22] = std::make_shared<PotionData>(PotionData{ MP, "중급 마나 포션" , 2, 60 });

	itemDB[13] = std::make_shared<PotionData>(PotionData{ HP, "상급 체력 포션", 1, 200 });
	itemDB[23] = std::make_shared<PotionData>(PotionData{ MP, "상급 마나 포션" , 1, 120 });
}

