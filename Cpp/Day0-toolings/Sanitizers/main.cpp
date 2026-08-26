//
// Created by yentrinh on 26/8/26.
//
#include <iostream>
using namespace std;
void outOfBounds() {
  int arr[5] = {10, 20, 30, 40, 50};
  int outBoundValue = arr[7];
  cout << "Out of bound value: " << outBoundValue << "\n";
}

int main() {
  outOfBounds();
  return 0;
}