#include "RouteHandler.hpp"
#include "controllers/SignupHandler.hpp"
#include "controllers/LogoutHandler.hpp"
#include "controllers/LoginController.hpp"
#include "controllers/LoginHandler.hpp"
#include "controllers/SongController.hpp"
#include "controllers/LikeHandler.hpp"
#include "controllers/LikedSongController.hpp"
#include "controllers/PlaylistsController.hpp"
#include "controllers/NewPlaylistHandler.hpp"
#include "controllers/PlaylistController.hpp"
#include "controllers/AddSongHandler.hpp"
#include "controllers/RemoveSongHandler.hpp"
#include <fstream>
const std::string PUBLIC_DIR = "public";
void RouteHandler::run()
{
	srand(time(NULL));
	try
	{
		UtunesServer* server = new UtunesServer(2025);
		server->setNotFoundErrPage(PUBLIC_DIR+"/404.html");
		load_img(server);
		load_css(server);
		server->get("/", new HomeController(PUBLIC_DIR+"/index.html",utunes));
		server->get("/signup", new SignupController(PUBLIC_DIR+"/signup.html",utunes));
		server->post("/signup", new SignupHandler(utunes));
		server->get("/login", new LoginController(PUBLIC_DIR+"/login.html"));
		server->post("/login", new LoginHandler(utunes));
		server->get("/logout", new LogoutHandler(utunes));
		server->get("/song", new SongController(PUBLIC_DIR+"/song-single.html",utunes));
		server->get("/like", new LikeHandler(utunes));
		server->get("/liked_songs", new LikedSongController(PUBLIC_DIR+"/liked-songs.html",utunes));
		server->get("/manage_playlists", new PlaylistsController(PUBLIC_DIR+"/playlists.html",utunes));
		server->post("/new_playlist", new NewPlaylistHandler(utunes));
		server->get("/playlist", new PlaylistController(PUBLIC_DIR+"/playlist.html",utunes));
		server->post("/add_song_playlist", new AddSongHandler(utunes));
		server->get("/delete_song", new RemoveSongHandler(utunes));
		server->get("/about", new ShowPage(PUBLIC_DIR+"/about.html"));
		server->get("/contact", new ShowPage(PUBLIC_DIR+"/contact.html"));
		server->run();
	}
	catch (Server::Exception e)
	{
		std::cerr << e.getMessage() << std::endl;
	}
	catch(const std::bad_alloc&){}
}

void RouteHandler::load_css(UtunesServer* server)
{
	std::ifstream f("src/web/files.txt");
	std::string path;
	while(f >> path)
	{
		server->get(path, new ShowPage(PUBLIC_DIR+path));
	}
	f.close();
}

void RouteHandler::load_img(UtunesServer* server)
{
	std::ifstream f("src/web/images.txt");
	std::string path;
	while(f >> path)
	{
		server->get(path, new ShowImage(PUBLIC_DIR+path));
	}
	f.close();
}

















