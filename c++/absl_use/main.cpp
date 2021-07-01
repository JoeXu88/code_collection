#include "absl/strings/str_split.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/strings/str_format.h"
#include "absl/strings/numbers.h"
#include "timecost.h"
#include <vector>

void absl_test_split()
{
    std::string str = "abc:def:ghijk:l:m:n";
    
    nsCost cost("absl split");
    cost.start();
    std::vector<std::string> reslt = absl::StrSplit(str, ":");
    cost.end();

    for(auto s:reslt)
    {
        printf("[%s]  ", s.c_str());
    }
    printf("\n");
}

void test_split()
{
    std::string str = "abc:def:ghijk:l:m:n";
    // std::string delemit = ":";
    char delemit = ':';
    std::vector<std::string> reslt;
    {
        nsCost cost("own split");
        int start_pos = 0;
        int len = str.length();
        for(int i=0; i<len; i++)
        {
            if(str[i] == delemit)
            {
                reslt.push_back(str.substr(start_pos, i-start_pos));
                start_pos = i+1;
            }
        }
        if(start_pos != len)
            reslt.push_back(str.substr(start_pos, len-start_pos));
    }

    for(auto &s:reslt)
    {
        printf("[%s]  ", s.c_str());
    }
    printf("\n");
    reslt.clear();

    {
        const char* sep = ":,";
        char pstr[] = "abc:def:ghijk,l:m,n";
        nsCost cost("strk split");
        char *p;
        p = strtok((char*)pstr, sep);
        while(p){
            reslt.push_back(std::string(p));
            p = strtok(NULL, sep);
        }
    }

    for(auto &s:reslt)
    {
        printf("[%s]  ", s.c_str());
    }
    printf("\n");
}

void absl_test_strcat()
{
    std::string rslt;
    {
        nsCost cost("absl strcat");
        rslt = absl::StrCat("test", 1, 3.2);
    }
    printf("cat: %s\n", rslt.c_str());
    rslt.clear();

    {
        nsCost cost("absl strappend");
        // absl::StrAppend(&rslt, "test", 1, 3.2);
        absl::StrAppend(&rslt, "test");
        absl::StrAppend(&rslt, 1, 3.2);
    }
    printf("append: %s\n", rslt.c_str());
    rslt.clear();

    {
        nsCost cost("absl strfmt");
        rslt = absl::StrFormat("%s%d%f", "test", 1, 3.2);
    }
    printf("strfmt: %s\n", rslt.c_str());
}

void test_strcat()
{
    char relst[128] = {0};
    {
        nsCost cost("own strcat");
        const char* test = "test";
        int a = 1;
        float b = 3.2;
        sprintf(relst, "%s%d%f", test, a, b);
    }

    std::ostringstream os;
    {
        nsCost cost("std stream");
        os << "test" << 1 << 3.2;
    }
    printf("stream reslt: %s\n", os.str().c_str());
}

void absl_test_stoi()
{
    int reslt = -1;
    std::string str = "-123456789";
    {
        nsCost cost("absl stoi");
        absl::SimpleAtoi(str, &reslt);
    }

    printf("int val: %d\n", reslt);
}

void test_stoi()
{
    int reslt = -1;
    std::string str = "-123456789";
    {
        nsCost cost("absl stoi");
        reslt = std::stoi(str);
    }

    printf("int val: %d\n", reslt);
}

int main()
{
    absl_test_split();
    printf("----------------------\n");
    test_split();
    printf("----------------------\n");
    absl_test_strcat();
    printf("----------------------\n");
    test_strcat();
    printf("----------------------\n");
    absl_test_stoi();
    test_stoi();
    return 0;
}



/*
test result on centos7 with lts_2020_02_25 version:
cpu 4 core 3GHz

absl split TimeCost 10500ns
[abc]  [def]  [ghijk]  [l]  [m]  [n]
----------------------
own split TimeCost 6400ns
[abc]  [def]  [ghijk]  [l]  [m]  [n]
strk split TimeCost 3000ns
[abc]  [def]  [ghijk]  [l]  [m]  [n]
----------------------
absl strcat TimeCost 12100ns
cat: test13.2
absl strappend TimeCost 2900ns
append: test13.2
absl strfmt TimeCost 13100ns
strfmt: test13.200000
----------------------
own strcat TimeCost 5500ns
std stream TimeCost 8900ns
stream reslt: test13.2
----------------------
absl stoi TimeCost 2000ns
int val: -123456789
absl stoi TimeCost 2900ns
int val: -123456789
*/