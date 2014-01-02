template<typename T>
class Flexure
{
public:
  // Access subfields
  virtual Flexure& operator[] (unsigned int i) = 0;
  virtual const Flexure& operator[] (unsigned int i) const = 0;

  // Register function observers (on changes)
  virtual void Observe(void (*function)(const T& old_val, const T& new_val)) = 0;
  virtual void Unobserve(void (*function)(const T& old_val, const T& new_val)) = 0;

  // Access stored data
  virtual Flexure& operator= (const T& other) = 0;
  virtual operator T() = 0;
}
