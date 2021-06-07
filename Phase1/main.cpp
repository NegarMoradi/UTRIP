#include"Header.h"
#include"UTRIP.h"

using namespace std;

int main(int argc,char * argv[])
{
	UTRIP Program(argv[1]);
	Program.get_put();
}