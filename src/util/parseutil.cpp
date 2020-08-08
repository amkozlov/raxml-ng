#include "../common.h"

using namespace std;

vector<string> split_string(const string& s, char delim)
{
   vector<string> tokens;
   string token;
   istringstream ss(s);
   while (std::getline(ss, token, delim))
   {
      tokens.push_back(token);
   }
   return tokens;
}

bool isprefix(const std::string& s, const std::string& prefix)
{
  return s.rfind(prefix, 0) == 0;
}
