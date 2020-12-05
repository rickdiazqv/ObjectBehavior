#pragma once
#include "gamedata.h"

constexpr const char* j_name = "name";
constexpr const char* j_race = "race";
constexpr const char* j_org = "org";
constexpr const char* j_role = "role";
constexpr const char* j_charm = "charm";
constexpr const char* j_know = "know";
constexpr const char* j_force = "force";
constexpr const char* j_libido = "libido";
constexpr const char* j_estrus = "estrus";
constexpr const char* j_ideology = "ideology";
constexpr const char* j_stress = "stress";
//constexpr const char* j_ = "";

class Person {
private:
	string _name;
	int _race;
	int _org;
	int _role;
	int _charm;
	int _know;
	int _force;
	int _libido;
	int _estrus;
	int _ideology;
	int _stress;

public:
	Person();
	Person(
		string name, 
		int race, 
		int org, 
		int role, 
		int charm,
		int know,
		int force,
		int libido,
		int entrus,
		int ideology,
		int stress);
	Person(json& status);
	~Person();
};

struct Race final {
	inline static const int HUMAN = 0;
	inline static const int ANGEL = 1;
	inline static const int DEMON = 2;
};