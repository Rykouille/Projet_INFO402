#ifndef _GRAWINK_H_
#define _GRAWINK_H_

#include <inttypes.h>
#include <forward_list>
#include <vector>
#include "ShapeFactory.h"

#define DEFAULT_CANVAS_SIZE 10


class GrawEditor {
  protected:

    // Pairs de nos vectors contenant nos formes suivant leur familles ainsi qu'un booléen pour la sélection.

    std::pair<std::vector<Geom2D::Curve::Segment*>, bool> StrokeList;
    std::pair<std::vector<Geom2D::Surface::Triangle*>, bool> TriangleList;
    std::pair<std::vector<Geom2D::Surface::Rectangle*>, bool> RectangleList;
    std::pair<std::vector<Geom2D::Surface::Pentagon*>, bool> PentagonList;
    std::pair<std::vector<Geom2D::Surface::Hexagon*>, bool> HexagonList;
    std::pair<std::vector<Geom2D::Surface::Heptagon*>, bool> HeptagonList;
    std::pair<std::vector<Geom2D::Surface::Octogon*>, bool> OctogonList;
    std::pair<std::vector<Geom2D::Curve::Circle*>, bool> EllipsisList;  

    // Listes chainées contenant nos objets supprimés et ajouté, permettant le Undo et Redo

    std::forward_list<Geom2D::Base*> undoList;
    std::forward_list<Geom2D::Base*> redoList;

    // Notre output stream
    float size_canvas;

    GrawEditor(): size_canvas(1000) {}

    // Fonction utilisée par Delete() pour trouver un ptr et le supprimer du vector correspondant.
    template <typename T> void aller_zou(std::vector<T*>&, Geom2D::Base*);

    // Fonction utilisée par Print() pour afficher le contenu de nos vecteurs de formes.
    template<typename T> void printShapeList(std::vector<T*>);

    // Fonction utilisée par Export() pour ajouter nos formes à notre SVG.
    template<typename T> void exportShape(std::vector<T*>, SVG::stream&);

    // Fonction pour supprimer les éléments de nos vectors de pointeurs.
    template<typename T> void freeVec(std::vector<T*>);

    // Fonction qui nous renvoie si un point se situe dans le canvas.
    bool isInCanvas(Geom2D::Point);
  
  public:

    //On empêche l'assignation et la construction par copie pour respecter nos règles de Singleton,
    // De même pour notre constructeur et assignation par déplacement.
    GrawEditor(const GrawEditor&) = delete;
    GrawEditor(GrawEditor&&) = delete;

    GrawEditor& operator=(GrawEditor&&) = delete;
    GrawEditor& operator=(const GrawEditor&) = delete;

    ~GrawEditor();

    //Static, donc définie en dehors de la classe.
    static GrawEditor& GetEditor();


    // Ajoute un nouvel objet au canevas
    GrawEditor& Add(Geom2D::Base*);

    // Supprime un objet du canevas
    GrawEditor& Delete(Geom2D::Base*);

    // Annule le dernier ajout d'objet
    GrawEditor& Undo();

    // Réinsère le dernier objet supprimé
    GrawEditor& Redo();

    // Redimensionne le canevas
    GrawEditor& Resize(float);

    /* Redimensionne le canevas en supprimant les objets extérieurs 
      Pour savoir si un objet est à l'extérieur on va vérifier suivant certains critère.

      - En ce qui concerne les Circle, nous vérifions si leur centre est toujours dans le Canvas.
      - Pour les Polygones on, vérifie si leur barycentre est dans le Canvas
      - En ce qui concerne les rectangles, étant donné que ceux-ci sont construits différemment, 
          on va seulement vérifier si leur coin est en dehors du Canvas.
      - Enfin pour les segments, on vérifie un de leur centre est en dehors du Canvas 
    
      On supprime ces formes alors, sans les passer dans Undo.
    */
    GrawEditor& Crop(float);

    // Sélectionne les objets à exporter/afficher.
    // La sélection pourra se faire sous la forme d'une disjonction ("OU" binaires) de `enum ShapeType`.
    // Par exemple pour sélectionner uniquement les triangles, les rectangles et les octogones, on pourra passer en paramètre :
    //  ShapeType::Triangle | ShapeType::Rectangle | ShapeType::Octogon, ou
    //  bien l'équivalent en hexadécimal (0x46ULL), ou en décimal (70ULL).
    // Passer ShapeType::All resélectionne l'ensemble des formes du canevas.
    GrawEditor& Select(ShapeType);

    // Affiche l'ensemble des objets contenus dans le canevas, triés par
    // catégorie, dans la sortie standard.
    GrawEditor& Print( /* pas de paramètre */ );   

    // Écrit le code SVG résultant des objets contenus dans le canevas
    GrawEditor& ExportSVG(char*);

    // Crée une nouvelle instance de la classe `Geom2D::Base` (i.e. Rectangle,
    // Triangle, Stroke, Circle, etc.) et retourne un pointeur vers l'objet nouvellement alloué.
    // Cet objet peut ensuite être transformé, passé en paramètre à `Add` ou à `Delete`.
    template <typename Shape> Shape* GetNew(ShapeType forme){
    
    Shape* res = ShapeFactory::createShape(forme);
    return res;
}


};

#endif /* _GRAWINK_H_ */
