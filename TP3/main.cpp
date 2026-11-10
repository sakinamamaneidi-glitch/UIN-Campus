#include "statistiques.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

constexpr int NOTE_MIN = 0;
constexpr int NOTE_MAX = 20;
constexpr int MAX_ETUDIANTS = 200;

double lireNote(const std::string& message) {
    while (true) {
        std::cout << message;

        std::string saisie;
        std::cin >> saisie;

        std::replace(saisie.begin(), saisie.end(), ',', '.');

        try {
            std::size_t position{};
            double note = std::stod(saisie, &position);

            if (position == saisie.size() &&
                note >= NOTE_MIN && note <= NOTE_MAX) {
                return note;
            }
        } catch (...) {
        }

        std::cout << "Erreur : entrez une note entre 0 et 20.\n";
    }
}

int main() {
    std::string ue;
    int nombreEtudiants{};

    std::cout << "Nom de l'UE : ";
    std::getline(std::cin >> std::ws, ue);

    while (true) {
        std::cout << "Nombre d'etudiants (1-200) : ";

        if (std::cin >> nombreEtudiants &&
            nombreEtudiants >= 1 &&
            nombreEtudiants <= MAX_ETUDIANTS) {
            break;
        }

        std::cout << "Nombre invalide.\n";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::vector<double> notes;

    for (int i = 0; i < nombreEtudiants; ++i) {
        notes.push_back(
            lireNote("Note de l'etudiant " +
                     std::to_string(i + 1) + " : ")
        );
    }

    const Statistiques resultat = calculerStatistiques(notes);

    std::cout << "\n===== RESULTATS =====\n";
    std::cout << "UE : " << ue << '\n';
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Minimum : " << resultat.minimum << '\n';
    std::cout << "Maximum : " << resultat.maximum << '\n';
    std::cout << "Moyenne : " << resultat.moyenne << '\n';
    std::cout << "Ecart-type : " << resultat.ecartType << '\n';

    std::cout << "Admis : " << resultat.admis << " / "
              << nombreEtudiants << '\n';

    std::cout << "Pourcentage admis : "
              << 100.0 * resultat.admis / nombreEtudiants
              << "%\n";

    std::cout << "\n===== HISTOGRAMME =====\n";

    for (std::size_t i = 0; i < resultat.effectifs.size(); ++i) {
        Mention mention = static_cast<Mention>(i);

        std::cout << std::left << std::setw(12)
                  << libelle(mention) << " : "
                  << std::string(
                         static_cast<std::size_t>(
                             resultat.effectifs[i]), '*')
                  << " (" << resultat.effectifs[i] << ")\n";
    }

    return 0;
}
    
