#include <iostream>

#include <string>

#include <cmath>

using namespace std;

int main()
{
  while (true)
  {
    string cmd;
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