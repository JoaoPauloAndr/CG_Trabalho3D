LIBS = -lGL -lGLU -lglut -ltinyxml
UTILS_PATH = utils/
OPENGL_PATH = openGL/
CHARACTER_PATH = characters/
PLATFORMS_PATH = game_platforms/


all: g++
	@echo "Trabalho compilado."

g++: main.cpp $(UTILS_PATH)xml_parsing.cpp $(PLATFORMS_PATH)game_platforms.cpp $(CHARACTER_PATH)character.cpp	
	g++ -o trabalhocg main.cpp $(UTILS_PATH)xml_parsing.cpp $(PLATFORMS_PATH)game_platforms.cpp $(CHARACTER_PATH)character.cpp $(LIBS)

clean:
	@rm -f *.o *.output trabalhocg	