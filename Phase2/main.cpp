#include"Header.hpp"
#include"UTRIP.hpp"

using namespace std;

int main(int argc,char * argv[])
{
	vector<string> adresses;
	adresses.push_back(argv[1]);
	adresses.push_back(argv[2]);
	UTRIP Program(adresses);
	Program.get_put();
}
