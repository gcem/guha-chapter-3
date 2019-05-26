CXX=g++
CXXFLAGS=-lGL -lGLU -lGLEW -lglut -lm -Wno-write-strings

targets = exc322-canvas
objects322 = exc322-canvas.o exc322-objects.o


exc322-canvas.o exc322-objects.o: exc322-objects.h
exc322-canvas: $(objects322)

$(targets): 
	$(CXX)  -o $@ $^ $(CPPFLAGS) $(CXXFLAGS) 

%.o:%.cpp
	$(CXX) $*.cpp $(CPPFLAGS) $(CXXFLAGS) -c

%:
	$(CXX) -o $@ $*.cpp $(CPPFLAGS) $(CXXFLAGS) 

.PHONY: clean
clean:
	rm *.o
