#ifndef _CURVE_H_
#define _CURVE_H_
#include <iostream>
#include <cassert>
#include "GeomBase.h"
#include "SVG.h"
#include "Array.h"

// Les classes définies dans ce fichier représentent les traits des dessins
// (segment de droite), notamment les circonférences (contours de cercle,
// contour de polygone régulier).

namespace Geom2D {
namespace Curve {

	////////////////////////////////////////////////////////////////////////////////////////
	//  Circle
	class Circle : public Geom2D::Base, public Stroke, public Fill {
	
	protected:
		Point center;
		float radius;

	public:
		Circle(const Point &xy, float r, size_t width = 1, 
					const Color& line = Color::defaut , const Color& fill = Color::none) :
			Stroke(line, width), Fill(fill), center(xy), radius(r) {}
		
		virtual ~Circle() {}
		
		std::ostream& info(std::ostream& stream) const { return stream << *this; }
		
		void write(SVG::stream &stream) const { stream << *this; }
		
		void Translate(const Point &v) override { center += v; }
		void Scale(float s) override { radius *= s; }
		void Rotate(float) override {}	// ne rien faire : omission du nom du paramètre (évite un warning "unused parameter")

		inline Point getCenter(){ return center; }
		
		friend std::ostream& operator<<(std::ostream& s, const Circle& d);
		friend SVG::stream& operator<<(SVG::stream& s, const Circle& p);

		ShapeType getType() const override { return ShapeType::Ellipsis; }
	};

	////////////////////////////////////////////////////////////////////////////////////////
	//  Segment
	class Segment : public Base, public Stroke, public Array::Static<Point,2>{
	public:
		Segment(const Point &p1, const Point &p2, const Color &col = Color::defaut, size_t width = 1) :
			Stroke(col, width), Array::Static<Point,2>({p1,p2}) {}
		
		Segment(const std::initializer_list<Point> &list, const Color &col = Color::defaut, size_t width = 1) :
			Stroke(col, width), Array::Static<Point,2>(list) {
			assert(list.size() == 2);
		}
		virtual ~Segment() {}
		
		std::ostream& info(std::ostream& stream) const { return stream << *this; }
		void write(SVG::stream &stream) const { stream << *this; }
		
		void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
		void Scale(float s) { Array::Geometry::Scale(*this,s); }
		void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
		
		// Renvoi le point au milieu du segment
		Point getCenter_Segment(){ 
			Point res((tab[0].getx()+tab[1].getx())/2, (tab[0].gety()+tab[1].gety())/2);
			return res; 
		}


		friend std::ostream& operator<<(std::ostream& s, const Segment& p);
		friend SVG::stream& operator<<(SVG::stream& s, const Segment& p);

		ShapeType getType() const override { return ShapeType::Stroke; }
	};

}
}

#endif // _CURVE_H_
