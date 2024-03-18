#ifndef GEOM_BASE_H
#define GEOM_BASE_H

#include <algorithm>
#include <cstdlib>
#include "SVG.h"
#include <cmath>

// Les classes définies dans ce fichier représentent les abstractions utiles
// aux constructions (couleurs, points d'un espace 2D).

////////////////////////////////////////////////////////////////////////////////////////
struct Default {};
extern Default	defaut;

struct None {};
extern None		none;

struct Empty {};
extern Empty	empty;
////////////////////////////////////////////////////////////////////////////////////////
// Forward declaration
class Figure;

////////////////////////////////////////////////////////////////////////////////////////
class Color {
	
	public:
		enum colortype : uint8_t {
			black = 0, white, red, yellow, orange, turquoise, violet, pink, green,
			grey, cyan, blue, brown, none
		};
	
	private:
		static const std::size_t nColor = 12;
		static const char *name[];
		colortype  color;
	
	public:
		static const colortype defaut = black;
		
		Color(const colortype &c) : color(c) {}
		Color(Default) : color(black) {}
		// note: construction et assignation par copie déjà définies

		Color(const Color &c) : color(c.color) {}
		Color& operator=(const Color& v) {
			if (&v != this) color = v.color;
			return *this;
		}
		
		const char *getName() const { return name[color]; }
		
		void set(const colortype &c) { color = c; }
		
		friend std::ostream &operator<<(std::ostream &s, const Color &c) {
			return s << c.getName();
		}
		friend SVG::stream& operator<<(SVG::stream& s, const Color &c) {
			return s << c.getName();
		}
};


//Famille de formes
enum class ShapeType: uint64_t {
	Stroke    = 1ULL << 0,  // = 0000 0001 = 0x01 =   1
	Triangle  = 1ULL << 1,  // = 0000 0010 = 0x02 =   2
	Rectangle = 1ULL << 2,  // = 0000 0100 = 0x04 =   4
	Pentagon  = 1ULL << 3,  // = 0000 1000 = 0x08 =   8
	Hexagon   = 1ULL << 4,  // = 0001 0000 = 0x10 =  16
	Heptagon  = 1ULL << 5,  // = 0010 0000 = 0x20 =  32
	Octogon   = 1ULL << 6,  // = 0100 0000 = 0x40 =  64
	Ellipsis  = 1ULL << 7,  // = 1000 0000 = 0x80 = 128
	All       = ~0ULL       // = 111...111 = 0xff...ff = (2^64)-1
};


namespace Geom2D {

	////////////////////////////////////////////////////////////////////////////////////////
	// Fill
	class Fill {
		
	protected:
		Color   fill_color;

	public:
		explicit Fill(const Color &c = Color::defaut) : fill_color(c) {}
		
		void setFillColor(const Color &color) { fill_color = color; }
		const Color &getFillColor() const { return fill_color; }
		const Fill &getFill() const { return *this; }
		
		friend std::ostream& operator<<(std::ostream& s, const Fill& d);
		friend SVG::stream& operator<<(SVG::stream& s, const Fill& p);
	};

	////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////
	// Stroke
	class Stroke {

	protected:
		Color	stroke_color;
		size_t	stroke_width;

	public:
		explicit Stroke(const Color &c = Color::defaut, size_t width=1) : stroke_color(c), stroke_width(width) {}
		
		void setStrokeColor(const Color &color) { stroke_color = color; }
		void setStrokeWidth(size_t width) { stroke_width = width; }

		Color getStrokeColor() const{ return stroke_color; }
		size_t getStrokeWidth() const{return stroke_width; }

		const Stroke &getStroke() const { return *this; }
		
		friend std::ostream& operator<<(std::ostream& s, const Stroke& d);
		friend SVG::stream& operator<<(SVG::stream& s, const Stroke& p);
	};

	////////////////////////////////////////////////////////////////////////////////////////

	constexpr float pi_f = 3.14159265358979323846f;

	////////////////////////////////////////////////////////////////////////////////////////
	///  Point
	class Point {
	protected: float x, y;
	public:
		inline Point(float u, float v) : x(u), y(v) {}
		inline Point() : Point(0.f,0.f) {}
		inline Point(None) {}
		
		inline float getx() const { return x; }
		inline float gety() const { return y; }
		
		inline void set(float u, float v) { x = u; y = v; }
		
		inline void operator+=(const Point &p) { x += p.getx(); y += p.gety(); }
		inline void operator/=(float v) { x /= v; y/= v; }
		
		inline void min(const Point &p) { x = std::min(x, p.x); y = std::min(y, p.y); }
		inline void max(const Point &p) { x = std::max(x, p.x); y = std::max(y, p.y); }
		
		friend std::ostream& operator<<(std::ostream& s, const Point& p) { return s << "(" << p.x << "," << p.y << ")"; }
		friend SVG::stream& operator<<(SVG::stream& s, const Point& p) { s << p.x << "," << p.y; return s; }
		
		inline void translate(const Point &v) { x += v.x; y += v.y; }
		inline void scale(const Point &c, float s) {
			x = c.x + s*(x - c.x);
			y = c.y + s*(y - c.y);
		}
		inline void rotate(const Point &c, float a) {
			Point  p(x - c.x, y - c.y);
			float  sina = sinf(a), cosa = cosf(a);
			x = c.x + sina*p.x - cosa*p.y;
			y = c.y + cosa*p.x + sina*p.y;
		}
		inline void polar(float radius, float angle, const Point &center) {
			x = center.x + radius*cosf(angle);
			y = center.y + radius*sinf(angle);
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////
	// interface transformation
	class Transform {
	public:
		virtual void Translate(const Point &p) = 0;
		virtual void Rotate(float a) = 0;
		virtual void Scale(float s) = 0;
	};

	////////////////////////////////////////////////////////////////////////////////////////
	// Base de toutes les figures en utilisant.
	class Base : public Transform, public SVG::Write  {
	
	public:
		
		Base() {}
		virtual std::ostream& info(std::ostream&) const = 0;
		virtual ShapeType getType() const = 0;
		virtual ~Base() = 0;
		
		friend class ::Figure;
	};
}

#endif