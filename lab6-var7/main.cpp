#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "DungeonMap.h"
#include "Observer/console_observer.h"
#include "Observer/file_observer.h"

int main() {
  DungeonEditor editor;

  auto consoleObs = std::make_shared<ConsoleObserver>();
  auto fileObs = std::make_shared<FileObserver>("log.txt");

  editor.attachObserver(consoleObs);
  editor.attachObserver(fileObs);

  const int attackRadius = 100;

  std::cout << "=== Dungeon Editor for Balagur Fate 3 ===" << std::endl;
  std::cout << "Available NPC types: Orc, Knight, Bear" << std::endl;
  std::cout << "Combat rules (Variant 7):" << std::endl;
  std::cout << "  - Orcs kill Bears and Orcs" << std::endl;
  std::cout << "  - Bears kill Knights" << std::endl;
  std::cout << "  - Knights kill Orcs" << std::endl;
  std::cout << "Coordinates range: 0-500" << std::endl;

  while (true) {
    std::cout << "\n1) Add NPC" << std::endl;
    std::cout << "2) Print NPCs" << std::endl;
    std::cout << "3) Save to file (default: dungeon_save.txt)" << std::endl;
    std::cout << "4) Load from file (default: dungeon_load.txt)" << std::endl;
    std::cout << "5) Run battle" << std::endl;
    std::cout << "6) Clear all NPCs" << std::endl;
    std::cout << "0) Exit" << std::endl;
    std::cout << "> ";

    int cmd = 0;
    if (!(std::cin >> cmd)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!" << std::endl;
      continue;
    }

    if (cmd == 0)
      break;

    switch (cmd) {
    case 1: {
      std::string typeStr;
      std::string name;
      int x, y;

      std::cout << "NPC type (Orc/Knight/Bear): ";
      std::cin >> typeStr;
      std::cout << "Name: ";
      std::cin >> name;
      std::cout << "x y (0-500): ";
      std::cin >> x >> y;

      try {
        editor.addNPC(typeStr, name, x, y);
        std::cout << "NPC added successfully!" << std::endl;
      } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
      }
      break;
    }

    case 2: {
      editor.printAll();
      break;
    }

    case 3: {
      std::string path;
      std::cout << "File path (default: dungeon_save.txt): ";
      std::cin.ignore();
      std::getline(std::cin, path);
      if (path.empty())
        path = "dungeon_save.txt";

      try {
        editor.saveToFile(path);
        std::cout << "Saved " << editor.getNPCCount() << " NPCs to " << path
                  << std::endl;
      } catch (const std::exception &e) {
        std::cout << "Error saving file: " << e.what() << std::endl;
      }
      break;
    }

    case 4: {
      std::string path;
      std::cout << "File path (default: dungeon_load.txt): ";
      std::cin.ignore();
      std::getline(std::cin, path);
      if (path.empty())
        path = "dungeon_load.txt";

      try {
        if (editor.getNPCCount() > 0) {
          std::cout << "Warning: This will overwrite current dungeon. "
                       "Continue? (y/n): ";
          char confirm;
          std::cin >> confirm;
          if (confirm != 'y' && confirm != 'Y') {
            std::cout << "Load cancelled." << std::endl;
            break;
          }
        }

        editor.loadFromFile(path);
        std::cout << "Loaded " << editor.getNPCCount() << " NPCs from " << path
                  << std::endl;
      } catch (const std::exception &e) {
        std::cout << "Error loading file: " << e.what() << std::endl;
      }
      break;
    }

    case 5: {
      if (editor.getNPCCount() < 2) {
        std::cout << "Need at least 2 NPCs for battle!" << std::endl;
        break;
      }

      int radius;
      std::cout << "Attack radius (default: " << attackRadius << "): ";
      std::cin >> radius;
      if (radius <= 0)
        radius = attackRadius;

      std::cout << "\n=== BATTLE STARTED ===" << std::endl;
      std::cout << "Attack radius: " << radius << std::endl;
      std::cout << "Participants: " << editor.getNPCCount() << std::endl;

      editor.fight(radius);

      std::cout << "=== BATTLE FINISHED ===" << std::endl;
      std::cout << "Survivors: " << editor.getNPCCount() << std::endl;
      break;
    }

    case 6: {
      char confirm;
      std::cout << "Clear all NPCs? (y/n): ";
      std::cin >> confirm;
      if (confirm == 'y' || confirm == 'Y') {
        editor.clearAll();
        std::cout << "All NPCs cleared!" << std::endl;
      }
      break;
    }

    default:
      std::cout << "Invalid command!" << std::endl;
    }
  }

  std::cout << "\n=== Final Dungeon State ===" << std::endl;
  editor.printAll();
  std::cout << "\nGoodbye! Log saved to log.txt" << std::endl;

  return 0;
}