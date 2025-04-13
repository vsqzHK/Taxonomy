#include "clases.h"
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

// -----------------------------
// Implementación PreguntaNoEncontrada
PreguntaNoEncontrada::PreguntaNoEncontrada()
    : runtime_error("Pregunta no encontrada.") {}

// -----------------------------
// Implementación Pregunta
Pregunta::Pregunta(int id, string enunciado, string nivelTaxonomico, int tiempoEstimado, string tipoPregunta, int ano)
    : id(id), enunciado(enunciado), nivelTaxonomico(nivelTaxonomico), tiempoEstimado(tiempoEstimado), tipoPregunta(tipoPregunta), ano(ano) {}

void Pregunta::mostrarInfo() {
    cout << "ID: " << id << "\nEnunciado: " << enunciado
         << "\nNivel Taxonomico: " << nivelTaxonomico
         << "\nTipo de Pregunta: " << tipoPregunta
         << "\nAno: " << ano
         << "\nTiempo Estimado: " << tiempoEstimado << " min\n";
}

string Pregunta::getNivelTaxonomico() { return nivelTaxonomico; }
int Pregunta::getTiempoEstimado() { return tiempoEstimado; }
int Pregunta::getId() { return id; }
string Pregunta::getEnunciado() { return enunciado; }
string Pregunta::getTipoPregunta() { return tipoPregunta; }
int Pregunta::getAno() { return ano; }
void Pregunta::setEnunciado(string nuevo) { enunciado = nuevo; }

// -----------------------------
// Implementación Evaluacion
void Evaluacion::agregarPregunta(Pregunta p) {
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

void Evaluacion::eliminarPregunta(int id) {
    for (size_t i = 0; i < preguntas.size(); ++i) {
        if (preguntas[i].getId() == id) {
            preguntas.erase(preguntas.begin() + i);
            cout << "Pregunta eliminada correctamente.\n";
            return;
        }
    }
    throw PreguntaNoEncontrada();
}

void Evaluacion::actualizarPregunta(int id, string nuevoEnunciado) {
    for (auto &p : preguntas) {
        if (p.getId() == id) {
            p.setEnunciado(nuevoEnunciado);
            cout << "Pregunta actualizada correctamente.\n";
            return;
        }
    }
    throw PreguntaNoEncontrada();
}

void Evaluacion::buscarPorNivelTaxonomico(string nivel) {
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

void Evaluacion::mostrarEvaluacion() {
    if (preguntas.empty()) {
        cout << "No hay preguntas registradas.\n";
        return;
    }
    for (auto &p : preguntas) {
        p.mostrarInfo();
        cout << "----------------------\n";
    }
}

int Evaluacion::calcularTiempoTotal() {
    int total = 0;
    for (auto &p : preguntas) {
        total += p.getTiempoEstimado();
    }
    return total;
}

void Evaluacion::generarEvaluacionPorNivel(string nivel, int cantidad) {
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

// -----------------------------
// Implementación SistemaEvaluacion
SistemaEvaluacion::SistemaEvaluacion() {
    nivelesValidos = {"Recordar", "Entender", "Aplicar", "Analizar", "Evaluar", "Crear"};
}

bool SistemaEvaluacion::esNivelValido(string nivel) {
    return find(nivelesValidos.begin(), nivelesValidos.end(), nivel) != nivelesValidos.end();
}

string SistemaEvaluacion::limpiarInput(string prompt) {
    string entrada;
    cout << prompt;
    getline(cin, entrada);
    return entrada;
}

string SistemaEvaluacion::seleccionarTipoPregunta() {
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

void SistemaEvaluacion::mostrarMenu() {
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
