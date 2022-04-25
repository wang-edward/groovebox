#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include "al/io/al_AudioIO.hpp"
#include "al/graphics/al_Graphics.hpp"
#include "track.hpp"
#include "gui.hpp"
class timeline {
    public:
        void render(al::AudioIOData& io);
        void render(al::Graphics& g);
        void align_tracks();
        void init();
        

    protected:
        static const int NUMBER_TRACKS = 1;
        long long current_position;
        track tracks[NUMBER_TRACKS];
        bool playing = true;

        gui screen;

        void init_files();
        

};

#endif