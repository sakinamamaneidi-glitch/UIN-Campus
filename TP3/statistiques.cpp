#include "statistiques.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

Mention mentionPour(double note) {
    if (note < 10) return Mention::Ajourne;
    if (note < 12) return Mention::Passable;
    if (note < 14) return Mention::AssezBien;
    if (note < 16) return Mention::Bien;
    return Mention::TresBien;
}

std::string libelle(Mention mention) {
    switch (mention) {
        case Mention::Ajourne: return "Ajourne";
        case Mention::Passable: return "Passable";
        case Mention::AssezBien: return "Assez bien";
        case Mention::Bien: return "Bien";
        case Mention::TresBien: return "Tres bien";
    }
    return "Inconnu";
}

Statistiques calculerStatistiques(
    const std::vector<double>& notes
) {
    if (notes.empty()) {
        throw std::invalid_argument("Aucune note fournie.");
    }

    Statistiques resultat{};

    resultat.minimum = *std::min_element(notes.begin(), notes.end());
    resultat.maximum = *std::max_element(notes.begin(), notes.end());

    double somme{};

    for (double note : notes) {
        somme += note;

        Mention mention = mentionPour(note);
        ++resultat.effectifs[static_cast<std::size_t>(mention)];
    }

    resultat.moyenne = somme / static_cast<double>(notes.size());

    double sommeCarres{};

    for (double note : notes) {
        double difference = note - resultat.moyenne;
        sommeCarres += difference * difference;
    }

    resultat.ecartType = std::sqrt(
        sommeCarres / static_cast<double>(notes.size())
    );

    resultat.admis = static_cast<int>(notes.size())
                     - resultat.effectifs[0];

    return resultat;
}
