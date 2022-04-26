#include "gui.hpp"

#include <iostream>

void gui:: update_scaling(float x, float y) {

    x_scaling = round(x) / x_dimension;  // x = width of window (960), x_dimension = emulated width (240)
    y_scaling = round(y) / y_dimension;  // y = height of window (640), y_dimension = emulated height (160)
}

void gui:: init () {

    for (int x=0;x<x_dimension;x++) {
        for (int y=0;y<y_dimension;y++) {

            int width = x * x_scaling; //width = 4
            int height = y * y_scaling; //height = 4

            //coordinates of farthest corner
            int next_width = (x+1) * x_scaling; 
            int next_height = (y+1) * y_scaling;

            //debug
            std::cout<<x<<" "<<y<<std::endl;
            std::cout<<width<<" "<<height<<std::endl;
            std::cout<<next_width<<" "<<next_height<<std::endl;


            //random color
            al::Color temp ((std::rand()%100)/50,(std::rand()%100)/50,(std::rand()%100)/50);

            //draw square (with 5 vertices?)
            test[x][y].primitive(al::Mesh::TRIANGLE_STRIP);
            test[x][y].vertex(width,height,0);
            test[x][y].vertex(width,next_height,0);
            test[x][y].vertex(next_width,next_height,0);
            test[x][y].vertex(next_width,height,0);
            test[x][y].vertex(width,height,0);

            //apply random color to all vertices of box (not sure why 5 colors are required)
            for (int i=0;i<5;i++) {
                test[x][y].color(temp);
            }
        }
    }


}

void gui:: rand_color() {
    
    //animation to randomize the color of a random pixel
    
    al::Color temp ((std::rand()%100)/50,(std::rand()%100)/50,(std::rand()%100)/50);

    int tempx = abs(std::rand()*100 % x_dimension);
    int tempy = abs(std::rand()*100 % y_dimension);

    test[tempx][tempy].colors().clear();

    //each mesh has 5 vertices?
    for (int i=0;i<5;i++) {
        test[tempx][tempy].color(temp);
    }
}

void gui:: render (al::Graphics& g) {
    g.meshColor();  // use mesh's color

    // randomize the colors a bunch of times
    for (int i=0;i<500;i++) {
        rand_color();
    }

    // draw all squares (O(n^2) lol)
    for (int i=0;i<x_dimension;i++) {
        for (int j=0;j<y_dimension;j++) {
            g.draw(test[i][j]);
        }
    }
}
