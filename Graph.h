#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <vector>
using namespace std;
enum color { white, gray, black };

class N_Graphe
{
private:
	struct Noeud
	{
		char valeur;
		color couleur;
		int niveau;
		vector<Noeud*>* fils;
	public:
		Noeud(char val);
		~Noeud();
	};
	Noeud* tete;
	queue<Noeud*> *file;
	map<Noeud*, Noeud*> pere;
public:
	N_Graphe(char sommet);
	~N_Graphe();
	void ajouterNoeud(char pere,char valeur);
	void supprimerNoeud(char valeur);
	void afficherChemin(char S);
	void parcoursLargeur();

};