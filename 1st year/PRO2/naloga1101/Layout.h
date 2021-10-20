//
// Created by timve on 2. 06. 2021.
//

#ifndef NALOGA1101_LAYOUT_H
#define NALOGA1101_LAYOUT_H

#include "View.h"
#include <vector>
#include <memory>

class Layout {
private:
    std::vector<std::shared_ptr<View>> views;
public:
    void addView(std::shared_ptr<View> view);
    std::shared_ptr<View> getView(int position) const;
    void draw();
};


#endif //NALOGA1101_LAYOUT_H
