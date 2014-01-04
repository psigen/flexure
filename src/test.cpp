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

template <typename T>
class TypedFlexure {
  public:
    TypedFlexure(const string& name) : name_(name) {
    };
    TypedFlexure<T>& operator=(const T&) {}
   T* x_;
    const string name_;
};


class InferenceFlexure{
  public:
  InferenceFlexure(const string& name) : name_(name) {}
  template <typename T_Other>
    TypedFlexure<T_Other> operator=(const T_Other& value) {
      return (TypedFlexure<T_Other>(name_));
    }

  const string name_;
};


class Flexure {
public: 
  Flexure();
  Flexure (const string& name) {}
  /*
  int& operator[](const string& name) {
    return (a_);
  }
  int a_;
  */
  // template <typename T>
  InferenceFlexure operator[](const string& name) {
    return InferenceFlexure(name);
  }
  
  // const type;
};

int main() {
  int a = 3;
  double b = 5.0;
  const int type_a = TypeName(a);
  const int type_b = TypeName(b);
  printf("b = %d\n", type_b);
  Flexure f("/");
  auto bar = (f["apple"] = 2);
  f["pear"] = "String";
  // The following is valid:
  bar = 3;

  // The following will throw a compile error:
  // bar = "string";
  return 0;
}
