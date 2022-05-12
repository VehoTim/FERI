//
// Created by timve on 2. 06. 2021.
//

#include "Layout.h"

void Layout::addView(std::shared_ptr<View> view) {
    views.push_back(view);
}

std::shared_ptr<View> Layout::getView(int position) const{
    return views[position];
}

void Layout::draw() {
    for(std::shared_ptr<View> &v : views){
        v->draw();
        std::cout << std::endl;
    }
}
