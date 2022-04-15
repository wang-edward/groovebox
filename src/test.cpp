#include "test.hpp"

struct MyApp : public App {
  PolySynth pSynth;

  void onCreate() override {
    // Pre-allocate voice to avoid real-time allocation
    pSynth.allocatePolyphony<SineEnv>(16);

    navControl().active(false);  // Disable navigation via keyboard, since we
                                 // will be using keyboard for note triggering
  }

  void onSound(AudioIOData& io) override {
    pSynth.render(io);  // Render audio
  }

  void onDraw(Graphics& g) override {
    g.clear();
    pSynth.render(g);
  }

  bool onKeyDown(Keyboard const& k) override {
    int midiNote = asciiToMIDI(k.key());
    if (midiNote > 0) {
      float frequency = ::pow(2., (midiNote - 69.) / 12.) * 440.;
      SineEnv* voice = pSynth.getVoice<SineEnv>();
      voice->freq(frequency);
      pSynth.triggerOn(voice, 0, midiNote);
    }
    return true;
  }

  bool onKeyUp(Keyboard const& k) override {
    int midiNote = asciiToMIDI(k.key());
    if (midiNote > 0) {
      pSynth.triggerOff(midiNote);
    }
    return true;
  }
};

int main() {
  // Create app instance
  MyApp app;

  // Start audio
  app.configureAudio(44100., 256, 2, 0);

  // Set up sampling rate for Gamma objects
  Domain::master().spu(app.audioIO().framesPerSecond());

  app.start();
}
