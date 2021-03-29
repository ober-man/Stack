#pragma once

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cstddef>
#include<windows.h>
#include<cassert>
#include<cmath>

#define UNSAFE // turn off safety
#include"enums.h"

long long RandomBig();
void SetColor(ConsoleColor text, ConsoleColor background);

const bool FAIL = false;
const bool SUCCESS = true;
const int LEN = 12;
typedef long long hash_t;

#include"stack_class.h"
#include"functions.h"
