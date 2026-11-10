#include "uincampus/regles.hpp"
#include "uincampus/saisie.hpp"
#include "uincampus/version.hpp"

#include <format>
#include <print>
#include <string>
#include <vector>

int main() {
  std::println("UIN-Campus {} — Calcul de la moyenne d'un étudiant\n",
               uin::version());

  const std::string nom = uin::lireTexte("Nom de l'étudiant : ");
  const int nbNotes = uin::lireEntier("Nombre de notes (1 à 30) : ", 1, 30);

  std::vector<double> notes;

  for (int i{1}; i <= nbNotes; ++i) {
    notes.push_back(uin::lireNote(std::format("   Note {} : ", i)));
  }

  double somme{0.0};

  for (double n : notes) {
    somme += n;
  }

  const double moyenne = somme / static_cast<double>(notes.size());
  const uin::Mention mention = uin::mentionPour(moyenne);

  std::println("\n{:-<40}", "");
  std::println("{:<20}{:>20}", "Étudiant", nom);
  std::println("{:<20}{:>20}", "Nombre de notes", notes.size());
  std::println("{:<20}{:>20.2f}", "Moyenne", moyenne);
  std::println("{:<20}{:>20}", "Mention", uin::libelle(mention));

  std::println("{:<20}{:>20}", "Décision",
               moyenne >= uin::seuilValidation ? "Validé" : "Non validé");

  std::println("{:-<40}", "");
}
