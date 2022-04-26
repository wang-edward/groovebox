#include "gui.hpp"

#include <iostream>

void gui:: update_scaling(float x, float y) {

    x_scaling = round(x) / x_dimension;
    y_scaling = round(y) / y_dimension;
}

void gui:: init () {

    for (int x=0;x<x_dimension;x++) {
        for (int y=0;y<y_dimension;y++) {

            int width = x * x_scaling;
            int height = y * y_scaling;

            int next_width = (x+1) * x_scaling;
            int next_height = (y+1) * y_scaling;

            std::cout<<x<<" "<<y<<std::endl;
            std::cout<<width<<" "<<height<<std::endl;
            std::cout<<next_width<<" "<<next_height<<std::endl;


            al::Color temp ((std::rand()%100)/50,(std::rand()%100)/50,(std::rand()%100)/50);

            // al::Color temp (1,0,0);


            //example x = 0, y = 0
            test[x][y].primitive(al::Mesh::TRIANGLE_STRIP);
            test[x][y].vertex(width,height,0);
            test[x][y].vertex(width,next_height,0);
            test[x][y].vertex(next_width,next_height,0);
            test[x][y].vertex(next_width,height,0);
            test[x][y].vertex(width,height,0);

            for (int i=0;i<5;i++) {
                test[x][y].color(temp);
            }
        }
    }


}

void gui:: rand_color() {
    al::Color temp ((std::rand()%100)/50,(std::rand()%100)/50,(std::rand()%100)/50);

    int tempx = abs(std::rand()*100 % x_dimension);
    int tempy = abs(std::rand()*100 % y_dimension);

    // std::cout<<tempx<<" "<<tempy<<std::endl;

    test[tempx][tempy].colors().clear();

    //each mesh has 5 vertices?
    for (int i=0;i<5;i++) {
        test[tempx][tempy].color(temp);
    }
}

void gui:: render (al::Graphics& g) {
    g.meshColor();  // use mesh's color
    // g.draw(grid);

    for (int i=0;i<500;i++) {
        rand_color();
    }

    for (int i=0;i<x_dimension;i++) {
        for (int j=0;j<y_dimension;j++) {
            g.draw(test[i][j]);
        }
    }
}