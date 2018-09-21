#ifndef NOH_HPP
#define NOH_HPP

typedef int Dado;

class Noh {
    friend class Fila;
    public:
        Noh(Dado d);
    private:
        Noh* mProximo;
        Dado mDado;
};

#endif // NOH_HPP
