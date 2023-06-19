#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using std::string;
using std::ifstream;
using std::cout;

int main(int argc, char** argv)
{
	//reading the mapping
	char printable['~' - ' ' + 1];
	char mapped['~' - ' ' + 1];
	for (int i = ' '; i <= '~'; i++)
	{
		printable[i - ' '] = i;
	}
	ifstream mapping("extras\\mapping.txt");
	string mapstr;
	char idx = ' ';
	if (mapping.is_open())
	{
		while (mapping && idx <= '~')
		{
			mapping >> mapstr;
			std::stringstream ss;
			ss << "0x" << mapstr[0] << mapstr[1];
			char mapped_c = std::stoul(ss.str(), nullptr, 16);
			mapped[mapped_c - ' '] = idx++;
		}
	}
	//reversing the mapping
	string key(argv[1]);
	for (int i = 0; i < key.length(); i++)
	{
		cout << mapped[key[i] - ' '];
	}
	return 0;
};