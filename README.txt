	IN/IN:

Plus compliqué à programmer. Mais permet de faire des arrêts et démarrages brutaux.

	PHASE/ENABLE:

Plus simple mais ne permet pas d’actions brutales et rapides.

	FONCTIONS PRÊTES:

avancer(vitesse,delai);
reculer(vitesse,delai);
brake(delai);
rotationD(vitesse, delai);
rotationG(vitesse, delai);
arret(delai);

	VARIABLES MANIPULABLES:

vitesse => compris entre 0 et 255, PAS DE NOMBRE NÉGATIF (car c’est du 8 bit)
delai => en miniseconde

	À FAIRE:

-Tester le voltage de sortie du moteur pour pouvoir trouvé la vitesse max (pour 3V)
-Voir avec l’équipe l’utilité d’ajouter accélération brutale aux fonctions.
-Tester pour calibrer les temps de rotations VS angles.
-Programmer les futures fonctions pour les servomoteurs.
-Tester les distances VS temps pour calibrer le robot.
-Tester le code de la diode, ajouter des diodes pour aider à certains diagnostiques?