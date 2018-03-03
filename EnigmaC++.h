//
// Created by jimbo on 01/03/2018.
//

#ifndef ENIGMAC_V2_ENIGMAC_H
#define ENIGMAC_V2_ENIGMAC_H

#endif //ENIGMAC_V2_ENIGMAC_H

#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Plugboard {
public:
    Plugboard() = default;

    void Swap(unsigned long long int a, unsigned long long int b);

    int GetIndex(int x);

private:
    string _alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string _pattern = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

class Reflector {
public:
    Reflector() = default;

    explicit Reflector(string pattern);

    int GetIndex(int x);

private:
    string _alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string _pattern;
};

class Rotor {
public:
    Rotor() = default;

    Rotor(tuple<string, int, int>, int, int);

    bool IsNotched() { return (_reelPosition == _notch1 || _reelPosition == _notch2); };

    void Rotate() { _reelPosition = (_reelPosition + 1) % 26; }

    int Transpose(int, bool);

private:
    string _pattern;
    string _alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int _notch1 = 0;
    int _notch2 = 0;
    int _reelPosition = 0;
    int _rsl = 0;

    int GetIndex(int, bool);
};

class EnigmaMachine {
public:

    EnigmaMachine() = default;

    int KeyPress(int keyValue);

    bool SetupEnigmaMachine(string setupValues);

    string Transpose_CipherText(string cipherText);

private:
    const string _alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const tuple<string, int, int> _rotor_Blank = tuple<string, int, int>("ABCDEFGHIJKLMNOPQRSTUVWXYZ", -99, -99);
    const tuple<string, int, int> _rotor_I = tuple<string, int, int>("EKMFLGDQVZNTOWYHXUSPAIBRCJ", 16, -99);
    const tuple<string, int, int> _rotor_II = tuple<string, int, int>("AJDKSIRUXBLHWTMCQGZNPYFVOE", 4, -99);
    const tuple<string, int, int> _rotor_III = tuple<string, int, int>("BDFHJLCPRTXVZNYEIWGAKMUSQO", 21, -99);
    const tuple<string, int, int> _rotor_IV = tuple<string, int, int>("ESOVPZJAYQUIRHXLNFTGKDCMWB", 9, -99);
    const tuple<string, int, int> _rotor_V = tuple<string, int, int>("VZBRGITYUPSDNHLXAWMJQOFECK", 25, -99);
    const tuple<string, int, int> _rotor_VI = tuple<string, int, int>("JPGVOUMFYQBENHZRDKASXLICTW", 25, 12);
    const tuple<string, int, int> _rotor_VII = tuple<string, int, int>("NZJHGRCXMYSWBOUFAIVLPEKQDT", 25, 12);
    const tuple<string, int, int> _rotor_VIII = tuple<string, int, int>("FKQHTLXOCBJSPDZRAMEWNIUYGV", 25, 12);
    const tuple<string, int, int> _rotor_b = tuple<string, int, int>("LEYJVCNIXWPBQMDRTAKZGFUHOS", -99, -99);
    const tuple<string, int, int> _rotor_g = tuple<string, int, int>("FSOKANUERHMBTIYCWLQPZXVGJD", -99, -99);
    const string _reflector_Blank = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string _reflector_A = "EJMZALYXVBWFCRQUONTSPIKHGD";
    const string _reflector_B = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    const string _reflector_C = "FVPJIAOYEDRZXWGCTKUQSBNMHL";
    const string _reflector_b = "ENKQAUYWJICOPBLMDXZVFTHRGS";
    const string _reflector_c = "RDOBJNTKVEHMLFCWZAXGYIPSUQ";
    Rotor _rotor0;
    Rotor _rotor1;
    Rotor _rotor2;
    Rotor _rotor3;
    Reflector _reflector;
    Plugboard _plugboard;
    bool _readyToDecode = false;

    int GetLampValue(int keyValue);

    Plugboard Create_Plugboard(string plugboardLinks);

    Reflector Create_Reflector(char reflector);

    Rotor Create_Rotor(char reel, char ring, char pstn);

    void RotateTheRotors();
};

