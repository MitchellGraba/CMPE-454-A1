// Missile class

#ifndef MISSILE_H
#define MISSILE_H

#include "headers.h"
#include "gpuProgram.h"

class Missile
{
public:
  // Constructors

  Missile() {}

  Missile(vec3 p, vec3 v, float y, vec3 c)
  {
    pos0 = p;
    posT = p;
    posA = p;
    posB = p;
    posC = p;
    pos1 = p;
    velocity = v;
    colour = c;
    destY = y;
  }

  // Draw the missile and its trail

  void draw(GPUProgram *gpuProgram)
  {
   
    vec3 verts[2] = {
        vec3(posT.x, posT.y, 0),
        vec3(pos1.x, pos1.y, 0)};
        
    vec3 vertsA[2] = {
        vec3(posT.x, posT.y, 0),
        vec3(posA.x, posA.y, 0)};
        
    vec3 vertsB[2] = {
        vec3(posT.x, posT.y, 0),
        vec3(posB.x, posB.y, 0)};
        
     vec3 vertsC[2] = {
        vec3(posT.x, posT.y, 0),
        vec3(posC.x, posC.y, 0)};    
            
    gpuProgram->drawVertices(&verts[0], 2, GL_LINES, colour);
    gpuProgram->drawVertices(&vertsA[0], 2, GL_LINES, vec3(colour.x - 0.33,colour.y-0.33, colour.z));
    gpuProgram->drawVertices(&vertsB[0], 2, GL_LINES, vec3(colour.x-0.66,colour.y-0.66, colour.z));
     gpuProgram->drawVertices(&vertsC[0], 2, GL_LINES, vec3(colour.x-0.85,colour.y-0.85, colour.z));
    
  }

  // Move the missile over a time interval, deltaT

  void move(float deltaT)
  {
    pos1 = pos1 + deltaT * velocity;

    if(sqrt((pos1 - pos0).squaredLength()) > 0.0666){
      posA = posA + deltaT * velocity;
    }
    if(sqrt((pos1 - pos0).squaredLength()) > 0.1333){
      posB = posB + deltaT * velocity;
    }

    if(sqrt((pos1 - pos0).squaredLength()) > 0.1333){
      posC = posC + deltaT * velocity;
    }

     if(sqrt((pos1 - pos0).squaredLength()) > 0.2){
      posT = posT + deltaT * velocity;
    }

  }

  // Return the current position

  vec3 position()
  {
    return pos1;
  }

  // Has the missile reached its destination?

  bool hasReachedDestination(bool *state)
  {

    return hasHitBoundary() || hasHitYdest() || hasHitCity0(state) || hasHitCity1(state) || 
    hasHitCity2(state) || hasHitCity3(state) || hasHitCity4(state) || hasHitCity5(state) || 
    hasHitSilo();
  }

  bool hasHitYdest()
  {
    return ((pos1 - pos0).y > abs(destY - pos0.y)) ? true : false;
  }

  bool hasHitBoundary()
  {

    return pos1.x > 1 || pos1.y > 0.68 || pos1.x < 0 || pos1.y < 0;
  }

   bool hasHitSilo(){
      return ((pos1.x >= 0.06 && pos1.x <= 0.14) || (pos1.x >= 0.46 && pos1.x <= 0.54) ||
		  (pos1.x >= 0.86 && pos1.x <= 0.94)) && (pos1.y <= 0.01);
  }

  bool hasHitCity0(bool state[])
  {

    if (state[0])
    {
      return false;
    }

    

    return pos1.x >= 0.16 && pos1.x <= 0.24 && pos1.y <= 0.03;
  }
  bool hasHitCity1(bool state[])
  {

    if (state[1])
    {
      return false;
    }

   
    return pos1.x >= 0.26 && pos1.x <= 0.34 && pos1.y <= 0.03;
  }
  bool hasHitCity2(bool state[])
  {

    if (state[2])
    {
      return false;
    }

    

    return pos1.x >= 0.36 && pos1.x <= 0.44 && pos1.y <= 0.03;
  }
  bool hasHitCity3(bool state[])
  {
    

    if (state[3])
    {
      return false;
    }

   

    return pos1.x >= 0.56 && pos1.x <= 0.64 && pos1.y <= 0.03;
  }
  bool hasHitCity4(bool state[])
  {

    if (state[4])
    {
      return false;
    }

    

    return pos1.x >= 0.66 && pos1.x <= 0.74 && pos1.y <= 0.03;
  }
  bool hasHitCity5(bool state[])
  {
    if (state[5])
    {
      return false;
    }

    return pos1.x >= 0.76 && pos1.x <= 0.84 && pos1.y <= 0.03;
  }

  bool hasHitCity(int i)
  {

    if (i > 2)
    {

      return pos1.x >= (((float)i / 10.0) + 0.3 - 0.04) && pos1.x <= (((float)i / 10.0) + 0.3 + 0.04) && pos1.y <= 0.03;
    }

    return pos1.x >= (((float)i / 10.0) + 0.2 - 0.04) && pos1.x <= (((float)i / 10.0) + 0.2 + 0.04) && pos1.y <= 0.03;
  }

private:
  vec3 pos0;     // start position
  vec3 posT;     // trailing position
  vec3 posA;
  vec3 posB;
  vec3 posC;
  vec3 pos1;     // current position
  vec3 velocity; // velocity
  vec3 colour;   // colour of missile trail
  float destY;   // y position at destination
};

#endif
