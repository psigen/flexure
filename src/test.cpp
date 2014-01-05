#include <stdio.h>
#include <map>
#include <string>
#include "type_enum.h"

using std::map;
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

struct Undefined {
};

class InferenceFlexure;

template <typename T = Undefined>
class Flexure {
 public:
  Flexure(const string& name) : name_(name) {
  };
  
  Flexure<T>& operator=(const T&) {
    return (*this);
  }
  Flexure<Undefined> operator[](const string& name);
 
  template <typename T_Other>
  Flexure<T_Other> operator=(const T_Other& value);
  
  T* x_;
  const string name_;
};

template <> template <typename T_Other>
Flexure<T_Other> Flexure<Undefined>::operator=(const T_Other& value) {
   return (Flexure<T_Other>(name_));
}

/*
template <typename T> template <typename T_Other = T>
Flexure<T_Other> Flexure<T>::operator=(const T_Other& value) {
   return (Flexure<T>(name_));
}
*/

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
Flexure<Undefined> Flexure<T>::operator[](const string& name)
{
  return Flexure<Undefined>(name);
}

class Memory {
  Memory();
  void* pointer();
  ~Memory();
};

// Would help to have this be compatible with std::allocator for transparent use
// with std::map for schema.
class HeapAllocator {
  void Init(Memory* memory) {}
  void* Alloc(size_t size);
  void Free(void* ptr);
};

class Entry {

 protected:
  FlexureTypes type_;
  size_t ref_count_;
 public:
  void* pointer_;
};

class FlexureDataStore {
 public:
  FlexureDataStore();
  Entry& Get(const string& fq_name);

 protected:
  map<string, Entry> schema_;
  HeapAllocator heap_alloc_;
};

int main() {
  int a = 3;
  double b = 5.0;
  const int type_a = TypeName(a);
  const int type_b = TypeName(b);
  printf("a : %d\n", type_a);
  printf("b : %d\n", type_b);
  Flexure<> f("/");
  auto apple = f["apple"];
  apple = 3;
  // The following works at compile time, but should fail at run time:
  apple = "String";

  auto bar = (f["apple"] = 2);
  f["pear"] = "String";
  // The following is valid:
  bar = 3;
  
  auto foo = bar["foo"];
  foo = 2;
  foo = "blah";
  
  
  // The following will throw a compile error:
  // bar = "string";
  return 0;
}
