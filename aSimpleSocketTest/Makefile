Server: Server.cpp
	g++ -o Server Server.cpp

Client:Client.cpp
	g++ -o Client Client.cpp

clean:
	rm Client Server ClientBook ServerBook

ServerBook: ServerBook.cpp NetworkApplication.cpp
	g++ -o ServerBook ServerBook.cpp NetworkApplication.cpp

ClientBook: ClientBook.cpp NetworkApplication.cpp
	g++ -o ClientBook ClientBook.cpp NetworkApplication.cpp