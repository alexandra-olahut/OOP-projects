#include "SoftwareApplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Controller controller{ "Users.txt", "Issues.txt" };
    for (auto user : controller.getUsers())
    {
        SoftwareApplication* window = new SoftwareApplication{ controller, user };
        controller.addObserver(window);
        window->show();
    }

    return a.exec();
}
