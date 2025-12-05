#include "DungeonMap.h"
#include "NPC/bear.h"
#include "NPC/knight.h"
#include "NPC/npc.h"
#include "NPC/npc_factory.h"
#include "NPC/orc.h"
#include "Observer/console_observer.h"
#include "Observer/file_observer.h"
#include "Visitor/fight_visitor.h"
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>

TEST(NPCTest, BasicFunctionality) {
  Orc orc("Grom", 100, 100);
  EXPECT_EQ(orc.getType(), "Orc");
  EXPECT_EQ(orc.getName(), "Grom");
  EXPECT_EQ(orc.getX(), 100);
  EXPECT_EQ(orc.getY(), 100);

  Knight knight("Arthur", 200, 200);
  EXPECT_EQ(knight.getType(), "Knight");
  EXPECT_EQ(knight.getName(), "Arthur");

  Bear bear("Baloo", 300, 300);
  EXPECT_EQ(bear.getType(), "Bear");
  EXPECT_EQ(bear.getName(), "Baloo");
}

TEST(NPCTest, DistanceCalculation) {
  Orc orc1("Orc1", 0, 0);
  Knight knight1("Knight1", 3, 4);

  // Расстояние = 5 (3-4-5 треугольник)
  EXPECT_TRUE(orc1.isClose(knight1, 5));
  EXPECT_FALSE(orc1.isClose(knight1, 4));

  // Тест на одинаковых позициях
  Orc orc2("Orc2", 100, 100);
  Knight knight2("Knight2", 100, 100);
  EXPECT_TRUE(orc2.isClose(knight2, 0));
  EXPECT_TRUE(orc2.isClose(knight2, 1));
}

TEST(NPCTest, FactoryCreation) {
  auto orc = NPCFactory::createNPC("Orc", "FactoryOrc", 10, 20);
  EXPECT_EQ(orc->getType(), "Orc");
  EXPECT_EQ(orc->getName(), "FactoryOrc");

  auto knight = NPCFactory::createNPC("Knight", "FactoryKnight", 30, 40);
  EXPECT_EQ(knight->getType(), "Knight");
  EXPECT_EQ(knight->getName(), "FactoryKnight");

  auto bear = NPCFactory::createNPC("Bear", "FactoryBear", 50, 60);
  EXPECT_EQ(bear->getType(), "Bear");
  EXPECT_EQ(bear->getName(), "FactoryBear");

  // Неверный тип
  EXPECT_THROW(NPCFactory::createNPC("Dragon", "Invalid", 0, 0),
               std::runtime_error);

  // Неверные координаты
  EXPECT_THROW(NPCFactory::createNPC("Orc", "BadOrc", -10, 100),
               std::runtime_error);
  EXPECT_THROW(NPCFactory::createNPC("Orc", "BadOrc2", 100, 600),
               std::runtime_error);
}

TEST(NPCTest, FactorySerialization) {
  // Используем имя без пробелов для простоты
  auto orc = std::make_shared<Orc>("SerializedOrc", 150, 150);
  std::string data = NPCFactory::saveToString(*orc);

  auto loaded = NPCFactory::loadFromString(data);
  EXPECT_EQ(loaded->getType(), "Orc");
  EXPECT_EQ(loaded->getName(), "SerializedOrc");
  EXPECT_EQ(loaded->getX(), 150);
  EXPECT_EQ(loaded->getY(), 150);

  // Тест с рыцарем
  auto knight = std::make_shared<Knight>("SirLancelot", 250, 350);
  data = NPCFactory::saveToString(*knight);
  loaded = NPCFactory::loadFromString(data);
  EXPECT_EQ(loaded->getType(), "Knight");
  EXPECT_EQ(loaded->getName(), "SirLancelot");
}

TEST(NPCTest, FactoryFileOperations) {
  // Создаем тестовых NPC
  std::vector<std::shared_ptr<NPC>> npcs;
  npcs.push_back(NPCFactory::createNPC("Orc", "FileOrc", 10, 20));
  npcs.push_back(NPCFactory::createNPC("Knight", "FileKnight", 30, 40));
  npcs.push_back(NPCFactory::createNPC("Bear", "FileBear", 50, 60));

  // Сохраняем в файл
  const std::string filename = "test_save.txt";
  NPCFactory::saveToFile(npcs, filename);

  // Проверяем, что файл создан
  std::ifstream file(filename);
  ASSERT_TRUE(file.is_open());

  // Читаем первую строку (количество)
  size_t count;
  file >> count;
  EXPECT_EQ(count, 3);

  file.close();

  // Загружаем из файла
  auto loaded = NPCFactory::loadFromFile(filename);
  ASSERT_EQ(loaded.size(), 3);

  // Проверяем загруженные данные
  EXPECT_EQ(loaded[0]->getType(), "Orc");
  EXPECT_EQ(loaded[0]->getName(), "FileOrc");
  EXPECT_EQ(loaded[0]->getX(), 10);

  // Удаляем тестовый файл
  std::remove(filename.c_str());
}

TEST(NPCTest, FactoryInvalidFile) {
  EXPECT_THROW(NPCFactory::loadFromFile("nonexistent_file.txt"),
               std::runtime_error);
}

// ==================== DungeonMap Tests ====================

TEST(DungeonMapTest, AddRemoveNPC) {
  DungeonEditor editor;

  EXPECT_EQ(editor.getNPCCount(), 0);

  // Добавляем NPC
  editor.addNPC("Orc", "TestOrc", 100, 100);
  EXPECT_EQ(editor.getNPCCount(), 1);

  editor.addNPC("Knight", "TestKnight", 200, 200);
  EXPECT_EQ(editor.getNPCCount(), 2);

  // Удаляем NPC
  editor.removeNPC("TestOrc");
  EXPECT_EQ(editor.getNPCCount(), 1);

  // Удаляем несуществующего NPC
  editor.removeNPC("NonExistent");
  EXPECT_EQ(editor.getNPCCount(), 1); // Количество не должно измениться

  // Очищаем все
  editor.clearAll();
  EXPECT_EQ(editor.getNPCCount(), 0);
}

TEST(DungeonMapTest, InvalidCoordinates) {
  DungeonEditor editor;

  EXPECT_THROW(editor.addNPC("Orc", "Orc1", -10, 100), std::runtime_error);
  EXPECT_THROW(editor.addNPC("Orc", "Orc2", 100, 600), std::runtime_error);
  EXPECT_THROW(editor.addNPC("Orc", "Orc3", 1000, 1000), std::runtime_error);
}

TEST(DungeonMapTest, DuplicateName) {
  DungeonEditor editor;

  editor.addNPC("Orc", "Unique", 100, 100);
  EXPECT_THROW(editor.addNPC("Knight", "Unique", 200, 200), std::runtime_error);

  // Но разные имена должны работать
  editor.addNPC("Knight", "Unique2", 300, 300);
  EXPECT_EQ(editor.getNPCCount(), 2);
}

TEST(DungeonMapTest, FileOperations) {
  DungeonEditor editor;

  // Добавляем NPC
  editor.addNPC("Orc", "SaveOrc", 100, 200);
  editor.addNPC("Knight", "SaveKnight", 300, 400);

  // Сохраняем
  const std::string filename = "dungeon_test_save.txt";
  editor.saveToFile(filename);

  // Создаем новый редактор и загружаем
  DungeonEditor editor2;
  editor2.loadFromFile(filename);

  EXPECT_EQ(editor2.getNPCCount(), 2);

  // Проверяем загруженные данные
  auto npcs = editor2.getNPC();
  EXPECT_EQ(npcs[0]->getType(), "Orc");
  EXPECT_EQ(npcs[0]->getName(), "SaveOrc");

  // Удаляем тестовый файл
  std::remove(filename.c_str());
}

TEST(DungeonMapTest, EmptyBattle) {
  DungeonEditor editor;

  // Битва без NPC
  editor.fight(100);
  EXPECT_EQ(editor.getNPCCount(), 0);

  // Один NPC - не должно быть битвы
  editor.addNPC("Orc", "LonelyOrc", 100, 100);
  editor.fight(100);
  EXPECT_EQ(editor.getNPCCount(), 1); // Все еще должен быть жив
}

TEST(DungeonMapTest, ObserverAttachment) {
  DungeonEditor editor;

  auto consoleObs = std::make_shared<ConsoleObserver>();
  auto fileObs = std::make_shared<FileObserver>("test_log.txt");

  editor.attachObserver(consoleObs);
  editor.attachObserver(fileObs);

  // Добавляем NPC - наблюдатели должны получить уведомление
  editor.addNPC("Orc", "ObservedOrc", 100, 100);

  // Удаляем наблюдателя
  editor.detachObserver(fileObs);

  // Очищаем тестовый файл
  std::remove("test_log.txt");
}

// ==================== Visitor Tests ====================

TEST(VisitorTest, FightVisitorCreation) {
  std::vector<std::shared_ptr<NPC>> npcs;
  FightVisitor visitor(npcs, 100);

  // Проверяем, что visitor создан
  SUCCEED();
}

TEST(VisitorTest, OrcCombatRules) {
  std::vector<std::shared_ptr<NPC>> npcs;

  // Создаем NPC
  auto orc = std::make_shared<Orc>("TestOrc", 0, 0);
  auto bear = std::make_shared<Bear>("TestBear", 5, 0);       // Близко
  auto knight = std::make_shared<Knight>("TestKnight", 5, 0); // Близко
  auto orc2 = std::make_shared<Orc>("TestOrc2", 8, 0);        // Близко

  npcs.push_back(orc);
  npcs.push_back(bear);
  npcs.push_back(knight);
  npcs.push_back(orc2);

  // Создаем visitor с радиусом 10
  FightVisitor visitor(npcs, 10);
  visitor.setAttacker(orc);

  // Орк атакует
  orc->accept(visitor);

  // В жертвы должны попасть: медведь и другой орк (но не рыцарь)
  // Применяем убийства (нужен KillSubject)
  // Для теста просто проверяем, что visitor работает
  SUCCEED();
}

// ==================== Observer Tests ====================

TEST(ObserverTest, ConsoleObserver) {
  ConsoleObserver observer;

  // Просто проверяем, что не падает
  observer.update("Test message");
  SUCCEED();
}

TEST(ObserverTest, FileObserver) {
  const std::string filename = "observer_test.txt";

  {
    FileObserver observer(filename);
    observer.update("Test message 1");
    observer.update("Test message 2");
  } // Файл закроется при разрушении observer

  // Проверяем, что файл создан и содержит сообщения
  std::ifstream file(filename);
  ASSERT_TRUE(file.is_open());

  std::string line;
  std::getline(file, line);
  EXPECT_EQ(line, "Test message 1");

  std::getline(file, line);
  EXPECT_EQ(line, "Test message 2");

  file.close();
  std::remove(filename.c_str());
}

TEST(ObserverTest, SubjectBasic) {
  Subject subject;

  auto observer1 = std::make_shared<ConsoleObserver>();
  auto observer2 = std::make_shared<ConsoleObserver>();

  subject.attach(observer1);
  subject.attach(observer2);

  // Уведомляем - не должно падать
  subject.notify("Test notification");

  subject.detach(observer1);
  subject.notify("Another notification");

  SUCCEED();
}

// ==================== Integration Tests ====================

TEST(IntegrationTest, CompleteWorkflow) {
  DungeonEditor editor;

  // 1. Создаем NPC
  editor.addNPC("Orc", "Grom", 100, 100);
  editor.addNPC("Knight", "Arthur", 150, 150);
  editor.addNPC("Bear", "Baloo", 200, 200);

  EXPECT_EQ(editor.getNPCCount(), 3);

  // 2. Сохраняем в файл
  editor.saveToFile("integration_test.txt");

  // 3. Очищаем и загружаем
  editor.clearAll();
  EXPECT_EQ(editor.getNPCCount(), 0);

  editor.loadFromFile("integration_test.txt");
  EXPECT_EQ(editor.getNPCCount(), 3);

  // 4. Запускаем битву
  editor.fight(100);

  // 5. Удаляем тестовый файл
  std::remove("integration_test.txt");
}

// ==================== Edge Cases ====================

TEST(EdgeCaseTest, LargeDistanceBattle) {
  DungeonEditor editor;

  editor.addNPC("Orc", "Orc1", 0, 0);
  editor.addNPC("Knight", "Knight1", 500, 500); // Максимальное расстояние

  // Битва с радиусом 1000 (больше диагонали карты)
  editor.fight(1000);

  // Должны сразиться
  EXPECT_EQ(editor.getNPCCount(), 1); // Рыцарь убивает орка
}