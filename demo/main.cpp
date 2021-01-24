#include <Broker.hpp>

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << Broker::Checking(".", cout);
  } else if (argc == 2) {

    cout << Broker::Checking(argv[1], cout);
  } else {
    cout << "Too many arguments!";
  }
}