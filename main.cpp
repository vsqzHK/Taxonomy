#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Excepción personalizada
class PreguntaNoEncontrada : public runtime_error {
public:
    PreguntaNoEncontrada() : runtime_error("Pregunta no encontrada.") {}
};

class Pregunta {
private:
    int id;
    string enunciado;
    string nivelTaxonomico;
    int tiempoEstimado;

public:
    Pregunta(int id, string enunciado, string nivelTaxonomico, int tiempoEstimado)
        : id(id), enunciado(enunciado), nivelTaxonomico(nivelTaxonomico), tiempoEstimado(tiempoEstimado) {}

    void mostrarInfo() {
        cout << "ID: " << id << "\nEnunciado: " << enunciado
             << "\nNivel Taxonómico: " << nivelTaxonomico
             << "\nTiempo Estimado: " << tiempoEstimado << " min\n";
    }

    string getNivelTaxonomico() { return nivelTaxonomico; }
    int getTiempoEstimado() { return tiempoEstimado; }
    int getId() { return id; }
    void setEnunciado(string nuevo) { enunciado = nuevo; }
};

class Evaluacion {
private:
    vector<Pregunta> preguntas;

public:
    void agregarPregunta(Pregunta p) {
        for (auto &preg : preguntas) {
            if (preg.getId() == p.getId()) {
                throw invalid_argument("ID duplicado. Ya existe una pregunta con ese ID.");
            }
        }
        preguntas.push_back(p);
    }

    void eliminarPregunta(int id) {
        for (size_t i = 0; i < preguntas.size(); ++i) {
            if (preguntas[i].getId() == id) {
                preguntas.erase(preguntas.begin() + i);
                cout << "Pregunta eliminada correctamente.\n";
                return;
            }
        }
        throw PreguntaNoEncontrada();
    }

    void actualizarPregunta(int id, string nuevoEnunciado) {
        for (auto &p : preguntas) {
            if (p.getId() == id) {
                p.setEnunciado(nuevoEnunciado);
                cout << "Pregunta actualizada correctamente.\n";
                return;
            }
        }
        throw PreguntaNoEncontrada();
    }

    void buscarPorNivelTaxonomico(string nivel) {
        bool encontrada = false;
        for (auto &p : preguntas) {
            if (p.getNivelTaxonomico() == nivel) {
                p.mostrarInfo();
                encontrada = true;
            }
        }
        if (!encontrada)
            cout << "No se encontraron preguntas con ese nivel.\n";
    }

    void mostrarEvaluacion() {
        for (auto &p : preguntas) {
            p.mostrarInfo();
            cout << "----------------------\n";
        }
    }

    int calcularTiempoTotal() {
        int total = 0;
        for (auto &p : preguntas) {
            total += p.getTiempoEstimado();
        }
        return total;
    }

    void generarEvaluacionPorNivel(string nivel, int cantidad) {
        vector<Pregunta> seleccionadas;
        for (auto &p : preguntas) {
            if (p.getNivelTaxonomico() == nivel) {
                seleccionadas.push_back(p);
            }
        }
        if (seleccionadas.size() < cantidad) {
            throw runtime_error("No hay suficientes preguntas para ese nivel.");
        }
        cout << "\n--- Evaluación Generada ---\n";
        int total = 0;
        for (int i = 0; i < cantidad; ++i) {
            seleccionadas[i].mostrarInfo();
            cout << "----------------------\n";
            total += seleccionadas[i].getTiempoEstimado();
        }
        cout << "Tiempo total estimado: " << total << " min\n";
    }
};

class SistemaEvaluacion {
private:
    Evaluacion evaluacion;
    vector<string> nivelesValidos = {"Recordar", "Entender", "Aplicar", "Analizar", "Evaluar", "Crear"};

    bool esNivelValido(string nivel) {
        return find(nivelesValidos.begin(), nivelesValidos.end(), nivel) != nivelesValidos.end();
    }

public:
    void mostrarMenu() {
        int opcion;
        do {
            cout << "\n1. Agregar Pregunta\n2. Eliminar Pregunta\n3. Actualizar Pregunta\n4. Buscar por Nivel Taxonómico";
            cout << "\n5. Mostrar Evaluación\n6. Calcular Tiempo Total\n7. Generar Evaluación por Nivel y Cantidad\n8. Salir\n";
            cout << "Ingrese su opción: ";
            cin >> opcion;
            cin.ignore();

            try {
                if (opcion == 1) {
                    int id, tiempo;
                    string enunciado, nivel;
                    cout << "ID: "; cin >> id; cin.ignore();
                    cout << "Enunciado: "; getline(cin, enunciado);
                    cout << "Nivel Taxonómico: "; getline(cin, nivel);
                    if (!esNivelValido(nivel)) throw invalid_argument("Nivel taxonómico no válido.");
                    cout << "Tiempo estimado (min): "; cin >> tiempo;
                    evaluacion.agregarPregunta(Pregunta(id, enunciado, nivel, tiempo));
                }
                else if (opcion == 2) {
                    int id;
                    cout << "ID de la pregunta a eliminar: ";
                    cin >> id;
                    evaluacion.eliminarPregunta(id);
                }
                else if (opcion == 3) {
                    int id;
                    string nuevoEnunciado;
                    cout << "ID de la pregunta a actualizar: ";
                    cin >> id; cin.ignore();
                    cout << "Nuevo enunciado: "; getline(cin, nuevoEnunciado);
                    evaluacion.actualizarPregunta(id, nuevoEnunciado);
                }
                else if (opcion == 4) {
                    string nivel;
                    cout << "Ingrese el nivel taxonómico: ";
                    getline(cin, nivel);
                    evaluacion.buscarPorNivelTaxonomico(nivel);
                }
                else if (opcion == 5) {
                    evaluacion.mostrarEvaluacion();
                }
                else if (opcion == 6) {
                    cout << "Tiempo total estimado: " << evaluacion.calcularTiempoTotal() << " min\n";
                }
                else if (opcion == 7) {
                    string nivel;
                    int cantidad;
                    cout << "Nivel taxonómico: ";
                    getline(cin, nivel);
                    if (!esNivelValido(nivel)) throw invalid_argument("Nivel taxonómico no válido.");
                    cout << "Cantidad de preguntas: ";
                    cin >> cantidad;
                    evaluacion.generarEvaluacionPorNivel(nivel, cantidad);
                }
            } catch (const exception &e) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Error: " << e.what() << "\n";
            }
        } while (opcion != 8);
    }
};

int main() {
    SistemaEvaluacion sistema;
    sistema.mostrarMenu();
    return 0;
}