#include "SineEnv.hpp"


SineEnv:: SineEnv() {
  mAmpEnv.curve(0);  // make segments lines
  mAmpEnv.sustainPoint(2);

  addSphere(mMesh, 0.5, 30, 30);
}

// Note parameters
SineEnv& SineEnv:: freq(float v) {
  mOsc.freq(v);
  return *this;
}

// Audio processing function
void SineEnv:: onProcess(al::AudioIOData& io) {
  while (io()) {
    float s = mOsc() * mAmpEnv() * mAmp;
    io.out(0) += s;
    io.out(1) += s;
  }
  if (mAmpEnv.done()) {
    free();
  }
}

// Graphics processing function
void SineEnv:: onProcess(al::Graphics& g)  {
  float spatialEnv = mAmpEnv.value();
  g.pushMatrix();
  g.blending(true);
  g.blendTrans();
  g.translate(mOsc.freq() / 250 - 3, spatialEnv * 2 - 1, -8);
  g.color(spatialEnv, mOsc.freq() / 1000, spatialEnv, spatialEnv);
  g.draw(mMesh);
  g.popMatrix();
}

void SineEnv:: onTriggerOn() { 
  mAmpEnv.reset(); 
  std::cout<<"on"<<std::endl;  
}

void SineEnv:: onTriggerOff() { 
  mAmpEnv.release(); 
  std::cout<<"off"<<std::endl;  
}

