#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
  string cmd;
  string i = "";
  string response = "";

  ifstream Config("C:/ProgramData/Password Manager/.config");
  getline(Config, i);

  if (i == "")
  {
    cout << "Commencing initial setup.\n";
    Config.close();
    CreateDirectory("C:/ProgramData/Password Manager", NULL);
    ofstream Config("C:/ProgramData/Password Manager/.config");
    cout << "Require Master Password when retrieveing passwords (y/n)?\n>>> ";
    cin >> response;
    while (true)
    {
      if (response != "y" || response != "x")
      {
        break;
      }
      cout << "Invalid input\n>>> ";
      cout << response;
      cin >> response;
    }
    if (response == "y")
    {
      Config << "True";
    }
    else if (response == "n")
    {
      Config << "False";
    }
      Config.close();
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