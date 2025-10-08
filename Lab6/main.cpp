#include "schedulerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    SchedulerWindow window;
    window.show();
    
    return app.exec();
}