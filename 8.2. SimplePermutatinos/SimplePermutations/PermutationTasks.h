#pragma once
#include <iostream>
#include <vector>

using Permutation = std::vector<int>;

Permutation ReadPermutation(std::istream& input);
std::ostream& operator<<(std::ostream& os, const Permutation& p);

Permutation SolvePermutationEquation(const Permutation& A, const Permutation& B); // 1
void NextKPermutations(std::ostream& output, Permutation p, int K); // 2

std::vector<int> PermToInversionVector(const Permutation& p);  // 3
Permutation InversionVectorToPerm(const std::vector<int>& inv);

void JohnsonTrotter(std::ostream& output, int N);  // 4
void GenerateAllRecursive(std::ostream& output, int N);