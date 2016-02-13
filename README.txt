	IN/IN:

Plus compliqué à programmer. Mais permet de faire des arrêts et démarrage brutaux.

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

vitesse => compris entre 0 et 255
delai => en miniseconde

	À FAIRE:

-Voir avec équipe utilité ajouté accélération brutale
-Tester pour calibrer les temps de rotations VS angles.
-Programmer les futures fonctions pour servomoteurs.
-Tester les distances VS temps pour calibrer le robot.
-Tester le code de la diode, ajouter des diodes pour aider à certains diagnostiques?