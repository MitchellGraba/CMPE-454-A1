// Types of building


#ifndef BUILDING_H
#define BUILDING_H


#include "headers.h"
#include "gpuProgram.h"



class Building {
 public:

  // Constructors

  Building() {}

  Building( vec3 p ) {
    pos = p;
  }


  vec3 position() {
	  return pos;
  }

  // Draw the building

  virtual void draw( GPUProgram *gpuProgram ) = 0;

 protected:

  vec3 pos;			// centre
};



#endif
