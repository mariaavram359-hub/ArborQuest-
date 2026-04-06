#include <iostream>
#include <utility>
#include <string>
// #include <vector>
// #include <array>
// #include "include/Example.h"

class Adresa {
private:
    std::string oras;
    std::string strada;
    int numar;

public:
    explicit Adresa(std::string oras_ = "Necunoscut", std::string strada_ = "Necunoscuta", int numar_ = 0)
        : oras{std::move(oras_)}, strada{std::move(strada_)}, numar{numar_} {}

    [[nodiscard]] const std::string& getOras() const { return oras; }
    [[nodiscard]] const std::string& getStrada() const { return strada; }
    [[nodiscard]] int getNumar() const { return numar; }

    friend std::ostream& operator<<(std::ostream& os, const Adresa& a) {
        os << "Str. " << a.strada << " nr. " << a.numar << ", " << a.oras;
        return os;
    }
};

class Angajat {
private:
    std::string nume;
    std::string functie;
    float salariu;

public:
    explicit Angajat(std::string nume_ = "Anonim", std::string functie_ = "Casier", float salariu_ = 2000.0f)
        : nume{std::move(nume_)}, functie{std::move(functie_)}, salariu{salariu_} {}

    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] const std::string& getFunctie() const { return functie; }
    [[nodiscard]] float getSalariu() const { return salariu; }

    void maresteSalariu(float procent) {
        salariu += salariu * (procent / 100.0f);
    }

    friend std::ostream& operator<<(std::ostream& os, const Angajat& a) {
        os << " - " << a.nume << " (" << a.functie << ") | Salariu: " << a.salariu << " RON";
        return os;
    }
};

class Autor{
private:
    std::string nume;
    int anNastere;

public:
    explicit Autor(std::string  nume_autor = "Anonim", int an_nastere_autor = 0)
        : nume{std::move(nume_autor)}, anNastere{an_nastere_autor} {
        // std::cout << "Constrcutor de intializare Autor (" << nume <<") \n";
    }

     const std::string& getNume() const {return nume; }
     // [[nodiscard]] int getAnNastere() const {return anNastere; }

    friend std::ostream& operator<<(std:: ostream& os, const Autor& a) {
        os << a.nume << " (an. " << a.anNastere << ")";
        return os;
    }
};

class Categorie {
    std::string nume;
    std::string nivelDificultate;

public:
    explicit Categorie(const std::string& nume_categorie = "General", const std::string& nivel_categorie = "Mediu")
        : nume{nume_categorie}, nivelDificultate{nivel_categorie} {
    }

    const std::string& getNume() const {return nume; }
    const std::string& getNivelDificultate() const {return nivelDificultate; }

    friend std::ostream& operator<<(std:: ostream& os, const Categorie& c) {
        os << "[" << c.nume << "| Dificultate: " << c.nivelDificultate << "]";
        return os;
    }
};

class Recenzie {
private:
    std::string numeAutor;
    std::string comentariu;
    int nota;

public:
    explicit Recenzie(std::string nume = "Anonim", std::string com = "Fara comentariu", int n = 5)
        : numeAutor{std::move(nume)}, comentariu{std::move(com)}, nota{n} {
        if (this->nota < 1) this->nota = 1;
        if (this->nota > 5) this->nota = 5;
    }

    [[nodiscard]] int getNota() const { return nota; }

    friend std::ostream& operator<<(std::ostream& os, const Recenzie& r) {
        os << "[" << r.nota << "/5] " << r.numeAutor << ": " << r.comentariu;
        return os;
    }
};

class Carte {
private:
    std::string titlu;
    Autor autor;
    Categorie categorie;
    float pret;
    int stoc;
    Recenzie recenzii[10];
    int numarRecenzii = 0;

public:
    explicit Carte(std::string  titlu_carte = "Fara titlu",
        Autor  autor_carte = Autor{},
        const Categorie& categorie_carte = Categorie{},
        float pret_carte = 0.0f,
        int stoc_carte = 0)
            :titlu{std::move(titlu_carte)}, autor {std::move(autor_carte)}, categorie{categorie_carte}, pret{pret_carte}, stoc{stoc_carte}{
        // std::cout << "Constrcutor de Carte (" << titlu << ") \n";
    }

    [[nodiscard]] const std::string& getTitlu() const {return titlu; }
    [[nodiscard]] const Autor& getAutor() const {return autor; }
    const Categorie& getCategorie() const { return categorie; }
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
    void adaugaRecenzie(const Recenzie& r) {
        if (numarRecenzii < 10) {
            recenzii[numarRecenzii] = r;
            numarRecenzii++;
        }
    }
    float calculeazaNotaMedie() const {
        if (numarRecenzii == 0) return 0.0f;
        float suma = 0.0f;
        for (int i = 0; i < numarRecenzii; ++i) {
            suma += static_cast<float>(recenzii[i].getNota());
        }
        return suma / static_cast<float>(numarRecenzii);
    }
    friend std::ostream& operator<<(std::ostream& os, const Carte& c) {
        os << "Cartea '" << c.titlu << "' " << c.categorie
           << " scrisa de " << c.autor.getNume()
           << " | Pret: " << c.pret << " RON | Stoc: " << c.stoc << " buc.";

        if (c.numarRecenzii > 0) {
            os << " | Nota Medie: " << c.calculeazaNotaMedie() << "/5 (" << c.numarRecenzii << " recenzii)";
        }
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
            std::cout << "[Raft] Adaugata cartea '" << c.getTitlu()
                      << "' " << c.getCategorie() << "\n";
        } else {
            std::cout << "[Eroare] Raftul este plin!\n";
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
            os << "Raftul este gol \n";
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
    explicit Client(std::string nume_client = "Necunoscut", std::string email_client = "-", float portofel_client = 0.0f) :
        nume{std::move(nume_client)}, email{std::move(email_client)}, portofel{portofel_client} {}

    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] float getPortofel() const { return portofel; }

    void plateste(float suma) {
        if (portofel >= suma) {
            portofel -= suma;
        }
    }

    [[nodiscard]] Recenzie scrieRecenzie(const std::string& mesaj, int nota) const {
        return Recenzie(nume, mesaj, nota);
    }

    friend std::istream& operator>>(std::istream& is, Client& c) {
        std::getline(is >> std::ws, c.nume);
        is >> c.email;
        is >> c.portofel;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Client& c) {
        os << c.nume << " (" << c.email << ") | Portofel: " << c.portofel << " Ron";
        return os;
    }
};

class Comanda{
private:
    static int contorComenzi;
    int idComanda;
    Client client;
    std::string titluriDorite[10];
    int numarCartiDorite;

public:
    explicit Comanda(const Client &client_curent = Client{})
        : client{client_curent}, numarCartiDorite{0} {
        contorComenzi++;
        idComanda = contorComenzi;
    }

    Client& getClient() {return client;}
    int getNumarCartiDorite() const {return numarCartiDorite;}
    const std::string& getTitluDorit(int index) const {return titluriDorite[index];}
    int getId() const{ return idComanda; }

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
    Adresa adresaLibrarie;
    Angajat angajati[10];
    int numarAngajati = 0;
    std::string numeLibrarie;
    float buget;
    Raft raftCarti;

public:
   explicit Bookstore(const std::string& nume_librarie = "Carturesti", float buget_librarie = 1000.0f)
       : numeLibrarie{nume_librarie}, buget{buget_librarie} {

   }

   //  void aprovizioneaza(const Carte& c) {
   //     raftCarti.adaugaCarte(c);
   // }

    Bookstore& operator+=(const Carte& c) {
       raftCarti.adaugaCarte(c);
       return *this;
   }

    void stabilesteLocatie(const Adresa& locatie) {
       adresaLibrarie = locatie;
   }

    void angajeaza(const Angajat& omNou) {
       if (numarAngajati < 10) {
           angajati[numarAngajati] = omNou;
           numarAngajati++;
       }
   }

    void afiseazaEchipa() const {
       std::cout << "\n=== ECHIPA LIBRARIEI ===\n";
       for (int i = 0; i < numarAngajati; ++i) {
           std::cout << angajati[i] << "\n";
       }
       std::cout << "========================\n";
   }

    void vindeCarte(const std::string& titluCautat, int cantitate_dorita) {
       Carte* carteGasita = raftCarti.gasesteCarte(titluCautat);
       if (carteGasita != nullptr ) {
           if (carteGasita->getStoc() >= cantitate_dorita) {
               carteGasita->scadeStoc(cantitate_dorita);
               float valoareVanzare = carteGasita->getPret() * cantitate_dorita;
               buget += valoareVanzare;
               std::cout << "[Vanzare] S-au vandut " << cantitate_dorita << "x '"
                         << titluCautat << "' " << carteGasita->getCategorie()
                         << " | Incasat " << valoareVanzare << " RON\n";
           }
           else {
               std::cout << "Stoc insuficient \n";
           }
       }
       else {
           std::cout << "Cartea nu a fost gasita pe raft \n";
       }
   }

    void primesteRecenzie(const std::string& titlu, const Recenzie& r) {
       Carte* carteGasita = raftCarti.gasesteCarte(titlu);
       if (carteGasita != nullptr) {
           carteGasita->adaugaRecenzie(r);
           std::cout << "[Sistem] A fost adaugata o recenzie de " << r.getNota()
                     << " stele pentru cartea '" << titlu << "'.\n";
       } else {
           std::cout << "[Sistem] Nu am putut adauga recenzia. Cartea '" << titlu << "' nu exista pe raft.\n";
       }
   }

       void proceseazaComanda(Comanda& cmd) {
       std::cout << "[NOUA COMANDA #" << cmd.getId() << "] Client: " << cmd.getClient().getNume()
                 << " | Buget initial: " << cmd.getClient().getPortofel() << " RON\n";
       std::cout << "Carti solicitate (" << cmd.getNumarCartiDorite() << "):\n";

       float totalDePlata = 0.0f;

       for (int i = 0; i < cmd.getNumarCartiDorite(); ++i) {
           const std::string& titlu = cmd.getTitluDorit(i);
           const Carte* carteGasita = raftCarti.gasesteCarte(titlu);

           if (carteGasita != nullptr && carteGasita->getStoc() > 0) {
               totalDePlata += carteGasita->getPret();
               // Aici printam cu tot cu categorie
               std::cout << "  + " << titlu << " " << carteGasita->getCategorie()
                         << " (" << carteGasita->getPret() << " RON)\n";
           } else {
               std::cout << "  - [Indisponibil] " << titlu << " (Lipsa stoc sau nu exista)\n";
           }
       }

       std::cout << "Total de plata calculat: " << totalDePlata << " RON\n";

       if (totalDePlata == 0.0f) {
           std::cout << "Tranzactie anulata. Nicio carte valabila in cos.\n\n";
           return;
       }

       if (cmd.getClient().getPortofel() >= totalDePlata) {
           cmd.getClient().plateste(totalDePlata);
           buget += totalDePlata;

           for (int i = 0; i < cmd.getNumarCartiDorite(); ++i) {
               Carte* carteGasita = raftCarti.gasesteCarte(cmd.getTitluDorit(i));
               if (carteGasita != nullptr && carteGasita->getStoc() > 0) {
                   carteGasita->scadeStoc(1);
                   carteGasita->adaugaRecenzie(cmd.getClient().scrieRecenzie("Achizitie excelenta, abia astept sa o citesc!", 5));
               }
           }
           std::cout << "[Rezultat] Tranzactie REUSITA! Portofel ramas: "
                     << cmd.getClient().getPortofel() << " RON.\n";
       } else {
           std::cout << "[Rezultat] Tranzactie ANULATA! Fonduri insuficiente.\n";
       }
   }

    void inregistreazaClient() {
       std::cout <<"\n Procesare Comenzi \n";
       Client clientCurent;
       while (std::cin >> clientCurent) {
           Comanda comandaCurenta(clientCurent);
           std::cin >> comandaCurenta;

           proceseazaComanda(comandaCurenta);
       }
   }

    void campanieReduceri(const std::string& numeAutor, float procent) {
       std::cout <<"\n Reducere de "<< procent << "% pentru autorul " << numeAutor << ".\n";
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

class BookstoreApp {
private:
    Categorie categorii[3] {
        Categorie("Clean Code", "Mediu"),
        Categorie("Software Engineering", "Avansat"),
        Categorie("Arhitectura Sistemelor", "Avansat")
    };

    Autor autori[5] {
        Autor("Robert Martin", 1952),
        Autor("Andrew Hunt", 1968 ),
        Autor("Martin Fowler", 1963),
        Autor("Martin Kleppmann", 1998),
        Autor("John Ousterhout", 1954)
    };

    Carte carti[5] {
        Carte("Clean Code", autori[0], categorii[0], 40.0f, 10),
        Carte("The Pragmatic Programmer", autori[1], categorii[1], 50.0f, 5),
        Carte("Rafactoring", autori[2], categorii[1], 60.0f, 2),
        Carte("Designing Data-Intensive Applications", autori[3], categorii[2], 45.0f, 8),
        Carte("A Philosophy of Software Design", autori[4], categorii[1], 60.0f, 10)
    };

    Bookstore magazin{"Coding Bookstore", 500.0f};

public:

    void init() {
        std::cout << "Pornire sistem gestiune\n";

        for (int i = 0; i < 5; ++i) {
            magazin += carti[i];
        }
        magazin.stabilesteLocatie(Adresa("Bucuresti", "Calea Victoriei", 45));
        magazin.angajeaza(Angajat("Popescu Andrei", "Manager", 5000.0f));
        magazin.angajeaza(Angajat("Ionescu Maria", "Casier", 3500.0f));
        magazin.angajeaza(Angajat("Vasile Ion", "Manipulant Marfa", 3000.0f));

        magazin.afiseazaEchipa();
        std::cout <<"\n STAREA INITIALA A MAGAZINULUI\n";
        std::cout << magazin;
        magazin.campanieReduceri("Andrew Hunt", 30.0f);
        std::cout <<"\nUn client random(fara cont) intra si cumpara o carte\n";
        magazin.vindeCarte("Clean Code", 1);
        magazin.primesteRecenzie("Clean Code", Recenzie("Alex", "O carte esentiala!", 5));
        magazin.primesteRecenzie("Clean Code", Recenzie("Mihai", "Cam grea, dar utila.", 4));

        // Adăugăm o recenzie pentru "Rafactoring"
        magazin.primesteRecenzie("Rafactoring", Recenzie("Andrei", "Mi-a schimbat modul de a gandi.", 5));

        // Cărțile fără recenzii vor afișa "[Fara recenzii]"
        magazin.inregistreazaClient();

        std::cout <<"\n STAREA LA FINALUL ZILEI\n";
        std::cout << magazin;
    }
};

int Comanda::contorComenzi = 0;

int main() {
    BookstoreApp app;
    app.init();

    return 0;
}
