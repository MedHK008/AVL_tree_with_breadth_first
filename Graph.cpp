#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// Constructeur
N_Graphe::Noeud::Noeud(char val)
    : valeur(val), couleur(white), niveau(-1), fils(new vector<Noeud*>) {
}

// Destructeur
N_Graphe::Noeud::~Noeud()
{
    delete fils;
}


// Constructeur
N_Graphe::N_Graphe(char sommet)
{
    tete = new Noeud(sommet);
    tete->niveau = 0;
    file = new queue<Noeud*>;
    file->push(tete);
}

// Destructeur
N_Graphe::~N_Graphe()
{
    while (!file->empty()) {
        delete file->front();
        file->pop();
    }
    delete file;
}

// Ajouter un noeud
void N_Graphe::ajouterNoeud(char pere, char valeur) {
    // Initialisation
    Noeud* temp = nullptr;
    Noeud* pere1 = nullptr;

    // Vérifier si le noeud existe déjà
    std::queue<Noeud*> tempQueue;
    while (!file->empty()) {
        Noeud* current = file->front();
        file->pop();
        tempQueue.push(current);
        if (current->valeur == valeur) {
            temp = current;
        }
    }

    // Si le noeud n'existe pas, créer un nouveau noeud
    if (!temp) {
        temp = new Noeud(valeur);
    }

    // Restaurer la file originale
    while (!tempQueue.empty()) {
        Noeud* current = tempQueue.front();
        tempQueue.pop();
        file->push(current);

        if (current->valeur == pere) {
            pere1 = current;
        }
    }

    // Lier le noeud au parent, s'il existe
    if (pere1) {
        pere1->fils->push_back(temp);
        temp->fils->push_back(pere1);
		file->push(temp);
    }
    else if (pere == '0') {
        tete = temp;
        file->push(temp);
    }
    else {
        std::cout << "Parent non trouvé." << std::endl;
    }
}

void N_Graphe::supprimerNoeud(char valeur)
{
}

void N_Graphe::afficherChemin(char S)
{
    if (file->empty()) {
        cout << "File vide. Aucun chemin disponible." << endl;
        return;
    }

    queue<Noeud*> file2;
    Noeud* courant = nullptr;

    while (!file->empty()) {
        if (file->front()->valeur == S) {
            courant = file->front();
        }
        file2.push(file->front());
        file->pop();
    }

    *file = file2;

    if (courant == nullptr || pere.find(courant) == pere.end()) {
        cout << "Noeud non trouvé." << endl;
        return;
    }

    cout << courant->valeur;
    while (pere[courant] != nullptr) {
        courant = pere[courant];
        cout << " -> " << courant->valeur;
    }
    cout << endl;
}

void N_Graphe::parcoursLargeur()
{
    if (!tete) {
        cout << "Graphe vide." << endl;
        return;
    }

    queue<Noeud*> file2;
    pere[tete] = nullptr;

    file2.push(tete);
    tete->couleur = gray;

    while (!file2.empty()) {
        Noeud* courant = file2.front();
        courant->couleur = black;
        file2.pop();

        for (Noeud* fils : *(courant->fils)) {
            if (fils->couleur == white) {
				cout << fils->valeur << " ";
                fils->couleur = gray;
                fils->niveau = courant->niveau + 1;
                pere[fils] = courant;
                file2.push(fils);
            }
        }
    }
}