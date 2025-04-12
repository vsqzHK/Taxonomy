#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <limits>

using namespace std;

// Excepcion personalizada lanzada si no se encuentra una pregunta por ID
class PreguntaNoEncontrada : public runtime_error {
public:
    PreguntaNoEncontrada() : runtime_error("Pregunta no encontrada.") {}
};

// Clase que representa una pregunta individual
class Pregunta {
private:
    int id;
    string enunciado;
    string nivelTaxonomico;
    int tiempoEstimado;
    string tipoPregunta;
    int ano;

public:
    // Constructor para inicializar una pregunta
    Pregunta(int id, string enunciado, string nivelTaxonomico, int tiempoEstimado, string tipoPregunta, int ano)
        : id(id), enunciado(enunciado), nivelTaxonomico(nivelTaxonomico), tiempoEstimado(tiempoEstimado), tipoPregunta(tipoPregunta), ano(ano) {}

    // Muestra la información de la pregunta
    void mostrarInfo() {
        cout << "ID: " << id << "\nEnunciado: " << enunciado
             << "\nNivel Taxonomico: " << nivelTaxonomico
             << "\nTipo de Pregunta: " << tipoPregunta
             << "\nAno: " << ano
             << "\nTiempo Estimado: " << tiempoEstimado << " min\n";
    }

    // Métodos de acceso
    string getNivelTaxonomico() { return nivelTaxonomico; }
    int getTiempoEstimado() { return tiempoEstimado; }
    int getId() { return id; }
    string getEnunciado() { return enunciado; }
    string getTipoPregunta() { return tipoPregunta; }
    int getAno() { return ano; }

    // Permite actualizar el enunciado
    void setEnunciado(string nuevo) { enunciado = nuevo; }
};

// Clase que gestiona el conjunto de preguntas de una evaluación
class Evaluacion {
private:
    vector<Pregunta> preguntas;

public:
    // Agrega una nueva pregunta validando ID duplicado y años consecutivos
    void agregarPregunta(Pregunta p) {
        for (auto &preg : preguntas) {
            if (preg.getId() == p.getId()) {
                throw invalid_argument("ID duplicado. Ya existe una pregunta con ese ID.");
            }
            if (preg.getEnunciado() == p.getEnunciado() && abs(preg.getAno() - p.getAno()) <= 1) {
                throw invalid_argument("Esta pregunta ya fue usada el ano anterior o siguiente.");
            }
        }
        preguntas.push_back(p);
    }

    // Elimina una pregunta por ID
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

    // Actualiza el enunciado de una pregunta
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

    // Busca y muestra preguntas por nivel taxonómico
    void buscarPorNivelTaxonomico(string nivel) {
        bool encontrada = false;
        for (auto &p : preguntas) {
            if (p.getNivelTaxonomico() == nivel) {
                p.mostrarInfo();
                cout << "----------------------\n";
                encontrada = true;
            }
        }
        if (!encontrada)
            cout << "No se encontraron preguntas con ese nivel.\n";
    }

    // Muestra todas las preguntas registradas
    void mostrarEvaluacion() {
        if (preguntas.empty()) {
            cout << "No hay preguntas registradas.\n";
            return;
        }
        for (auto &p : preguntas) {
            p.mostrarInfo();
            cout << "----------------------\n";
        }
    }

    // Calcula el tiempo total estimado de resolución
    int calcularTiempoTotal() {
        int total = 0;
        for (auto &p : preguntas) {
            total += p.getTiempoEstimado();
        }
        return total;
    }

    // Genera una evaluación con una cantidad específica de preguntas de un nivel
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
        cout << "\n--- Evaluacion Generada ---\n";
        int total = 0;
        for (int i = 0; i < cantidad; ++i) {
            seleccionadas[i].mostrarInfo();
            cout << "----------------------\n";
            total += seleccionadas[i].getTiempoEstimado();
        }
        cout << "Tiempo total estimado: " << total << " min\n";
    }
};

// Clase principal que administra la interacción del sistema
class SistemaEvaluacion {
private:
    Evaluacion evaluacion;
    vector<string> nivelesValidos = {"Recordar", "Entender", "Aplicar", "Analizar", "Evaluar", "Crear"};

    // Verifica si el nivel taxonómico ingresado es válido
    bool esNivelValido(string nivel) {
        return find(nivelesValidos.begin(), nivelesValidos.end(), nivel) != nivelesValidos.end();
    }

    // Limpia y solicita entrada con mensaje personalizado
    string limpiarInput(string prompt) {
        string entrada;
        cout << prompt;
        getline(cin, entrada);
        return entrada;
    }

    // Permite al usuario elegir el tipo de pregunta mediante opciones numeradas
    string seleccionarTipoPregunta() {
        int opcionTipo;
        do {
            cout << "Seleccione el tipo de pregunta:\n";
            cout << "1. Opcion multiple\n";
            cout << "2. Verdadero o falso\n";
            cout << "Ingrese su opcion (1-2): ";
            cin >> opcionTipo;
            cin.ignore();

            if (opcionTipo == 1) return "Opcion multiple";
            if (opcionTipo == 2) return "Verdadero o falso";

            cout << "Opcion invalida. Intente de nuevo.\n";
        } while (true);
    }

public:
    // Muestra el menú principal de operaciones del sistema
    void mostrarMenu() {
        int opcion = 0;
        do {
            cout << "\n1. Agregar Pregunta\n2. Eliminar Pregunta\n3. Actualizar Pregunta\n4. Buscar por Nivel Taxonomico";
            cout << "\n5. Mostrar Evaluacion\n6. Calcular Tiempo Total\n7. Generar Evaluacion por Nivel y Cantidad\n8. Salir\n";
            cout << "Ingrese su opcion: ";
            if (!(cin >> opcion)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida. Intente de nuevo.\n";
                continue;
            }
            cin.ignore();

            try {
                if (opcion == 1) {
                    // Ingreso de datos para una nueva pregunta
                    int id, tiempo, ano;
                    string enunciado, nivel, tipo;
                    cout << "ID: "; cin >> id; cin.ignore();
                    enunciado = limpiarInput("Enunciado: ");
                    nivel = limpiarInput("Nivel Taxonomico (Recordar, Entender, Aplicar, Analizar, Evaluar, Crear): ");
                    if (!esNivelValido(nivel)) throw invalid_argument("Nivel taxonomico no valido.");
                    tipo = seleccionarTipoPregunta();
                    cout << "Ano de la pregunta: "; cin >> ano;
                    if (ano < 1900 || ano > 2100) throw invalid_argument("Ano invalido.");
                    cout << "Tiempo estimado (min): "; cin >> tiempo;
                    cin.ignore();
                    evaluacion.agregarPregunta(Pregunta(id, enunciado, nivel, tiempo, tipo, ano));
                } else if (opcion == 2) {
                    int id;
                    cout << "ID de la pregunta a eliminar: ";
                    cin >> id; cin.ignore();
                    evaluacion.eliminarPregunta(id);
                } else if (opcion == 3) {
                    int id;
                    string nuevoEnunciado;
                    cout << "ID de la pregunta a actualizar: ";
                    cin >> id; cin.ignore();
                    nuevoEnunciado = limpiarInput("Nuevo enunciado: ");
                    evaluacion.actualizarPregunta(id, nuevoEnunciado);
                } else if (opcion == 4) {
                    string nivel = limpiarInput("Ingrese el nivel taxonomico: ");
                    evaluacion.buscarPorNivelTaxonomico(nivel);
                } else if (opcion == 5) {
                    evaluacion.mostrarEvaluacion();
                } else if (opcion == 6) {
                    cout << "Tiempo total estimado: " << evaluacion.calcularTiempoTotal() << " min\n";
                } else if (opcion == 7) {
                    string nivel = limpiarInput("Nivel taxonomico: ");
                    if (!esNivelValido(nivel)) throw invalid_argument("Nivel taxonomico no valido.");
                    int cantidad;
                    cout << "Cantidad de preguntas: ";
                    cin >> cantidad;
                    cin.ignore();
                    if (cantidad <= 0) throw invalid_argument("Cantidad invalida.");
                    evaluacion.generarEvaluacionPorNivel(nivel, cantidad);
                } else if (opcion != 8) {
                    cout << "Opcion no valida. Intente de nuevo.\n";
                }
            } catch (const exception &e) {
                cout << "Error: " << e.what() << "\n";
            }
        } while (opcion != 8);
        cout << "Saliendo del sistema. Gracias por usar la aplicacion.\n";
    }
};

// Punto de entrada del programa
int main() {
    SistemaEvaluacion sistema;
    sistema.mostrarMenu();
    return 0;
}
