class sample : public SynthVoice {
  public:
    const char* path;
    SamplePlayer<> player;
    float gain;
    Mesh disc;


    void init() override {
        addDisc(disc, 1.0, 30);
    }
    
    //constructors
    sample();
    sample (const char* _path, float _gain);
    
    //copy constructor
    sample (const sample &m);

    //copy assignment operator
    sample& operator=(const sample& new_sample);

    //destructor
    ~sample();
    
    void onProcess(AudioIOData& io) override;

    void onProcess(Graphics& g) override;

    void onTriggerOn() override;

    void onTriggerOff() override;

    void load_path(const char* _path);
    void update_gain(float _gain);
    float output();
};

//default constructor
sample::sample() {
    gain = 0.;
}
//constructor
sample::sample (const char* _path, float _gain) {
    load_path(_path);
    gain = _gain;
}
//copy constructor
sample::sample (const sample &m) {
    path = m.path;
    gain = m.gain;
    load_path(path);
}
sample& sample::operator=(const sample& new_sample) {

}
sample::~sample() {

}
void sample::load_path(const char* _path) {
    path = _path;
    player.load(path);
}
void sample::update_gain(float _gain) {
    gain = _gain;
}
float sample::output() {
    return player() * gain;
}

void sample::onProcess(AudioIOData& io) {
    cout<<"asd";
}

void sample::onProcess(Graphics& g) {
    cout<<"asd";
}

void sample::onTriggerOn() {
    cout<<"asd";
}

void sample::onTriggerOff() {
    cout<<"asd";
}