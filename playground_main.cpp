#include <iostream>

void play(int& x) {
  x = 10;
  std::cout << "X is " << x << "\n";
  return;
}
int main() {
  int x = 5;

  // Lambda capturing by value
  auto myLambda = [&] {
    // int y = x;
    x = 10;  // Modification within the lambda
    return x;
  };

  int result = myLambda();  // result will be 5 (original value)

  std::cout << "x is " << x << "\n";
  std::cout << "result is " << result << "\n";

  int temp = 5;
  play(temp);

  return 0;
}
