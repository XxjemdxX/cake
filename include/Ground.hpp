#include <chipmunk/chipmunk.h>

class Suelo {
public:
    Suelo(cpSpace* space) {
        cpBody* ground = cpSpaceGetStaticBody(space);
        
        // Crear el suelo ladeado
        // Estos puntos definen una línea inclinada
        cpVect punto1 = cpv(0, 500);  // Primer extremo (normalmente en la parte inferior)
        cpVect punto2 = cpv(800, 400);  // Segundo extremo inclinado, se mueve hacia arriba en y

        shape = cpSegmentShapeNew(ground, punto1, punto2, 0);
        cpShapeSetFriction(shape, 1.0);
        cpSpaceAddShape(space, shape);
    }

    ~Suelo() {
        cpShapeFree(shape);
    }

private:
    cpShape* shape;
};
