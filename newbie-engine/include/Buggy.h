#ifndef __BUG__
#define __BUG__

# ifdef WIN32
#  include <windows.h>
# endif

#include "Veichle.h"
#include <ode/ode.h>

class Bugy:public Veichle
{
    public:
    float length;
    float width;
    float height;
    float wheelRadius;
    float startZ;
    float chassiMass;
    float cMassOffset;
    float wheelMass;
    float maxTorque;
    float maxRPM;

    bool accelPressed;
    bool leftPressed;
    bool rightPressed;
    bool brakingPressed;
    bool reversePressed;
    Bugy();
    Bugy(dSpaceID space, dWorldID world);

    void Update(float dt);
    void controlInput();
    void Draw();
    vec3d getForces();
    vec3d getTorques();
    vec3d getPosition();
    Matrix getRotation();
    private:
        vec3d _force;
        vec3d _torque;
};


#endif
