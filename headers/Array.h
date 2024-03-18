#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <iostream>
#include <cstring>
#include <cassert>
#include "SVG.h"

namespace Array {
	
	template <class T, size_t N> class Static {
	
	protected:
		T	tab[N];
	
	public:
		using type = T;
		Static() {};
		
		Static(const std::initializer_list<T> &list) {
			assert(list.size() <= N);
			size_t  i = 0;
			
			for (const T &p : list) 
				tab[i++] = p;
		}
		
		Static(const Static<T, N> &array) {
			// memcpy(tab, array.tab, N*sizeof(T)); // non: faire une copie
			size_t i=0;
			for(const T &x : array.tab) 
				tab[i++] = x;
		}
		
		size_t size() const { return N; }

		Static<T, N>& operator=(const Static<T, N> &array) {
			if (&array != this) memcpy(tab, array.tab, N*sizeof(T));
			return *this;
		}
		
		T& operator[](size_t i) { return tab[i]; }
		const T& operator[](size_t i) const { return tab[i]; }
		
		friend std::ostream& operator<<(std::ostream &stream, const Static<T,N> &array) {
			if (array.size() > 0) {
				stream << array.tab[0];
				for (size_t i = 1; i < array.size(); i++) 
					stream << " " << array.tab[i];
			}
			return stream;
		}
		
		friend SVG::stream& operator<<(SVG::stream &stream, const Static<T,N> &array) {
			if (array.size() > 0) {
				stream << array.tab[0];
				for (size_t i = 1; i < array.size(); i++) 
					stream << " " << array.tab[i];
			}
			return stream;
		}
	};

	template <class T> class Fixed {
	
	protected:
		size_t	len;
		T		*tab;
	
	public:
		using type = T;
		explicit Fixed(size_t n) : len(n), tab(n == 0 ? nullptr : new T[n]) {}
		
		Fixed(const std::initializer_list<T> &list) : Fixed(list.size()) {
			size_t  i = 0;
			for (const T &p : list) tab[i++] = p;
		}
		
		Fixed(const Fixed<T> &array) : Fixed(array.len) {
			for (size_t i = 0; i < len; i++) tab[i] = array.tab[i];
			// if (len > 0) memcpy(tab, array.tab, len*sizeof(T));
		}
		
		Fixed<T>& operator=(const Fixed<T> &array) {
			assert(array.len == len);
			if (&array != this)
				for (size_t i = 0; i < len; i++) 
					tab[i] = array.tab[i];
			// memcpy(tab, array.tab, len*sizeof(T));
			return *this;
		}
		
		~Fixed() { if (tab) delete[] tab; }
		
		size_t size() const { return len; }
		
		T& operator[](size_t i) { return tab[i]; }
		const T& operator[](size_t i) const { return tab[i]; }
		
		friend std::ostream& operator<<(std::ostream &stream, const Fixed<T> &array) {
			if (array.size() > 0) {
				stream << array.tab[0];
				for (size_t i = 1; i < array.size(); i++) 
					stream << " " << array.tab[i];
			}
			return stream;
		}
		friend SVG::stream& operator<<(SVG::stream &stream, const Fixed<T> &array) {
			if (array.size() > 0) {
				stream << array.tab[0];
				for (size_t i = 1; i < array.size(); i++) 
					stream << " " << array.tab[i];
			}
			return stream;
		}
	};

/*		GEOMETRY	*/

	namespace Geometry {

		constexpr float pi_f = 3.14159265358979323846f;

		template <class T> typename T::type Center(const T &array) {
			// Calcul barycentre (moyenne des points)
			assert(array.size() != 0);
			typename T::type center = array[0];
			
			for (size_t i = 1; i < array.size(); i++) 
				center += array[i];
			
			center /= float(array.size());
			return center;
		}

		template <class T> void Translate(T &array, const typename T::type &vector) {
			if (array.size() == 0) return;
			
			for (size_t i = 0; i < array.size(); i++) 
				array[i].translate(vector);
		}

		template <class T> void Scale(T &array, float scaling) {
			if (array.size() == 0) return;
			typename T::type center = Center(array);
			
			for (size_t i = 0; i < array.size(); i++) 
				array[i].scale(center, scaling);
		}

		template <class T> void Rotate(T &array, float angle) {
			if (array.size() == 0) return;
			typename T::type center = Center(array);
			
			for (size_t i = 0; i < array.size(); i++) 
				array[i].rotate(center,angle);
		}

		// Réparti régulièrement N points (N=array.size()) autour d'un centre
		// `center`, à une distance de `radius`.
		template <class T> void FillnGon(T &array, const typename T::type &center, float radius) {
			if (array.size() == 0) return;
			
			float angle = 2.f * Geometry::pi_f / float(array.size());
			
			for (size_t i = 0; i < array.size(); i++) 
				array[i].polar(radius,float(i)*angle,center);
		}
	}

/*		SVG		*/

	namespace SVG {
		
		template <class T> void output(::SVG::stream &stream, const T &array) {
			if (array.size() == 0) return;
			stream << array[0];
			
			for (size_t i = 1; i < array.size(); i++) 
				stream << " " << array[i];
		}
	}

};

#endif // _ARRAY_H_
