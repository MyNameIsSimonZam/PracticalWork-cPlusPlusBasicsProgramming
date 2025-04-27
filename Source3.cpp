#include <iostream>
#include <string>

/*Задание 3. Валидация IP-адреса
Что нужно сделать
Проверьте, задаёт ли введённая пользователем строка корректный IP-адрес четвёртой версии (IPv4).
IP-адрес должен представлять из себя четыре числа, разделённые точками без пробелов,
причём каждое число должно быть в диапазоне от 0 до 255 включительно.
Числа не должны содержать ведущих нулей. Других символов в строке, кроме вышеописанных, быть не должно.
Пользователь вводит строку, задающую IP-адрес через стандартный ввод.
В результате программа должна вывести слово Valid, если адрес корректен, и слово Invalid, если это не так.

Примеры
Корректные:
127.0.0.1
255.255.255.255
1.2.3.4
55.77.213.101
Некорректные:
255.256.257.258 (есть числа больше 255)
0.55.33.22. (лишняя точка в конце)
10.00.000.0 (лишние нули)
23.055.255.033 (опять лишние нули)
65.123..9 (две точки подряд)
a.b.c.d (посторонние символы вместо чисел и точек)

Рекомендации
• Активно используйте оператор индексации строки str[i], но помните,
что индексы начинаются с нуля, а не с единицы.
• Создайте отдельную функцию для получения отдельных чисел из IP-адреса и валидируйте эти отдельные числа.
• Для валидации отдельных цифр у чисел следует использовать оператор сравнения с константами символов.
Символы от ‘0’ до ‘9’ расположены последовательно и поэтому уместны операторы <= и >=.
Вам потребуется функция, принимающая на вход строку со всем IP-адресом и порядковый номер октета.
Октет — это часть IP-адреса между точками. Он содержится в восьми битах, отсюда и название (окта — восемь). 2^8 = 256.
Отсюда уже предел значения октета — 255. То есть вызов get_address_part(“192.168.1.1”, 1) вернёт 168.
Данная функция проходит по всей строке и ищет разделители — точки, одновременно с этим накапливает символы в строку,
которую вернёт в результате. При нахождении разделителя нужно вернуть полученную строку.
Проверку её корректности нужно делать в другой функции (проверить длину == 3 и то, что число в строке находится в диапазоне [0,255] ).
*/

bool validOctet(std::string octet) {
  int checkSum = 0;
  int factor = 1;

  if (octet.length() > 3 || octet.length() < 1) return false;
  if (octet[0] == '0') {
    if (octet.length() != 1) return false;
  }
  else {
    for (int i = octet.length() - 1; i >= 0; --i) {
      if (octet[i] < '0' || octet[i] > '9') return false;
      else {
        checkSum += (octet[i] - '0') * factor;
        factor *= 10;
      }
    }
  }
  return (checkSum > 255) ? false : true;
}

std::string getOctet(std::string ip, int octetNumber) {
  std::string octetValue;
  int dotCount = 0;

  for (int i = 0; i < ip.length(); ++i) {
    if (ip[i] == '.') dotCount++;
    else if (octetNumber - 1 == dotCount) octetValue += ip[i];
  }

  return octetValue;
}

bool validIPv4(std::string ip) {
  bool errorFlag = true;
  int dotCount = 0;

  for (int i = 0; i < ip.length(); ++i) {
    if (ip[i] == '.') dotCount++;
    if (dotCount > 3) { errorFlag = false; return false; }
  }

  for (int i = 1; i <= 4; ++i) {
    errorFlag = validOctet(getOctet(ip, i));
    if (errorFlag == false) break;
  }
  return (errorFlag) ? true : false;
}

void task3() {
  std::string ip;
  //std::string ip1 = "255.255.255.255";
  //std::string ip2 = "1.2.3.4";
  //std::string ip3 = "55.77.213.101";
  //std::string ip4 = "255.256.257.258";
  //std::string ip5 = "0.55.33.22.";
  //std::string ip6 = "10.00.000.0";
  //std::string ip7 = "23.055.255.033";
  //std::string ip8 = "65.123..9";
  //std::string ip9 = "a.b.c.d";
  std::cout << "Insert the IPv4: ";
  std::cin.ignore();
  std::getline(std::cin, ip);

  std::cout << ((validIPv4(ip)) ? "Valid\n" : "Invalid\n");
  //std::cout << ((validIPv4(ip1)) ? "ip1 Valid\n" : "Invalid\n");
  //std::cout << ((validIPv4(ip2)) ? "ip2 Valid\n" : "Invalid\n");
  //std::cout << ((validIPv4(ip3)) ? "ip3 Valid\n" : "Invalid\n");
  //std::cout << ((validIPv4(ip4)) ? "ip4 Valid\n" : "Invalid\n");
  //std::cout << ((validIPv4(ip5)) ? "ip5 Valid\n" : "Invalid\n");
  //std::cout << ((validIPv4(ip6)) ? "ip6 Valid\n" : "Invalid\n");
  //std::cout << ((validIPv4(ip7)) ? "ip7 Valid\n" : "Invalid\n");
  //std::cout << ((validIPv4(ip8)) ? "ip8 Valid\n" : "Invalid\n");
  //std::cout << ((validIPv4(ip9)) ? "ip9 Valid\n" : "Invalid\n");
}
