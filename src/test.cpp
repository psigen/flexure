#include <stdio.h>
#include <string>

using std::string;

template <typename T>
constexpr int TypeName(const T& x) {
  return 0;
}

template <>
constexpr int TypeName<int>(const int& x) {
  return 1;
}

template <>
constexpr int TypeName<double>(const double& x) {
  return 2;
}

class InferenceFlexure;

template <typename T = void*>
class Flexure {
 public:
  Flexure(const string& name) : name_(name) {
  };
  
  Flexure<T>& operator=(const T&) {}
  InferenceFlexure operator[](const string& name);

  T* x_;
  const string name_;
};

class InferenceFlexure {
  public:
  InferenceFlexure(const string& name) : name_(name) {}
  template <typename T_Other>
    Flexure<T_Other> operator=(const T_Other& value) {
      return (Flexure<T_Other>(name_));
    }

  const string name_;
};

template <typename T>
InferenceFlexure Flexure<T>::operator[](const string& name)
{
  return InferenceFlexure(name);
}

int main() {
  int a = 3;
  double b = 5.0;
  const int type_a = TypeName(a);
  const int type_b = TypeName(b);
  printf("b = %d\n", type_b);
  Flexure<> f("/");
  auto bar = (f["apple"] = 2);
  f["pear"] = "String";
  // The following is valid:
  bar = 3;

  // The following will throw a compile error:
  // bar = "string";
  return 0;
}
