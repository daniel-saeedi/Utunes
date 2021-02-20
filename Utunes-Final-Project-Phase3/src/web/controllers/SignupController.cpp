#include "SignupController.hpp"

std::map<std::string,std::string> SignupController::handle(Request *req)
{
	std::map<std::string,std::string> context;
	std::string error = req->getQueryParam("error");
	context["error"] = error;
	if(req->getSessionId() != "") context["logged_in"] = "true";
	else context["logged_in"] = "false";
	return context;
}