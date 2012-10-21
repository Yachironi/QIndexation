#include "indexation.h"
#include "ui_indexation.h"

using namespace std;

string readv (FILE * resultat)
{
        char c;
        string var="";
        do
        {
                c=getc(resultat);
                if((c!=';')&&(c!=EOF))
                {
                        var+=c;
                }
                else if (var!="")
                {
                        return var;
                }
                else
                {
                    return "EOF";
                }

        }while(c!=EOF);
}

void update(FILE * nom)
{
    cout<<"update called";
    fseek(nom,0,0);
    string res;
    int taille;
    FILE * nom2=fopen("resultat.txt","w+");
    do
    {
        res=readv(nom);
        if((res.length()<=30)&&(res!="EOF"))
        {
            taille=res.length();
            for(int k=0;k<=(30-taille);k++)
            {
                res+=" ";
            }
            cout<<res;
            fputs((char*)res.c_str(),nom2);
        }
    }while(res!="EOF");
    fclose(nom2);
}


int indexation::nbr_mot(string nom)
{
        char c;
        int i=0;
        string var;
        cout<<"\n"+nom+"\n";
        FILE * index=fopen(nom.c_str(),"r");
    if (index==NULL)
        cout<<"ERREUR, Ce Fichier n'existe pas";
    else
                {
                        while(c!=EOF)
                        {
                                c=getc(index);
                                if (c!=EOF)
                                {
                                        if ((c!= ' ')&&(c!='\n'))
                                                {
                                                        if((c!='.')&&(c!=',')&&(c!='\'')&&(c!='\"')&&(c!=';')&&(c!='<')&&(c!='>'))
                                                        {
                                                                var+=c;
                                                        }
                                                }
                                        else
                                        {
                                                if(var.length()>3)
                                                {
                                                   i++;
                                                }
                                                var="";
                                        }
                                }
                        }
                        fclose(index);
                }
    cout<<i;
                return i;
}

bool indexation::verif_2 (string mot,en *t,int k)
{
    for(int i=0;i<k;i++)
    {
        if (t[i].mot==mot)
        {
            t[i].rec++;
            return true;
        }
    }
    return false;
}


void indexation::index_2(string nom,int nbr,string chemin)
{
    char c=0;
    int i=0,j=0,k=0;
    string var;
    string nom_res=nom+"_Inversé.txt";
    int taill=nbr;
    en *t;
    t=new en[taill];
    FILE * index=fopen((chemin+nom+".txt").c_str(),"r");
    FILE * resultat=fopen("index.txt","a");
    if (index==NULL)
            cout<<"\n ERREUR, Ce Fichier n'existe pas\n\n";
    else
        {
            while(c!=EOF)
            {
                c=getc(index);
                i++;
                if (c!=EOF)
                {
                    if ((c!= ' ')&&(c!='\n'))
                        {
                            if((c!='.')&&(c!=',')&&(c!='\'')&&(c!='\"')&&(c!=';')&&(c!='<')&&(c!='>'))
                            {
                                var+=c;
                                j++;
                            }
                        }
                    else
                    {
                        if(var.length()>3)
                        {
                            if (!verif_2(var,t,k))
                            {

                                std::stringstream tmp;
                                tmp << (i-j-2);
                                t[k].mot=var;
                                var=tmp.str();
                                t[k].pos=(i-j-2);
                                t[k].rec=1;
                                k++;
                            }
                        }
                        var="";
                        j=0;
                    }
                }
            }
            fclose(index);
        }
        for(int i=0;i<k;i++)
        {
            std::stringstream tmp;
            tmp << t[i].pos;
            std::stringstream tmp2;
            tmp2 << t[i].rec;
            var=t[i].mot+";"+tmp.str()+";"+tmp2.str()+"\n";
            fputs((char*)var.c_str(),resultat);
        }
        fclose(resultat);
    }

int indexation::isDir(char* s)
{
    if ((strchr(s, '.')) == NULL) /* Si le nom du chemin n'a pas de point (une extension). */
       { return 1;}
    else
       { return 0;}
}

void indexation::explorer(string doc,fichier *t,int *k)
{
    DIR *dp;
    string n;
       struct dirent *ep;
       int static i=0;
       dp = opendir ((char*)(doc).c_str());
       if (dp != NULL)
         {
           while ((ep = readdir (dp)))
             {
                 n=ep->d_name;
                 if((n.length()>=5)&&(n.substr(n.length()-4,4)==".txt"))
                 {
                     //int nbr=nbr_mot(doc+"\\"+n);
                     t[i].chemin=doc+"/";
                     cout<<"\n"+t[i].chemin+n+"\n";
                     //t[i].nbr=nbr;
                     t[i].nom=n.substr(0,n.length()-4);
                     i++;
                     *k=i;
                 }

                    if(isDir((char*)n.c_str()))
                    {
                            explorer(doc+"/"+n,t,k);
                   }

                 }
          closedir (dp);
         }
       else
         {
             cout<<"\n Fin \n";
             perror ("Couldn't open the directory");

         }

}


void indexation::on_pushButton_clicked()
{
    QDesktopServices desk;
    //QDesktopServices::openDocument("C:\Debug\1\1a.txt");
    desk.openUrl(QUrl::fromLocalFile("C:\\Debug\\1\\1a.txt"));
}


void indexation::addc(QTreeWidgetItem *parent,QString nom,QString prenom,QString desc,QString stem,QString etape)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,nom);
    item->setText(1,prenom);
    item->setText(2,desc);
    item->setText(3,stem);
    item->setText(4,etape);
    parent->addChild(item);
}


indexation::indexation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::indexation)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->setHeaderLabels(QStringList() << "Mots" << "Stemming" << "Etape" <<"Premier Position" <<"Occurence"<< "Chemin" );
}

void indexation::add(QString mot,QString pos,QString rec,QString chemin,QString stem,QString etape)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,mot);
    item->setText(1,stem);
    item->setText(2,etape);
    item->setText(3,pos);
    item->setText(4,rec);
    item->setText(5,chemin);
}

void indexation::on_inv_clicked()
{
    findex f(100000);
    fichier *t;
        t=new fichier[20];
        int i;
        int *k;
        k=new int;
        cout << "Hello world!" << endl;
        explorer(ui->lineEdit->text().toStdString(),t,k);
        cout<<*k;
        cout<<"\n Fin exploer \n";
        //cout<<t[0].nom;
        for(int i=0;i<*k;i++)
             {
                 cout<<(t[i].chemin+t[i].nom+".txt"+"\n");
                 f.index(t[i].nom+".txt",t[i].chemin);
             }
             f.save();
     en * tab;
     tab=f.gett();
     for(int i=0;i<f.getp();i++)
     add(
                 QString::fromStdString(tab[i].mot),
                 QString::number(tab[i].pos),
                 QString::number(tab[i].rec),
                 QString::fromStdString(tab[i].chemin),
                 QString::fromStdString(tab[i].stem),
                 QString::fromStdString(tab[i].etape)
                 );
     //ui->textEdit->append(QString::fromStdString(tab[0].mot));
    //ui->textEdit->append("Fin du programme");
}

indexation::~indexation()
{
    delete ui;
}

void indexation::on_pushButton_2_clicked()
{
    QString dossier = QFileDialog::getExistingDirectory(this);
    ui->lineEdit->setText(dossier);
}

void indexation::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    //ui->textEdit->append(item->text(5).replace("\\","\\\\"));
    QDesktopServices desk;
    desk.openUrl(QUrl::fromLocalFile(item->text(5).replace("\\","\\\\")));
}

void indexation::on_actionQuitter_3_triggered()
{
  close();
}

void indexation::on_action_Propo_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Indexation");
    msgBox.exec();
}
