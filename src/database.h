#ifndef DATABASE_H
#define DATABASE_H

namespace Flexure
{

enum Type { FLOAT32, FLOAT64, INT32, INT64, UINT32, UINT64 };

class Database
{
 public:
  Database();
  ~Database();

  template <typename T> boost::shared_ptr<T> get(std::string name);
  // OR
  template <typename T> boost::shared_ptr<T> get(std::string name, Flexure::Type type);
};

}

#endif DATABASE_H
