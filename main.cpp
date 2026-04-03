#include <iostream>
#include <utility>
#include <string>
// #include <vector>
// #include <array>
// #include "include/Example.h"

class Autor{
private:
    std::string nume;
    int anNastere;

public:
    explicit Autor(std::string  nume_autor = "Anonim", int an_nastere_autor = 0)
        : nume{std::move(nume_autor)}, anNastere{an_nastere_autor} {
        // std::cout << "Constrcutor de intializare Autor (" << nume <<") \n";
    }

     [[nodiscard]] const std::string& getNume() const {return nume; }
     [[nodiscard]] int getAnNastere() const {return anNastere; }

    friend std::ostream& operator<<(std:: ostream& os, const Autor& a) {
        os << a.nume << " (an. " << a.anNastere << ")";
        return os;
    }
};

class Carte {
private:
    std::string titlu;
    Autor autor;
    float pret;
    int stoc;

public:
    explicit Carte(std::string  titlu_carte = "Fara titlu",
        Autor  autor_carte = Autor{},
        float pret_carte = 0.0f,
        int stoc_carte = 0)
            :titlu{std::move(titlu_carte)}, autor {std::move(autor_carte)}, pret{pret_carte}, stoc{stoc_carte}{
        // std::cout << "Constrcutor de Carte (" << titlu << ") \n";
    }


    [[nodiscard]] const std::string& getTitlu() const {return titlu; }
    [[nodiscard]] const Autor& getAutor() const {return autor; }
    [[nodiscard]] float getPret() const {return pret; }
    [[nodiscard]] int getStoc() const {return stoc; }

    void scadeStoc(int cantitate) {
        if (stoc >= cantitate) {
            stoc -= cantitate;
        }
    }

    //aplicam reducere(pentru cand voi implementa logica de la reducerea in functie de autor)
    void aplicaReducere(float procent) {
        pret -= (pret * procent / 100.0f);
    }

    friend std::ostream& operator<<(std:: ostream& os, const Carte& c) {
        os << "Cartea " << c.titlu << " scrisa de " << c.autor
           << " | Pret: " << c.pret << " RON | Stoc: " << c.stoc << " buc.";
        return os;
    }
};

class Raft {
private:
    Carte carti[100];
    int numarCarti;

public:
    explicit Raft() : numarCarti{0} {

    }

    ~Raft() = default;
    Raft(const Raft& alt_raft) : numarCarti{alt_raft.numarCarti} {
        for (int i = 0; i < numarCarti; ++i) {
            carti[i] = alt_raft.carti[i];
        }
    }

    Raft& operator=(const Raft& alt_raft) {
        if (this != &alt_raft) {
            numarCarti = alt_raft.numarCarti;
            for (int i = 0; i < numarCarti; ++i) {
                carti[i] = alt_raft.carti[i];
            }
        }
        return *this;
    }

    void adaugaCarte(const Carte& c) {
        if (numarCarti < 100) {
            carti[numarCarti] = c;
            numarCarti++;
        }
        else {
            std::cout << "Raftul este plin!";
        }
    }

    Carte* gasesteCarte(const std::string& titluCautat) {
        for (int i = 0; i < numarCarti; ++i) {
            if (carti[i].getTitlu() == titluCautat) {
                return &carti[i];
            }
        }
        return nullptr;
    }

    void aplicaReducereAutor(const std::string& numeAutor, float procent) {
        for (int i = 0; i < numarCarti; ++i) {
            if (carti[i].getAutor().getNume() == numeAutor) {
                carti[i].aplicaReducere(procent);
            }
        }
    }

    [[nodiscard]] float calculeazaValoare() const {
        float total = 0.0f;
        for (int i = 0; i < numarCarti; ++i) {
            total += (carti[i].getPret() * carti[i].getStoc());
        }
        return total;
    }

    friend std::ostream& operator<<(std::ostream& os, const Raft& r) {
        if (r.numarCarti == 0) {
            os << "Raftul este gol";
        }
        else {
            for (int i = 0; i < r.numarCarti; ++i) {
                os << " " << i + 1 <<". "<<r.carti[i] << "\n";
            }
        }
        return os;
    }
};

class Client {
    private:
    std::string nume;
    std::string email;
    float portofel;

public:
    explicit Client(const std::string& nume_client = "Necunoscut", std::string email_client = "-", float portofel_client = 0.0f) :
    nume{nume_client}, email{std::move(email_client)}, portofel{portofel_client}{}

    [[nodiscard]] std::string getNume() const {return nume;}
    [[nodiscard]] float getPortofel() const {return portofel;}

    void plateste(float suma) {
        if (portofel > suma) {
            portofel -= suma;
        }
    }

    friend std::istream& operator>>(std::istream& is, Client& c) {
        // std::cout<<"Introdu nume client: ";
        std::getline(is >> std::ws, c.nume);
        // std::cout<<"Introdu email: ";
        is >> c.email;
        // std::cout<<"Introdu buget client: ";
        is >> c.portofel;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Client& c) {
        os << c.nume << " " <<"(" << c.email <<") | Portofel: " << c.portofel << " Ron";
        return os;
    }

};

class Comanda{
private:
    Client client;
    std::string titluriDorite[10];
    int numarCartiDorite;

public:
    explicit Comanda(const Client &client_curent = Client{})
        : client{client_curent}, numarCartiDorite{0} {}

    Client& getClient() {return client;}
    [[nodiscard]] int getNumarCartiDorite() const {return numarCartiDorite;}
    [[nodiscard]] const std::string& getTitluDorit(int index) const {return titluriDorite[index];}

    friend std::istream& operator>>(std::istream& is, Comanda& cmd) {
        // std::cout <<"Numar carti dorite de client (Max 10): ";
        is >> cmd.numarCartiDorite;

        if (cmd.numarCartiDorite > 10) cmd.numarCartiDorite = 10;
        if (cmd.numarCartiDorite < 0) cmd.numarCartiDorite = 0;

        for (int i = 0; i < cmd.numarCartiDorite; ++i) {
            // std::cout << i + 1 << " : ";
            std::getline(is >> std::ws, cmd.titluriDorite[i]);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Comanda& cmd) {
        os << "\n Bon Comanda \n";
        os << cmd.client << "\n";
        os << "Carti dorite (" << cmd.numarCartiDorite << "): \n";
        for (int i = 0; i < cmd.numarCartiDorite; ++i) {
            os << "-" << cmd.titluriDorite[i] << "\n";
        }
        os << "\n";
        return os;
    }
};

class Bookstore {
private:
    std::string numeLibrarie;
    float buget;
    Raft raftCarti;

public:
   explicit Bookstore(const std::string& nume_librarie = "Carturesti", float buget_librarie = 1000.0f)
       : numeLibrarie{nume_librarie}, buget{buget_librarie} {

   }

    void aprovizioneaza(const Carte& c) {
       raftCarti.adaugaCarte(c);
   }

    void vindeCarte(const std::string& titluCautat, int cantitate_dorita) {
       Carte* carteGasita = raftCarti.gasesteCarte(titluCautat);
       if (carteGasita != nullptr ) {
           if (carteGasita->getStoc() >= cantitate_dorita) {
               carteGasita->scadeStoc(cantitate_dorita);
               float valoareVanzare = carteGasita->getPret() * cantitate_dorita;
               buget += valoareVanzare;
               std::cout << "S-au vandut" << cantitate_dorita << "x'"<< titluCautat<<"'<< | Incasat "<< valoareVanzare << "Ron \n" ;
           }
           else {
               std::cout << "Stoc insuficient";
           }
       }
       else {
           std::cout << "Cartea nu a fost gasita pe raft";
       }
   }

    void proceseazaComanda(Comanda& cmd) {
        std::cout << "\n";
        std::cout << "[NOUA COMANDA] Client: " << cmd.getClient().getNume()
                  << " | Buget initial: " << cmd.getClient().getPortofel() << " RON\n";
        std::cout << "Carti solicitate (" << cmd.getNumarCartiDorite() << "):\n";

        float totalDePlata = 0.0f;

        // 1. Trecem prin cărțile dorite și simulăm "scanarea" lor la casă
        for (int i = 0; i < cmd.getNumarCartiDorite(); ++i) {
            const std::string& titlu = cmd.getTitluDorit(i);
            Carte* carteGasita = raftCarti.gasesteCarte(titlu);

            if (carteGasita != nullptr && carteGasita->getStoc() > 0) {
                totalDePlata += carteGasita->getPret();
                std::cout << "  +" << titlu << " (" << carteGasita->getPret() << " RON)\n";
            } else {
                std::cout << "  - [Indisponibil] " << titlu << " (Lipsa stoc sau nu exista)\n";
            }
        }

        std::cout << "Total de plata calculat: " << totalDePlata << " RON\n";

        if (totalDePlata == 0.0f) {
            std::cout << "Tranzactie anulata. Nicio carte valabila in cos.\n";
            std::cout << "\n";
            return;
        }

        if (cmd.getClient().getPortofel() >= totalDePlata) {
            // Tranzacția reușește
            cmd.getClient().plateste(totalDePlata);
            buget += totalDePlata;

            for (int i = 0; i < cmd.getNumarCartiDorite(); ++i) {
                Carte* carteGasita = raftCarti.gasesteCarte(cmd.getTitluDorit(i));
                if (carteGasita != nullptr && carteGasita->getStoc() > 0) {
                    carteGasita->scadeStoc(1);
                }
            }
            std::cout << "Tranzactie REUSITA! Portofel ramas: "
                      << cmd.getClient().getPortofel() << " RON.\n";
        } else {
            // Tranzacția eșuează
            std::cout << "Tranzactie ANULATA! Fonduri insuficiente.\n";
        }
        std::cout << "\n";
    }

    void campanieReduceri(const std::string& numeAutor, float procent) {
       std::cout <<"Reducere de "<< procent << "% pentru autorul" << numeAutor << "\n";
       raftCarti.aplicaReducereAutor(numeAutor, procent);
   }

    friend std::ostream& operator<<(std::ostream& os, const Bookstore& b) {
       os << " BOOKSTORE: " << b.numeLibrarie << " | Buget Cash: " << b.buget << " RON\n";
       os << "Inventar curent pe raft:\n";
       os << b.raftCarti;
       os << "Valoare totala marfa pe raft: " << b.raftCarti.calculeazaValoare() << " RON\n";
       return os;
   }
};


    int main() {
        //voi adauga mai tarziu sa fie librarie it-stilor, cu carti legate de coding
    Bookstore magazin("Libraria X", 500.0f);
    Autor autor1("Mihai Eminescu", 1850);
    Autor autor2("J.K. Rowling", 1965);

    Carte carte1("Poezii", autor1, 40.0f, 10);
    Carte carte2("Harry Potter vol. 1", autor2, 50.0f, 5);
    Carte carte3("Harry Potter vol. 2", autor2, 60.0f, 2);

    magazin.aprovizioneaza(carte1);
    magazin.aprovizioneaza(carte2);
    magazin.aprovizioneaza(carte3);

    std::cout << "\nSTAREA INITIALA A MAGAZINULUI\n";
    std::cout << magazin;
    std::cout << "\nACTIVITATI DE DIMINEATA \n";
    magazin.campanieReduceri("J.K. Rowling", 10.0f);
    std::cout << "Un client achizitioneaza(nu are cont, este in trecere)\n";
    magazin.vindeCarte("Poezii", 1);

    std::cout << "Incep comenzile... \n";

    for (int i = 0; i < 3; ++i) {
        Client clientCurent;
        std::cin >> clientCurent;
        Comanda comandaCurenta(clientCurent);
        std::cin >> comandaCurenta;

        magazin.proceseazaComanda(comandaCurenta);
    }

    std::cout << "\nSTAREA LA FINALUL ZILEI\n";
    std::cout << magazin;

    return 0;
}
