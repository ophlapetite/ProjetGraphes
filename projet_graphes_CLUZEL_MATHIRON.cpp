
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

const int N=100;    // variable pour gérer la taille des tableaux
int nb_aretes;
int nb_sommets;
int adj[N][N];    //matrice d'adjacence
int degre[N];     // tableau des degrés des sommets du graphe
int centre[N];    // tableau des numéro de centre des sommets du graphe
int d;            //variable qui contiendra la valeur de la dégénérescence du graphe
int nbChromatique; // variable qui contiendra le nombre chromatique


//fonction qui initialise le tableau des degrés des sommets
void initdegre(){
  //on initialise un compteur à 0 qui va compter le nombre de 1 dans chaque ligne
  int compt=0;
  // on parcours la matrice
  for(int i=0;i<nb_sommets;i++)
  {
    // on remet le compteur à 0 à la fin de chaque ligne
    compt=0;
    for(int j=0;j<nb_sommets;j++)
      {
        // si la case contient 1, on incrémente le compteur
        if(	adj[i][j]==1)
          {
            compt++;
          }
      }
    //à la fin de la ligne i,on peut stocker la valeur du compteur dans le tableau de degré
    degre[i]=compt;
  }
}


//fonction qui va initialiser nb_aretes, nb_sommets et la matrice d'adjacence
void lirereseau(string nom) {

    //on ouvre le fichier
    ifstream input("./"+nom);

    //si l'ouverture du fichier a réussit
    if (input.is_open()) {

        string ignored;
        getline(input, ignored); // Nous n'avons pas besoin de la 1ere ligne


        // La deuxieme ligne :
        input >> ignored;   // Commence par '%'
        input >> nb_aretes;  // Suivi du nombre de liens
        input >> nb_sommets; // Suivi du nombre de noeuds
        input >> ignored;   // Suivi d'un nombre dont nous n avons pas besoin


    		//on initialise la matrice d'adjacence avec des 0
    		for(int i=0; i<nb_sommets;i++){
    			for(int j=0; j<nb_sommets;j++){
    			adj[i][j]=adj[j][i]=0;
    			}
    		}

        // on prépare des variables temporaires qui récupèreront les valeurs
    		int sommetA=0;
    		int sommetB=0;

        // Chaque ligne suivante decrit une arete reliant deux sommets
        for (int i = 0; i < nb_aretes; i++) {
  			      // on récupère les valeurs
              input >> sommetA;
              input >> sommetB;
        			// on décrémente car notre tableau commence à 0 et dans les fichiers les sommets commencent à 1
        			sommetA=sommetA-1;
        			sommetB=sommetB-1;
        			// on remplit la matrice d'adjacence
        			adj[sommetA][sommetB]=adj[sommetB][sommetA]=1;
        }
        // on appelle la fonction init degré qui va initialiser les degrés à partir de la matrice
        initdegre();
        //on ferme le fichier
        input.close();

    // si le fichier ne s'est pas ouvert on affiche un message d'erreur
    } else {
        cout << "L ouverture du fichier " << nom << " a echoué.\n";
        exit(1);
    }

}



    // fonction qui cherche si un tableau est vide (=rempli de zéros) (pour la matrice d'adjacence)
    bool isVide(int tab[][N]){
      // on parcours la matrice
      for(int i=0;i<nb_sommets;i++)
      {
        for (int j=0; j<nb_sommets; j++)
        {
          //si la case contient autre chose que 0, la matrice n'est pas vide
          if(tab[i][j]!=0)
          {
            return false;
          }

        }
      }
      return true;
    }


    // fonction qui cherche s'il existe dans le tableau des valeurs inférieures ou égales à un entier k
    bool exist(int tab[], int k){
      //on parcourt le tableau
      for(int i=0;i<nb_sommets;i++)
      {
        //si la case contient un entier <=k, on renvoit vrai
        if(tab[i]<=k && tab[i]>0)
        {
          return true;
        }
      }
      return false;
    }



    // fonction qui supprime un sommet i de la matrice d'adjacence
    void supprimeSommet(int i){

      //on supprime la ligne et la colonne correspondants à ce sommet en mettant les valeurs à 0
      for(int j=0; j<nb_sommets;j++)
      {
        adj[i][j]=adj[j][i]=0;
      }

    }


    //fonction qui calcule la dégénérescence
    int degenerescence(){
    // on initialise k à 0
    int k=0;

    //tant qu'il reste des sommets on fait
    while(!isVide(adj)){
        // on incrémente k
        k++;
        //tant qu'il existe des sommets de degré <=k
        while(exist(degre,k))
        {
            // on parcours la liste de degrés
            for(int i=0; i<nb_sommets;i++){
              //si le degré du sommet est <=k
              if (degre[i]<=k && degre[i]>0)
              {
                //on note son centre qui est égal au degré au moment où il est supprimé
                centre[i]=degre[i];
                // on supprime le sommet de la matrice d'adjacence
                supprimeSommet(i);
              }
            }
            //on recalcule les degrés avec la nouvelle matrice d'adjacence
            initdegre();
        }

    }
    // on affiche la degenerescence
    cout<<"degenerescence : "<<k<<endl;
    cout << endl;
    //on retourne sa valeur
    return k;
    }

//fonction qui affiche la matrice d'adjacence
void afficheMatrice(){
	cout<< "Matrice d'adjacence:"<<endl;
	for(int i=0;i<nb_sommets;i++)
		  {
			for(int j=0;j<nb_sommets;j++)
			  {cout<< adj[i][j];}
			cout<<endl;
		  }
  cout << endl;
}

//fonction qui affiche les sommets du graphe et les sommets auquel ils sont reliés
void afficheSommets(){
	for(int i=0;i<nb_sommets;i++)
	  { cout << "sommet " << i << " relié aux sommet(s): ";
		for(int j=0;j<nb_sommets;j++)
		  if(adj[i][j]) cout << j << " ";
		cout << endl;
	  }
  cout << endl;
}


//fonction qui affiche le tableau des degré des sommets
void afficheDegre(){
	for(int i=0; i<nb_sommets;i++)
  {
	   cout<<"sommet"<<i<<": degré"<< degre[i]<<endl;
	}
  cout << endl;
}

//fonction qui affiche le tableau des numéro de centre de chaque sommet
void afficheCentre(){
  for(int i=0; i<nb_sommets;i++)
  {
    cout<<"sommet "<<i<<": centre"<< centre[i]<<endl;
  }
  cout << endl;
}


bool convient2(int x, int c) // pour DSATUR... attention à bien faire aller i jusqu'à n et non s'arrêter à x
{
     for(int i=0;i<nb_sommets;i++)
      if(adj[x][i] && (couleur2[i]==c)) return false;
     return true;
}

int centreMax(int centretmp[]) // retourne le sommet de centre max d'un graphe
{

  int maxCENTRE=-1,smax=0;
  for(int i=0;i<nb_sommets;i++)
  if(centretmp[i]>maxCENTRE)
   { maxCENTRE=centretmp[i];  smax=i;}
   //cout << "sommet " << smax << " choisi" << endl;
   centretmp[i]=-1;
  return smax;
}

// fonction pour l'estimation du nombre chromatique par l'algorithme DSATUR
int DSATUR()
{
  int centre_tmp[N];
  for(int i=0;i<nb_sommets;i++){
   centre_tmp[i]=centre[i];
 }
  int couleur1[N], couleur2[N], DSAT[N], Degre[N];
  int nb=0,c,x,cmax=0;
  for(int i=0;i<nb_sommets;i++)
  {
    couleur2[i]=0; DSAT[i]=0; Degre[i]=0;
    for(int j=0;j<nb_sommets;j++)
     if(adj[i][j]) Degre[i]++;
  }

  while(nb<nb_sommets)  // tant qu'on a pas colorié tous les sommets
  {
    c=1;
    x=centreMax(centre_tmp); // on choisit le sommet de DSAT max non encore colorié
    while(!convient2(x,c)) c++; // on cherche la plus petite couleur disponible pour ce sommet
    for(int j=0; j<nb_sommets;j++) // mise à jour des DSAT
     {
       if(adj[x][j] && convient2(j,c)) DSAT[j]++; // j n'avait aucun voisin colorié c,on incrémente donc son DSAT
     }
    couleur2[x]=c;
    if(cmax<c) cmax=c;
    nb++;
  }
  cout << "DSAT: coloration en " << cmax << " couleurs " << endl;
       for(int i=0;i<nb_sommets;i++) cout << "couleur de " << i << " : " << couleur2[i] << endl;
  return cmax;
}

int main()
{
	 //on lit le réseau dont le nom est passé en paramètre
	 lirereseau("test_arbre");
   afficheMatrice();
   afficheSommets();
   afficheDegre();
   d=degenerescence();
   afficheCentre();


 return 0;
}
