#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>

class Button;
class DataBase
{
public:
	void Insert(Button& inButton);
	int Found(std::string inName);
	std::vector<Button> mDB;
};

#endif // DATABASE_H
