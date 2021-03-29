#pragma once
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <Windows.h>
int power(int a, int b, int n);
template <typename T>
T modpow(T base, T exp, T modulus);
int mul(int a, int b, int n);
void crypt(int p, int g, int x, std::string inFileName, std::string outFileName);
void decrypt(int p, int x, std::string inFileName, std::string outFileName);