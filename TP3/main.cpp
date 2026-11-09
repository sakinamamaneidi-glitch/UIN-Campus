#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

constexpr int NOTE_MIN = 0;
constexpr int NOTE_MAX = 20;
constexpr int NB_MENTIONS = 5;
constexpr int MAX_ETUDIANTS = 200;

enum class Mention {
    Ajourné,
    Passable,
    AssezBien,
    Bien,
    TresBien
};

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
        } catch (const std::exception&) {
            // Saisie invalide.
        }

        std::cout << "Erreur : entrez une note entre 0 et 20.\n";
    }
}

Mention mentionPour(double note) {
    if (note < 10) return Mention::Ajourné;
    if (note < 12) return Mention::Passable;
    if (note < 14) return Mention::AssezBien;
    if (note < 16) return Mention::Bien;
    return Mention::TresBien;
}

std::string libelle(Mention mention) {
    switch (mention) {
        case Mention::Ajourné: return "Ajourne";
        case Mention::Passable: return "Passable";
        case Mention::AssezBien: return "Assez bien";
        case Mention::Bien: return "Bien";
        case Mention::TresBien: return "Tres bien";
    }
    return "Inconnu";
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

    std::array<double, MAX_ETUDIANTS> notes{};
    std::array<int, NB_MENTIONS> effectifs{};

    double somme{};
    double minimum = NOTE_MAX;
    double maximum = NOTE_MIN;

    for (int i = 0; i < nombreEtudiants; ++i) {
        notes[static_cast<std::size_t>(i)] =
            lireNote("Note de l'etudiant " +
                     std::to_string(i + 1) + " : ");

        double note = notes[static_cast<std::size_t>(i)];

        somme += note;
        minimum = std::min(minimum, note);
        maximum = std::max(maximum, note);

        Mention mention = mentionPour(note);
        ++effectifs[static_cast<std::size_t>(mention)];
    }

    double moyenne =
        somme / static_cast<double>(nombreEtudiants);

    double sommeCarres{};

    for (int i = 0; i < nombreEtudiants; ++i) {
        double difference =
            notes[static_cast<std::size_t>(i)] - moyenne;
        sommeCarres += difference * difference;
    }

    double ecartType = std::sqrt(
        sommeCarres / static_cast<double>(nombreEtudiants));

    int admis = nombreEtudiants - effectifs[0];

    std::cout << "\n===== RESULTATS =====\n";
    std::cout << "UE : " << ue << '\n';
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Minimum : " << minimum << '\n';
    std::cout << "Maximum : " << maximum << '\n';
    std::cout << "Moyenne : " << moyenne << '\n';
    std::cout << "Ecart-type : " << ecartType << '\n';

    std::cout << "Admis : " << admis << " / "
              << nombreEtudiants << '\n';

    std::cout << "Pourcentage admis : "
              << 100.0 * admis / nombreEtudiants << "%\n";

    std::cout << "\n===== HISTOGRAMME =====\n";

    for (std::size_t i = 0; i < effectifs.size(); ++i) {
        Mention mention = static_cast<Mention>(i);

        std::cout << std::left << std::setw(12)
                  << libelle(mention) << " : "
                  << std::string(
                         static_cast<std::size_t>(effectifs[i]), '*')
                  << " (" << effectifs[i] << ")\n";
    }

    return 0;
}