#ifndef _SURFACE_H_
#define _SURFACE_H_
#include <iostream>
#include <cassert>
#include "GeomBase.h"
#include "SVG.h"
#include "Array.h"

namespace Geom2D {
namespace Surface {

		////////////////////////////////////////////////////////////////////////////////////////
		//  Polygon
		class Polygon : public Geom2D::Base, public Fill, public Stroke, public Array::Fixed<Point> {
		
		public:
		// `cent` est le centre du triangle et `size` la distance entre les sommets et le centre.
			Polygon(std::size_t npoints, const Point &centre, 
					float size, const Color &c = Color::defaut, const Color& fill = Color::none);
			
			Polygon(const std::initializer_list<Point> &list, const Color &c = Color::defaut, const Color& fill = Color::none);
			virtual ~Polygon() {}
			
			std::ostream& info(std::ostream& stream) const;
			
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s)            { Array::Geometry::Scale(*this,s); }
			void Rotate(float a)           { Array::Geometry::Rotate(*this,a); }

			virtual ShapeType getType() const = 0;
			
			friend std::ostream& operator<<(std::ostream& s, const Polygon& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Polygon& p);

			Point calcBarycentre(){ return Array::Geometry::Center(*this); }
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Triangle
		class Triangle : public Polygon {
		
		public:
			Triangle(const Point &cent, float size, const Color &col = Color::defaut, const Color& fill = Color::none):
				Polygon(3, cent, size, col, fill) {}
			
			Triangle(const std::initializer_list<Point> &list, const Color &col = Color::none) :
					Polygon(list, col) {}
			
			virtual ~Triangle() {}

			ShapeType getType() const override { return ShapeType::Triangle; }
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Pentagon
		class Pentagon : public Polygon {
		
		public:
			Pentagon(const Point &cent, float size, const Color &col = Color::defaut, const Color& fill = Color::none):
				Polygon(5, cent, size, col, fill) {}
			
			Pentagon(const std::initializer_list<Point> &list, const Color &col = Color::defaut, const Color& fill = Color::none) :
					Polygon(list, col, fill) {}
			
			virtual ~Pentagon() {}

			ShapeType getType() const override { return ShapeType::Pentagon; }
		};
		
		////////////////////////////////////////////////////////////////////////////////////////
		//  Hexagon
		class Hexagon : public Polygon {
		
		public:
			Hexagon(const Point &cent, float size, const Color &col = Color::defaut, const Color& fill = Color::none):
				Polygon(6, cent, size, col, fill) {}
			
			Hexagon(const std::initializer_list<Point> &list, const Color &col = Color::defaut, const Color& fill = Color::none) :
					Polygon(list, col, fill) {}
			
			virtual ~Hexagon() {}

			ShapeType getType() const override { return ShapeType::Hexagon; }
		
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Heptagon
		class Heptagon : public Polygon {
		
		public:
			Heptagon(const Point &cent, float size, const Color &col = Color::defaut, const Color& fill = Color::none):
				Polygon(7, cent, size, col, fill) {}
			
			Heptagon(const std::initializer_list<Point> &list, const Color &col = Color::defaut, const Color& fill = Color::none) :
					Polygon(list, col, fill) {}
			
			virtual ~Heptagon() {}

			ShapeType getType() const override { return ShapeType::Heptagon; }
		
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Octogon
		class Octogon : public Polygon {
		
		public:
			Octogon(const Point &cent, float size, const Color &col = Color::defaut, const Color& fill = Color::none):
				Polygon(8, cent, size, col, fill) {}
			
			Octogon(const std::initializer_list<Point> &list, const Color &col = Color::defaut, const Color& fill = Color::none) :
					Polygon(list, col, fill) {}
			
			virtual ~Octogon() {}

			ShapeType getType() const override { return ShapeType::Octogon; }
		};

		
		////////////////////////////////////////////////////////////////////////////////////////
		//  Rectangle
		class Rectangle : public Geom2D::Base, public Fill , public Stroke{
		
		protected:
			Point corner;
			float width, height;
			float rotate;
		
		public:
			Rectangle(const Point &xy, float w, float h, const Color &c=Color::defaut, const Color& fill=Color::none)
				: Fill(c), Stroke(fill), corner(xy), width(w), height(h), rotate(0.f) {}
			
			virtual ~Rectangle() {};
			
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			
			void Translate(const Point &v) { corner += v; }
			void Scale(float s) { width *= s; height *= s; }
			void Rotate(float a) { rotate += a; }

			inline Point& getCorner(){ return corner; }
			
			
			friend std::ostream& operator<<(std::ostream& s, const Rectangle& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Rectangle& p);

			ShapeType getType() const override { return ShapeType::Rectangle; }
		};

		////////////////////////////////////////////////////////////////////////////////////////
		///  Square
		class Square : public Rectangle {

		public:
			Square(const Point &xy, float s, const Color& c=Color::defaut, const Color& fill=Color::none)
				: Rectangle(xy, s, s, c, fill) {}

			virtual ~Square() {};

			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }

			friend std::ostream& operator<<(std::ostream& s, const Square& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Square& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  inline definitions

		// polygon
		inline Polygon::Polygon(std::size_t npts, const Point &cent, float size, const Color &color, const Color& fill) :
			Fill(color), Stroke(fill), Array::Fixed<Point>(npts) {
				Array::Geometry::FillnGon(*this,cent,size);
		}
		inline Polygon::Polygon(const std::initializer_list<Point> &list, const Color &color, const Color& fill) :
			Fill(color), Stroke(fill), Array::Fixed<Point>(list) {}
	}


}



#endif // _SURFACE_H_
