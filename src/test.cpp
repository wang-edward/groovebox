#include <iostream>
#include <vector>
#include <array>
#include <filesystem>
#include <string>
#include <random>

#include "Gamma/SamplePlayer.h"
#include "Gamma/Analysis.h"
#include "Gamma/Effects.h"
#include "Gamma/Envelope.h"
#include "Gamma/Oscillator.h"
// #include <Player.h>

#include "al/app/al_App.hpp"
// #include "al/sound/al_SoundFile.hpp"
#include "al/graphics/al_Font.hpp"
#include "al/graphics/al_Mesh.hpp"
#include "al/sound/al_Speaker.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/scene/al_PolySynth.hpp"
#include "al/scene/al_SynthSequencer.hpp"
#include "al/ui/al_ControlGUI.hpp"
#include "al/ui/al_Parameter.hpp"
// #include "al/ui/al_FileSelector.hpp"

#include "al/graphics/al_Image.hpp"


#include "track.hpp"
#include "timeline.hpp"


#define AUDIO_BLOCK_SIZE 128

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

struct MyApp : public al::App {

    timeline tl;
    al::Texture texture;

    int f_width, f_height;
  
  void onInit() override {
    // dimensions(960,640);
    dimensions(240,160);

    updateDraw(tl.get_gui());

    // tl.init();
    // tl.playing = true;
  }
  void onCreate() override {
    // navControl().active(false);
    // nav().pos(0,0,10);

    const char* filename = "data/image/doom_midway1.png";

    auto imageData = al::Image(filename);

    if (imageData.array().size() == 0) {
      std::cout << "failed to load image" << std::endl;
    }
    std::cout << "loaded image size: " << imageData.width() << ", "
         << imageData.height() << std::endl;

    texture.create2D(imageData.width(), imageData.height());
    texture.submit(imageData.array().data(), GL_RGBA, GL_UNSIGNED_BYTE);

    texture.filter(al::Texture::LINEAR);

    f_width = imageData.width(); f_height = imageData.height();
  }
  
  void onSound(al::AudioIOData& io) override {
    // tl.render(io);
  }

  void updateDraw(gui& target) {
    target.update_scaling(width(), height());
  }

  void onDraw (al::Graphics& g) override {
    // g.clear();
    g.camera(al::Viewpoint::ORTHO_FOR_2D);  // Ortho [0:width] x [0:height]
    // g.camera(al::Viewpoint::IDENTITY);  // Ortho [0:width] x [0:height]

    g.clear(0.2);

    g.pushMatrix();

    // Push the texture/quad back 5 units (away from the camera)
    
    // g.translate(0, 0, -5);

    g.quad(texture, 100, 100, f_width, f_height);

    g.popMatrix();

    // tl.render(g);
    // std::cout<<width()<<std::endl;
  }

  bool onKeyDown(al::Keyboard const& k) override {

    int key_pressed = al::asciiToIndex(k.key());
    std::cout<<key_pressed<<std::endl;

   
    return true;
  }

  // Whenever a key is released this function is called
  bool onKeyUp(al::Keyboard const& k) override {
    
    return true;
  }
    
};

int main() {
  MyApp app;
  app.configureAudio(44100., 256, 2, 0);
  gam::Domain::master().spu(app.audioIO().framesPerSecond());

  app.start();
}
