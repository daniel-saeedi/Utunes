#include "HomeController.hpp"
#include "../../FilterSystem.hpp"

std::map<std::string,std::string> HomeController::handle(Request *req)
{
	std::map<std::string,std::string> context;
	std::vector<Song*> songs = utunes->get_songs_vector();
	int users_count =  utunes->get_users_count();
	context["error"] = req->getQueryParam("error");
	context["songs_count"] = std::to_string(songs.size()); 
	context["users_count"] = std::to_string(users_count);
	if(req->getQueryParam("filter") == "")
		context["songs"] = songs_html(songs);
	else
		context["songs"] = get_filtered_songs(req);
	if(req->getSessionId() != "") 
		context["logged_in"] = req->getSessionId();
	else 
		context["logged_in"] = "false";
	return context;
}

std::string HomeController::songs_html(std::vector<Song*> songs)
{
	std::string html;
	for(int i = 0;i < songs.size();i++)
	{
		html += produce_row(songs[i]->get_id(),songs[i]->get_title(),songs[i]->get_artist(),songs[i]->get_year());
	}
	return html;
}

std::string HomeController::get_filtered_songs(Request *req)
{
	std::string html;
	std::string artist = req->getQueryParam("artist");
	std::string min_likes = req->getQueryParam("min_likes");
	std::string max_likes = req->getQueryParam("max_likes");
	std::string min_year = req->getQueryParam("min_year");
	std::string max_year = req->getQueryParam("max_year");
	User* current_user = utunes->find_user_by_email(req->getSessionId());
	std::vector<Song*> songs = utunes->get_songs_vector();
	FilterSystem filter_sys = FilterSystem(current_user);
	if(artist != "") filter_sys.add_artist_filter(artist);
	if(min_likes != "" && max_likes != "") filter_sys.add_likes_filter(std::stoi(min_likes),std::stoi(max_likes));
	if(min_year != "" && max_year != "") filter_sys.add_publish_year_filter(std::stoi(min_year),std::stoi(max_year));
	std::vector<Song*> filtered_songs = filter_sys.get_filtered_songs(songs);
	html = songs_html(filtered_songs);
	return html;
}

std::string HomeController::produce_row(int id,std::string song,std::string artist,int year)
{
	std::string result = "<tr>";
	result += "<td>" + std::to_string(id) + "</td>";
	result += "<td><img class='thumbnail' style='border-radius:50%;' src='images/song.png' width='70'></td>";
	result += "<td><a href='song?id="+std::to_string(id)+"'>" + song + "</a></td>";
	result += "<td>" + artist + "</td>";
	result += "<td>" + std::to_string(year) + "</td></a></tr>";
	return result;
}