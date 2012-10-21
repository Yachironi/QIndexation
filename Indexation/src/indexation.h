#ifndef INDEXATION_H
#define INDEXATION_H
#include <QMainWindow>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <QString>
#include <QtCore>
#include<QtGui>
#include <index.h>
#include <QDesktopServices>
#include <QUrl>

using namespace std;

namespace Ui {
    class indexation;
}

class indexation : public QMainWindow
{
    Q_OBJECT
    //void add(QString nom,QString prenom):
public:
    explicit indexation(QWidget *parent = 0);
    ~indexation();
private slots:
    void on_inv_clicked();
    void on_pushButton_clicked();
    void addc(QTreeWidgetItem * parent,QString nom,QString prenom,QString desc,QString stem,QString etape);
    void on_pushButton_2_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_actionQuitter_3_triggered();

    void on_action_Propo_triggered();

private :
    void add(QString nom,QString prenom,QString desc,QString chemin,QString stem,QString etape);
    void index_2(string nom,int nbr,string chemin);
    bool verif_2 (string mot,en *t,int k);
    int nbr_mot(string nom);
    int isDir(char* s);
    void explorer(string doc,fichier *t,int *k);
    void save(en*t,int x);
private:
    Ui::indexation *ui;
};

#endif // INDEXATION_H
