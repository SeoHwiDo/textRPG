# 문법 오류 정리 보고서

## 1. playerStat.cpp
- 위치: [textRPG/playerStat.cpp](textRPG/playerStat.cpp)
- 문제 구문:
  ```cpp
  class player {
      char* name = '\0';

      player(*char name,)
  };
  ```
- 문제점:
  - `player(*char name,)`는 C++ 문법상 잘못된 선언 형태입니다.
  - `char*` 포인터 초기화 방식도 `\0` 대신 문자열 타입과 맞지 않아 사용하기 어렵습니다.
- 수정 내용:
  - 클래스를 `PlayerStat`으로 정리하고, 이름을 저장하는 필드를 `std::string`으로 변경했습니다.
  - 생성자와 접근자 함수를 추가해 기본적인 사용 흐름이 가능하도록 수정했습니다.

## 2. Skill.cpp
- 위치: [textRPG/Skill.cpp](textRPG/Skill.cpp)
- 문제 구문:
  ```cpp
  skill_data skill_select() {
      
  }
  ```
- 문제점:
  - 함수 정의가 비어 있고, `Actor` 타입과의 연결도 없어서 호출 측과 맞지 않았습니다.
  - `skill_data`를 반환해야 하는데 반환문이 없어 구현이 불완전했습니다.
- 수정 내용:
  - `skill_select(Actor&)` 형태로 선언하고, 기본값을 반환하도록 구현했습니다.
  - `Actor` 선언 전방 선언을 추가해 순환 참조를 피했습니다.

## 3. Actor.cpp
- 위치: [textRPG/Actor.cpp](textRPG/Actor.cpp)
- 문제 구문:
  ```cpp
  Skill::skill_data=Skill::skill_select(def);
  auto dmg = this->playerStat[wis] + this->playerEquip[0].stat+;
  ```
- 문제점:
  - `Skill::skill_data=...`는 타입과 변수를 구분하지 않아 문법적으로 잘못되었습니다.
  - `stat+;`는 표현식이 비어 있어 문법 오류가 발생합니다.
- 수정 내용:
  - `Skill::skill_data skill = Skill::skill_select(def);`로 변경했습니다.
  - 스킬 피해를 더하는 방식으로 계산식을 정리했습니다.

## 4. Actor.cpp
- 위치: [textRPG/Actor.cpp](textRPG/Actor.cpp)
- 문제 구문:
  ```cpp
  std::map<int, actionFunc> actionsWithFunc = {
      {attack, actionFunc{"공격", [this](Actor def) {
  ```
- 문제점:
  - 람다 인자가 `Actor` 값 복사로 되어 있어, 이후 메서드 호출과 맞지 않았습니다.
  - `this`를 사용하는 초기화 구문이 생성자 이전에 들어가면 안전하지 않았습니다.
- 수정 내용:
  - `actionsWithFunc`를 멤버로 두고, 생성자에서 초기화하도록 분리했습니다.
  - 람다 인자를 `Actor&`로 바꾸어 실제 메서드 호출과 일관되게 수정했습니다.

## 5. main.cpp
- 위치: [textRPG/main.cpp](textRPG/main.cpp)
- 문제 구문:
  ```cpp
  int main() {

  }
  ```
- 문제점:
  - 진입점이 비어 있어 프로젝트가 실제로 실행 가능한 흐름을 갖지 않았습니다.
- 수정 내용:
  - 기본적인 `Actor` 생성 및 이름 출력 흐름을 넣어 실행 가능한 진입점을 구성했습니다.
