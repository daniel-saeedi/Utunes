# Utunes

Utunes is an audio streaming and media services provider. This project has 3 phases: 

1. [Phase 1](/Utunes-Final-Project-Phase1) : Implementing backend of utunes using APHTTP(AP HTTP::_server_** is a simple web application server-side blocking framework for C++ based on simplified versions of [W++](http://konteck.github.io/wpp/), [HappyHTTP](http://scumways.com/happyhttp/happyhttp.html), and [cpp-netlib](http://cpp-netlib.org/) and specifically designed for this course.)
2. [Phase 2](/Utunes-Final-Project-Phase2) :  A simple implementation of recommendation system based on confidence score
3. [Phase 3](/Utunes-Final-Project-Phase3) : Frontend Implementation

You can run each phase with these commands : 

# Phase 1
    make
    ./utunes.o ./songs.csv
    
 # Phase 2
    make
    ./utunes.o ./testcase/songs.csv ./testcase/liked_songs.csv
    
  # Phase 3
    make
    ./utunes.o  ./songs.csv ./liked_songs.csv
    
 Then go to localhost:5000 to see the website.
