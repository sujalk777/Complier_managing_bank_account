#include "entry.h"
using namespace std;

SymEntry::SymEntry() {
    key = "";
    val = nullptr;
    left = nullptr;
    right = nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational* v) {
    key = k;
    val = v;
    left = nullptr;
    right = nullptr;
}

SymEntry::~SymEntry() {
    delete val;
}
