class mpc : public SynthVoice {
  public:
    const char* path;
    SamplePlayer<> player;
    float gain;
    Mesh disc;
    void init() override {
        addDisc(disc, 1.0, 30);
    }

    void onProcess(AudioIOData& io) override {

    }


    mpc() {
        gain = 0.;
    }
    mpc (const char* _path, float _gain) {
      load_path(_path);
      gain = _gain;
    }
    mpc (const mpc &m) {
        path = m.path;
        gain = m.gain;
        load_path(path);
    }
    void load_path(const char* _path) {
      path = _path;
      player.load(path);
    }
    void update_gain(float _gain) {
      gain = _gain;
    }
    float output() {
      return player() * gain;
    }
};