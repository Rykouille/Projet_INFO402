#include <cassert>
#include "headers/GeomBase.h"

// mot-clé pour l'initialisation
Default	defaut;
None	none;
Empty	empty;

////////////////////////////////////////////////////////////////////////////////////////
// classe de base de Color
const char *Color::name[] = { "black", "white",  "red", "yellow", "orange", "turquoise",
	"violet", "pink", "green", "grey", "cyan", "blue", "brown", "none" };
const Color::colortype Color::defaut;

namespace Geom2D {
	////////////////////////////////////////////////////////////////////////////////////////
	// classe de base de Geom2D
	Base::~Base() = default;


	// Fill
	std::ostream& operator<<(std::ostream& s, const Fill& p) {
		return s << "fill=" << p.getFillColor();
	}



	//Stroke
	std::ostream& operator<<(std::ostream& s, const Stroke& p) {
		return s << "stroke=" << p.getStroke().getStrokeColor() << ",width=" << p.getStroke().getStrokeWidth();
	}

	SVG::stream& operator<<(SVG::stream& s, const Stroke& p) {
		const Color col_none = Color(Color::none);
		return s << " stroke=" << quoted(p.getStroke().getStrokeColor())
			<< " stroke-width=" << quoted(p.getStroke().getStrokeWidth())
			<< " fill=" << quoted(col_none);
	}
}
