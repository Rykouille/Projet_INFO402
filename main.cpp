#include <cstdio>
#include "headers/Grawink.h"
#include "headers/Surface.h"
#include "headers/Curve.h"

int main() {
	using namespace Geom2D;

	char fname[] = "canvas.html";

	GrawEditor& editor = GrawEditor::GetEditor();

	Geom2D::Base* shape = editor.GetNew<Geom2D::Base>(ShapeType::Hexagon);
	Geom2D::Base* shape2 = editor.GetNew<Geom2D::Base>(ShapeType::Ellipsis);

	editor.Add(new Surface::Hexagon({ 750,500 }, 100, Color::yellow)).
	Add(new Surface::Square({ 200,400 }, 300, Color::green, Color::red)).
	Add(new Curve::Circle({ 600,400 }, 300, 4, Color::black)).
	Add(new Surface::Triangle({ 200,200 }, 150, Color::yellow)).
	Add(new Surface::Rectangle({ 400, 200 }, 200, 300, Color::cyan)).
	Add(new Surface::Square({ 200,400 }, 300, Color::green)).
	Add(new Curve::Segment({ 100,200 },{ 500,300 },Color::turquoise,6)).
	Add(new Surface::Pentagon({ 500,500 }, 100, Color::red)).
	Add(new Surface::Heptagon({ 200,200 }, 50, Color::red)).
	Add(shape).Add(shape2);

	int n = 3;

	printf("Objets UNDO : \n\n");
	for(int i=0; i<n; i++){
		std::cout << i+1 << ". ";
		editor.Undo();
	}

	printf("\n\n");

	printf("Objets REDO : \n\n");
	editor.Redo();

	printf("PAF on resize, taille / 2 ! \n");
	editor.Resize(0.5);

	printf("hop on remet la taille comme dhab\n");
	editor.Resize(2);

	printf("Hop on crop la moitiée !\n");
	editor.Crop(0.5);

	printf("On regarde le résultat...\n");
	editor.Resize(2);

	editor.Select(ShapeType::All);

	editor.ExportSVG(fname);

	printf("fin !!!!\n");
	return 0;
}
