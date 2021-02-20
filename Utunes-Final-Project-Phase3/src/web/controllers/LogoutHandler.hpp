#ifndef LOGOUT_HANDLER_H
#define LOGOUT_HANDLER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Utunes.hpp"
class LogoutHandler : public RequestHandler
{
public:
	LogoutHandler(Utunes* _utunes) : utunes(_utunes){}
	Response* callback(Request* request);
private:
	Utunes* utunes;
};
#endif