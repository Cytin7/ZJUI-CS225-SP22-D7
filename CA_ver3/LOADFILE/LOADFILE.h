#pragma once
// Multiple head file only include once

// Include libraries
#include <fstream>
#include <sstream>

// Include our head files
#include "../ListNode/ListNode.h"

string ReadLine(char* filename, int line);
int CountLines(char* filename);
string* split(string i);

string* get_birth(string i);
int LoadList(string filename, ListNode* List);
