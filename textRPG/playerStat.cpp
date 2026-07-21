#include <iostream>
#include <string>

class PlayerStat {
public:
    explicit PlayerStat(const std::string& name = "무명") : name(name) {}

    void setName(const std::string& inputName) {
        name = inputName;
    }

    std::string getName() const {
        return name;
    }

private:
    std::string name;
};