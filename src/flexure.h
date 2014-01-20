#ifndef FLEXURE_H
#define FLEXURE_H

#include <string>

namespace Flexure
{
struct Undefined;

template <typename T = Undefined>
class Flexure
{
 public:
  Flexure(const string& name = "");
  virtual ~Flexure();

  // Data accessor methods
  Flexure<T>& operator=(const T&);  
  operator T();

  // Runtime casting accessor methods
  template <typename T2> Flexure<T2> operator=(const T2& value);
  template <typename T2> operator T2(); 

  // Hierarchy accessor methods
  Flexure<Undefined> operator[](const string& name);
  template <typename T2> Flexure<T2> Get(const string& name); 
  
  // Meta-accessor methods
  void Observe(void (*function)(const T& value));
  void Unobserve(void (*function)(const T& value));
 
  void Lock();
  void Unlock();
  
 private:
  Flexure::Entry entry_;
};

template<typename T>
class Flexure
{
public:
  // Access subfields
  virtual Flexure& operator[] (unsigned int i) = 0;
  virtual const Flexure& operator[] (unsigned int i) const = 0;

  // Register function observers (on changes)
  void Observe(void (*function)(const T& value));
  void Unobserve(void (*function)(const T& value));

  // Lock hierarchy for copy-on-unlock
  void Lock();
  void Unlock();

  // Access stored data
  virtual Flexure& operator= (const T& other) = 0;
  virtual operator T() = 0;
}

}
#endif FLEXURE_H
