typedef struct liste_couleurs {                
	struct couleur{
	int rouge;
	int vert;
	int bleu;
	int alpha;
	}*couleur;
   struct liste_couleurs *suivant;
}liste_couleurs;

void insertion (struct couleur *, struct liste_couleurs *);                
void parcours (struct liste_couleurs *);