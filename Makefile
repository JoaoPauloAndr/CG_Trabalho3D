LIBS = -lGL -lGLU -lglut -ltinyxml
UTILS_PATH = utils/
OPENGL_PATH = openGL/
CHARACTER_PATH = characters/
PLATFORMS_PATH = game_platforms/
SHOT_PATH = shot/


all: g++
	@echo "Trabalho compilado."

g++: main.cpp $(UTILS_PATH)xml_parsing.cpp $(PLATFORMS_PATH)game_platforms.cpp $(CHARACTER_PATH)character.cpp $(SHOT_PATH)shot.cpp
	g++ -o trabalhocg main.cpp $(UTILS_PATH)xml_parsing.cpp $(PLATFORMS_PATH)game_platforms.cpp $(CHARACTER_PATH)character.cpp $(SHOT_PATH)shot.cpp $(LIBS)

clean:
	@rm -f *.o *.output trabalhocg	