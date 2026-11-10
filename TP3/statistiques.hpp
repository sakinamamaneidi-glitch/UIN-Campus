#pragma once

#include <array>
#include <string>
#include <vector>

constexpr int NB_MENTIONS = 5;

enum class Mention {
    Ajourne,
    Passable,
    AssezBien,
    Bien,
    TresBien
};

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    double ecartType{};
    int admis{};
    std::array<int, NB_MENTIONS> effectifs{};
};

Mention mentionPour(double note);

std::string libelle(Mention mention);

Statistiques calculerStatistiques(
    const std::vector<double>& notes
);
