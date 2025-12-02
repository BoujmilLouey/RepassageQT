#include "mainwindow.h"
#include "dbconnection.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!DBConnection::instance().open()) {
        QMessageBox::critical(nullptr,
                              "Base de données",
                              "Impossible d'ouvrir la base de données.\n"
                              "Vérifiez la configuration de la connexion.");
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
