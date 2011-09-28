#ifndef OPENVPN_COMMON_EXCEPTION_H
#define OPENVPN_COMMON_EXCEPTION_H

#include <string>
#include <sstream>
#include <exception>

#include <boost/system/error_code.hpp>

namespace openvpn {
  template <typename ErrorCode>
  inline std::string errinfo(ErrorCode err)
  {
    boost::system::error_code e(err, boost::system::system_category());
    return e.message();
  }

  // string exception class
  class Exception : public std::exception
  {
  public:
    Exception(std::string err) : err_(err) {}
    virtual const char* what() const throw() { return err_.c_str(); }
    ~Exception() throw() {}
  private:
    std::string err_;
  };

  // define a simple custom exception class with no extra info
# define OPENVPN_SIMPLE_EXCEPTION(C) \
  class C : public std::exception { \
  public: \
    virtual const char* what() const throw() { return #C; } \
  }

  // define a simple custom exception class with no extra info that inherits from a custom base
# define OPENVPN_SIMPLE_EXCEPTION_INHERIT(C, B)	\
  class C : public B { \
  public: \
    virtual const char* what() const throw() { return #C; } \
  }

  // define a custom exception class that allows extra info
# define OPENVPN_EXCEPTION(C) \
  class C : public openvpn::Exception { \
  public: \
    C() : openvpn::Exception(#C) {} \
    C(std::string err) : openvpn::Exception(#C ": " + err) {} \
  }

  // define a custom exception class that allows extra info, and inherits from a custom base
# define OPENVPN_EXCEPTION_INHERIT(C, B)		\
  class C : public B { \
  public: \
    C() : B(#C) {} \
    C(std::string err) : B(#C ": " + err) {} \
  }

  // throw an Exception with stringstream concatenation allowed
# define OPENVPN_THROW_EXCEPTION(stuff) \
  do { \
    std::ostringstream _ovpn_exc; \
    _ovpn_exc << stuff; \
    throw openvpn::Exception(_ovpn_exc.str()); \
  } while (0)

  // throw an OPENVPN_EXCEPTION class with stringstream concatenation allowed
# define OPENVPN_THROW(exc, stuff) \
  do { \
    std::ostringstream _ovpn_exc; \
    _ovpn_exc << stuff; \
    throw exc(_ovpn_exc.str()); \
  } while (0)

} // namespace openvpn

#endif // OPENVPN_COMMON_EXCEPTION_H