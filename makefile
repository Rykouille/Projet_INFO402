CPPFLAGS= -std=c++17 -g -Wall -Wextra -Wconversion -O0
SRCs=Curve.cpp GeomBase.cpp Surface.cpp SVG.cpp Grawink.cpp 
OBJs=$(SRCs:.cpp=.o)
EXE=Projet
CXX=g++
AR=ar
HEAD = headers/
LIBRARY=libgraweditor
LIB=-L. -l:$(LIBRARY).a

.PHONY: all clean


all: $(LIBRARY).a $(EXE) clean

$(EXE): main.o $(LIBRARY).a
	$(CXX) $(CPPFLAGS) $< $(LIB) $(LIBRARY).a -o $@
 
$(LIBRARY).a: $(OBJs)
	$(AR) rcs $@ $^


clean:
	rm -f *.o

mrproper: clean
	rm canvas.html *.a $(EXE)

Curve.o: $(HEAD)SVG.h $(HEAD)Curve.h $(HEAD)GeomBase.h $(HEAD)Array.h
GeomBase.o: $(HEAD)GeomBase.h $(HEAD)SVG.h
main.o: $(HEAD)GeomBase.h $(HEAD)SVG.h $(HEAD)Surface.h $(HEAD)Array.h $(HEAD)Curve.h
Surface.o: $(HEAD)SVG.h $(HEAD)Surface.h $(HEAD)GeomBase.h $(HEAD)Array.h
SVG.o: $(HEAD)SVG.h
Grawink.o: $(HEAD)Grawink.h