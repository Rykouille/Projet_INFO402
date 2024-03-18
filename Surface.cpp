#include "headers/SVG.h"
#include "headers/Surface.h"

namespace Geom2D {
	namespace Surface {

		// Polygon
		std::ostream& Polygon::info(std::ostream& stream) const { return stream << *this; }

		std::ostream& operator<<(std::ostream& s, const Polygon& p) {
			const Array::Fixed<Point> &pp = p;
			return s << "Polygon[nVertex=" << p.size() << "," << pp
				<< ",fill=" << p.fill_color << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Polygon& p) {
			const Array::Fixed<Point> &pp = p;
			return s << "<polygon "
				<< " points=" << quoted(pp)
				<< " fill=" << quoted(p.fill_color)
				<< p.getStroke()
				<< "/>\n";
		}

		// Rectangle
		std::ostream& Rectangle::info(std::ostream& stream) const { return stream << *this; }

		std::ostream& operator<<(std::ostream& s, const Rectangle& d) {
			return s << "Rectangle[corner=" << d.corner
				<< ",width=" << d.width	 << ",height=" << d.height
				<< ",angle=" << d.rotate << ",fill=" << d.fill_color
				<< d.getStroke()
				<< "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Rectangle& p) {
			s << "<rect"
				<< " x=" << quoted(p.corner.getx()) << " y=" << quoted(p.corner.gety())
				<< " width=" << quoted(p.width) << " height=" << quoted(p.height)
				<< " fill=" << quoted(p.fill_color)
				<< p.getStroke();
			if (p.rotate) {
				Point center(p.corner.getx() + p.width / 2.f, p.corner.gety() + p.height / 2.f);
				s << " transform=" << quoted("rotate(" << p.rotate << " " << center << ")");
			}
			return s << "/>\n";
		}

		// Square
		std::ostream& Square::info(std::ostream& stream) const { return stream << *this; }

		std::ostream& operator<<(std::ostream& s, const Square& d) {
			return s << "Square[corner=" << d.corner
				<< ",sidelen=" << d.width
				<< ",fill=" << d.fill_color << "]";
		}
		SVG::stream& operator<<(SVG::stream& s, const Square& p) {
			const Rectangle& pp = p;
			return s << pp;
		}

	}
}
