#include "Potion.h"
using namespace Util;
// 00=체력 10=마나
//0=하급 1=중급 2=상급
void Potion::InitDB(){
	
	itemDB[makePotionID(PotionType::HP,PotionGrade::LOW)] = std::make_shared<PotionData>(PotionData{ PotionType::HP, "하급 체력 포션", PotionGrade::LOW, 50 });
	itemDB[makePotionID(PotionType::MP,PotionGrade::LOW)] = std::make_shared<PotionData>(PotionData{ PotionType::MP, "하급 마나 포션", PotionGrade::LOW, 30 });
	itemDB[makePotionID(PotionType::HP,PotionGrade::MID)] = std::make_shared<PotionData>(PotionData{ PotionType::HP, "중급 체력 포션", PotionGrade::MID, 100 });
	itemDB[makePotionID(PotionType::MP,PotionGrade::MID)] = std::make_shared<PotionData>(PotionData{ PotionType::MP, "중급 마나 포션", PotionGrade::MID, 60 });
	itemDB[makePotionID(PotionType::HP,PotionGrade::HIGH)] = std::make_shared<PotionData>(PotionData{ PotionType::HP, "상급 체력 포션", PotionGrade::HIGH, 200 });
	itemDB[makePotionID(PotionType::MP,PotionGrade::HIGH)] = std::make_shared<PotionData>(PotionData{ PotionType::MP, "상급 마나 포션", PotionGrade::HIGH, 120 });
}

