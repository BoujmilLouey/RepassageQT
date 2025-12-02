#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include "client.h"
#include "commande.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT   // <-- super important

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots pour les boutons Clients
    void on_btnAjouterClient_clicked();
    void on_btnModifierClient_clicked();
    void on_btnSupprimerClient_clicked();
    void on_btnRechercheClient_clicked();
    void on_btnStatsClients_clicked();
    void on_btnExporterClientsPdf_clicked();
    void on_btnTotalDepenseClient_clicked();
    void on_btnFideliteClient_clicked();


    // (On ajoutera ceux de Commande plus tard si besoin)

private:
    Ui::MainWindow *ui;

    QSqlQueryModel *m_modelClients;
};

#endif // MAINWINDOW_H
