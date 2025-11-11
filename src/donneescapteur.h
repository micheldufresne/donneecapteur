#pragma once
#include <Arduino.h>
#include <math.h>
#include <type_traits> // pour std::is_arithmetic

template <typename T>
class Queue
{
public:
    // Constructeur : taille + valeur initiale
    Queue(size_t capacity, const T &vdepart)
        : _capacity(capacity), _front(0), _rear(0), _size(capacity)
    {
        _buffer = new T[_capacity];
        for (size_t i = 0; i < _capacity; i++)
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
        if (isFull())
            return false;
        _buffer[_rear] = item;
        _rear = (_rear + 1) % _capacity;
        _size++;
        return true;
    }

    // Retrait du premier élément
    bool pop(T &out)
    {
        if (isEmpty())
            return false;
        out = _buffer[_front];
        _front = (_front + 1) % _capacity;
        _size--;
        return true;
    }

    // Lecture du premier élément
    bool peek(T &out) const
    {
        if (isEmpty())
            return false;
        out = _buffer[_front];
        return true;
    }

    // Réinitialise la file
    void remplir(const T &vdepart)
    {
        for (size_t i = 0; i < _capacity; i++)
        {
            _buffer[i] = vdepart;
        }
        _front = 0;
        _rear = 0;
        _size = _capacity;
    }

    // --- Méthodes statistiques ---

    // Moyenne
    double moyenne() const
    {
        static_assert(std::is_arithmetic<T>::value, "moyenne() requiert un type numérique");
        if (isEmpty())
            return 0.0;
        double somme = 0;
        for (size_t i = 0; i < _capacity; i++)
        {
            somme += static_cast<double>(_buffer[i]);
        }
        return somme / static_cast<double>(_capacity);
    }

    // Écart entre le max et le min
    double ecart() const
    {
        static_assert(std::is_arithmetic<T>::value, "ecart() requiert un type numérique");
        if (isEmpty())
            return 0.0;
        T minVal = _buffer[0];
        T maxVal = _buffer[0];
        for (size_t i = 1; i < _capacity; i++)
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
        if (isEmpty())
            return 0.0;

        double moy = moyenne();
        double sommeCarres = 0;
        for (size_t i = 0; i < _capacity; i++)
        {
            double diff = static_cast<double>(_buffer[i]) - moy;
            sommeCarres += diff * diff;
        }
        return sqrt(sommeCarres / static_cast<double>(_capacity));
    }

    // Accesseurs d’état
    bool isEmpty() const {
        return _size == 0; 
    }
    bool isFull() const {
        return _size == _capacity; 
    }
    size_t size() const {
        return _size; 
    }
    size_t capacity() const {
        return _capacity; 
    }

private:
    T *_buffer;
    size_t _capacity;
    size_t _front;
    size_t _rear;
    size_t _size;
};
