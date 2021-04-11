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

void copyToClipboard(const string &s)
{
  OpenClipboard(0);
  EmptyClipboard();
  HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
  if (!hg)
  {
    CloseClipboard();
    return;
  }
  memcpy(GlobalLock(hg), s.c_str(), s.size());
  GlobalUnlock(hg);
  SetClipboardData(CF_TEXT, hg);
  CloseClipboard();
  GlobalFree(hg);
}

int main()
{
  string cmd;
  string i = "";
  string response = "";
  string DataTemp;
  int count = 0;
  bool copy;

  ifstream DataCheck("C:/ProgramData/Password Manager/.config");
  getline(DataCheck, i);
  DataCheck.close();

  if (i == "")
  {
    cout << "Commencing initial setup.\n";
    CreateDirectory("C:/ProgramData/Password Manager", NULL);
    ofstream Config("C:/ProgramData/Password Manager/.config");
    cout << "Auto copy passwords to clipboard (y/n)?\n>>> ";
    cin >> response;
    while (true)
    {
      if (response == "y" || response == "n ")
      {
        break;
      }
      cout << "Invalid input\n>>> ";
      cout << response;
      cin >> response;
    }
    if (response == "y")
    {
      Config << 1;
    }
    else if (response == "n")
    {
      Config << 0;
    }
    Config.close();
    cout << "Setup Complete.\n";
  }

  count = 0;
  ifstream Config("C:/ProgramData/Password Manager/.config");
  while (getline(Config, i))
  {
    switch (count)
    {
    case 0:
      copy = (i == "1") ? true : false;
    }
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
      ofstream DataWrite("C:/ProgramData/Password Manager/" + v[0] + ".password");
      DataWrite << v[1] << "\n"
                << encrypt(v[2], v[3]);
      DataWrite.close();
      cout << "Added: " << v[0] << ", with username: " << v[1] << ", and encrypted password as: " << encrypt(v[2], v[3]) << ".\n";
    }
    else if (cmd == "get")
    {
      i = "";
      ifstream DataRead("C:/ProgramData/Password Manager/" + v[0] + ".password");
      count = 0;
      while (getline(DataRead, i))
      {
        switch (count)
        {
        case 0:
          if (i == "Deleted")
          {
            cout << "No Password found.\n";
            break;
          }
          cout << v[0] << ":\n";
          cout << "Username: " << i << "\n";
          break;
        case 1:
          cout << "Password: " << encrypt(i, v[1]) << "\n";
          if (copy)
          {
            copyToClipboard(encrypt(i, v[1]));
          }
          break;
        }
        count++;
      }
      if (i == "")
      {
        cout << "No Password found.\n";
      }
    }
    else if (cmd == "delete")
    {
      ofstream DataWrite("C:/ProgramData/Password Manager/" + v[0] + ".password");
      DataWrite << "Deleted";
      DataWrite.close();
      cout << "Deleted " << v[0] << ".\n";
    }
    else if (cmd == "settings")
    {
      ofstream Config("C:/ProgramData/Password Manager/.config");
      if (v[0] == "copy")
      {
        if (v[1] == "enabled")
        {
          Config << 1;
          cout << "Enabled automatic copying.\n";
        }
        else
        {
          Config << 0;
          cout << "Disabled automatic copying.\n";
        }
        Config.close();
      }
    }
    else if (cmd == "help")
    {
      cout << "Usage [command] [params]\n\nSettings:\n  Copy - Enabled: automatically coppies password to keyboard.\n\nCommands:\n  add [name] [username] [password] [encryption key] - Adds/Updates a password.\n  get [name] [encryption key] - Fetches and returns username + password.\n  delete [name] - Deletes password.\n  settings [setting] [value] - Updates a setting.\n  help - Displays all commands and information.\n  version - Displays the version.\n  exit - Exits the program.\n\n  Everything except password-names/usernames/passwords should be lowercase.\n";
    }
    else if (cmd == "version")
    {
      cout << "Current version: 0.1.0\n";
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
