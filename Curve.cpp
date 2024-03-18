#include "headers/SVG.h"
#include "headers/Curve.h"

namespace Geom2D {

	namespace Curve {

		// Circle
		std::ostream& operator<<(std::ostream& s, const Circle& d) {
			return s << "Circle[center=" << d.center << ",radius=" << d.radius
				<< "," << d.getStroke() << ", fill=" << d.getFillColor() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Circle& p) {
			return s << "<circle"
				<< " cx=" << quoted(p.center.getx()) << " cy=" << quoted(p.center.gety())
				<< " r=" << quoted(p.radius)
				<< "fill=" << quoted(p.fill_color)
				<< p.getStroke()
				<< "/>\n";
		}

		// Segment
		std::ostream& operator<<(std::ostream& s, const Segment& p) {
			const Array::Static<Point,2>  &pp = p;
			return s << "Segment[" << pp << "," << p.getStroke() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Segment& p) {
			const Array::Static<Point,2>  &pp = p;
			return s << "<polyline"
				<< " points=" << quoted(pp)
				<< p.getStroke()
				<< "/>\n";
		}
	}
}
