#include <QtGui/QApplication>
#include "indexation.h"

int main(int argc, char *argv[])
{
    //setWindowIcon( QPixmap( "logo_ind_g.png" ) );
    QApplication a(argc, argv);
    indexation w;
    w.show();

    return a.exec();
}
