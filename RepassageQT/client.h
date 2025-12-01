#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQueryModel>

class Client
{
public:
    Client();
    Client(int id, const QString &nom, const QString &prenom,
           const QString &email, const QString &telephone,
           const QString &adresse);

    int id() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString nom() const { return m_nom; }
    void setNom(const QString &nom) { m_nom = nom; }

    QString prenom() const { return m_prenom; }
    void setPrenom(const QString &prenom) { m_prenom = prenom; }

    QString email() const { return m_email; }
    void setEmail(const QString &email) { m_email = email; }

    QString telephone() const { return m_telephone; }
    void setTelephone(const QString &telephone) { m_telephone = telephone; }

    QString adresse() const { return m_adresse; }
    void setAdresse(const QString &adresse) { m_adresse = adresse; }

    // CRUD (requêtes préparées)
    bool ajouter();
    bool modifier();
    bool supprimer();

    // Affichage
    static QSqlQueryModel* afficher();

private:
    int m_id;
    QString m_nom;
    QString m_prenom;
    QString m_email;
    QString m_telephone;
    QString m_adresse;
};

#endif // CLIENT_H
