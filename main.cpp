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

string encrypt(string text, string key)
{
  string cipher;
  string alphabet;

  for (int i = 32; i <= 126; i++)
  {
    alphabet += (int)i;
  }

  for (int i = 0; i < text.size(); i++)
  {
    char c0 = text[i];
    char c1 = key[i % key.size()];
    int start = 0;

    for (int j = 0; j < alphabet.size(); j++)
    {
      if (alphabet[j] == c0)
      {
        start = j;
        break;
      }
    }

    int offSet = 0;

    for (int j = start; j < start + alphabet.size(); j++)
    {
      int letter = j % alphabet.size();

      if (alphabet[letter] == c1)
      {
        break;
      }
      offSet++;
    }
    cipher += alphabet[offSet];
  }
  return cipher;
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
  string DataTemp;
  int count = 0;

  ifstream DataCheck("C:/ProgramData/Password Manager/.config");
  getline(DataCheck, i);
  DataCheck.close();

  if (i == "")
  {
    cout << "Commencing initial setup.\n";
    CreateDirectory("C:/ProgramData/Password Manager", NULL);
    ofstream DataNew("C:/ProgramData/Password Manager/.config");
    DataNew << "0";
    DataNew.close();
    cout << "Setup Complete.\n";
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
      ofstream DataWrite("C:/ProgramData/Password Manager/" + v[0] + ".password");
      DataWrite << v[1] << "\n" << encrypt(v[2], v[3]);
      DataWrite.close();
    }
    else if (cmd == "get")
    {
      ifstream DataRead("C:/ProgramData/Password Manager/" + v[0] + ".password");
      int count = 0;
      while (getline(DataRead, i))
      {
        switch (count) {
          case 0:
            cout << "Username: " << i << "\n";
            break;
          case 1:
            cout << "Password: " << encrypt(i, v[1]) << "\n";
            break;
        }
        count++;
      }
    }
    else if (cmd == "help")
    {
      cout << "Usage [command] [params]\n\nCommands:\n  add [name] [username] [password] [encryption key] - Adds a new password.\n  get [name] [encryption key] - Fetches and returns username + password.\n  help - Displays all commands and information.\n  version - Displays the version.\n  exit - Exits the program.\n";
    }
    else if (cmd == "version")
    {
      cout << "0.1.0";
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
