#pragma once
#include <Arduino.h>
#include <math.h>
#include <type_traits> // pour std::is_arithmetic

template <typename T>

class TabLastData
{
public:
    // Constructeur : taille + valeur initiale
    TabLastData(size_t capacity, const T &vdepart)
        : _capacite(capacity), _i(0)
    {
        _buffer = new T[_capacite];
        for (size_t i = 0; i < _capacite; i++)
        {
            _buffer[i] = vdepart;
        }
    }

    // Destructeur
    ~TabLastData()
    {
        delete[] _buffer;
    }

    // Ajout en fin
    bool push(const T &item)
    {
        _buffer[_i] = item;
        _i = (_i + 1) % _capacite;
        return true;
    }


    // Lecture du dernier entré
    bool dernierEntre(T &out) const
    {
        out = _buffer[(_i-1)%_capacite];
        return true;
    }

    // Réinitialise la file
    void remplir(const T &vdepart)
    {
        for (size_t i = 0; i < _capacite; i++)
        {
            _buffer[i] = vdepart;
        }
        _i=0;
    }

    //Max
    T max() const
    {
        T maxVal = _buffer[0];
        for (size_t i = 1; i < _capacite; i++)
        {
            if (_buffer[i] > maxVal)
                maxVal = _buffer[i];
        }
        return maxVal;
    }

    // Moyenne
    double moyenne() const
    {
        static_assert(std::is_arithmetic<T>::value, "moyenne() requiert un type numérique");
        double somme = 0;
        for (size_t i = 0; i < _capacite; i++)
        {
            somme += static_cast<double>(_buffer[i]);
        }
        return somme / static_cast<double>(_capacite);
    }

    // Écart entre le max et le min
    double ecart() const
    {
        static_assert(std::is_arithmetic<T>::value, "ecart() requiert un type numérique");
        T minVal = _buffer[0];
        T maxVal = _buffer[0];
        for (size_t i = 1; i < _capacite; i++)
        {
            if (_buffer[i] < minVal)
                minVal = _buffer[i];
            if (_buffer[i] > maxVal)
                maxVal = _buffer[i];
        }
        return static_cast<double>(maxVal) - static_cast<double>(minVal);
    }

    // Écart type
    double ecartType() const
    {
        static_assert(std::is_arithmetic<T>::value, "ecartType() requiert un type numérique");

        double moy = moyenne();
        double sommeCarres = 0;
        for (size_t i = 0; i < _capacite; i++)
        {
            double diff = static_cast<double>(_buffer[i]) - moy;
            sommeCarres += diff * diff;
        }
        return sqrt(sommeCarres / static_cast<double>(_capacite));
    }

    // Accesseurs d’état
    size_t getTailleMax() const
    {
        return _capacite;
    }

private:
    T *_buffer;
    size_t _capacite;
    size_t _i;
};

template <typename T>
class Queue
{
public:
    // Constructeur : taille + valeur initiale
    Queue(size_t capacity, const T &vdepart)
        : _capacite(capacity), _indDebut(0), _indFin(0), _taille(0)
    {
        _buffer = new T[_capacite];
        for (size_t i = 0; i < _capacite; i++)
        {
            _buffer[i] = vdepart;
        }
    }

    // Destructeur
    ~Queue()
    {
        delete[] _buffer;
    }

    // Ajout en fin
    bool push(const T &item)
    {
        if (estPleine())
            return false;
        _buffer[_indFin] = item;
        _indFin = (_indFin + 1) % _capacite;
        _taille++;
        return true;
    }

    // Retrait du premier élément
    bool pop(T &out)
    {
        if (estVide())
            return false;
        out = _buffer[_indDebut];
        _indDebut = (_indDebut + 1) % _capacite;
        _taille--;
        return true;
    }

    // Lecture du premier élément
    bool peek(T &out) const
    {
        if (estVide())
            return false;
        out = _buffer[_indDebut];
        return true;
    }

    // Réinitialise la file
    void remplir(const T &vdepart)
    {
        for (size_t i = 0; i < _capacite; i++)
        {
            _buffer[i] = vdepart;
        }
        _indDebut = 0;
        _indFin = 0;
        _taille = _capacite;
    }

    // --- Méthodes statistiques ---

    // Moyenne
    double moyenne() const
    {
        static_assert(std::is_arithmetic<T>::value, "moyenne() requiert un type numérique");
        if (estVide())
            return 0.0;
        double somme = 0;
        for (size_t i = 0; i < _capacite; i++)
        {
            somme += static_cast<double>(_buffer[i]);
        }
        return somme / static_cast<double>(_capacite);
    }

    // Écart entre le max et le min
    double ecart() const
    {
        static_assert(std::is_arithmetic<T>::value, "ecart() requiert un type numérique");
        if (estVide())
            return 0.0;
        T minVal = _buffer[0];
        T maxVal = _buffer[0];
        for (size_t i = 1; i < _capacite; i++)
        {
            if (_buffer[i] < minVal)
                minVal = _buffer[i];
            if (_buffer[i] > maxVal)
                maxVal = _buffer[i];
        }
        return static_cast<double>(maxVal) - static_cast<double>(minVal);
    }

    // Écart type
    double ecartType() const
    {
        static_assert(std::is_arithmetic<T>::value, "ecartType() requiert un type numérique");
        if (estVide())
            return 0.0;

        double moy = moyenne();
        double sommeCarres = 0;
        for (size_t i = 0; i < _capacite; i++)
        {
            double diff = static_cast<double>(_buffer[i]) - moy;
            sommeCarres += diff * diff;
        }
        return sqrt(sommeCarres / static_cast<double>(_capacite));
    }

    // Accesseurs d’état
    bool estVide() const {
        return _taille == 0; 
    }
    bool estPleine() const {
        return _taille == _capacite; 
    }
    size_t getTailleActu() const {
        return _taille; 
    }
    size_t getTailleMax() const {
        return _capacite; 
    }

private:
    T *_buffer;
    size_t _capacite;
    size_t _indDebut;
    size_t _indFin;
    size_t _taille;
};
