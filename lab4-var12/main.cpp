#include "pentagon.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "vector.h"

#include <iostream>
#include <memory>

int main() {
  vector::Vector<std::shared_ptr<figure::Figure<double>>> figures;
  int com_type;

  std::cout << "\n1. Добавить трапецию\n";
  std::cout << "\n2. Добавить ромб\n";
  std::cout << "\n3. Добавить пятиугольник\n";
  std::cout << "\n4. Вывести центры всех фигур\n";
  std::cout << "\n5. Вывести площади всех фигур\n";
  std::cout << "\n6. Вывести общую площадь\n";
  std::cout << "\n7. Удалить фигуру по индексу\n";
  std::cout << "\n0. Выход\n";
  std::cin >> com_type;

  while (true) {
    if (com_type == 0)
      break;
    switch (com_type) {
    case 1: {
      auto cur = std::make_shared<figure::Trapezoid<double>>();
      std::cin >> *cur;
      figures.PushBack(cur);
      std::cout << "Трапеция добавлена\n";
      break;
    }

    case 2: {
      auto cur = std::make_shared<figure::Rhombus<double>>();
      std::cin >> *cur;
      figures.PushBack(cur);
      std::cout << "Ромб добавлен\n";
      break;
    }

    case 3: {
      auto cur = std::make_shared<figure::Pentagon<double>>();
      std::cin >> *cur;
      figures.PushBack(cur);
      std::cout << "Пятиугольник добавлен\n";
      break;
    }

    case 4: {
      if (figures.IsEmpty()) {
        std::cout << "Нет фигур\n";
      } else {
        figures.template PrintAllCenters<figure::Figure<double>>();
      }
      break;
    }

    case 5: {
      if (figures.IsEmpty()) {
        std::cout << "Нет фигур\n";
      } else {
        figures.template PrintAllAreas<figure::Figure<double>>();
      }
      break;
    }

    case 6: {
      std::cout << "Общая площадь всех фигур: "
                << figures.template TotalArea<figure::Figure<double>>()
                << std::endl;
      break;
    }

    case 7: {
      if (figures.IsEmpty()) {
        std::cout << "Нет фигур для удаления\n";
        break;
      }
      size_t pos;
      std::cout << "Введите номер фигуры от 1 до " << figures.Size() << "): ";
      std::cin >> pos;
      --pos;
      if (pos < figures.Size()) {
        figures.Erase(pos);
        std::cout << "Фигура удалена\n";
      } else {
        std::cout << "Неверный номер\n";
      }
      break;
    }

    default: {
      std::cout << "Неверный номер\n";
      break;
    }
    }

    std::cin >> com_type;
  }
}