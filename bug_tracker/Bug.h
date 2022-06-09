#pragma once
#include <iostream>
#include <string>
#include "I_Printable.h"
#include <chrono>
#include <ctime> 

class Bug : public I_Printable{
private:
	static constexpr const char* def_bug{ "No bug has been added" };
	static const int def_bug_creator_id{0 };
	static constexpr const char* def_bug_time { "00:00:00"};
	static constexpr const char* def_bug_creator_name{ "Unnamed bug creator"};
	static const int def_bug_id{ 0 };
	static constexpr const char* def_bug_status{ "Pending" };
protected:
	int bug_id;
	std::string bug;
	std::string bug_time;
	int bug_creator_id;
	std::string bug_creator_name;
	std::string bug_status;
public:
	Bug(int bug_id = def_bug_id, 
		std::string bug = def_bug, 
		std::string bug_time = def_bug_time, 
		int bug_creator = def_bug_creator_id, 
		std::string bug_creator_name = def_bug_creator_name,
		std::string bug_status = def_bug_status);
	int get_bug_id() const;
	virtual void print(std::ostream& os) const override;
	~Bug() = default;

};