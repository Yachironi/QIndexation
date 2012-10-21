#ifndef INDEX_H
#define INDEX_H

using namespace std;
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <algorithm>
#include <QString>

using namespace std;
typedef struct mot
{
    string mot;
    int pos;
    int rec;
    string chemin;
    string stem;
    string etape;
}en;

typedef struct fich
{
    string nom;
    int nbr;
    string chemin;
}fichier;

class findex
{
private:
    en * t;
    int taille;
    int p;
public:
    findex(int x)
    {
        t=new en[x];
        p=0;
    }

    bool verif(string nom)
    {
        for(int i=0;i<p;i++)
        {
            if (t[i].mot==nom)
            {
                t[i].rec++;
                return true;
            }
        }
        return false;
    }

    void ajout(string mot,int pos,string chemin)
    {
        if(!verif(mot))
        {
            t[p].mot=mot;
            t[p].pos=pos;
            t[p].chemin=chemin;
            t[p].rec=1;
            t[p].stem=steming(mot,p);
            p++;
        }
    }

    int getp()
    {
        return p;
    }

    void save()
    {
        cout<<"save appele";
        QString CurrentDir = QDir::currentPath()+"\\Index.txt";
        FILE * resultat=fopen((char*)CurrentDir.toStdString().c_str(),"w+");
        string var;
        for(int i=0;i<p;i++)
                {
                    stringstream tmp;
                    tmp << t[i].pos;
                    stringstream tmp2;
                    tmp2 << t[i].rec;
                    var=t[i].mot+";"+tmp.str()+";"+tmp2.str()+"\n";
                    fputs((char*)var.c_str(),resultat);
                }
        fclose(resultat);
    }

    en* gett()
    {
        return t;
    }

    string upper(string strToConvert)
    {
        transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

        return strToConvert;
    }

    bool term(string mot,string term)
    {
        int x=term.length();
        if (x<mot.length())
        return (upper(mot.substr((mot.length()-x),term.length()))==term);
        else
            return false;
    }

    string remplace(string mot,string term1,string term2)
    {
        int x1=term1.length();
        return mot.replace(mot.length()-x1,x1,term2);
    }

    int m(string mot)
    {
        char* ch=(char*)mot.c_str();
        string voyelle="aeyuio";
        int v=0,m=0;
        for(int i=0;i<(mot.length()-1);i++)
        {
            if(voyelle.find(ch[i]))
                v++;
            else
            {
                if(v)
                {
                    v=0;
                    m++;
                }
            }
        }
        return m;
    }

    bool v(string mot,string term1,string term2)
    {
        char* ch=(char*) remplace(mot,term1,term2).c_str();
        string voyelle="aeyuio";
        int v=0,c=0;
        for(int i=0;i<(mot.length()-1);i++)
        {
            if(!voyelle.find(ch[i]))
            {
                c++;
                if(v)
                {
                    return true;
                }
            }
            else
            {
                if(v)
                {
                    return true;
                }
                if(c)
                {
                    c=0;
                    v++;
                }
            }
        }
    }

    string e1a(string mot)
    {
        if(term(mot,"SSES"))
            mot=remplace(mot,"sses","ss");
        else if(term(mot,"IES"))
            mot=remplace(mot,"ies","i");
        else if(term(mot,"SS"))
            ;
        else if(term(mot,"S"))
            mot=remplace(mot,"S","");
        return mot;
    }

    string e1b(string mot)
    {
        if((term(mot,"EED"))&&(m(mot)>0))
            mot=remplace(mot,"eed","ee");
        else if ((term(mot,"ED"))&&(v(mot,"ed","")))
            mot=remplace(mot,"ed","");
        else if ((term(mot,"ING"))&&(v(mot,"ing","")))
            mot=remplace(mot,"ing","");
        return mot;
    }

    string e1c(string mot)
    {
        if((term(mot,"Y"))&&(v(mot,"y","i")))
            remplace(mot,"y","i");
        return mot;
    }

    string e2(string mot)
    {
        if((term(mot,"ATIONAL"))&&(m(mot)>0))
            mot=remplace(mot,"ational","ate");
        else if((term(mot,"TIONAL"))&&(m(mot)>0))
            mot=remplace(mot,"tional","tion");
        else if((term(mot,"ENCI"))&&(m(mot)>0))
            mot=remplace(mot,"enci","ence");
        else if((term(mot,"ANCI"))&&(m(mot)>0))
            mot=remplace(mot,"anci","ance");
        else if((term(mot,"IZER"))&&(m(mot)>0))
            mot=remplace(mot,"izer","ize");
        else if((term(mot,"ABLI"))&&(m(mot)>0))
            mot=remplace(mot,"abli","able");
        else if((term(mot,"ALLI"))&&(m(mot)>0))
            mot=remplace(mot,"alli","al");
        else if((term(mot,"ENTLI"))&&(m(mot)>0))
            mot=remplace(mot,"entli","ent");
        else if((term(mot,"ELI"))&&(m(mot)>0))
            mot=remplace(mot,"eli","E");
        else if((term(mot,"OUSLI"))&&(m(mot)>0))
            mot=remplace(mot,"ousli","ous");
        return mot;
    }

    string e3(string mot)
    {
        if((term(mot,"ICATE"))&&(m(mot)>0))
            mot=remplace(mot,"icate","ic");
        else if((term(mot,"ATIVE"))&&(m(mot)>0))
            mot=remplace(mot,"ative","");
        else if((term(mot,"ALIZE"))&&(m(mot)>0))
            mot=remplace(mot,"alize","al");
        else if((term(mot,"ICITI"))&&(m(mot)>0))
            mot=remplace(mot,"iciti","ic");
        else if((term(mot,"ICAL"))&&(m(mot)>0))
            mot=remplace(mot,"ical","ic");
        else if((term(mot,"FUL"))&&(m(mot)>0))
            mot=remplace(mot,"full","");
        else if((term(mot,"NESS"))&&(m(mot)>0))
            mot=remplace(mot,"ness","");
        return mot;
    }

    string e4(string mot)
    {
        if((term(mot,"AL"))&&(m(mot)>1))
            mot=remplace(mot,"ational","");
        else if((term(mot,"TIONAL"))&&(m(mot)>1))
            mot=remplace(mot,"ance","");
        else if((term(mot,"ENCE"))&&(m(mot)>1))
            mot=remplace(mot,"ence","");
        else if((term(mot,"ER"))&&(m(mot)>1))
            mot=remplace(mot,"er","");
        else if((term(mot,"IC"))&&(m(mot)>1))
            mot=remplace(mot,"ic","");
        else if((term(mot,"ABLE"))&&(m(mot)>1))
            mot=remplace(mot,"able","");
        return mot;
    }

    string e5(string mot)
    {
        if((term(mot,"E"))&&(m(mot)>1))
            mot=remplace(mot,"e","");
        else if((term(mot,"E"))&&(m(mot)==1))
           ;
        else if((term(mot,"E"))&&(m(mot)>1))
              ;
        return mot;
    }

    string steming(string mot,int pos)
    {
        if(e1a(mot)!=mot)
               {
                   mot=e1a(mot);
                   t[p].etape+="  Etape 1-A";
               }
               if(e1b(mot)!=mot)
               {
                   mot=e1b(mot);
                   t[p].etape+="  Etape 1-B ";
               }
               if(e1c(mot)!=mot)
               {
                   mot=e1c(mot);
                   t[p].etape+="  Etape 1-C";
               }
               if(e2(mot)!=mot)
               {
                   mot=e2(mot);
                   t[p].etape+="  Etape 2";
               }
               if(e3(mot)!=mot)
               {
                   mot=e3(mot);
                   t[p].etape+="  Etape 3";
               }
               if(e4(mot)!=mot)
               {
                   mot=e4(mot);
                   t[p].etape+="  Etape 4";
               }
               if(e5(mot)!=mot)
               {
                   mot=e5(mot);
                   t[p].etape+="  Etape 5";
               }
        return mot;
    }
    // Indexation de fichier text à partir de son nom et le chemin ou il est stocké.
    void index(string nom,string chemin)
    {
        char c=0;
        int i=0,j=0;
        string var;
        int pos=0;
        size_t found=0;
        string exep="/*-+.²&\"'(-_=?§µ$£^¨<>+°;:,[]1234567890";
        FILE * index=fopen((chemin+nom).c_str(),"r");
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
                            found=exep.find(c);
                                if(found==string::npos)
                                {
                                    var+=c;
                                    //j++;
                                }
                            }
                        else
                        {
                            j++;
                            if(var.length()>3)
                            {
                                ajout(var,j,chemin+nom);
                            }
                            var="";
                            //j=0;
                        }
                    }
                }
                fclose(index);
            }
    }
};


#endif // INDEX_H
