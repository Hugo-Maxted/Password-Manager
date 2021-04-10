#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
  string cmd;
  string i = "";
  string DataArr[100] = {};
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
    cout << ">>> ";
    cin >> cmd;
    if (cmd == "add")
    {
    }
    else if (cmd == "get")
    {
      
    }
    else if (cmd == "help")
    {
      cout << "Usage [command] [params]\n\nCommands:\n  add [name] [username] [password] - Adds a new password.\n  get [name] [master password] - Fetches and returns username + password.\n  help - Displays all commands and information.\n  version - Displays the version.\n  exit - Exits the program.\n";
    }
    else if (cmd == "version")
    {
      cout << "0.0.1";
    }
    else if (cmd == "exit")
    {
      break;
    }
    else
    {
      cout << "Unknown command '" << cmd << "' use help for a list off all commands.\n";
    }
  }
}