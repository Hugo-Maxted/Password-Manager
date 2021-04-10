#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstring>
#include <vector>

using namespace std;

string SplitSTR(string input)
{
  string split = input;
  char array[split.length() + 1];
  strcpy(array, split.c_str());
  return array;
}

string encript(string input, string key)
{
  string output = input;
  string keyChars = SplitSTR(key);
  for (int i = 0; i < output.size(); i++)
  {
    output[i] = input[i] ^ keyChars[i % (sizeof(keyChars) / sizeof(char))];
  }
  return output;
}

void split(string s, vector<string> &v)
{
  string temp = "";
  for (int i = 0; i < s.length(); ++i)
  {
    if (s[i] == ' ')
    {
      v.push_back(temp);
      temp = "";
    }
    else
    {
      temp.push_back(s[i]);
    }
  }
  v.push_back(temp);
}

int main()
{
  string cmd;
  string i = "";
  string DataArr[100] = {};
  string DataTemp;
  int count = 0;

  ifstream DataCheck("C:/ProgramData/Password Manager/data");
  getline(DataCheck, i);
  DataCheck.close();

  if (i == "")
  {
    cout << "Commencing initial setup.\n";
    CreateDirectory("C:/ProgramData/Password Manager", NULL);
    ofstream DataNew("C:/ProgramData/Password Manager/data");
    DataNew.close();
    cout << "Setup Complete.\n";
  }

  ifstream DataRead("C:/ProgramData/Password Manager/data");

  while (getline(DataRead, i))
  {
    DataArr[count] = i;
    count++;
  }

  while (true)
  {
    string params;
    vector<string> v;
    cout << ">>> ";
    cin >> cmd;
    getline(cin, params);
    params.erase(0, 1);
    split(params, v);
    if (cmd == "add")
    {
      ofstream DataWrite("C:/ProgramData/Password Manager/data");
      DataWrite << v[0] << v[1] << encript(v[2], v[3]);
      DataWrite.close();
    }
    else if (cmd == "get")
    {
      cout << encript(encript(v[0], "KEY"), "KEY");
    }
    else if (cmd == "help")
    {
      cout << "Usage [command] [params]\n\nCommands:\n  add [name] [username] [password] [encryption key] - Adds a new password.\n  get [name] [encryption key] - Fetches and returns username + password.\n  help - Displays all commands and information.\n  version - Displays the version.\n  exit - Exits the program.\n";
    }
    else if (cmd == "version")
    {
      cout << "0.0.1";
    }
    else if (cmd == "exit")
    {
      exit(0);
    }
    else
    {
      cout << "Unknown command '" << cmd << "' use help for a list off all commands.\n";
    }
  }
}
