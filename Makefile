CC = g++ -Wall
EXECUTABLE = run.exe

SOURCES = main.cpp \
          trajectory\builder\BallisticTrajectory.cpp \
		  trajectory\builder\BallisticTrajectory3D.cpp \
		  core\Core.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(SFML_FLAGS)

.cpp.o:
	$(CC) -c $< -o $@

clean: 
	del $(OBJECTS)