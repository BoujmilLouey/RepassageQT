#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Commande
{
public:
    Commande();
    Commande(int id, const QDate &dateCommande,
             double montantTotal, const QString &statut, int idClient);

    int id() const { return m_id; }
    void setId(int id) { m_id = id; }

    QDate dateCommande() const { return m_dateCommande; }
    void setDateCommande(const QDate &d) { m_dateCommande = d; }

    double montantTotal() const { return m_montantTotal; }
    void setMontantTotal(double m) { m_montantTotal = m; }

    QString statut() const { return m_statut; }
    void setStatut(const QString &s) { m_statut = s; }

    int idClient() const { return m_idClient; }
    void setIdClient(int idClient) { m_idClient = idClient; }

    // CRUD
    bool ajouter();
    bool modifier();
    bool supprimer();

    static QSqlQueryModel* afficher();

private:
    int m_id;
    QDate m_dateCommande;
    double m_montantTotal;
    QString m_statut;
    int m_idClient;
};

#endif // COMMANDE_H
