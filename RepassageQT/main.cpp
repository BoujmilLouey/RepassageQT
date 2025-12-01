#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

#include "dbconnection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Ouverture de l’unique connexion Oracle
    bool ok = DBConnection::instance().open();
    if (!ok) {
        // Pour l’examen à distance : on explique que sur la machine de la maison,
        // Oracle n’est pas installé, mais que le code et le script sont prévus pour Oracle.
        QMessageBox::warning(nullptr,
                             "Connexion BD",
                             "Impossible d'ouvrir la connexion Oracle sur cette machine.\n"
                             "Le code est toutefois prêt pour une base Oracle (QOCI).");
        // On continue quand même pour pouvoir montrer l’IHM
    }

    MainWindow w;
    w.show();
    return a.exec();
}
