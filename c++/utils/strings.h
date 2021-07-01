#include <string.h>
#include <string>
#include <vector>

//support multi sep, like ":,"
//we can test with str like "abc:def:ghijk,l:m,n"
std::vector<string> split(char* str, const char* sep)
{
	std::vector<string> reslt;
	char *p;
    p = strtok(str, sep);
    while(p){
        reslt.push_back(std::string(p));
        p = strtok(NULL, sep);
    }

    return reslt;
}