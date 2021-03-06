#include "AddSongHandler.hpp"
Response* AddSongHandler::callback(Request *request)
{
	Response* res = Response::redirect("/");
	if(request->getSessionId() == "") return res;
	try
	{
		int playlist_id = stoi(request->getBodyParam("playlist_id"));
		int song_id = stoi(request->getBodyParam("song_id"));
		res = Response::redirect("/playlist?id="+std::to_string(playlist_id));
		Song* song = utunes->find_song_by_id(song_id);
		User* current_user = utunes->find_user_by_email(request->getSessionId());
		PlaylistSystem* playlist_sys = utunes->get_playlist_sys();
		playlist_sys->add_song_to_playlist(playlist_id,song,current_user);
	}
	catch(std::exception& excep)
	{
		std::string message = excep.what();
		res = Response::redirect("/?error="+message);
	}
	return res;
}