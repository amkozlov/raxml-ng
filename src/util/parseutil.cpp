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
