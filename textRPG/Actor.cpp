#include <iostream>
#include <string>
#include <random>
#include <functional>
#include <vector>
#include <map>
#include <limits>
#include "Dice.cpp"
#include "Skill.cpp"

class Actor {
public:
    const static int STAT_MAX = 25;
    const static int STAT_MIN = 0;

    enum stat {
        str = 0,
        dex,
        con,
        wis,
        cha,
        remain
    };

    enum equipType {
        wep = 0,
        shd = 1
    };

    struct equip {
        equipType et;
        std::string name;
        int stat;
        int power;
        int grade;

        equip() : et(wep), name(""), stat(0), power(0), grade(0) {}
        equip(equipType et) : equip() { this->et = et; }
        equip(equipType et, const std::string& eq_name, int eq_stat, int eq_pow, int grade)
            : et(et), name(eq_name), stat(eq_stat), power(eq_pow), grade(grade) {}
    };

private:
    std::string name = "무명";
    int hp = 10;
    int mp = 10;
    int gold = 0;
    int level = 1;
    int exp = 0;
    int playerStat[5] = { 0 };
    equip playerEquip[2] = {
        equip(wep),
        equip(shd)
    };

public:
    Actor() {
        initActions();
    }

    Actor(std::string name) : name(name) {
        initActions();
    }

    Actor& operator=(const Actor& p) {
        if (this != &p) {
            name = p.name;
            hp = p.hp;
            mp = p.mp;
            gold = p.gold;
            level = p.level;
            exp = p.exp;
            for (int i = 0; i < 5; ++i) {
                playerStat[i] = p.playerStat[i];
            }
            playerEquip[0] = p.playerEquip[0];
            playerEquip[1] = p.playerEquip[1];
        }
        return *this;
    }

    enum actions {
        attack = 1,
        skiil,
        dfense,
        run,
        item
    };

    struct actionFunc {
        std::string name;
        std::function<bool(Actor& def)> func;
    };

    std::map<int, actionFunc> actionsWithFunc;

    void initActions() {
        actionsWithFunc = {
            { attack, actionFunc{"공격", [this](Actor& def) { return this->basic_attack(def); }} },
            { skiil, actionFunc{"스킬", [this](Actor& def) { return this->skill_attack(def); }} },
            { dfense, actionFunc{"방어", [this](Actor& def) { return true; }} },
            { run, actionFunc{"도망", [this](Actor& def) { return this->runOut(def); }} },
            { item, actionFunc{"아이템", [this](Actor& def) { return true; }} }
        };
    }

    void setName(std::string inputName) {
        this->name = inputName;
    }

    std::string getName() const {
        return this->name;
    }

    void setStat(stat inputStat, int point) {
        this->playerStat[inputStat] += point;
    }

    int getStat(stat inputStat) const {
        return this->playerStat[inputStat];
    }

    void setEquip(equip n_equip) {
        this->playerEquip[n_equip.et] = n_equip;
    }

    equip getEquip(equipType inputType) const {
        return playerEquip[inputType];
    }

    void setHp(int inputHp) {
        this->hp = inputHp;
    }

    void addHp(int inputHp) {
        this->hp += inputHp;
    }

    int getHp() const {
        return this->hp;
    }

    void setMp(int inputMp) {
        this->mp = inputMp;
    }

    void addMp(int inputMp) {
        this->mp += inputMp;
    }

    int getMp() const {
        return this->mp;
    }

    void setGold(int inputGold) {
        this->gold = inputGold;
    }

    void addGold(int inputGold) {
        this->gold += inputGold;
    }

    int getGold() const {
        return this->gold;
    }

    void setLevel(int inputLevel) {
        this->level = inputLevel;
    }

    void setExp(int inputExp) {
        this->exp = inputExp;
    }

    void addExp(int inputExp) {
        this->exp += inputExp;
    }

    int getExp() const {
        return this->exp;
    }

    bool isAlive() {
        return this->hp > 0;
    }

    bool choiceAction(Actor& def) {
        std::cout << "행동을 선택하세요:\n";
        for (const auto& action : actionsWithFunc) {
            std::cout << action.first << ". " << action.second.name << "\n";
        }

        int selected = 0;
        while (true) {
            std::cout << "입력: ";
            std::cin >> selected;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "숫자만 입력 가능합니다.\n\n";
                continue;
            }

            auto it = actionsWithFunc.find(selected);
            if (it != actionsWithFunc.end()) {
                if (it->second.func) {
                    return it->second.func(def);
                }
                std::cout << "아직 구현되지 않은 행동입니다.\n\n";
            }
            else {
                std::cout << "잘못된 번호입니다. 다시 선택하세요.\n\n";
            }
        }
    }

    bool basic_attack(Actor& def) {
        auto dmg = this->playerStat[str] + this->playerEquip[0].stat;
        auto defs = def.playerEquip[1].stat;
        auto miss = static_cast<double>(def.playerStat[dex]) / STAT_MAX;
        if (!Dice::check_success(miss)) {
            def.addHp(-(dmg - defs > 0 ? dmg - defs : 0));
        }
        return def.isAlive();
    }

    bool skill_attack(Actor& def) {
        Skill::skill_data skill = Skill::skill_select(def);
        auto dmg = this->playerStat[wis] + this->playerEquip[0].stat + skill.dmg;
        auto defs = def.playerEquip[1].stat;
        auto miss = static_cast<double>(def.playerStat[dex]) / STAT_MAX;
        if (!Dice::check_success(miss)) {
            def.addHp(-(dmg - defs > 0 ? dmg - defs : 0));
        }
        return def.isAlive();
    }

    bool defending(Actor& def) {
        return true;
    }

    bool runOut(Actor& def) {
        return Dice::check_versus_success(this->playerStat[dex], def.playerStat[dex]);
    }

    bool use_item(Actor& def) {
        return true;
    }

    void checkEquip(equip n_equip) {
        equip* o_equip = &playerEquip[n_equip.et];
        if (o_equip->name == n_equip.name) {
            o_equip->power += n_equip.power;
        }
        else {
            if (o_equip->stat < n_equip.stat) {
                *o_equip = n_equip;
            }
        }
    }
};