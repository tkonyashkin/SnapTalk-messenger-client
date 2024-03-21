#include <QApplication>
#include "chatwidget.h"


int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    ChatWidget cw;
    cw.show();

    return app.exec();
}
