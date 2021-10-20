#include <iostream>
#include "Layout.h"
#include "Button.h"
#include "ImageButton.h"
#include "TextInput.h"
#include <memory>

int main() {
    Layout* l = new Layout();
    std::string s = "Besedilo";
    std::string path ="potDoSlike.png";

    l->addView(std::make_shared<TextView>(Position(20.5,22), Size(2.5,2.5,Unit::mm), s));
    l->addView(std::make_shared<ImageView>(Position(1.75, 30.05), Size(0.5, 0.2, Unit::dp), path));
    l->addView(std::make_shared<Button>(Position(22.22, 3), Size(0.1, 0.5, Unit::in), "Click"));
    l->addView(static_cast<std::shared_ptr<Button>>(std::make_shared<ImageButton>(Position(33.50, 2.91), Size(5,0.99, Unit::pt), s, path)));
    l->addView(std::make_shared<Button>(Position(17.2, 0), Size(10, 25, Unit::px), "Press the button"));

    l->addView(static_cast<std::shared_ptr<Button>>(std::make_shared<ImageButton>(Position(0, 4), Size(10, 2, Unit::mm), "Potrdi", "/../images/confirm.png")));

    std::vector<Button> b;
    b.push_back(std::make_shared<Button>())

    std::cout << "Print:\n";
    l->draw();
    std::cout << std::endl;

    std::cout << "Visible: " << std::endl;
    l->getView(4)->setVisible(true);
    if(l->getView(4)->isVisible())
        l->getView(4)->draw();
    else std::cout << "Not visible!\n";
    std::cout << "\nAfter:\n";
    l->getView(4)->setVisible(false);
    if(l->getView(4)->isVisible())
        l->getView(4)->draw();
    else std::cout << "Not visible!\n";
    std::cout << std::endl;

    std::dynamic_pointer_cast<Button>(l->getView(4))->onClick();
    std::dynamic_pointer_cast<Button>(l->getView(4))->setEnabled(false);
    std::dynamic_pointer_cast<Button>(l->getView(4))->onClick();

    std::cout << std::endl << std::endl;

    //Formular za vnos
    Layout *formular = new Layout();
    formular->addView(std::make_shared<TextInput>(Position(1,1), Size(10,2.5,Unit::mm), "Ime", 20, "Marija"));
    formular->addView(std::make_shared<TextInput>(Position(2,1), Size(10,2.5,Unit::mm), "Priimek", 20, "Novak"));
    formular->addView(std::make_shared<TextInput>(Position(3,1), Size(10,2.5,Unit::mm), "Leto r.", 4, "2005"));
    formular->addView(std::make_shared<Button>(Position(4,1), Size(15,2.5,Unit::mm), "OK"));
    formular->addView(std::make_shared<Button>(Position(4,1), Size(15,2.5,Unit::mm), "Cancel"));

    formular->draw();

    std::getline(std::cin, s);
    std::dynamic_pointer_cast<TextInput>(formular->getView(0))->setInputText(s);

    std::getline(std::cin, s);
    std::dynamic_pointer_cast<TextInput>(formular->getView(1))->setInputText(s);

    std::getline(std::cin, s);
    std::dynamic_pointer_cast<TextInput>(formular->getView(2))->setInputText(s);

    formular->draw();


    return 0;
}
