CC = g++ -Wall
EXECUTABLE = run.exe

SOURCES = main.cpp \
          trajectory_creator\BallisticTrajectory.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(SFML_FLAGS)

.cpp.o:
	$(CC) -c $< -o $@

clean: 
	del $(OBJECTS)