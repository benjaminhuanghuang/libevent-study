#include <event2/event.h>
#include <iostream>

using namespace std;

int main()
{
#ifdef _WIN32
  // init socket in windows
  WSDATA wsa;
  WSASStartup(MAKEWORD(2, 2), &wsa);
#endif
  //create  libevent context
  event_base *base = event_base_new();

  if (base)
  {
    cout << "event_base_new success" << endl;
  }
}