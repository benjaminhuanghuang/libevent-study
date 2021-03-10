/*
* Server listen at 9995
*
*/
#include <event2/event.h>
#include <event2/listener.h>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

static const int PORT = 9995;

// callback

static void listener_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *)
{
  cout << "listen_cb" << endl;
}

int main()
{
#ifdef _WIN32
  // init socket in windows
  WSDATA wsa;
  WSASStartup(MAKEWORD(2, 2), &wsa);
#else
  // 发送数据给已关闭的socket, 忽略管道信号
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
  {
    return 1;
  }
#endif
  //create  libevent context
  event_base *base = event_base_new();

  if (base)
  {
    cout << "event_base_new success" << endl;
  }

  // Address
  struct sockaddr_in sin = {0};

  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT); // host order to network order

  // Listen
  evconnlistener *ev = evconnlistener_new_bind(base,
                                               listener_cb,
                                               (void *)base,
                                               LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                                               -1,                      // 连接队列大小
                                               (struct sockaddr *)&sin, // address an port
                                               sizeof(sin));

  // envet
  event_base_dispatch(base);
  evconnlistener_free(ev);

  event_base_free(base);

#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}