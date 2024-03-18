#include "headers/Grawink.h"

GrawEditor::~GrawEditor(){

    freeVec(StrokeList.first);
    StrokeList.first.clear();

    freeVec(TriangleList.first);
    TriangleList.first.clear();

    freeVec(RectangleList.first);
    RectangleList.first.clear();

    freeVec(PentagonList.first);
    PentagonList.first.clear();

    freeVec(HexagonList.first);
    HexagonList.first.clear();

    freeVec(HeptagonList.first);
    HeptagonList.first.clear();

    freeVec(OctogonList.first);
    OctogonList.first.clear();

    freeVec(EllipsisList.first);
    EllipsisList.first.clear();

    printf("Wouhou tout est détruit !\n");
}


GrawEditor& GrawEditor::GetEditor(){
    static GrawEditor instance;
    return instance;
}

GrawEditor& GrawEditor::Add(Geom2D::Base* obj){
    
    if(obj == nullptr) return *this;

    switch(obj->getType()){
        
        case ShapeType::Stroke:
            StrokeList.first.push_back(dynamic_cast<Geom2D::Curve::Segment*>(obj));
            undoList.push_front(obj);
            break;

        case ShapeType::Triangle:
            TriangleList.first.push_back(dynamic_cast<Geom2D::Surface::Triangle*>(obj));
            undoList.push_front(obj);
            break;

        case ShapeType::Rectangle:
            RectangleList.first.push_back(dynamic_cast<Geom2D::Surface::Rectangle*>(obj));
            undoList.push_front(obj);
            break;

        case ShapeType::Pentagon:
            PentagonList.first.push_back(dynamic_cast<Geom2D::Surface::Pentagon*>(obj));
            undoList.push_front(obj);
            break;

        case ShapeType::Hexagon:
            HexagonList.first.push_back(dynamic_cast<Geom2D::Surface::Hexagon*>(obj));
            undoList.push_front(obj);
            break;

        case ShapeType::Heptagon:
            HeptagonList.first.push_back(dynamic_cast<Geom2D::Surface::Heptagon*>(obj));
            undoList.push_front(obj);
            break;

        case ShapeType::Octogon:
            OctogonList.first.push_back(dynamic_cast<Geom2D::Surface::Octogon*>(obj));
            undoList.push_front(obj);
            break;

        case ShapeType::Ellipsis:
            EllipsisList.first.push_back(dynamic_cast<Geom2D::Curve::Circle*>(obj));
            undoList.push_front(obj);
            break;

        case ShapeType::All:
            printf("C'est pas censé arriver, normalement.\n");
            break;

        default: 
            printf("Imaginons qu'une erreur soit renvoyée ici...\n");
    }

    return *this;
}


GrawEditor& GrawEditor::Delete(Geom2D::Base* ptr = nullptr){
    
    if(ptr == nullptr) return *this;

    switch(ptr->getType()){
        
        case ShapeType::Stroke:
            aller_zou(StrokeList.first, ptr);
            redoList.push_front(ptr);
            break;

        case ShapeType::Triangle:
            aller_zou(TriangleList.first, ptr);
            redoList.push_front(ptr);
            break;

        case ShapeType::Rectangle:
            aller_zou(RectangleList.first, ptr);
            redoList.push_front(ptr);
            break;

        case ShapeType::Pentagon:
            aller_zou(PentagonList.first, ptr);
            redoList.push_front(ptr);
            break;

        case ShapeType::Hexagon:
            aller_zou(HexagonList.first, ptr);
            redoList.push_front(ptr);
            break;

        case ShapeType::Heptagon:
           aller_zou(HeptagonList.first, ptr);
           redoList.push_front(ptr);
           break;

        case ShapeType::Octogon:
            aller_zou(OctogonList.first, ptr);
            redoList.push_front(ptr);
            break;

        case ShapeType::Ellipsis:
            aller_zou(EllipsisList.first, ptr);
            redoList.push_front(ptr);
            break;

        case ShapeType::All:
            printf("C'est pas censé arriver, normalement.\n");
            break;

        default: 
            printf("Imaginons qu'une erreur soit renvoyée ici... \n");

        
    }

    return *this;
}

GrawEditor& GrawEditor::Undo(){

    if(undoList.empty()) return *this;

    Geom2D::Base* ptr = *undoList.begin();

    undoList.pop_front();
    
    ptr->info(std::cout) << std::endl;
    Delete(ptr);

    return *this;
}

GrawEditor& GrawEditor::Redo(){

    if(redoList.empty()) return *this;


    Geom2D::Base* ptr = *redoList.begin();
    redoList.pop_front();
 
    ptr->info(std::cout) << std::endl;
    Add(ptr);

    return *this;
}

GrawEditor& GrawEditor::Resize(float coef = 1.0){

    size_canvas *= coef;
    return *this;
}

GrawEditor& GrawEditor::Crop(float coef = 1.0){
    Resize(coef);

    for(auto i : EllipsisList.first){
       if(!isInCanvas(i->getCenter())) aller_zou(EllipsisList.first, i);
    }
    for(auto i : RectangleList.first){
        if(!isInCanvas(i->getCorner())) aller_zou(RectangleList.first, i);
    }
    for(auto i : TriangleList.first){
        if(!isInCanvas(i->calcBarycentre())) aller_zou(TriangleList.first, i);
    }
    for(auto i : PentagonList.first){
        if(!isInCanvas(i->calcBarycentre())) aller_zou(PentagonList.first, i);
    }
    for(auto i : HexagonList.first){
        if(!isInCanvas(i->calcBarycentre())) aller_zou(HexagonList.first, i);
    }
    for(auto i : HeptagonList.first){
        if(!isInCanvas(i->calcBarycentre())) aller_zou(HeptagonList.first, i);
    }
    for(auto i : OctogonList.first){
        if(!isInCanvas(i->calcBarycentre())) aller_zou(OctogonList.first, i);
    }
    for(auto i : TriangleList.first){
        if(!isInCanvas(i->calcBarycentre())) aller_zou(TriangleList.first, i);
    }
    for(auto i : StrokeList.first){
        if(!isInCanvas(i->getCenter_Segment())) aller_zou(StrokeList.first, i);
    }

    return *this;
}

GrawEditor& GrawEditor::Select(ShapeType forme){

    switch(forme){

    case ShapeType::Stroke:
        StrokeList.second = true;
        break;

    case ShapeType::Triangle:
        TriangleList.second = true;
        break;

    case ShapeType::Rectangle:
        RectangleList.second = true;
        break;

    case ShapeType::Pentagon:
        PentagonList.second = true;
        break;

    case ShapeType::Hexagon:
        HexagonList.second = true;
        break;

    case ShapeType::Heptagon:
        HeptagonList.second = true;
        break;

    case ShapeType::Octogon:
        OctogonList.second = true;
        break;

    case ShapeType::Ellipsis:
        EllipsisList.second = true;
        break;

    case ShapeType::All:
        StrokeList.second = true;
        TriangleList.second = true;
        RectangleList.second = true;
        PentagonList.second = true;
        HexagonList.second = true;
        HeptagonList.second = true;
        OctogonList.second = true;
        EllipsisList.second = true;
        break;

    default:
        printf("Imaginons qu'une erreur soit renvoyée ici...\n");

    }

    return *this;
}

GrawEditor& GrawEditor::Print(){

    if(StrokeList.second == true){
        std::cout << "Les segments dans le canvas : " << std::endl;
        printShapeList(StrokeList.first);
    }
    if(TriangleList.second == true){
        std::cout << "Les triangles dans le canvas : " << std::endl;
        printShapeList(TriangleList.first);
    }
    if(RectangleList.second == true){
        std::cout << "Les rectangles dans le canvas : " << std::endl;
        printShapeList(RectangleList.first);
    }
    if(PentagonList.second == true){
        std::cout << "Les pentagones dans le canvas : " << std::endl;
        printShapeList(PentagonList.first);
    }
    if(HexagonList.second == true){
        std::cout << "Les hexagones dans le canvas : " << std::endl;
        printShapeList(HexagonList.first);
    }
    if(HeptagonList.second == true){
        std::cout << "Les heptagones dans le canvas : " << std::endl;
        printShapeList(HeptagonList.first);
    }
    if(OctogonList.second == true){
        std::cout << "Les octogones dans le canvas : " << std::endl;
        printShapeList(OctogonList.first);
    }
    if(EllipsisList.second == true){
        std::cout << "Les ellipses dans le canvas : " << std::endl;
        printShapeList(EllipsisList.first);
    }

    return *this;
}

GrawEditor& GrawEditor::ExportSVG(char* fname){

    SVG::stream output(fname, size_canvas);

    if(StrokeList.second == true){
        exportShape(StrokeList.first, output);
    }
    if(TriangleList.second == true){
        exportShape(TriangleList.first, output);
    }
    if(RectangleList.second == true){
        exportShape(RectangleList.first, output);
    }
    if(PentagonList.second == true){
        exportShape(PentagonList.first, output);
    }
    if(HexagonList.second == true){
        exportShape(HexagonList.first, output);
    }
    if(HeptagonList.second == true){
        exportShape(HeptagonList.first, output);
    }
    if(OctogonList.second == true){
        exportShape(OctogonList.first, output);
    }
    if(EllipsisList.second == true){
        exportShape(EllipsisList.first, output);
    }

    output.close();

    return *this;
}

template<typename T> void GrawEditor::freeVec(std::vector<T*> vec){
    for(auto it : vec)
        delete it;
}

template<typename T> void GrawEditor::aller_zou(std::vector<T*>& vec, Geom2D::Base* ptr){

    //Haha lambda expression goes brrrr
    auto it = std::find_if(
        vec.begin(), vec.end(), [&](const Geom2D::Base* trouve){ return trouve == ptr; });
    
    if(it != vec.end()){
        vec.erase(it);
    }
}

template<typename T> void GrawEditor::printShapeList(std::vector<T*> vec){
    for(auto i: vec){
        i->info(std::cout);
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename T> void GrawEditor::exportShape(std::vector<T*> vec, SVG::stream& output){
    for(auto i: vec){
        i->write(output);
    }
}

bool GrawEditor::isInCanvas(Geom2D::Point p){
    return p.getx() <= size_canvas && p.gety() <= size_canvas;
}