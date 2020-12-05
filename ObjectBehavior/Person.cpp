#include "Person.h"
#include "useful.h"

Person::Person() : Person(
"",
-1,
-1,
-1,
-1,
-1,
-1,
-1,
-1,
-1,
-1) {

}

Person::Person(json& stat) : Person(
stat.count(j_name) > 0 ? j2s(stat[j_name]) : "",
stat.count(j_race) > 0 ? j2i(stat[j_race]) : -1,
stat.count(j_org) > 0 ? j2i(stat[j_org]) : -1,
stat.count(j_role) > 0 ? j2i(stat[j_role]) : -1,
stat.count(j_charm) > 0 ? j2i(stat[j_charm]) : -1,
stat.count(j_know) > 0 ? j2i(stat[j_know]) : -1,
stat.count(j_force) > 0 ? j2i(stat[j_force]) : -1,
stat.count(j_libido) > 0 ? j2i(stat[j_libido]) : -1,
stat.count(j_estrus) > 0 ? j2i(stat[j_estrus]) : -1,
stat.count(j_ideology) > 0 ? j2i(stat[j_ideology]) : -1,
stat.count(j_stress) > 0 ? j2i(stat[j_stress]) : -1) {

}

Person::Person(
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
	int stress) {

}

Person::~Person() {

}