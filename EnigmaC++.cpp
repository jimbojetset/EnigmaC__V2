//
// Created by jimbo on 01/03/2018.
//

#include "EnigmaC++.h"

using namespace std;

void Plugboard::Swap(unsigned long long int a, unsigned long long int b) {
    if (a != b && _alpha[a] == _pattern[a] && _alpha[b] == _pattern[b]) {
        _pattern = _pattern.replace(a, 1, "~");
        _pattern.replace((b), 1, string(1, _alpha[a]));
        _pattern.replace((a), 1, string(1, _alpha[b]));
    }
}

int Plugboard::GetIndex(int x) {
    return static_cast<int>(_pattern.find(_alpha[x], 0));
}

Reflector::Reflector(string pattern) {
    _pattern = std::move(pattern);
}

int Reflector::GetIndex(int x) {
    return static_cast<int>(_pattern.find(_alpha[x], 0));
}

Rotor::Rotor(tuple<string, int, int> rotor, int ringPos, int startPos) {
    _pattern = get<0>(rotor);
    _notch1 = get<1>(rotor);
    _notch2 = get<2>(rotor);
    _reelPosition = startPos;
    _rsl = ringPos;
}

int Rotor::Transpose(int x, bool dir) {
    x = (x + _reelPosition - _rsl + 26) % 26;
    int t = GetIndex(x, dir) - _reelPosition + _rsl + 26;
    return t % 26;
}

int Rotor::GetIndex(int x, bool dir) {
    if (dir)
        return static_cast<int>(_alpha.find(_pattern[x]));
    else
        return static_cast<int>(_pattern.find(_alpha[x]));
}

int EnigmaMachine::KeyPress(int keyValue) {
    if (_readyToDecode) {
        RotateTheRotors();
        int lampValue = GetLampValue(keyValue);
        return lampValue;
    }
    return -99;
}

bool EnigmaMachine::SetupEnigmaMachine(string setupValues) {
    _readyToDecode = false;
    stringstream ss(setupValues);
    vector<string> result;
    while (ss.good()) {
        string substr;
        getline(ss, substr, ':');
        result.push_back(substr);
    }
    if (result.size() == 5) {
        char reflector = result[0][0];
        string reel = result[1];
        string ring = result[2];
        for (char &c : ring) c = static_cast<char>(toupper(c));
        string pstn = result[3];
        for (char &c : pstn) c = static_cast<char>(toupper(c));
        string plugboard = result[4];
        for (char &c : plugboard) c = static_cast<char>(toupper(c));
        _reflector = Create_Reflector(reflector);
        _rotor0 = Create_Rotor(reel[0], ring[0], pstn[0]);
        _rotor1 = Create_Rotor(reel[1], ring[1], pstn[1]);
        _rotor2 = Create_Rotor(reel[2], ring[2], pstn[2]);
        _rotor3 = Create_Rotor(reel[3], ring[3], pstn[3]);
        _plugboard = Create_Plugboard(plugboard);
        _readyToDecode = true;
    }
    return _readyToDecode;
};

string EnigmaMachine::Transpose_CipherText(string cipherText) {
    if (_readyToDecode && !cipherText.empty()) {
        stringstream plainText;
        for (char &keyValue : cipherText) {
            auto key = static_cast<int>(_alpha.find(keyValue, 0));
            if (key > -1) {
                int lampValue = KeyPress(key);
                plainText << _alpha.at(static_cast<unsigned long long int>(lampValue));
            } else
                plainText << ' ';
        }
        return plainText.str();
    }
    return "ERROR";

}

int EnigmaMachine::GetLampValue(int keyValue) {
    int val = _plugboard.GetIndex(keyValue);
    val = _rotor3.Transpose(val, true);
    val = _rotor2.Transpose(val, true);
    val = _rotor1.Transpose(val, true);
    val = _rotor0.Transpose(val, true);
    val = _reflector.GetIndex(val);
    val = _rotor0.Transpose(val, false);
    val = _rotor1.Transpose(val, false);
    val = _rotor2.Transpose(val, false);
    val = _rotor3.Transpose(val, false);
    int lampValue = _plugboard.GetIndex(val);
    return lampValue;
}

Plugboard EnigmaMachine::Create_Plugboard(string plugboardLinks) {
    _plugboard = Plugboard();
    stringstream ss(plugboardLinks);
    vector<string> result;
    while (ss.good()) {
        string substr;
        getline(ss, substr, '-');
        result.push_back(substr);
    }
    if (!result.empty()) {
        auto itr = result.begin();
        while (itr != result.end()) {
            string str = *itr;
            _plugboard.Swap(static_cast<int>(_alpha.find(str.at(0))), static_cast<int>(_alpha.find(str.at(1))));
            itr++;
        }
    }
    return _plugboard;
}

Reflector EnigmaMachine::Create_Reflector(char reflector) {
    switch (reflector) {
        case '-':
            return Reflector(_reflector_Blank);
        case 'A':
            return Reflector(_reflector_A);
        case 'B':
            return Reflector(_reflector_B);
        case 'C':
            return Reflector(_reflector_C);
        case 'b':
            return Reflector(_reflector_b);
        case 'c':
            return Reflector(_reflector_c);
        default:
            return Reflector();
    }
}

Rotor EnigmaMachine::Create_Rotor(char reel, char ring, char pstn) {
    switch (reel) {
        case '-':
            return Rotor(_rotor_Blank, 0, 0);
        case '1':
            return Rotor(_rotor_I, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        case '2':
            return Rotor(_rotor_II, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        case '3':
            return Rotor(_rotor_III, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        case '4':
            return Rotor(_rotor_IV, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        case '5':
            return Rotor(_rotor_V, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        case '6':
            return Rotor(_rotor_VI, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        case '7':
            return Rotor(_rotor_VII, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        case '8':
            return Rotor(_rotor_VIII, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        case 'b':
            return Rotor(_rotor_b, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        case 'g':
            return Rotor(_rotor_g, static_cast<int>(_alpha.find(ring, 0)), static_cast<int>(_alpha.find(pstn, 0)));
        default:
            return Rotor();
    }
}

void EnigmaMachine::RotateTheRotors() {
    if (_rotor2.IsNotched()) {
        _rotor1.Rotate();
        _rotor2.Rotate();
    } else if (_rotor3.IsNotched())
        _rotor2.Rotate();
    _rotor3.Rotate();
}

int main(int argc, char *argv[]) {
    string args = "B:-368:-AHM:-UZV:AN-EZ-HK-IJ-LR-MQ-OT-PV-SW-UX$KEPV MM E NCAS GDQYGYW";
    if (argc > 1)
        args = argv[1];
    istringstream stream(args);
    string settings;
    string cipherText;
    getline(stream, settings, '$');
    getline(stream, cipherText, '\n');
    EnigmaMachine enigma;
    enigma.SetupEnigmaMachine(settings);
    string plainText = enigma.Transpose_CipherText(cipherText);
    cout << plainText;
    return 0;
}









