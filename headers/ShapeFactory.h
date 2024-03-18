#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include "Surface.h"
#include "Curve.h"


class ShapeFactory{

public:

    static Geom2D::Base* createShape(ShapeType forme){

        switch(forme){

            case ShapeType::Stroke:
                return new Geom2D::Curve::Segment(*new Geom2D::Point(100, 100), *new Geom2D::Point(200, 100));
                break;

            case ShapeType::Triangle:
                return new Geom2D::Surface::Triangle(*new Geom2D::Point(100,100), 1);
                break;

            case ShapeType::Rectangle:
                return new Geom2D::Surface::Square(*new Geom2D::Point(100, 100), 20);
                break;

            case ShapeType::Pentagon:
                return new Geom2D::Surface::Pentagon(*new Geom2D::Point(100, 100), 1);
                break;

            case ShapeType::Hexagon:
                return new Geom2D::Surface::Hexagon(*new Geom2D::Point(100, 100), 1);
                break;

            case ShapeType::Heptagon:
                return new Geom2D::Surface::Hexagon(*new Geom2D::Point(100, 100), 1);
                break;

            case ShapeType::Octogon:
                return new Geom2D::Surface::Hexagon(*new Geom2D::Point(100, 100), 1);
                break;

            case ShapeType::Ellipsis:
                return new Geom2D::Curve::Circle(*new Geom2D::Point(100, 100), 10);
                break;

            default:
            return nullptr; //A remplacer par une exception.        
        }
    }

};

#endif