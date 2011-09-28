#ifndef OPENVPN_COMMON_NOW_H
#define OPENVPN_COMMON_NOW_H

#include <ctime>

namespace openvpn {

  typedef time_t now_t;
  now_t now = 0; /* GLOBAL */

} // namespace openvpn

#endif // OPENVPN_COMMON_NOW_H