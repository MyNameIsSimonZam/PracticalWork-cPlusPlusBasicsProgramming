#include <iostream>
#include <string>

/*Задание 4. Оценка результатов игры в крестики-нолики
Что нужно сделать
Петя и Вася играли в крестики-нолики и не стёрли результаты своей игры.
Теперь перед вами табличка 3 × 3, которая осталась после их поединка.
Вы хотите понять, выиграл ли кто-то из них или они не доиграли.
На вход программе даётся три строки, кодирующие верхнюю,
среднюю и нижнюю строчки игрового поля.
Крестик обозначается символом X (английская заглавная буква X),
нолик — символом O (заглавная английская буква O), пустая клетка — точкой.
Если ввод некорректен, то есть такая таблица не могла получиться в ходе настоящей игры,
то надо написать в ответ слово Incorrect.
Если таблица корректна и выиграли крестики, то нужно вывести в ответ слова Petya won,
если нолики — Vanya won, иначе (то есть они не доиграли или сыграли вничью)
надо написать Nobody.

Примеры
X..
OXO
OOO
Ответ: Incorrect (потому что ноликов в конце игры не может быть больше, чем крестиков).
X..
.X.
OO.
Ответ: Nobody (потому что они не доиграли).
XXO
OOX
XOX
Ответ: Nobody (потому что это ничья).
XO.
XO.
X.O
Ответ: Incorrect (крестики уже победили, и ноликов не может быть столько же).
OX.
XOX
X.O
Ответ: Incorrect (потому что нолики выиграли за три хода,
и на поле за это время не могло успеть появиться четыре крестика).
..X
OX.
X.O
Ответ: Petya won.
0..
...
...
Ответ: Incorrect (потому что допускаются только символы X, O и точка,
а цифра 0 не является допустимым символом).

Рекомендации
• Активно используйте оператор индексации строки str[i], но помните,
что индексы начинаются с нуля, а не с единицы.
• Чтобы обращаться к элементам игрового поля,
стоит написать отдельную функцию получения элемента поля по его координатам (x, y).
В таком случае часть алгоритмов поиска победителя можно обобщить.
• Функции проверки поля на корректность можно отделить от функций и алгоритмов проверки победителя.
• При достаточной модульности функций некоторые операции
можно реализовать через уже существующие процедуры.
К примеру, если уже есть проверка победителя в строке и имеется функция
получения колонки по индексу, то функцию поиска победителя
в колонке можно реализовать через обе процедуры.
• Проход по диагонали поля можно осуществить в цикле, используя счётчик цикла
в качестве обоих координат элемента. Для второй диагонали нужно
обратить одну из координат (2 − x или 2 − y).
• Общие условия некорректности поля таковы:
— выявлено несколько победителей одновременно; в функциях поиска победителей +
— нолики победили, а крестиков больше, чем ноликов;
— крестики победили, а ноликов столько же или больше;
— нолики и крестики победили несколько раз; в функциях поиска победителей +
— на поле есть невалидные символы. stringValidation ПРОВЕРКА НА ПЕРВОМ ЭТАПЕ  +

Для упрощения лучше создать отдельные функции для проверки победителя в строке или столбце,
которые на вход принимают строку, а на выходе выдают символ победителя. То есть ‘X’, ‘O’ или ‘.’*/

bool stringValidation(std::string first, std::string second,
  std::string third) {
  if (first.length() != 3) return false;
  if (second.length() != 3) return false;
  if (third.length() != 3) return false;

  for (int i = 0; i < first.length(); ++i) {
    if (first[i] != 'X' && first[i] != 'O' && first[i] != '.') return false;
    if (second[i] != 'X' && second[i] != 'O' && second[i] != '.') return false;
    if (third[i] != 'X' && third[i] != 'O' && third[i] != '.') return false;
  }

  return true;
}

char searchWinInRow(std::string first, std::string second,  // We catch dowblewinner in only row      
  std::string third) {
  int countO = 0;
  int countX = 0;

  if (first[0] == first[1] && first[1] == first[2]) {
    if (first[0] == 'O') ++countO;
    if (first[0] == 'X') ++countX;
  }
  if (second[0] == second[1] && second[1] == second[2]) {
    if (second[0] == 'O') ++countO;
    if (second[0] == 'X') ++countX;
  }
  if (third[0] == third[1] && third[1] == third[2]) {
    if (third[0] == 'O') ++countO;
    if (third[0] == 'X') ++countX;
  }

  if (countO == 1 && countX == 0) return 'O';
  if (countX == 1 && countO == 0) return 'X';
  if (countX == 0 && countO == 0) return '.';
  return '?';
}

char searchWinInColomn(std::string first, std::string second,      // We catch dowblewinner in only colomn       
  std::string third) {
  int countO = 0;
  int countX = 0;

  for (int i = 0; i < 3; ++i) {
    if (first[i] == second[i] && second[i] == third[i]) {
      if (first[i] == 'O') ++countO;
      if (first[i] == 'X') ++countX;
    }
  }
  if (countO == 1 && countX == 0) return 'O';
  if (countX == 1 && countO == 0) return 'X';
  if (countX == 0 && countO == 0) return '.';

  return '?';
}

char searchWinInDiagonal(std::string first, std::string second,
  std::string third) {
  int countO = 0;
  int countX = 0;
  bool flag = false;

  if (first[0] == second[1] && second[1] == third[2]) {
    flag = !flag;
    if (first[0] == 'O') ++countO;
    if (first[0] == 'X') ++countX;
  }
  if (first[2] == second[1] && second[1] == third[0]) {
    flag = !flag;
    if (first[2] == 'O') ++countO;
    if (first[2] == 'X') ++countX;
  }
  if (flag) {
    if (countO == 1) return 'O';
    if (countX == 1) return 'X';
  }

  return '.';
}

bool doubleWinner(std::string first, std::string second,
  std::string third) {
  char rowWinner = searchWinInRow(first, second, third);
  char colomnWinner = searchWinInColomn(first, second, third);
  char diagonalWinner = searchWinInDiagonal(first, second, third);

  if (rowWinner == colomnWinner) {
    if (rowWinner == 'X' || rowWinner == 'O') return false;
  }
  if (rowWinner == diagonalWinner) {
    if (rowWinner == 'X' || rowWinner == 'O') return false;
  }
  if (diagonalWinner == colomnWinner) {
    if (diagonalWinner != 'X' || diagonalWinner == 'O') return false;
  }
  return true;
}

bool twoWinners(std::string first, std::string second,
  std::string third) {
  char rowWinner = searchWinInRow(first, second, third);
  char colomnWinner = searchWinInColomn(first, second, third);
  char diagonalWinner = searchWinInDiagonal(first, second, third);

  int countO = 0;
  int countX = 0;

  if (rowWinner == 'O') ++countO;
  if (colomnWinner == 'O') ++countO;
  if (diagonalWinner == 'O') ++countO;
  if (rowWinner == 'X') ++countX;
  if (colomnWinner == 'X') ++countX;
  if (diagonalWinner == 'X') ++countX;

  if (countX > 0 && countO > 0) return false;

  return true;
}

int countX(std::string first, std::string second,
  std::string third) {
  int result = 0;

  for (int i = 0; i < first.length(); ++i) {
    if (first[i] == 'X') ++result;
  }
  for (int i = 0; i < second.length(); ++i) {
    if (first[i] == 'X') ++result;
  }
  for (int i = 0; i < third.length(); ++i) {
    if (first[i] == 'X') ++result;
  }

  return result;
}

int countO(std::string first, std::string second,
  std::string third) {
  int result = 0;

  for (int i = 0; i < first.length(); ++i) {
    if (first[i] == 'O') ++result;
  }
  for (int i = 0; i < second.length(); ++i) {
    if (first[i] == 'O') ++result;
  }
  for (int i = 0; i < third.length(); ++i) {
    if (first[i] == 'O') ++result;
  }

  return result;
}

int countDot(std::string first, std::string second,
  std::string third) {
  int result = 0;

  for (int i = 0; i < first.length(); ++i) {
    if (first[i] == '.') ++result;
  }
  for (int i = 0; i < second.length(); ++i) {
    if (first[i] == '.') ++result;
  }
  for (int i = 0; i < third.length(); ++i) {
    if (first[i] == '.') ++result;
  }

  return result;
}

char searchWinner(std::string first, std::string second,
  std::string third) {

  if (searchWinInRow(first, second, third) == 'X') {
    if (countX(first, second, third) == countO(first, second, third) - 1) {
      return 'X';
    }
  }
  if (searchWinInRow(first, second, third) == 'O') {
    if (countX(first, second, third) == countO(first, second, third)) {
      return 'O';
    }
  }

  if (searchWinInColomn(first, second, third) == 'X') {
    if (countX(first, second, third) == countO(first, second, third) - 1) {
      return 'X';
    }
  }
  if (searchWinInColomn(first, second, third) == 'O') {
    if (countX(first, second, third) == countO(first, second, third)) {
      return 'O';
    }
  }

  if (searchWinInDiagonal(first, second, third) == 'X') {
    if (countX(first, second, third) == countO(first, second, third) - 1) {
      return 'X';
    }
  }
  if (searchWinInDiagonal(first, second, third) == 'O') {
    if (countX(first, second, third) == countO(first, second, third)) {
      return 'O';
    }
  }
  return '.';
}

bool incorrectFounder(std::string first, std::string second,
  std::string third) {

  // there was fined error in row or colomn
  if (searchWinInRow(first, second, third) == '?' ||
    searchWinInColomn(first, second, third) == '?') {
    return false;
  }

  // Winner maast be only in row or colomn or diagonal
  if (!stringValidation(first, second, third) || !doubleWinner(first, second, third) ||
    !twoWinners(first, second, third)) {
    return false;
  }

  // X have to be more then O jasn on 1, or they have to be equal
  if (countX(first, second, third) != countO(first, second, third) ||
    (countX(first, second, third) - 1) != countO(first, second, third)) {
    return false;
  }

  return true;
}

void task4() {
  std::string test = "..X";
  std::string test1 = "OX.";
  std::string test2 = "X.O";
  //std::string test = "X..";
  //std::string test1 = ".X.";
  //std::string test2 = "OO.";

  if (!incorrectFounder(test, test1, test2)) {
    std::cout << "Incorrect\n";
  }
  else if (searchWinner(test, test1, test2) == 'X') {
    std::cout << "Petya won\n";
  }
  else if (searchWinner(test, test1, test2) == 'O') {
    std::cout << "Vasya won\n";
  }
  else if (searchWinner(test, test1, test2) == '.') {
    std::cout << "Nobody\n";
  }

}

/*Примеры
X..
OXO
OOO
Ответ : Incorrect(потому что ноликов в конце игры не может быть больше, чем крестиков).
X..
.X.
OO.
Ответ : Nobody(потому что они не доиграли).
XXO
OOX
XOX
Ответ : Nobody(потому что это ничья).
XO.
XO.
X.O
Ответ : Incorrect(крестики уже победили, и ноликов не может быть столько же).
OX.
XOX
X.O
Ответ : Incorrect(потому что нолики выиграли за три хода,
  и на поле за это время не могло успеть появиться четыре крестика).
  ..X
  OX.
  X.O
  Ответ : Petya won.
  0..
  ...
  ...
  Ответ : Incorrect(потому что допускаются только символы X, O и точка,
    а цифра 0 не является допустимым символом).               */