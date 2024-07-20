// Pins pour le 74HC165
/*
const int brocheCharge = 8;    // Pin pour charger les données
const int brocheInhibit = 9;   // Pin pour désactiver l'horloge
const int brocheDonnees = 11;  // Pin pour lire les données
const int brocheHorloge = 12;  // Pin pour l'horloge

unsigned long valeursPins;      // Valeurs actuelles des registres
unsigned long anciennesValeursPins;   // Anciennes valeurs des registres

void setup() {
    Serial.begin(9600);

    pinMode(brocheCharge, OUTPUT);
    pinMode(brocheInhibit, OUTPUT);
    pinMode(brocheHorloge, OUTPUT);
    pinMode(brocheDonnees, INPUT);

    digitalWrite(brocheHorloge, LOW);
    digitalWrite(brocheCharge, HIGH);

    valeursPins = lireRegistresDecalage();
    afficherValeurs();
    anciennesValeursPins = valeursPins;
}

void loop() {
    valeursPins = lireRegistresDecalage();

    if (valeursPins != anciennesValeursPins) {
        afficherValeurs();
        anciennesValeursPins = valeursPins;
    }
}

unsigned long lireRegistresDecalage() {
    unsigned long valeurOctets = 0;

    digitalWrite(brocheInhibit, HIGH);
    digitalWrite(brocheCharge, LOW);
    delayMicroseconds(5);
    digitalWrite(brocheCharge, HIGH);
    digitalWrite(brocheInhibit, LOW);

    for (int i = 0; i < 8; i++) {  // Lire 8 bits
        valeurOctets |= (digitalRead(brocheDonnees) << (7 - i));
        
        digitalWrite(brocheHorloge, HIGH);
        delayMicroseconds(5);
        digitalWrite(brocheHorloge, LOW);
    }

    return valeurOctets;
}

void afficherValeurs() {
    Serial.println("*Valeurs des registres a decalage:*");

    for (int i = 0; i <= 7; i++) {
        Serial.print((valeursPins >> i) & 1);
        Serial.print(" ");
    }
    Serial.println();
}
*/

/*
const int brocheCharge = 8;    // Pin pour charger les données
const int brocheInhibit = 9;   // Pin pour désactiver l'horloge
const int brocheDonnees = 11;  // Pin pour lire les données
const int brocheHorloge = 12;  // Pin pour l'horloge

const int NOMBRE_REGISTRES = 2; // Nombre de registres de décalage 74HC165

unsigned long valeursPins;      // Valeurs actuelles des registres
unsigned long anciennesValeursPins;   // Anciennes valeurs des registres

void setup() {
    Serial.begin(9600);

    pinMode(brocheCharge, OUTPUT);
    pinMode(brocheInhibit, OUTPUT);
    pinMode(brocheHorloge, OUTPUT);
    pinMode(brocheDonnees, INPUT);

    digitalWrite(brocheHorloge, LOW);
    digitalWrite(brocheCharge, HIGH);

    valeursPins = lireRegistresDecalage();
    afficherValeurs();
    anciennesValeursPins = valeursPins;
}

void loop() {
    valeursPins = lireRegistresDecalage();

    if (valeursPins != anciennesValeursPins) {
        afficherValeurs();
        anciennesValeursPins = valeursPins;
    }
}

unsigned long lireRegistresDecalage() {
    unsigned long valeurOctets = 0;

    digitalWrite(brocheInhibit, HIGH);
    digitalWrite(brocheCharge, LOW);
    delayMicroseconds(5);
    digitalWrite(brocheCharge, HIGH);
    digitalWrite(brocheInhibit, LOW);

    for (int i = 0; i < 8 * NOMBRE_REGISTRES; i++) {  // Lire le nombre de bits en fonction du nombre de registres
        valeurOctets <<= 1;  // Décale à gauche pour faire de la place pour le nouveau bit
        valeurOctets |= digitalRead(brocheDonnees);  // Lit le bit actuel et l'ajoute au registre
        digitalWrite(brocheHorloge, HIGH);
        delayMicroseconds(5);
        digitalWrite(brocheHorloge, LOW);
    }

    return valeurOctets;
}

void afficherValeurs() {
    Serial.println("*Valeurs des registres à décalage:*");

    for (int i = 0; i <= 8 * NOMBRE_REGISTRES - 1; i++) {  // Afficher du bit le plus significatif au moins significatif
        Serial.print((valeursPins >> i) & 1);
        Serial.print(" ");
    }
    Serial.println();
}
*/


const int brocheCharge = 8;    // Pin pour charger les données
const int brocheInhibit = 9;   // Pin pour désactiver l'horloge
const int brocheDonnees = 11;  // Pin pour lire les données
const int brocheHorloge = 12;  // Pin pour l'horloge

const int NOMBRE_REGISTRES = 3; // Nombre de registres de décalage 74HC165

unsigned long valeursPins;      // Valeurs actuelles des registres
unsigned long anciennesValeursPins;   // Anciennes valeurs des registres
int PIR = 20;
int LED = 13;
void setup() {
    Serial.begin(9600);  // Initialise la communication série

    // Configuration des broches en entrée/sortie
    pinMode(brocheCharge, OUTPUT);
    pinMode(brocheInhibit, OUTPUT);
    pinMode(brocheHorloge, OUTPUT);
    pinMode(brocheDonnees, INPUT);
pinMode(PIR,INPUT);
pinMode(LED,OUTPUT);
    digitalWrite(brocheHorloge, LOW);   // Initialise l'horloge à basse tension
    digitalWrite(brocheCharge, HIGH);   // Charge les données à l'état haut initial

    valeursPins = lireRegistresDecalage();  // Lit les valeurs initiales des registres
    afficherValeurs();  // Affiche les valeurs initiales lues
    anciennesValeursPins = valeursPins;  // Initialise les anciennes valeurs
}

void loop() {
    valeursPins = lireRegistresDecalage();  // Lit les nouvelles valeurs des registres
if ((valeursPins >> PIR)&1) digitalWrite(LED,HIGH);
else digitalWrite(LED,LOW);
    // Vérifie s'il y a eu un changement dans les valeurs des registres
    if (valeursPins != anciennesValeursPins) {
        afficherValeurs();  // Affiche les nouvelles valeurs si elles ont changé
        anciennesValeursPins = valeursPins;  // Met à jour les anciennes valeurs
    }
}

// Fonction pour lire les valeurs des registres à décalage
unsigned long lireRegistresDecalage() {
    unsigned long valeurOctets = 0;  // Initialise la valeur à retourner

    digitalWrite(brocheInhibit, HIGH);  // Désactive l'horloge pour permettre la lecture
    digitalWrite(brocheCharge, LOW);    // Charge les données pour la lecture
    delayMicroseconds(5);               // Attente courte pour stabiliser

    digitalWrite(brocheCharge, HIGH);   // Relâche la charge des données
    digitalWrite(brocheInhibit, LOW);   // Active l'horloge pour commencer la lecture

    // Boucle pour lire les bits des registres
    for (int i = 0; i < 8 * NOMBRE_REGISTRES; i++) {
        valeurOctets <<= 1;  // Décale à gauche pour faire de la place pour le nouveau bit
        valeurOctets |= digitalRead(brocheDonnees);  // Lit le bit actuel et l'ajoute au registre
        digitalWrite(brocheHorloge, HIGH);  // Pulse l'horloge pour avancer dans les bits
        delayMicroseconds(5);               // Attente courte entre les impulsions d'horloge
        digitalWrite(brocheHorloge, LOW);   // Baisse l'horloge pour finir l'impulsion
    }

    return valeurOctets;  // Retourne la valeur lue depuis les registres
}

// Fonction pour afficher les valeurs lues des registres
void afficherValeurs() {
    Serial.println("*Valeurs des registres à décalage :*");

    // Boucle pour afficher du bit le plus significatif au moins significatif
    for (int i = 0; i <= 8 * NOMBRE_REGISTRES - 1; i++) {
        Serial.print((valeursPins >> i) & 1);  // Affiche chaque bit (0 ou 1)
        Serial.print(" ");                     // Ajoute un espace pour la lisibilité
    }
    Serial.println();  // Termine la ligne après l'affichage de tous les bits
}

/*
#include <MaBibliotheque.h>

// Définissez les broches que vous utilisez
const int brocheCharge = 8;
const int brocheInhibit = 9;
const int brocheDonnees = 11;
const int brocheHorloge = 12;
const int NOMBRE_REGISTRES = 3;

// Créez une instance de MaBibliotheque
MaBibliotheque maBibliotheque(brocheCharge, brocheInhibit, brocheDonnees, brocheHorloge, NOMBRE_REGISTRES);

void setup() {
    Serial.begin(9600);
    maBibliotheque.begin();  // Initialise la bibliothèque comme précédemment
}

void loop() {
    // Lecture des nouvelles valeurs des registres
    unsigned long nouvellesValeurs = maBibliotheque.lireRegistresDecalage();

    // Obtenez les anciennes valeurs
    unsigned long anciennesValeurs = maBibliotheque.getAnciennesValeursPins();

    // Vérifiez s'il y a eu un changement dans les valeurs des registres
    if (nouvellesValeurs != anciennesValeurs) {
        // Affichez les nouvelles valeurs si elles ont changé
        Serial.println("Changement détecté dans les valeurs des registres :");
        maBibliotheque.afficherValeurs();

        // Mettez à jour les anciennes valeurs
        maBibliotheque.setAnciennesValeursPins(nouvellesValeurs);
    }

    delay(100); // Attente pour éviter la lecture trop rapide des registres
}

*/
